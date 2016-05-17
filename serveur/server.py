#!/usr/bin/python3
# This is server.py file

from pidrone.helpers import *
from pidrone.bluetooth import run as BluetoothServer
from pidrone.commands import run as MainServer
from pidrone.hostapd_management import *
from pidrone.streaming_management import *
from pidrone.logs import log


from .tcp_server import run as tcpServer,stop as stopTcpServer
from .bluetooth import run as startBluetoothServer
from .streaming import run as streamingServer, stop as stopStreamingServer

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
