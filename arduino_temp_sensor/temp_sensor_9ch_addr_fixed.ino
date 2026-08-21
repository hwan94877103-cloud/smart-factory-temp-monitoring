/*
 * DS18B20 온도센서 9개 (기준1 + 구간2~7 + 최종8) - 주소 고정 방식
 * 
 * 배선:
 *   그룹A (디지털 2번 핀): 기준(1), 구간2, 구간3, 구간4
 *   그룹B (디지털 4번 핀): 구간5, 구간6, 구간7, 최종(8)
 *   각 그룹마다 4.7kΩ 풀업저항 1개씩, 총 2개
 *   최종(8번) 센서는 물리적으로 멀리 떨어져 있어 전선을 연장함
 *     (얇은선 AWG22 - 굵은선 AWG14 - 얇은선 AWG22 순서로 연장, 총 거리 3m 이내)
 * 
 * 핵심: DS18B20은 병렬 연결 시 index 순서가 매번 바뀔 수 있어
 *       고유 주소(Address)로 직접 지정하여 항상 같은 물리적 센서를 읽도록 고정함
 * 
 * 출력 형식: 한 줄에 기준,구간2~7,최종 순서로 콤마 구분 출력
 */

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_A 2   // 그룹A: 기준, 구간2, 구간3, 구간4
#define ONE_WIRE_BUS_B 4   // 그룹B: 구간5, 구간6, 구간7, 최종

OneWire oneWireA(ONE_WIRE_BUS_A);
OneWire oneWireB(ONE_WIRE_BUS_B);
DallasTemperature sensorsA(&oneWireA);
DallasTemperature sensorsB(&oneWireB);

// ===== 확인된 센서 주소 (실측값으로 교체 필요) =====
// 기준 센서(1번, 물 시작온도 33도 확인용) - 주소 미확인, 확인 후 아래에 입력
DeviceAddress addrRef    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

DeviceAddress addr2 = {0x28, 0xD9, 0x75, 0x6C, 0x00, 0x00, 0x00, 0x71}; // 구간2
DeviceAddress addr3 = {0x28, 0x3A, 0x6B, 0x6C, 0x00, 0x00, 0x00, 0xDF}; // 구간3
DeviceAddress addr4 = {0x28, 0xC4, 0x61, 0x6C, 0x00, 0x00, 0x00, 0x03}; // 구간4
DeviceAddress addr5 = {0x28, 0x1D, 0x5B, 0x6C, 0x00, 0x00, 0x00, 0x68}; // 구간5
DeviceAddress addr6 = {0x28, 0x80, 0x32, 0x6C, 0x00, 0x00, 0x00, 0x71}; // 구간6
DeviceAddress addr7 = {0x28, 0x60, 0x8A, 0x6C, 0x00, 0x00, 0x00, 0x29}; // 구간7

// 최종(8번) 센서 - 주소 미확인, 확인 후 아래에 입력
DeviceAddress addrFinal  = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void setup() {
  Serial.begin(9600);
  sensorsA.begin();
  sensorsB.begin();
}

void printTemp(DallasTemperature &sensors, DeviceAddress addr) {
  float tempC = sensors.getTempC(addr);
  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.print("ERR");
  } else {
    Serial.print(tempC);
  }
}

void loop() {
  sensorsA.requestTemperatures();
  sensorsB.requestTemperatures();

  printTemp(sensorsA, addrRef);   Serial.print(",");
  printTemp(sensorsA, addr2);     Serial.print(",");
  printTemp(sensorsA, addr3);     Serial.print(",");
  printTemp(sensorsA, addr4);     Serial.print(",");
  printTemp(sensorsB, addr5);     Serial.print(",");
  printTemp(sensorsB, addr6);     Serial.print(",");
  printTemp(sensorsB, addr7);     Serial.print(",");
  printTemp(sensorsB, addrFinal);
  Serial.println();

  delay(1000);
}
