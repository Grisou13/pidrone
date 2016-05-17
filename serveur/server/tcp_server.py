#!/usr/bin/python3
import os,signal,sys
import logging
from socket import *
#logging.basicConfig(filename='./../logs/tcp_server.log',level=logging.NOTSET,stream=sys.stdout)
logging.basicConfig(level=logging.NOTSET,stream=sys.stdout)
#logging.info("starting server")

try:
    import _thread as thread
except ImportError:
    import thread


from commands import handle_command

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
            logging.info("data : |{}|".format(d))
            #cmd = d.split(" ")
            #logging.info(cmd)
            res = handle_command(d)
            res = res+"\n"
            logging.info(res)
            #res = "You sent me: {} \n".format(d) #dummy message for testing

            logging.info("received message from client: {}".format(data))
            logging.info("sending back : {} ".format(res.encode()))
            clientsocket.send(res.encode())
            #clientsocket.send("\n")
    clientsocket.close()

def run():
    global running
    host = ''
    port = 53820
    addr = (host, port)
    serversocket = socket(AF_INET, SOCK_STREAM)
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
