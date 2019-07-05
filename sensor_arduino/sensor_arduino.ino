#include <SoftwareSerial.h>// import the serial library

SoftwareSerial Genotronex(10, 11); // RX, TX
int BluetoothData; // the data given from Computer

int ledPin = 13; // choose the pin for the LED
int ledBluetooth = 9; //
int inPin = 7;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status
int bluetoothON = 0; // variable que indica que la conexion bluetooth esta activa


void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    Genotronex.begin(9600);
    Genotronex.println("Bluetooth On please press 1 or 0 blink LED ..");
    pinMode(ledPin, OUTPUT);  // declare LED as output
    pinMode(ledBluetooth, OUTPUT);
    pinMode(inPin, INPUT);    // declare pushbutton as input
}

void loop() {
  Serial.println("test");
  if (Genotronex.available()){
    digitalWrite(ledPin, HIGH);
    val = digitalRead(inPin);  // read input value
    if (val == HIGH) {         // check if the input is HIGH (button released)
      digitalWrite(ledBluetooth, HIGH);  // turn LED ON
      Genotronex.println("PING");
      delay(500);
      digitalWrite(ledBluetooth, LOW);  // turn LED OFF
    } 
  }
    
    // Genotronex.println("hola");
  
    // put your main code here, to run repeatedly:
    // if (Genotronex.available()){
    //     BluetoothData=Genotronex.read();
    //     if(BluetoothData=='1'){   // if number 1 pressed ....
    //         digitalWrite(ledBluetooth, HIGH);
    //         Genotronex.println("LED  On D13 ON ! ");
    //     }
    //     if (BluetoothData=='0'){// if number 0 pressed ....
    //         digitalWrite(ledBluetooth, HIGH);
    //         Genotronex.println("LED  On D13 Off ! ");
    //     }
    // }
  delay(100);// prepare for next data ...
}
