# 과제2 - ADC 정규화 & 필터링

## 1단계 - flag 없이 읽으면 생기는 문제

- 같은 샘플을 여러 번 읽음 (ADC는 10ms마다 갱신, 루프는 훨씬 빠름) → 필터가 둔하게 반응
- DMA가 갱신 중일 때 여러 채널을 연달아 읽으면 서로 다른 주기 값이 섞일 수 있음
- `adc1_buffer`가 volatile이 아니면 컴파일러가 읽기 자체를 최적화로 없앨 수 있음

## 2단계 - 정규화 + 이동평균

- Min-Max 정규화: `(x - min) / (max - min)`, min/max는 계속 갱신 (`normalize()`)
- 이동평균: 최근 8개 샘플 평균, 원형 버퍼 + `sum` 유지로 O(1) 갱신 (`moving_average()`)
- `hw2_raw`/`hw2_filt`를 Live Expressions로 비교 → 필터값이 더 부드럽게 움직임

## 3단계 - 4채널로 확장하는 방법

- `moving_average()`, `normalize()`는 채널과 무관한 함수라 그대로 재사용
- `process_channel(ch)`로 감싸고, `MovAvg_t`/`MinMax_t`를 채널별로 배열(`[4]`)로 분리
- 출력 변수(`hw2_raw` 등)도 `[4]` 배열로 바꾸고 `hw2_loop()`에서 4번 반복 호출

## 4단계 - flag 없이 buffer 인덱스 변화 감지

DMA 남은 전송 개수(`__HAL_DMA_GET_COUNTER`)는 4→3→2→1→4로 줄어든다.
`(4 - NDTR)`이 현재 쓰는 인덱스이므로, 이게 마지막에서 0으로 돌아오는
순간을 "한 세트 완료"로 판단한다.

```c
uint32_t idx = (4 - __HAL_DMA_GET_COUNTER(&hdma_adc1)) % 4;
if (idx == 0 && idx != last_idx) {
  // 한 세트 완료 -> 여기서 4채널 처리
}
last_idx = idx;
```

과제2 demo video <br>
https://drive.google.com/file/d/1kpBQXR2esqWVyP7V5yXf5JgojZcWc6F3/view?usp=drive_link <br>
https://drive.google.com/file/d/1k75Fe8PthWvWqhogl1tQTvhlz40UCKbo/view?usp=drive_link