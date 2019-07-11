# -*- coding: utf-8 -*-
from bluetooth import *
from time import sleep

from firebase import send_time, set_up_firebase
import I2C_LCD_driver
from utils import get_time


class PingDetect:

    def __init__(self):
        """

        """
        self.db = set_up_firebase()
        self.user_id = 'Morty'
        self.mylcd = I2C_LCD_driver.lcd()

        self.receive_data()

    def receive_data(self):
        """

        :return:
        """
        bd_addr = "00:18:E4:35:03:3A"
        port = 1
        sock = BluetoothSocket(RFCOMM)
        sock.connect((bd_addr, port))
        self.display_info('Sistema listo', 1)
        while 1:
            data = sock.recv(10)
            data = str(data, 'utf-8')
            print(data)

            if '1' in data:
                actual_time = get_time()
                self.mylcd.lcd_clear()
                msg = 'Ping en {}'.format(actual_time)
                send_time(self.db, self.user_id)
                self.display_info('Sistema listo', 1)
                self.display_info(msg, 2)
            if '2' in data:
                actual_time = get_time()
                self.mylcd.lcd_clear()
                msg = 'ALARMA {}'.format(actual_time)
                send_time(self.db, self.user_id)
                self.display_info('Sistema listo', 1)
                self.display_info(msg, 2)
            sleep(2.0)
        sock.close()

    def display_info(self, msg, row):
        """

        :param msg:
        :param row:
        :return:
        """
        self.mylcd.lcd_display_string(msg, row, 0)


if __name__ == "__main__":
    PingDetect()
