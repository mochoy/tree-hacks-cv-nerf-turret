#include <Button.h>
#include <Stepper.h>


#define PUSHER_MOTOR_PIN 9
#define FLYWHEEL_MOTOR_PIN 10

#define FLYWHEEL_ACCEL_DELAY 150
#define FIRE_DELAY 35

#define STEPS 200
#define STEP_SPEED 4


Stepper stepper(STEPS, 4, 5, 6, 7);

uint8_t pusherPow, flywheelPow;
String command = "";

bool toClearSerialBuffer = false;

void setup() {
	Serial.begin(9600);

	pinMode(PUSHER_MOTOR_PIN, OUTPUT);
	pinMode(FLYWHEEL_MOTOR_PIN, OUTPUT);

	stepper.setSpeed(STEP_SPEED);

}

void loop() {
	clearBuffer();
	readSerial();
}

void clearBuffer () {
	if (toClearSerialBuffer) {
		if (Serial.available() > 0) {
			Serial.println("clearing");

			while (Serial.available() > 0) {
				Serial.read();
			}	
		}

		toClearSerialBuffer = false;
	} 
}

void readSerial() {
	if (Serial.available() > 0) {
    char reading = Serial.read();
    int intReading = reading - '0';

  	Serial.print("Reading: ");
		Serial.println(reading);
		Serial.print("Command: ");

    // null terminator
		if (reading == 'a') {
			Serial.println(command);

			Serial.println("executing command");

			int degreesToTurn = command.toInt();
			Serial.print("rotation: ");
			Serial.println((String)(degreesToTurn + 1));

			command = "";
			Serial.println("resetting");

			rotate(degreesToTurn);

			return;
		} 

		//appending to command
		command += reading;

		//make sure command buffer never gets too big
		if (command.toInt() > 600 || command.toInt() < -600) {
			command = "";
		}

		Serial.println(command);
 
  }
}

void rotate(int stepsToRotate) {
	stepper.step(stepsToRotate);
	shoot();
}

void shoot() {
	Serial.print("shooting");

	digitalWrite(PUSHER_MOTOR_PIN, HIGH);
	delay(FLYWHEEL_ACCEL_DELAY);
	digitalWrite(PUSHER_MOTOR_PIN, HIGH);
	delay(FIRE_DELAY);

	digitalWrite(PUSHER_MOTOR_PIN, LOW);
	digitalWrite(PUSHER_MOTOR_PIN, LOW);

	Serial.println("finished\n\n");

	toClearSerialBuffer = true;
}

// void receiveI2CData () {
// 	while (Wire.available()) {
//     int reading = Wire.read();
//     Serial.print("data received: ");
//     Serial.println(reading);
// 8
//   }
// }