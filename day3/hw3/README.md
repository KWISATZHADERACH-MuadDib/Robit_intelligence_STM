# day3 hw3 - Robstride RS00 액추에이터 CW/CCW 제어

CAN 통신으로 RS00 액추에이터를 속도 모드로 돌려서 5초 CW, 5초 CCW를 반복.

- CAN1 (PA11 RX / PA12 TX, 트랜시버 SN65HVD230), 1Mbps 확장 프레임
  - APB1 45MHz, Prescaler 5, BS1 6TQ, BS2 2TQ
- 29비트 ID = `통신타입 << 24 | 호스트ID(0xFD) << 8 | 모터ID`
- 시작 시 통신 타입 0(장치 ID 요청)을 ID 1~127에 보내서 모터 ID를 자동으로 찾음 (기본 0x7F)
- 매뉴얼 4.3.3 속도 모드 순서: stop → run_mode(0x7005)=2 -> enable -> limit_cur(0x7018) -> acc_rad(0x7022) → spd_ref(0x700A)
- 파라미터 쓰기는 통신 타입 18(0x12), Byte0 ~ 1 index, Byte4 ~ 7 값(float, little endian)
- 입력 전압 24V, 속도 관련 값은 데이터시트의 절반 미만으로 사용
  - 속도 5 rad/s (최대 33), 전류 제한 4A (최대 16), 가속도 20 rad/s²
- 방향 전환 주기는 `PHASE_MS` (5000ms)

데모 영상 :https://drive.google.com/file/d/1qcuA95KMeIQIooeY3gQ5UbCiOwf38QX0/view?usp=drive_link


