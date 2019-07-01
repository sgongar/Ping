import pygame


def ring_alarm():
    """ TODO how to stop it?

    :return:
    """
    pygame.mixer.init()
    pygame.mixer.music.load("myFile.wav")
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy() == True:
        continue