import serial

serialport = "COM7"
ser = serial.Serial(serialport, 9600)
print(serialport)
while(1):
    print(ser.readline())
