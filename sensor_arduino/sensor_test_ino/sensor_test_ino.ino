// processing plotting code
// https://www.instructables.com/id/Arduino-Stress-Detector/


import processing.serial.*;
Serial myPort;

int numValues = 3;    // number of input values or sensors

// sensors:
float A = 0;          // PPG
int Amin = 0;
int Amax = 3;

float B = 0;          // Breathing
int Bmin = 0;
int Bmax = 3;

float C = 0;          // GSR
int Cmin = 0;
int Cmax = 1023;

float partH;          // partial screen height
int xPos = 1;         // horizontal position of the graph
void setup() {
  size(800, 600);
  partH = height / numValues;    // to divide screen up to draw the number of sensors

    // List all the available serial ports:
  println(Serial.list());
  // First port [0] in serial list usually Arduino:
  myPort = new Serial(this, Serial.list()[1], 9600);
  // don't generate a serialEvent() until get a newline character:
  myPort.bufferUntil('\n');
  background(0);
}
void draw() {
  // everything happens inside serialEvent()
}
void serialEvent(Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  //println(inString);

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // split the string on the commas and convert the resulting substrings into an integer array:
    float[] values = float(split(inString, ","));
    // the array has at least the # of elements as your # of sensors:
    if (values.length >= numValues) {
      // map to the range of partial screen height:
      A = map(values[0], Amin, Amax, 0, partH);
      B = map(values[1], Bmin, Bmax, 0, partH);
      C = map(values[2], Cmin, Cmax, 0, partH);
     // println(A + "\t" + B + "\t" + C);

      // draw lines:
      if (A >= partH/2) {
        stroke(255, 0, 0);  // red
      } else {
        stroke(0, 255, 0);
      }
      line(xPos, partH, xPos, partH - A);
      if (B >= partH/2) {
        stroke(255, 0, 0);  // red
      } else {
        stroke(0, 255, 0);
      }
      line(xPos, partH*2, xPos, partH*2 - B);
      if (C >= partH/2) {
        stroke(255, 0, 0);  // red
      } else {
        stroke(0, 255, 0);
      }
      line(xPos, partH*3, xPos, partH*3 - C);

      // graph title:
      text("PPG", width/2, 15);
      text("Breathing", width/2, partH + 15);
      text("GSR", width/2, partH*2 + 15);

      // draw dividing lines:
      stroke(255);
      line(0, partH, width, partH);
      line(0, partH*2, width, partH*2);
      // if at the edge of the screen, go back to the beginning:
      if (xPos >= width) {
        xPos = 0;
        background(0);   // erase screen with black
      } else {
        xPos++;          // increment the graph's horizontal position
      }
    }
  }
}

