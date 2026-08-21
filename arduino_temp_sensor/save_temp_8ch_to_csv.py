"""
아두이노에서 시리얼로 전송된 온도센서 8개 데이터를 CSV 파일로 저장하는 스크립트
(temp_sensor_8ch.ino와 함께 사용)

사용 전 준비:
    pip install pyserial

사용 방법:
    1. 아두이노에 temp_sensor_8ch.ino 업로드
    2. 아두이노 IDE의 시리얼 모니터는 반드시 닫을 것
    3. COM 포트 번호를 아래 PORT 변수에 맞게 수정
    4. python save_temp_8ch_to_csv.py 실행
"""

import serial
import csv
from datetime import datetime

PORT = 'COM5'      # 실제 연결된 COM 포트 번호로 수정
BAUD_RATE = 9600
FILENAME = "온도데이터_8개.csv"

ser = serial.Serial(PORT, BAUD_RATE, timeout=1)

with open(FILENAME, mode='a', newline='', encoding='utf-8') as file:
    writer = csv.writer(file)
    writer.writerow(["timestamp", "센서1", "센서2", "센서3", "센서4",
                      "센서5", "센서6", "센서7", "센서8"])

print("데이터 수집 시작... (Ctrl+C로 종료)")

try:
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            try:
                values = line.split(",")
                if len(values) == 8:
                    temps = [float(v) for v in values]
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

                    with open(FILENAME, mode='a', newline='', encoding='utf-8') as file:
                        writer = csv.writer(file)
                        writer.writerow([timestamp] + temps)

                    print(f"{timestamp} - {temps} 저장됨")
            except ValueError:
                pass
except KeyboardInterrupt:
    print("\n데이터 수집 종료")
    ser.close()
