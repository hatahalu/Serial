import serial
import RPi.GPIO as GPIO
import time

TX_PIN = 14

ser = serial.Serial('/dev/serial0',9600)

ser.timeout = 1

GPIO.setmode(GPIO.BCM)
GPIO.setup(TX_PIN,GPIO.OUT)

try:
    while True:
        ser.write("1")
        time.sleep(1)
except KeyboardInterrupt:
    GPIO.cleanup()
    ser.close()