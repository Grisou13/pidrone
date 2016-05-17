#!/usr/bin/python3
#from logs import log
import logging
import sys
from arduino import write_command
from helpers import flatten
#logging.basicConfig(level=logging.NOTSET,stream=sys.stdout)
status = [
"init","ready","fyling","error"
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
    return "ok"
def stop(command):
    return "ok"

commands = {"get_status":get_status,"start":start,"stop":stop,'tilt':write_command,'move':write_command,'rotate':write_command,"hover":write_command}
print("available commands : ",commands)
print("current status : ",get_status())

def handle_command(cmd):
    global commands
    global command_history
    logging.info("dispatching command {}".format(cmd))
    command_history.append(cmd)
    cmdName = cmd.split()[0]
    if cmdName in commands.keys():
        if len(command_history) < 1 and get_status() is not "error":
            set_status(get_status("ready"))
        res = commands[cmdName](cmd)
        if "error" in res:
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
    print("testing command 'get_status' : ",handle_command("get_status"))
    print("testing command 'start' : ",handle_command("start"))
    print("testing command 'move' : ",handle_command("move up 100"))
