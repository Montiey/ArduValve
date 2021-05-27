import serial
import sys
import random
import time


serialPort = '/dev/cu.usbmodem14201'
#serialPort = '/dev/cu.usbserial-1420'

ser = serial.Serial(
        port=serialPort,
        baudrate=115200
)

ser.isOpen()


while not ser.inWaiting():
    print('Reset now...')
    time.sleep(1)
    pass


def allOn():
    for i in range(0, 12):
        out = f'P{i}S1\n'
        ser.write(out.encode())

def allOff():
    for i in range(0, 12):
        out = f'P{i}S0\n'
        ser.write(out.encode())




while True:
    for d in [.5, .05, .01, .001]:
        for s in [1, 0]:
            for i in range(0, 12):
                out = f'P{i}S{s}\n'
                ser.write(out.encode())

                time.sleep(d)

                while ser.inWaiting():
                    sys.stdout.write(ser.read(1).decode('UTF-8'))


            time.sleep(1)

