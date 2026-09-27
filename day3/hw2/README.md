# day3 hw2 - double 변수 값으로 모터 제어

`volatile double motor_value` (범위 -1 ~ 1) 값에 따라 모터의 방향과 duty를 정함.

- 부호가 방향: 음수 -> CCW (PC8 LOW), 양수 -> CW (PC8 HIGH)
- 절댓값이 duty: `|motor_value| * 350` -> 최대 70%
- -1 -> CCW 70%, 1 -> CW 70%, 0 -> 정지
- 범위를 벗어난 값은 -1 ~ 1로 잘라서 사용
- PWM은 TIM1_CH1(PA8) 20kHz, 방향은 PC8 (day3 hw1과 동일한 배선)

값은 디버그 모드에서 Live Expressions에 `motor_value`를 추가한 뒤 직접
입력해서 바꾼다. 소수점이 안 보이면 Live Expressions에서 값 우클릭 ->
Number Format을 바꿔야 한다.

데모 영상 <br>
https://drive.google.com/file/d/16S57asj5SfuxJjbOoXZlH3D4RlH4BMtM/view?usp=drive_link