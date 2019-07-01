import pyrebase


config = {
  "apiKey": "AIzaSyCY0kY9qBvVyE0dvngn9TwLXwb5xyt2_Jw",
  "authDomain": "ping-7a807.firebaseapp.com",
  "databaseURL": "https://ping-7a807.firebaseio.com/",
  "storageBucket": "ping-7a807.appspot.com"
}

firebase = pyrebase.initialize_app(config)

user_id = 'Morty'

db = firebase.database()


"""
class CheckFirebase:
    def __init__(self):
        self.value = 0
        self._lock = threading.Lock()

    def check(self, name):
        print("alojomora")
        logging.info("Thread %s: starting update", name)
        logging.debug("Thread %s about to lock", name)
        with self._lock:
            logging.debug("Thread %s has lock", name)
            local_copy = self.value
            local_copy += 1
            time.sleep(0.1)
            self.value = local_copy
            logging.debug("Thread %s about to release lock", name)
        logging.debug("Thread %s after release", name)
        logging.info("Thread %s: finishing update", name)


if __name__ == "__main__":
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO,
                        datefmt="%H:%M:%S")

    check = CheckFirebase()
    logging.info("Testing update. Starting")
    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as executor:
        # for index in range(2):
        #     executor.submit(database.update, index)
        executor.submit(CheckFirebase.check, "database")
        executor.submit(CheckFirebase.check, "fall")
"""


def send_time(db, user_id):
    """

    :param db: acceso a la base de datos de firebase
    :param user_id: nombre del usuario
    :return: True si no hay ningun problema
    """

    data = db.child("users").get()
    user_data = data.val().get(user_id)

    new_data = {"name": "Mortimer 'Morty' Smith", "old_time": user_data['new_time'], "new_time": {".sv": "timestamp"},
                "location": "raspberrypi"}
    db.child("users").child("Morty").set(new_data)

    return True


def get_alarm(db, user_id):
    """

    :param db:
    :param user_id:
    :return:
    """

    data = db.child("users").get()
    user_data = data.val().get(user_id)

    final_time = user_data['new_time']/1000
    initial_time = user_data['old_time']/1000

    delay_time = (final_time - initial_time) / 60
    print(delay_time)

    if delay_time < 16:
        interval_condition = True
    else:
        interval_condition = False

    dummy_data = {'actual_time': {".sv": "timestamp"}}
    db.child("users").child("Dummy").set(dummy_data)

    actual_time = db.child("users").get().val().get("Dummy")['actual_time'] / 1000

    if ((actual_time - final_time) / 60) < 16:
        last_contact_condition = True
    else:
        last_contact_condition = False

    alarm = not(interval_condition and last_contact_condition)

    return alarm
