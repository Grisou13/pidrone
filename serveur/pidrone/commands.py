#!/usr/bin/python3
#from logs import log
import logging
import sys
import time
from .arduino import write_command,start as _start, stop as _stop
from .helpers import flatten
#logging.basicConfig(level=logging.NOTSET,stream=sys.stdout)
status = [
"init","ready","landing","error"
]
current_status = 0
command_history = []
def get_status_index(*args):
    return current_status

def get_status(*args):
    if len(args)>0:
        index = args[0]
        if index in status:
            return status[status.index(index)]
        elif isinstance(index,int) and index < len(status):
            return status[index]
    return status[current_status]
def set_status(index):
    global current_status
    global status
    #log(status.index(index))
    try:
        if status[index] is not None:
            current_status = index
    except TypeError as e:
        if status.index(index) is not -1:
            current_status = status.index(index)

def start(command):
    if get_status() is get_status("init"):
        logging.debug("available commands : {}".format(commands.keys()))
        logging.debug("current status : {}".format(get_status()))
        logging.info("starting the arduino")
        _start()
        write_command("throttle 5")
    set_status("ready")
    return "ready"
def stop(command):
    set_status("landing")
    write_command("land")
    time.sleep(5)
    #write_command("throttle 0")#set the throttle to 0 after land
    _stop()
    set_status("ready") #normally this should be triggered after landing procedure
    return "stopped"

commands = {"get_status":get_status,"start":start,"stop":stop,'tilt':write_command,'move':write_command,'rotate':write_command,"hover":write_command,"throttle":write_command,"land":write_command}


def handle_command(cmd):
    global commands
    global command_history
    command_history.append(cmd)
    cmdName = cmd.split()[0]
    if cmdName in commands.keys():
        res = commands[cmdName](cmd)
        if res is not None and "error" in res:
            set_status("error")
        return res
    return "command not found"
if __name__ == '__main__':

    set_status(0)
    print("status : ",get_status())
    #set_status("ready")
    print("status : ",get_status())
    set_status("fyling")
    print("status : ",get_status())
    start()
    #print("testing command 'get_status' : ",handle_command("get_status"))
    #print("testing command 'start' : ",handle_command("start"))
    #print("testing command 'move' : ",handle_command("move up 100"))
