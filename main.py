# -*- coding: utf-8 -*-
# import RPi.GPIO as GPIO
# import os
# import sys
from bluetooth import *
from time import sleep
# from subprocess import call
# import pyrebase

from firebase import send_time, set_up_firebase


class PingDetect:

    def __init__(self):
        """

        """
        self.db = set_up_firebase()
        user_id = 'Morty'

        # for i in range(10):
        #     send_time(self.db, user_id)

    def receive_data(self):
        """

        :return:
        """
        bd_addr = "00:18:E4:35:03:3A"
        port = 1
        sock = BluetoothSocket(RFCOMM)
        sock.connect((bd_addr, port))
        print('waiting')
        while 1:
            data = sock.recv(10)
            print(data)
            sleep(2.0)

        sock.close()


if __name__ == "__main__":
    PingDetect()
