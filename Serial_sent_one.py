import serial
import time
ser = serial.Serial('/dev/ttyS0',9600)
try:
    while True:
        ser.write(b'1')
        time.sleep(0.1)
except KeyboardInterrupt:
    ser.close()
