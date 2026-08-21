"""
DS18B20 온도센서 9개(기준1 + 구간2~7 + 최종8) - 주소 고정 방식 CSV 저장 스크립트
temp_sensor_9ch_addr_fixed.ino 와 함께 사용

사용 전 준비:
    pip install pyserial

사용 방법:
    1. 아두이노에 temp_sensor_9ch_addr_fixed.ino 업로드 (센서 주소 확인 후 코드에 입력 완료 상태)
    2. 아두이노 IDE의 시리얼 모니터는 반드시 닫을 것 (포트 충돌 방지)
    3. COM 포트 번호를 아래 PORT 변수에 맞게 수정
    4. python save_temp_9ch_to_csv.py 실행
"""

import serial
import csv
from datetime import datetime

PORT = 'COM5'      # 실제 연결된 COM 포트 번호로 수정
BAUD_RATE = 9600
FILENAME = "온도데이터_9채널.csv"

ser = serial.Serial(PORT, BAUD_RATE, timeout=1)

with open(FILENAME, mode='a', newline='', encoding='utf-8') as file:
    writer = csv.writer(file)
    writer.writerow(["timestamp", "기준(1번,33도확인)", "구간2", "구간3",
                      "구간4", "구간5", "구간6", "구간7", "최종(8번)"])

print("데이터 수집 시작... (Ctrl+C로 종료)")

try:
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            values = line.split(",")
            if len(values) == 8:
                timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

                with open(FILENAME, mode='a', newline='', encoding='utf-8') as file:
                    writer = csv.writer(file)
                    writer.writerow([timestamp] + values)

                print(f"{timestamp} - {values} 저장됨")
except KeyboardInterrupt:
    print("\n데이터 수집 종료")
    ser.close()
