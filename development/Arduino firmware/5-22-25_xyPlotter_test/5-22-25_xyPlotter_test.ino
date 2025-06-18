/*

Three-axis plotter (XY plus pen rotation)

pin mapping:

pin | role  | description
----|-------|-----------------
2     out     penStepper IN1 (purple wire)
3     out     penStepper IN3 (brown wire)
4     out     penStepper IN2 (orange wire)
5     out     penStepper IN4 (yellow wire)
A0    out     xStepper IN1 (purple wire)
A1    out     xStepper IN3 (brown wire)
A2    out     xStepper IN2 (orange wire)
A3    out     xStepper IN4 (yellow wire)
10    out     yStepper IN1 (purple wire)
11    out     yStepper IN3 (brown wire)
12    out     yStepper IN2 (orange wire)
13    out     yStepper IN4 (yellow wire)

*/



#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper penStepper;  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper xStepper(AccelStepper::FULL4WIRE, A0, A1, A2, A3);
AccelStepper yStepper(AccelStepper::FULL4WIRE, 10, 11, 12, 13);

void setup() {
  // Change these to suit your stepper if you want
  penStepper.setMaxSpeed(100);
  penStepper.setAcceleration(20);
  penStepper.moveTo(500);

  xStepper.setMaxSpeed(100);
  xStepper.setAcceleration(20);
  xStepper.moveTo(500);

  yStepper.setMaxSpeed(100);
  yStepper.setAcceleration(20);
  yStepper.moveTo(500);
}

void loop() {
  // If at the end of travel go to the other end
  if (penStepper.distanceToGo() == 0)
    penStepper.moveTo(-penStepper.currentPosition());
  penStepper.run();

  if (xStepper.distanceToGo() == 0)
    xStepper.moveTo(-xStepper.currentPosition());
  xStepper.run();

  if (yStepper.distanceToGo() == 0)
    yStepper.moveTo(-yStepper.currentPosition());
  yStepper.run();
}