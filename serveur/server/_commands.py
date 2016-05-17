#!/usr/bin/python3
import logging
logging.basicConfig(filename='./logs/commands.log',level=logging.INFO)
logging.info("starting server")
from socket import *

from threading import Thread

import os,signal,sys


running = True
host = ''
port = 53820
commands=[]


class ConnexionHandler(Thread):
    def __init__(self,socket, clientaddr):
        Thread.__init__(self)
        #logging.info("starting handling thread")
        logging.info("Accepted connection from: ", clientaddr)
        self.sock = socket
        self.addr = clientaddr
    def run():
        global running
        socket = self.sock
        logging.log(socket)
        while running:
            logging.info("running for client ",self.addr)
            data = socket.recv(2048)
            if not data:
                break
            else:
                msg = "You sent me: {} \n".format(data.decode())
                logging.info("sending back : \n {}".format(msg.encode()))
                logging.debug("received message from client: {}",data.decode())
                socket.send(msg.encode())
        socket.close()

def run():
    global host
    global port
    global running
    buf = 1024
    addr = (host, port)
    serversocket = socket(AF_INET, SOCK_STREAM)
    serversocket.bind(addr)
    serversocket.listen()#allow only 1 connection
    handlers = []
    try:
        logging.info("Server is listening for connections on port %s \n",port)
        while running:
            clientsocket, clientaddr = serversocket.accept()
            c = ConnexionHandler(clientsocket, clientaddr)
            c.start()
            logging.info(c)
            handlers.append(c)

    except KeyboardInterrupt:
        running=False
        logging.info("closing server")
        for h in handlers:
            h.join()
            logging.info("closing thread ",h)
        serversocket.close()

if __name__ == '__main__':

    run()
