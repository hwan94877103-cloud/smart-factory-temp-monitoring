"""
아두이노에서 시리얼로 전송된 온도 데이터를 CSV 파일로 저장하는 스크립트

사용 전 준비:
    pip install pyserial

사용 방법:
    1. 아두이노에 temp_sensor_single.ino (또는 temp_sensor_8ch.ino) 업로드
    2. 아두이노 IDE의 시리얼 모니터는 반드시 닫을 것 (포트 충돌 방지)
    3. COM 포트 번호를 아래 PORT 변수에 맞게 수정
    4. python save_temp_to_csv.py 실행
"""

import serial
import csv
from datetime import datetime

PORT = 'COM5'      # 실제 연결된 COM 포트 번호로 수정
BAUD_RATE = 9600
FILENAME = "온도데이터.csv"

ser = serial.Serial(PORT, BAUD_RATE, timeout=1)

with open(FILENAME, mode='a', newline='', encoding='utf-8') as file:
    writer = csv.writer(file)
    writer.writerow(["timestamp", "온도(C)"])

print("데이터 수집 시작... (Ctrl+C로 종료)")

try:
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            try:
                temp = float(line)
                timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

                with open(FILENAME, mode='a', newline='', encoding='utf-8') as file:
                    writer = csv.writer(file)
                    writer.writerow([timestamp, temp])

                print(f"{timestamp} - {temp}C 저장됨")
            except ValueError:
                pass
except KeyboardInterrupt:
    print("\n데이터 수집 종료")
    ser.close()
