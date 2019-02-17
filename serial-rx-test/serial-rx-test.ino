#define LED_PIN 13

String command = "";
int degreesToTurn = 0;

void setup() {
	Serial.begin(9600);

	pinMode(LED_PIN, OUTPUT);
}

void loop () {
	if (Serial.available() > 0) {
		char reading = Serial.read();
		
		Serial.print("Reading: ");
		Serial.println(reading);
		Serial.print("Command: ");

		// null terminator
		if (reading == 'a') {
			Serial.println(command);

			degreesToTurn = command.toInt();
			Serial.println((String)(degreesToTurn + 1));

			command = "";
			Serial.println("resetting");

			return;
		} 

		//appending to command
		command += reading;
		Serial.println(command);

	}

}