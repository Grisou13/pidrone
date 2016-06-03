#!/usr/bin/python3
import serial
#import re
import sys,os,time
import logging
from threading import Thread

#logging.basicConfig(level=logging.NOTSET,stream=sys.stdout)

if sys.platform == 'win32':
    USBDEVICE="COM7"
    ALTERNATIVES = ["COM1","COM2","COM3","COM4","COM5","COM6","COM7"]
else:
    USBDEVICE="/dev/ttyACM0"
    ALTERNATIVES=["/dev/ttyACM1","/dev/ttyUSB0","/dev/ttyUSB1","/dev/ttyAMA0"]
BAUDRATE = 9600

ser = serial.Serial(timeout=0) #,parity=serial.PARITY_EVEN, rtscts=1
ser.port=USBDEVICE
ser.baudrate = BAUDRATE
# from functools import wraps
# import errno
# import os
# import signal
#
# class TimeoutError(Exception):
#     pass
#
# def timeout(seconds=10, error_message=os.strerror(errno.ETIME)):
#     def decorator(func):
#         def _handle_timeout(signum, frame):
#             raise TimeoutError(error_message)
#
#         def wrapper(*args, **kwargs):
#             signal.signal(signal.SIGALRM, _handle_timeout)
#             signal.alarm(seconds)
#             try:
#                 result = func(*args, **kwargs)
#             finally:
#                 signal.alarm(0)
#             return result
#
#         return wraps(func)(wrapper)
#
#     return decorator

class Afficheur(Thread):
    """ lol docstring"""
    def __init__(self, serial):
        Thread.__init__(self)
        self.ser = serial
    def run(self):
        """ do something"""
        while True:
            logging.info(self.ser.readline())
def write_command(command):
    global ser
    logging.info("sending command ["+command+"] to arduino")
    #logging.info(ser.readline().decode())
    #return ""
    if not ser.isOpen():
        return None
    c=command+"\n"
    logging.info("Serial is {}".format(ser.isOpen()))
    ser.write(c.encode())#just write the data and return
    #return doRead()

def doRead():
    global ser
    r = ser.readline().decode().strip()
    logging.debug("Output of arduino : {}".format(r))
    return r

def stop():
    global ser
    if ser.isOpen():
        ser.close()

def start():
    global ser
    logging.info("starting arduino here")
    if ser.isOpen():
        ser.close()
    try:
        ser.open()
        time.sleep(3)
    except serial.serialutil.SerialException:
        if ser.isOpen() is not True:
            logging.info("serial not opened on default port "+USBDEVICE)
            logging.debug("trying others")
            for a in ALTERNATIVES:
                logging.info("trying on port {}\n".format(a))
                ser.port=a
                try:
                    ser.open()
                    time.sleep(5)
                    if(ser.isOpen()):
                        res = doRead()
                        if("Ready" in res):
                            break
                        else:
                            ser.close()
                            continue
                except serial.serialutil.SerialException:
                    continue
    logging.info("serial is "+ ("connected" if ser.isOpen() else "not connected")+"\n")
    if ser.isOpen():
        logging.info("on port : "+ser.port+"\n")
        if("Ready" not in doRead()):
            logging.info("closing the port, it doesn't have the Ready string")
            ser.close()
        else:
            logging.info("port is ok")
            write_command("start")
    return ser.isOpen()
if __name__ == '__main__':
    start()
    # if start():
    #     write_command("throttle 100")
    #     logging.info(ser.readline())
    # else:
    #     logging.info("something wnt wrong")
