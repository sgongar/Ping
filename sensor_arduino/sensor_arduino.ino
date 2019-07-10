#include <SoftwareSerial.h>            // Libreria para las comunicaciones seriales
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_ADXL345.h>          // SparkFun ADXL345 Library

SoftwareSerial Genotronex(10, 11);     // RX, TX

ADXL345 adxl = ADXL345();              // USE FOR I2C COMMUNICATION

const int onPin = 7;                   // the number of the pushbutton pin
const int onLed = 8;                   // the number of the LED pin
const int ledBluetooth = 9;            // Led de comunicacion bluetooth
const int inPin = 6;                   // choose the input pin (for a pushbutton)

// Variables will change:
int ledState = LOW;                    // the current state of the output pin
int lastledState = LOW;                //
int buttonState;                       // the current reading from the input pin
int lastButtonState = LOW;             // the previous reading from the input pin
int val = 0;                           // variable for reading the pin status
int on = 0;                            //

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;    // the last time the output pin was toggled
unsigned long debounceDelay = 50;      // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(57000);                 // Inicio de las comunicaciones seriales para el debug
  Genotronex.begin(9600);              // Inicio de la comunicacion serial bluetooth
  pinMode(onPin, INPUT);               // Fija el 
  pinMode(onLed, OUTPUT);              //
  pinMode(ledBluetooth, OUTPUT);       //
  pinMode(inPin, INPUT);               // declare pushbutton as input

  digitalWrite(onLed, ledState);       // Fija el estado inicial del LED
  
  adxl.powerOn();                      // Enciende el ADXL345
  adxl.setRangeSetting(2);             // Valoes aceptados 2g, 4g, 8g o 16g
  adxl.setSpiBit(0);                   // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
                                       // Default: Set to 1
                                       // SPI pins on the ATMega328: 11, 12 and 13 as reference in SPI Library
  // Detecciones deshabilitadas   
  adxl.setActivityXYZ(0, 0, 0);        // Deshabilita la deteccion de la actividad en los tres ejes
  adxl.setTapDetectionOnXYZ(0, 0, 0);  // Deshabilita la deteccion de los golpes en los tres ejes

  // Configuracion de la deteccion de inactividad
  adxl.setInactivityXYZ(1, 1, 1);     // Habilita la deteccion de inactividad en los tres ejes
  adxl.setInactivityThreshold(75);    // 62.5mg per increment Inactivity thresholds (0-255)
  adxl.setTimeInactivity(10);         // How many seconds of no activity is inactive?


  // Set values for what is considered FREE FALL (0-255)
  adxl.setFreeFallThreshold(5);       // (5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(30);       // (20 - 70) recommended - 5ms per increment
 
  // Configuracion de las interrupciones
  adxl.InactivityINT(1);              //
  adxl.ActivityINT(0);                //
  adxl.FreeFallINT(1);                //
  adxl.doubleTapINT(0);               //
  adxl.singleTapINT(0);               //
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(onPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // Enciende o apaga el led de encendido dependiendo del estado del sistema
  digitalWrite(onLed, ledState);
  if (ledState != lastledState){
    if (ledState == 1){
      on = 1;
    }
    else if (ledState == 0){
      on = 0;
    }
  }
  // Este codigo se ejecuta solo si esta encendido
  if (on == 1){
    // getInterruptSource clears all triggered actions after returning value
    // Do not call again until you need to recheck for triggered actions
    byte interrupts = adxl.getInterruptSource();
 
    // Free Fall Detection
    if(adxl.triggered(interrupts, ADXL345_FREE_FALL)){
      Serial.println("*** FREE FALL ***");
      Genotronex.println(2);
    }
    
    // Inactivity
    if(adxl.triggered(interrupts, ADXL345_INACTIVITY)){
      // Serial.println("*** INACTIVITY ***");
       //add code here to do when inactivity is sensed
    }

    val = digitalRead(inPin);  // Lee el valor del pulsador del Ping
    if (val == HIGH) {         // Comprueba el pulsador del Ping
      digitalWrite(ledBluetooth, HIGH);  // turn LED ON
      Genotronex.println(1);
      delay(500);
      digitalWrite(ledBluetooth, LOW);  // turn LED OFF
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  lastledState = ledState;
}

