#include <Stepper.h>

#define STEPS 200


Stepper stepper(STEPS, 4, 5, 6, 7);


void setup() {
	Serial.begin(9600);
  // Serial.println("Stepper test!");
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(4);
}

void loop() {
	stepperRight(40);
	// Serial.println("fads");
	delay(1500);
	stepperLeft(40);
	delay(1500);
}

void stepperRight(int steps) {
	Serial.println("stepper right");
	stepper.step(steps);
}	

void stepperLeft(int steps) {
	Serial.println("stepper left");
	stepper.step(-steps);
}