import serial

# シリアルポートの設定
ser = serial.Serial('/dev/ttyS0', 9600)  # ポートとボーレートを適切に設定してください

try:
    # "1" を送信
    ser.write(b'1')
    print("送信: 1")
    
    # 必要に応じて受信処理を追加できます
    # received_data = ser.read(1)
    # print(f"受信: {received_data.decode('utf-8')}")

except Exception as e:
    print(f"エラー: {str(e)}")

finally:
    ser.close()  # シリアルポートを閉じる
