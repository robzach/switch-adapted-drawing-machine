/*

Three-axis plotter (XY plus pen rotation)

When a pushbutton is pressed, draw a triangle.
When a different button is pressed, draw a square.

This is buggy! The basic button pressing is triggering drawing to happen,
but not in the order of points I expected. The pen motor isn't moving.

Push both axes to their center points before adding power.

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

23    in      triangle button
25    in      square button

*/



#include <AccelStepper.h>
#include <MultiStepper.h>


// Define a stepper and the pins it will use
AccelStepper penStepper;  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper xStepper(AccelStepper::FULL4WIRE, 6, 7, 8, 9);
AccelStepper yStepper(AccelStepper::FULL4WIRE, 10, 11, 12, 13);

MultiStepper steppers;  // "steppers" is the object for all motors

int triangleXPositions[] = { 0, 1000, 500, 0 };
int triangleYPositions[] = { 0, 0, 1000, 0 };

int squareXPositions[] = { 0, 1000, 1000, 0, 0 };
int squareYPositions[] = { 0, 0, 1000, 1000, 0 };

long positions[2];  // Array of desired stepper positions

int numTriangleSteps = 0;
int numSquareSteps = 0;

const int TRIANGLEBUTTONPIN = 23,
          SQUAREBUTTONPIN = 25;

void setup() {
  xStepper.setMaxSpeed(500);
  yStepper.setMaxSpeed(500);
  penStepper.setMaxSpeed(500);

  steppers.addStepper(xStepper);
  steppers.addStepper(yStepper);
  // steppers.addStepper(penStepper);

  numTriangleSteps = sizeof(triangleXPositions) / sizeof(triangleXPositions[0]);
  numSquareSteps = sizeof(squareXPositions) / sizeof(squareXPositions[0]);

  pinMode(TRIANGLEBUTTONPIN, INPUT_PULLUP);
  pinMode(SQUAREBUTTONPIN, INPUT_PULLUP);
}

void loop() {

  // read state of pushbuttons to select shape
  // note inverted logic because of input pullup
  bool triangleButton = !digitalRead(TRIANGLEBUTTONPIN);
  bool squareButton = !digitalRead(SQUAREBUTTONPIN);

  if (triangleButton) drawTriangle();
  if (squareButton) drawSquare();
}

void drawTriangle() {
  lowerPen();

  int index = 0;
  while (index < numTriangleSteps) {
    if (steppers.run() == 0) {                    // if steppers have arrived at their prior target
      positions[0] = -triangleXPositions[index];  // minus sign needed to flip output orientation
      positions[1] = triangleYPositions[index];
      steppers.moveTo(positions);  // go to their next target

      index++;
    }
  }
  raisePen();
}

void drawSquare() {
  lowerPen();

  int index = 0;
  while (index < numSquareSteps) {
    if (steppers.run() == 0) {                  // if steppers have arrived at their prior target
      positions[0] = -squareXPositions[index];  // minus sign needed to flip output orientation
      positions[1] = squareYPositions[index];
      steppers.moveTo(positions);  // go to their next target

      index++;
    }
  }

  raisePen();
}


/* 

The pen isn't moving as expected!

*/

void lowerPen() {
  penStepper.moveTo(200);
  penStepper.setSpeed(200);
}

void raisePen() {
  penStepper.moveTo(0);
  penStepper.setSpeed(200);
}