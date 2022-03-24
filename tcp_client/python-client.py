#!/usr/bin/env python3

import socket
import tqdm
import os


HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 8000        # The port used by the server


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    while True:
        frame = bytearray()
        text = input("insert cmd: ")

        frame.append(int(text))
        
        if int(text) == 3:
            text = input("insert direction: ")
            frame.append(int(text))
            text = input("insert speed: ")
            frame.append(int(text))

        s.sendall(frame)

    s.close()
