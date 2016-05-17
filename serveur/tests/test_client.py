#!/usr/bin/python3
from __future__ import print_function
import socket
#from __builtins__  import input
import types


class MySocket:
    """demonstration class only
      - coded for clarity, not efficiency
    """

    def __init__(self, sock=None):
        if sock is None:
            self.sock = socket.socket(
                            socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.sock = sock

    def connect(self, host, port):
        self.sock.connect((host, port))

    def mysend(self, msg):
        totalsent = 0
        self.msglen = len(msg)
        msg = msg.encode()
        while totalsent < self.msglen:
            sent = self.sock.send(msg[totalsent:])
            if sent == 0:
                raise RuntimeError("socket connection broken")
            totalsent = totalsent + sent

    def myreceive(self):
        chunks = []
        bytes_recd = 0
        while True:

            chunk = self.sock.recv(128)
            if chunk == b'':
                raise RuntimeError("socket connection broken")
            chunks.append(chunk)
            bytes_recd = bytes_recd + len(chunk)
            print(chunk)
            if "\n" in chunk.decode():
                break;
        return b''.join(chunks)
if __name__ == '__main__':
    s = MySocket()
    s.connect("127.0.0.1",53820)
    try:
        s.mysend("move up 100")
        print("received in response > ",s.myreceive())
    except KeyboardInterrupt as e:
        raise
