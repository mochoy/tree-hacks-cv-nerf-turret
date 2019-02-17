#define LED_PIN 13

void setup() {
	Serial.begin(9600);

	pinMode(LED_PIN, OUTPUT);
}

void loop () {
	if (Serial.available() > 0) {
		char reading = Serial.read();
		Serial.println(reading);
		if (reading == '1') {
			digitalWrite(LED_PIN, HIGH);
		}
	} else {
		digitalWrite(LED_PIN, LOW);
	}
}