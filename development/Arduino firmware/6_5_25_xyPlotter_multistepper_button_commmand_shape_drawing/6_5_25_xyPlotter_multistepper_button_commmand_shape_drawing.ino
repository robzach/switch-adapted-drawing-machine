/*

Three-axis plotter (XY plus pen rotation)

When a pushbutton is pressed, draw the next shape that's defined in
shapes_array.h. 

Three pushbuttons allow you to select a small, medium, or large version
of the drawing.

A joystick allows you to jog the x and y axes.

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

23    in      draw next shape button (green wire)
29    in      large drawing button (orange wire)
31    in      medium drawing button (yellow wire)
33    in      small drawing button (purple wire)

A0    in      x axis jog joystick (orange wire)
A1    in      y axis jog joystick (yellow wire)

*/

#include <AccelStepper.h>
#include <MultiStepper.h>
#include "shapes_array.h"

// Define steppers
AccelStepper penStepper;  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper xStepper(AccelStepper::FULL4WIRE, 6, 7, 8, 9);
AccelStepper yStepper(AccelStepper::FULL4WIRE, 10, 11, 12, 13);

MultiStepper steppers;  // "steppers" is the object for all motors

const int NEXTDRAWINGPIN = 23,
          LARGEDRAWINGPIN = 29,
          MEDIUMDRAWINGPIN = 31,
          SMALLDRAWINGPIN = 33,
          XAXISJOGPIN = A0,
          YAXISJOGPIN = A1;

const long PENUPPOS = 200,
           PENDOWNPOS = 0;

const int LARGEDRAWINGMULTIPLIER = 30,
          MEDIUMDRAWINGMULTIPLIER = 20,
          SMALLDRAWINGMULTIPLIER = 10;
int drawingMultiplier = 10;  // small by default

const int JOGREADSLOP = 10;  // used to ignore center position of jog joystick
const int JOGSTEPSIZE = 40;

long positions[3];  // array of desired stepper positions

int shapeIndex = 0;

void setup() {
  xStepper.setMaxSpeed(500);
  yStepper.setMaxSpeed(500);
  penStepper.setMaxSpeed(500);

  steppers.addStepper(xStepper);
  steppers.addStepper(yStepper);
  steppers.addStepper(penStepper);

  pinMode(NEXTDRAWINGPIN, INPUT_PULLUP);
  pinMode(LARGEDRAWINGPIN, INPUT_PULLUP);
  pinMode(MEDIUMDRAWINGPIN, INPUT_PULLUP);
  pinMode(SMALLDRAWINGPIN, INPUT_PULLUP);

  pinMode(XAXISJOGPIN, INPUT);
  pinMode(YAXISJOGPIN, INPUT);

  positions[2] = PENDOWNPOS;

  Serial.begin(9600);
}

void loop() {
  // read state of pushbuttons
  // note inverted logic because of input pullup
  bool nextDrawing = !digitalRead(NEXTDRAWINGPIN);

  bool drawLarge = !digitalRead(LARGEDRAWINGPIN);
  bool drawMedium = !digitalRead(MEDIUMDRAWINGPIN);
  bool drawSmall = !digitalRead(SMALLDRAWINGPIN);

  int xJogRead = analogRead(XAXISJOGPIN);
  int yJogRead = analogRead(YAXISJOGPIN);

  if (xJogRead > 512 + JOGREADSLOP) jogXPos();
  else if (xJogRead < 512 - JOGREADSLOP) jogXNeg();
  if (yJogRead > 512 + JOGREADSLOP) jogYPos();
  else if (yJogRead < 512 - JOGREADSLOP) jogYNeg();

  if (nextDrawing) {
    drawShape(shapeIndex);
    shapeIndex++;
  }

  if (drawLarge)  drawingMultiplier = LARGEDRAWINGMULTIPLIER;
  if (drawMedium) drawingMultiplier = MEDIUMDRAWINGMULTIPLIER;
  if (drawSmall)  drawingMultiplier = SMALLDRAWINGMULTIPLIER;
}

void drawShape(int shapeNum) {
  int index = 0;
  while (index < shapes[shapeNum].count + 1) {
    if (steppers.run() == 0) { // if steppers have arrived at their prior target
      positions[0] = drawingMultiplier * (-shapes[shapeNum].coordinates[index].x);  // minus sign needed to flip output orientation
      positions[1] = drawingMultiplier * shapes[shapeNum].coordinates[index].y;
      positions[2] = PENDOWNPOS;  // once arrived at starting point, lower pen

      steppers.moveTo(positions);  // go to their next target

      Serial.println("pen down");
      Serial.println((String) "positions[0], [1]: " + positions[0] + ", " + positions[1]);

      index++;
    }
  }
  home();
}

void home() {
  while (steppers.run()) {  // while steppers haven't gotten to their target
    positions[0] = 0;
    positions[1] = 0;
    positions[2] = PENUPPOS;
    steppers.moveTo(positions);
  }
}

void jogXPos() {
  positions[0] = xStepper.currentPosition() + JOGSTEPSIZE;
  positions[1] = yStepper.currentPosition();    // Keep Y at current position
  positions[2] = penStepper.currentPosition();  // Keep pen at current position
  steppers.moveTo(positions);
  while (steppers.run()) {
    // Wait for movement to complete
  }
  setNewOrigin();
}

void jogXNeg() {
  positions[0] = xStepper.currentPosition() - JOGSTEPSIZE;
  positions[1] = yStepper.currentPosition();    // Keep Y at current position
  positions[2] = penStepper.currentPosition();  // Keep pen at current position
  steppers.moveTo(positions);
  while (steppers.run()) {
    // Wait for movement to complete
  }
  setNewOrigin();
}

void jogYPos() {
  positions[0] = xStepper.currentPosition();
  positions[1] = yStepper.currentPosition() + JOGSTEPSIZE;  // Keep Y at current position
  positions[2] = penStepper.currentPosition();              // Keep pen at current position
  steppers.moveTo(positions);
  while (steppers.run()) {
    // Wait for movement to complete
  }
  setNewOrigin();
}

void jogYNeg() {
  positions[0] = xStepper.currentPosition();
  positions[1] = yStepper.currentPosition() - JOGSTEPSIZE;  // Keep Y at current position
  positions[2] = penStepper.currentPosition();              // Keep pen at current position
  steppers.moveTo(positions);
  while (steppers.run()) {
    // Wait for movement to complete
  }
  setNewOrigin();
}

void setNewOrigin() {
  xStepper.setCurrentPosition(0);
  yStepper.setCurrentPosition(0);

  // Serial.println("New origin set at current position");
}