#include "hw2.h"

extern uint32_t adc1_buffer[4];             // DMA가 계속 갱신하는 ADC 버퍼 (main.c)
extern volatile uint8_t adc_updated_flag;   // ADC 변환 완료 콜백이 세우는 flag (main.c)

/* Live Expressions에서 확인할 값: PA0(IN0) 채널 하나의 원본/필터/정규화 결과 */
volatile uint32_t hw2_raw          = 0;   // 원본값 (0 ~ 4095)
volatile float    hw2_filt         = 0;   // 이동평균 필터값
volatile float    hw2_norm_raw     = 0;   // 원본값 정규화 (0.0 ~ 1.0)
volatile float    hw2_norm_filt    = 0;   // 필터값 정규화 (0.0 ~ 1.0)
volatile uint32_t hw2_update_count = 0;   // 새 샘플이 처리된 횟수

static MovAvg_t ma;
static MinMax_t mm_raw;
static MinMax_t mm_filt;

// buffer는 DMA가 계속 덮어쓰므로 매번 메모리에서 다시 읽도록 volatile로 접근
static inline uint32_t adc_read_ch0(void)
{
  return *(volatile uint32_t *)&adc1_buffer[0];
}

// 최근 HW2_MA_WINDOW개 샘플의 평균. sum을 계속 유지해서 매번 전체를 다시 더하지 않음
static float moving_average(MovAvg_t *f, uint32_t x)
{
  f->sum -= f->buf[f->idx];   // 창(window)에서 밀려나는 가장 오래된 값 제거
  f->buf[f->idx] = x;         // 새 값 저장
  f->sum += x;
  f->idx = (f->idx + 1) % HW2_MA_WINDOW;
  if (f->count < HW2_MA_WINDOW) f->count++;   // 초기에는 채워진 개수만큼만 평균
  return (float)f->sum / (float)f->count;
}

// Min-Max 정규화: (x - min) / (max - min). 지금까지 관측된 min/max를 계속 갱신
static float normalize(MinMax_t *m, float x)
{
  if (x < m->min) m->min = x;
  if (x > m->max) m->max = x;
  float range = m->max - m->min;
  if (range < 1.0f) return 0.0f;   // 아직 변화폭이 없을 때 0으로 나누는 것을 방지
  return (x - m->min) / range;
}

void hw2_init(void)
{
  ma = (MovAvg_t){0};
  // 첫 샘플이 들어오자마자 min/max가 그 값으로 갱신되도록 반대 방향으로 초기화
  mm_raw  = (MinMax_t){4095.0f, 0.0f};
  mm_filt = (MinMax_t){4095.0f, 0.0f};
}

void hw2_loop(void)
{
  // ADC 변환 완료 콜백이 flag를 세운 시점에만 처리한다.
  // 그래야 같은 샘플을 중복으로 처리하거나 DMA가 buffer를 갱신하는 도중의
  // 값을 읽는 것을 피할 수 있다.
  if (!adc_updated_flag) return;
  adc_updated_flag = 0;

  uint32_t raw  = adc_read_ch0();
  float    filt = moving_average(&ma, raw);

  hw2_raw       = raw;
  hw2_filt      = filt;
  hw2_norm_raw  = normalize(&mm_raw, (float)raw);
  hw2_norm_filt = normalize(&mm_filt, filt);
  hw2_update_count++;
}
