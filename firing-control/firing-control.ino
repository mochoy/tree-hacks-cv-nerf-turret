#define PUSHER_PIN 9
#define FLYWHEEL_PIN 10

#define FLYWHEEL_ACCEL_DELAY 150
#define FIRE_DELAY 35


void setup() {
	pinMode(PUSHER_PIN, OUTPUT);
	pinMode(FLYWHEEL_PIN, OUTPUT);
}

void loop() {
	for (int i = 0; i < 10; i++) {
		fire();
	}

	delay(5000);
}

void fire() {
	digitalWrite(FLYWHEEL_PIN, HIGH);
	delay(FLYWHEEL_ACCEL_DELAY);
	digitalWrite(PUSHER_PIN, HIGH);
	delay(FIRE_DELAY);

	digitalWrite(FLYWHEEL_PIN, LOW);
	digitalWrite(PUSHER_PIN, LOW);
}