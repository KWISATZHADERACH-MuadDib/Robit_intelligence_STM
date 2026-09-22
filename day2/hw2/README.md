# day2 hw2 - DYNAMIXEL(MX-106) 제어

USART3(LL 드라이버, 1Mbps, PC10 TX / PC5 RX)로 Protocol 2.0 Write
Instruction Packet을 만들어 모터에 각도 명령을 보냄.

- ID 14, 스위치 PB12→90도, PB13→180도, PB14→0도 (raw 1024/2048/0)
- 시작 시 Torque Enable(주소 64)을 켬, 이후 Goal Position(주소 116)에 write
- CRC-16(poly 0x8005) 테이블 직접 계산·검증 후 사용
- 스위치가 눌리는 순간(에지)에만 패킷 1회 전송

과제 demo video <br>
https://drive.google.com/file/d/1yZnSRdWW1HF6huTznkU5-1jeBmmewTUI/view?usp=drive_link