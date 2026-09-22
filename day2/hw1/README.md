# day2 hw1 - Timer(TIM6) + GPIO

TIM6 인터럽트(100us 틱)로 PD2와 LED 4개를 제어.

- PD2: 0.5초마다 토글 (1초 주기)
- PB12→PB0, PB13→PB1, PB14→PB2, PB15→PB10: 누르는 동안만 0.5초 주기로 토글, 떼면 꺼짐
- 스위치/LED 모두 Active Low
- 시간 계산은 인터럽트 카운터 방식 (`TOGGLE_TICKS = 5000`)

과제 demo video <br>
https://drive.google.com/file/d/1LSQABdQ5X6ps-Sjk3O61xHAMw3PYy8qt/view?usp=drive_link
