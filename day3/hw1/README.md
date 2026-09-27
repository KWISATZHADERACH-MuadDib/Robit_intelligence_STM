# day3 hw1 - PWM 20kHz 생성 (duty 0/30/50/70%)

TIM1_CH1(PA8)로 20kHz PWM을 만들어 모터 드라이버의 PWM 핀에 연결하고, 스위치로 duty를 바꿈.

- PWM: 타이머 클럭 180MHz, PSC=17, ARR=499 -> 10MHz / 500 = 20kHz
- PB12->0%, PB13->30%, PB14->50%, PB15->70% (CCR1 = 0 / 150 / 250 / 350)
- 스위치를 아무것도 안 올리면 0% (정지)
- 스위치는 Active High, 입력은 내부 풀다운 사용
- PC8은 Motor_Direction_R 핀이라 GPIO 출력으로 HIGH 고정 (정방향)
- 입력 전압 Vin 12V

데모 영상 <br>
https://drive.google.com/file/d/1FCScaxYagVvbr9t5fhJUEn_TUTP_Bmlc/view?usp=drive_link