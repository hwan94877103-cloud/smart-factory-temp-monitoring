/*
 * DS18B20 온도센서 8개 (4개씩 2그룹) 제어 코드
 * 
 * 배선:
 *   그룹1 (센서 1~4): 디지털 2번 핀, 풀업저항 4.7kΩ (2번핀 - 5V)
 *   그룹2 (센서 5~8): 디지털 4번 핀, 풀업저항 4.7kΩ (4번핀 - 5V)
 *   모든 센서 VCC -> 5V 공통 / GND -> GND 공통
 * 
 * 출력 형식: 한 줄에 센서 1~8 온도값을 콤마로 구분하여 출력
 * 예) 24.50,25.12,24.87,26.30,25.00,24.75,25.44,24.90
 */

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_1 2   // 그룹1 (센서 1~4)
#define ONE_WIRE_BUS_2 4   // 그룹2 (센서 5~8)

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);

int count1 = 0;
int count2 = 0;

void setup() {
  Serial.begin(9600);

  sensors1.begin();
  sensors2.begin();

  count1 = sensors1.getDeviceCount();
  count2 = sensors2.getDeviceCount();
}

void loop() {
  sensors1.requestTemperatures();
  sensors2.requestTemperatures();

  // 그룹1 (센서 1~4) 출력
  for (int i = 0; i < count1; i++) {
    float t = sensors1.getTempCByIndex(i);
    Serial.print(t);
    Serial.print(",");
  }

  // 그룹2 (센서 5~8) 출력
  for (int i = 0; i < count2; i++) {
    float t = sensors2.getTempCByIndex(i);
    Serial.print(t);
    if (i < count2 - 1) Serial.print(",");
  }

  Serial.println();

  delay(1000);
}
