#include <Button.h>
#include <Stepper.h>

// 1Ommand codes
#define ROTATE_LEFT_COMMAND 1
#define ROTATE_RIGHT_COMMAND 2
#define SHOOT_COMMAND 3


#define PUSHER_MOTOR_PIN 9
#define FLYWHEEL_MOTOR_PIN 10

#define STEPS 200
#define STEPS_ON_ROTATION 


Stepper stepper(STEPS, 4, 5, 6, 7);
uint8_t pusherPow, flywheelPow;

void setup() {
	Serial.begin(9600);

	pinMode(PUSHER_MOTOR_PIN, OUTPUT);
	pinMode(FLYWHEEL_MOTOR_PIN, OUTPUT);

	stepper.setSpeed(4);

	// Wire.begin(SLAVE_ADDRESS);
	// Wire.onReceive(receiveI2CData);
}

void loop() {
	readSerial();
}

void readSerial() {
	if (Serial.available() > 0) {
    char reading = Serial.read();
    int intReading = reading -'0';

    if (reading == ROTATE_LEFT_COMMAND) {
    	rotateLeft();
    } else if (reading == ROTATE_RIGHT_COMMAND) {
    	rotateRight();
    } else if (reading == SHOOT_COMMAND) {
    	shoot();
    }

  }
}

void rotateLeft() {

}

void rotateRight() {

}

void shoot() {

}

// void receiveI2CData () {
// 	while (Wire.available()) {
//     int reading = Wire.read();
//     Serial.print("data received: ");
//     Serial.println(reading);

//   }
// }