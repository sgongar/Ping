# import pygame
import datetime

# def ring_alarm():
#     """ TODO how to stop it?
#
#     :return:
#     """
#     pygame.mixer.init()
#     pygame.mixer.music.load("myFile.wav")
#     pygame.mixer.music.play()
#     while pygame.mixer.music.get_busy() == True:
#         continue


def get_time():
    """

    :return:
    """
    now = f'{datetime.datetime.now():%H:%M:%S%z}'

    return now
