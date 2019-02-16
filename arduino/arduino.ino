#include <Button.h>
#include <Wire.h>

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

void setup() {
	Serial.begin(9600);

	pinMode(PUSHER_MOTOR_PIN, OUTPUT);
	pinMode(PUSHER_BRAKE_PIN, OUTPUT);
	pinMode(FLYWHEEL_MOTOR_PIN, OUTPUT);

	// Wire.begin(SLAVE_ADDRESS);
	// Wire.onReceive(receiveI2CData);
}

void loop() {

}


// void receiveI2CData () {
// 	while (Wire.available()) {
//     int reading = Wire.read();
//     Serial.print("data received: ");
//     Serial.println(reading);

//   }
// }