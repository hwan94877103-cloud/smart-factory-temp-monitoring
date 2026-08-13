/*
 * ESP32 펠티어 6채널 PWM 제어 (실시간 채널별 % 입력)
 * 
 * 핀 배정:
 *   채널1 -> GPIO 32   채널4 -> GPIO 26
 *   채널2 -> GPIO 33   채널5 -> GPIO 27
 *   채널3 -> GPIO 25   채널6 -> GPIO 14
 * 
 * 배선 (채널당 동일 구조):
 *   파워서플라이(+) -> 퓨즈 -> MOSFET Vin(+)
 *   ESP32 GPIO      -> MOSFET 게이트 (PWM)
 *   MOSFET Vout(+)  -> 퓨즈 -> 펠티어(+)
 *   MOSFET GND(Vout-) -> 펠티어(-) 직결 (퓨즈 없음)
 *   파워서플라이(-), MOSFET GND, ESP32 GND -> 공통 GND
 * 
 * 사용법: 시리얼 모니터에 "채널번호,퍼센트" 입력 후 엔터
 *   예) 3,30  -> 3번 채널을 30%로 설정
 */

const int pwmPins[6] = {32, 33, 25, 26, 27, 14};
const int freq = 20000;     // 20kHz
const int resolution = 8;   // 0~255

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    ledcAttach(pwmPins[i], freq, resolution);
    ledcWrite(pwmPins[i], 0);
  }
  Serial.println("형식: 채널번호,퍼센트 (예: 3,30)");
}

void loop() {
  if (Serial.available()) {
    int channel = Serial.parseInt();
    Serial.read();  // 콤마 건너뛰기
    int percent = Serial.parseInt();
    if (Serial.read() == '\n') {
      channel = constrain(channel, 1, 6) - 1;
      percent = constrain(percent, 0, 100);
      int duty = percent * 255 / 100;
      ledcWrite(pwmPins[channel], duty);

      Serial.print("채널 ");
      Serial.print(channel + 1);
      Serial.print(": ");
      Serial.print(percent);
      Serial.println("%");
    }
  }
}
