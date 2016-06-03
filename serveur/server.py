#!/usr/bin/python3
# This is server.py file
import sys

sys.dont_write_bytecode = True

from pidrone.helpers import *
from pidrone.bluetooth import run as startBluetoothServer
from pidrone.tcp_server import run as tcpServer,stop as stopTcpServer
from pidrone.streaming import run as streamingServer, stop as stopStreamingServer
from pidrone.logs import log



def set_exit_handler(func):
    signal.signal(signal.SIGTERM, func)


def tearDown(sig, func=None):
    log.debug("exit handler triggered")
    stopTcpServer()
    stopHostapd()
    stopStreamingServer()
    sys.exit(0)

def run():
    log.info("starting it all up")
    set_exit_handler(tearDown)
    startBluetoothServer()
    startHostapd()
    startStreaming()
    startTcpServer()

if __name__ == "__main__":
    run()
    set_exit_handler(tearDown)
