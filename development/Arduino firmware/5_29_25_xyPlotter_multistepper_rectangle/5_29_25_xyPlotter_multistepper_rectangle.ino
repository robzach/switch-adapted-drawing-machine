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

*/



#include <AccelStepper.h>
#include <MultiStepper.h>


// Define a stepper and the pins it will use
AccelStepper penStepper;  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper xStepper(AccelStepper::FULL4WIRE, 6, 7, 8, 9);
AccelStepper yStepper(AccelStepper::FULL4WIRE, 10, 11, 12, 13);

MultiStepper steppers;  // "steppers" is the object for all motors

// int square[][2] = {
//   { 0, 0 },
//   { 200, 0 },
//   { 200, 200 },
//   { 0, 200 },
//   { 0, 0 }
// };

int xPositions[] = { 0, 1000, 1000, 0, 0 };
int yPositions[] = { 0, 0, 1000, 1000, 0 };

long positions[2];  // Array of desired stepper positions

int numSteps = 0;

void setup() {
  xStepper.setMaxSpeed(500);
  yStepper.setMaxSpeed(500);
  // penStepper.setMaxSpeed(100);

  steppers.addStepper(xStepper);
  steppers.addStepper(yStepper);
  // steppers.addStepper(penStepper);

  numSteps = sizeof(xPositions) / sizeof(xPositions[0]);
}

void loop() {

  static int index = 0;
  if (steppers.run() == 0) {  // if steppers have arrived at their prior target
    positions[0] = xPositions[index];
    positions[1] = yPositions[index];
    steppers.moveTo(positions);

    index++;
    if (index > numSteps) {
      index = 0;
    }
  }
}