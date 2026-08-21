/*
 * DS18B20 온도센서 1개 단독 테스트 코드
 * 
 * 배선:
 *   VCC(빨강) -> 5V
 *   GND(검정) -> GND
 *   DATA(노랑) -> 디지털 2번 핀
 *   풀업저항 4.7kΩ (2번 핀 - 5V)
 */

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();

  Serial.print("발견된 센서 개수: ");
  Serial.println(sensors.getDeviceCount());
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.println("센서 연결 오류! 배선을 확인하세요.");
  } else {
    Serial.print("현재 온도: ");
    Serial.print(tempC);
    Serial.println(" C");
  }

  delay(1000);
}
