#include <Button.h>

// 1Ommand codes
#define ROTATE_LEFT 1
#define ROTATE_RIGHT 2
#define SHOOT 3


#define PUSHER_MOTOR_PIN 9
#define FLYWHEEL_MOTOR_PIN 10



uint8_t pusherPow, flywheelPow;

void setup() {
	Serial.begin(9600);

	pinMode(PUSHER_MOTOR_PIN, OUTPUT);
	pinMode(FLYWHEEL_MOTOR_PIN, OUTPUT);

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

    

  }
}

// void receiveI2CData () {
// 	while (Wire.available()) {
//     int reading = Wire.read();
//     Serial.print("data received: ");
//     Serial.println(reading);

//   }
// }