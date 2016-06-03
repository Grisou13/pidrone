#!/usr/bin/python3
import os,signal,sys
import logging
from socket import *
#maybe detect os, cause this won't work on windows
logging.basicConfig(filename='/var/log/tcp_server.log',level=logging.NOTSET,stream=sys.stdout)
#logging.basicConfig(level=logging.NOTSET,stream=sys.stdout)
#logging.info("starting server")

try:
    import _thread as thread
except ImportError:
    import thread


from .commands import handle_command

running = True

def handler(clientsocket, clientaddr):
    logging.info("Accepted connection from: {}".format(clientaddr))
    global running
    while running:
        data = clientsocket.recv(1024)
        #logging.info("data : {}".format(data.decode()))
        if not data:
            break
        else:
            d = data.decode()
            #logging.info("data : |{}|".format(d))
            #cmd = d.split(" ")
            #logging.info(cmd)
            res = handle_command(d)
            if res is not None and res is not "": #send back data
                res = res+"\n"
                #res = "You sent me: {} \n".format(d) #dummy message for testing
                logging.info("received message from client: {}".format(data))
                logging.info("sending back : {} ".format(res.encode()))
                clientsocket.send(res.encode())
            else:
                clientsocket.send(b"\n")#just send an empty string
    logging.info("client disconnect")
    handle_command("stop")
    clientsocket.close()
def stop():
    global running
    logging.info("stopiing server")
    running=False
def run():
    global running
    host = ''
    port = 53820
    addr = (host, port)
    serversocket = socket(AF_INET, TCP_NODELAY) #add TCP_NODELAY for faster responses, almost UDP, but still a tcp socket with acks and stuff
    serversocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    serversocket.bind(addr)
    serversocket.listen(255)#allow only 1 connection
    try:
        logging.info("Server is listening for connections on port %s \n",port)
        while running:
            clientsocket, clientaddr = serversocket.accept()
            thread.start_new_thread(handler, (clientsocket, clientaddr))
        serversocket.close()
    except KeyboardInterrupt as e:
        running=False

if __name__ == '__main__':
    run()
