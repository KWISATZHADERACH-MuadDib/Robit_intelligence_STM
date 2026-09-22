#ifndef __HW2_H
#define __HW2_H

#include "main.h"

#define HW2_MA_WINDOW  8   // 이동평균 윈도우 크기

// 이동평균 필터 상태 (원형 버퍼 + 합계를 유지해서 매 샘플마다 O(1)로 갱신)
typedef struct {
  uint32_t buf[HW2_MA_WINDOW];
  uint32_t sum;
  uint8_t  idx;
  uint8_t  count;
} MovAvg_t;

// Min-Max 정규화 상태 (지금까지 관측된 최소/최대값을 계속 갱신)
typedef struct {
  float min;
  float max;
} MinMax_t;

void hw2_init(void);
void hw2_loop(void);   // main의 while(1)에서 계속 호출

#endif /* __HW2_H */
