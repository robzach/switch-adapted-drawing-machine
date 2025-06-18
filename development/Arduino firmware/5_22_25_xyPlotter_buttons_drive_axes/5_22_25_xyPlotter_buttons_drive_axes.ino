/*

Three-axis plotter (XY plus pen rotation)

pin mapping:

pin | role  | description
----|-------|-----------------
2     out     penStepper IN1 (purple wire)
3     out     penStepper IN3 (brown wire)
4     out     penStepper IN2 (orange wire)
5     out     penStepper IN4 (yellow wire)
6     out     xStepper IN1 (purple wire)
7     out     xStepper IN3 (brown wire)
8     out     xStepper IN2 (orange wire)
9     out     xStepper IN4 (yellow wire)
10    out     yStepper IN1 (purple wire)
11    out     yStepper IN3 (brown wire)
12    out     yStepper IN2 (orange wire)
13    out     yStepper IN4 (yellow wire)

23    in      pen clockwise button
25    in      pen counterclockwise button
27    in      x axis jog +
29    in      x axis jog -
31    in      y axis jog +
33    in      y axis jog -

*/

#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper penStepper;  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper xStepper(AccelStepper::FULL4WIRE, 6, 7, 8, 9);
AccelStepper yStepper(AccelStepper::FULL4WIRE, 10, 11, 12, 13);

long penPos, xPos, yPos;

long penIncrement = 100, xIncrement = 100, yIncrement = 100;

// pause in between button reads
const long BUTTONPAUSE = 500;
long lastTimeRan;

const int PENCWBUTTONPIN = 23,
          PENCCWBUTTONPIN = 25,
          XPLUSBUTTONPIN = 27,
          XMINUSBUTTONPIN = 29,
          YPLUSBUTTONPIN = 31,
          YMINUSBUTTONPIN = 33;

void setup() {
  penStepper.setMaxSpeed(500);
  penStepper.setAcceleration(5000);

  xStepper.setMaxSpeed(500);
  xStepper.setAcceleration(5000);

  yStepper.setMaxSpeed(500);
  yStepper.setAcceleration(5000);

  pinMode(PENCWBUTTONPIN, INPUT_PULLUP);
  pinMode(PENCCWBUTTONPIN, INPUT_PULLUP);
  pinMode(XPLUSBUTTONPIN, INPUT_PULLUP);
  pinMode(XMINUSBUTTONPIN, INPUT_PULLUP);
  pinMode(YPLUSBUTTONPIN, INPUT_PULLUP);
  pinMode(YMINUSBUTTONPIN, INPUT_PULLUP);
}

void loop() {

  // read state of pushbuttons to drive motors
  bool penCW = !digitalRead(PENCWBUTTONPIN);  // note inverted logic because of input pullup
  bool penCCW = !digitalRead(PENCCWBUTTONPIN);
  bool xPlus = !digitalRead(XPLUSBUTTONPIN);
  bool xMinus = !digitalRead(XMINUSBUTTONPIN);
  bool yPlus = !digitalRead(YPLUSBUTTONPIN);
  bool yMinus = !digitalRead(YMINUSBUTTONPIN);

  // only read buttons every BUTTONPAUSE milliseconds
  if (millis() - lastTimeRan >= BUTTONPAUSE) {
    if (penCW) penPos += penIncrement;
    if (penCCW) penPos -= penIncrement;
    if (xPlus) xPos += xIncrement;
    if (xMinus) xPos -= xIncrement;
    if (yPlus) yPos += yIncrement;
    if (yMinus) yPos -= yIncrement;

    lastTimeRan = millis();
  }

  penStepper.moveTo(penPos);
  xStepper.moveTo(xPos);
  yStepper.moveTo(yPos);

  penStepper.run();
  xStepper.run();
  yStepper.run();
}