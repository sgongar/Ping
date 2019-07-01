import RPi.GPIO as GPIO
import os
import sys
import bluetooth
from subprocess import call
import pyrebase


class PingDetect:

    def __init__(self):
        self.counter = 0
        self.user_name = "test_user"
        self.user_location = "home"

        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(8, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setup(12, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.add_event_detect(8, GPIO.RISING, callback=self.onButton,
                              bouncetime=20)

        config = {
            "apiKey": "AIzaSyCY0kY9qBvVyE0dvngn9TwLXwb5xyt2_Jw",
            "authDomain": "ping-7a807.firebaseapp.com",
            "databaseURL": "https://ping-7a807.firebaseio.com/",
            "storageBucket": "ping-7a807.appspot.com"
        }

        firebase = pyrebase.initialize_app(config)

        self.db = firebase.database()

        from time import sleep
        while self.counter < 1:
            print('hola')
            sleep(5)
            # call(["espeak", "-ves",
            #       "El sistema se ha desconectado"])
            self.sendData()
            pass
        call(["espeak", "-ves",
              "El sistema se ha desconectado"])

    # Define a callback function that will be called by the GPIO
    # event system:
    def onButton(self, channel):
        if channel == 8:
            server = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
            print('Bluetooth Socket Created')

            host = ""
            port = 1
            try:
                server.bind((host, port))
                print("Bluetooth Binding Completed")
            except:
                print("Bluetooth Binding Failed")
                pass

            server.listen(1)  # One connection at a time
            self.client, address = server.accept()
            print("Connected To", address)
            print("Client:", self.client)
            self.client.send("Sistema iniciado")
            call(["espeak", "-ves",
                  "El sistema se ha conectado a Arduino"])
            while self.counter < 1:
                if GPIO.input(10) == GPIO.HIGH:
                    self.client.send('Alarma')
                    call(["espeak", "-ves", "La alarma ha sido activada"])
                    data = {"name": self.user_name, "time": {".sv": "timestamp"},
                            "location": self.user_location}
                    self.db.child("users").child("Morty").set(data)
                if GPIO.input(12) == GPIO.HIGH:
                    self.client.send('Reinicio')
                    call(["espeak", "-ves",
                          "El contador de alarma ha sido reiniciado"])

    def sendData(self):
        """
        Dummy function to send data to Firebase
        :return:
        """

        self.db.child("users").child("Morty").update({"time": {".sv": "timestamp"}})


if __name__ == "__main__":
    PingDetect()
