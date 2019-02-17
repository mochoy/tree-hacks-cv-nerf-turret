#include <Button.h>
#include <Wire.h>

// COmmand codes
#define ROTATE_LEFT 1
#define ROTATE_RIGHT 2
#define SHOOT 5

#define SLAVE_ADDRESS 0x04

#define PUSHER_MOTOR_PIN 3
#define PUSHER_BRAKE_PIN 2
#define FLYWHEEL_MOTOR_PIN 5

#define PUSHER_RETURN_SWICH_PIN 4

// parameters for buttons
#define INVERT true
#define PULLUP true
#define DEBOUNCE_MS 20



Button triggerBtn (PUSHER_RETURN_SWICH_PIN, PULLUP, INVERT, DEBOUNCE_MS);

uint8_t pusherPow, flywheelPow;
uint8_t commandType;	// buffer to indicate commandson which motor controls to complete
uint8_t timesToRead;	// keep track of how many times to read serial before resetting command type

void setup() {
	Serial.begin(9600);

	pinMode(PUSHER_MOTOR_PIN, OUTPUT);
	pinMode(PUSHER_BRAKE_PIN, OUTPUT);
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

    // set type of command
    if (commandType == 0) {
    	commandType = intReading;
  		Serial.println("Command: " + (String)commandType);
  		return;
  	}
  		
		if (commandType == ROTATE_LEFT) {
			Serial.println("Rotating left!");
			commandType = 0;
  	} else if (commandType == ROTATE_RIGHT) {
  		Serial.println("Rotating right!");
  		commandType = 0;
  	} else if (commandType == SHOOT) {
  		Serial.println("Shooting!");
  		if (!pusherPow) {
  			pusherPow = intReading;
  			return;
  		} 

  		flywheelPow = intReading;

  		commandType = 0;
  	}


  }
}

// void receiveI2CData () {
// 	while (Wire.available()) {
//     int reading = Wire.read();
//     Serial.print("data received: ");
//     Serial.println(reading);

//   }
// }