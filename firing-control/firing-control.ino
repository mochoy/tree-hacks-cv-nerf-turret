#define PUSHER_PIN 9
#define FLYWHEEL_PIN 10

#define FLYWHEEL_ACCEL_DELAY 50
#define FLYWHEEL_FIRE_DELAY 250
#define PUSHER_FIRE_DELAY 200

void setup() {
	pinMode(PUSHER_PIN, OUTPUT);
	pinMode(FLYWHEEL_PIN, OUTPUT);
}

void loop() {

}

void fire() {
	digitalWrite(FLYWHEEL_PIN, HIGH);
	delay(FLYWHEEL_ACCEL_DELAY);
	digitalWrite(PUSHER_PIN);
	delay(FLYWHEEL_FIRE_DELAY);
}