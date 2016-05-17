#!/usr/bin/python3
import serial
#import re
import sys,os,time
import logging
logging.basicConfig(level=logging.NOTSET,stream=sys.stdout)

if sys.platform == 'win32':
    USBDEVICE="COM3"
    ALTERNATIVES = ["COM4","COM5","COM6","COM7"]
else:
    USBDEVICE="/dev/ttyACME0"
    ALTERNATIVES=["/dev/ttyACME1","/dev/ttyUSB0","/dev/ttyUSB1"]
BAUDRATE = 9600

def write_command(command):
    global ser
    logging.info("sending command "+command+" to arduino")
    return ""
    if ser.is_open is not True:
        return False
    c=command+"\n"
    ser.write(c.encode())
    return doRead()

def doRead(tout = 1):
    global ser
    #matcher = re.compile(term)    #gives you the ability to search for anything
    tic     = time.clock()
    buff    = ser.read(128)
    # you can use if not ('\n' in buff) too if you don't like re
    while ((time.clock() - tic) < tout) and (not '\n' in buff.decode()):
       buff += ser.read(128)
    return buff



ser = serial.Serial(timeout=1,parity=serial.PARITY_EVEN, rtscts=1)
ser.port=USBDEVICE
ser.baudrate = BAUDRATE
try:
    ser.open()
except serial.serialutil.SerialException:
    if ser.is_open is not True:
        logging.info("serial not opened on default port "+USBDEVICE)
        logging.info("\ntrying others\n")
        for a in ALTERNATIVES:
            logging.info("trying on port {}\n".format(a))
            ser.port=a
            try:
                ser.open()
                if(ser.is_open):
                    res = doRead()
                    if(res == "Ready"):
                        break
                    else:
                        ser.close()
                        continue
            except serial.serialutil.SerialException:
                continue


logging.info("serial is "+ ("connected" if ser.is_open else "not connected")+"\n")
if ser.is_open:

    logging.info("on port : "+ser.port+"\n")
if __name__ == '__main__':
    res = write_command("move up 100")
    print(res)
