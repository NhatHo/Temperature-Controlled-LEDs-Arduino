/*
 Name:		LoveOMeter.ino
 Created:	5/15/2016 8:04:40 PM
 Author:	NhatHo
*/

const int sensorPin = A0;
const float baselineTemp = 25.0;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600); // open a serial port
	
	// Initialize pin 3,4,5 as OUTPUT pins and set 3 lights to OFF
	for (int pinNumber = 3; pinNumber < 6; pinNumber++) {
		pinMode(pinNumber, OUTPUT);
		digitalWrite(pinNumber, LOW);
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	int sensorVal = analogRead(sensorPin);
	Serial.print("Sensor value: ");
	Serial.print(sensorVal);

	// convert ADC reading to voltage
	float voltage = (sensorVal / 1024.0) * 5.0;

	Serial.print(". Volts: ");
	Serial.print(voltage);

	// convert voltage to actual temperature
	// Take into account offset of temperature sensor when it senses 0 degree Celcius
	float temperature = (voltage - 0.5) * 100;
	Serial.print(". Centigrate: ");
	Serial.println(temperature);

	// Temperature less than 25 degree Celcius --> No light to indicate
	if (temperature < baselineTemp) {
		digitalWrite(3, LOW);
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
	}

	// Temperature between 25 and 27 degree Celcius --> First light will be lit
	else if (temperature >= baselineTemp && temperature < baselineTemp + 2) {
		digitalWrite(3, HIGH);
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
	}

	// Temperature between 27 and 29 degree Celcius --> First and second lights will be lit
	else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
		digitalWrite(3, HIGH);
		digitalWrite(4, HIGH);
		digitalWrite(5, LOW);
	}

	// Temperature more than 29 degree Celcius --> All 3 lights will be lit
	else {
		digitalWrite(3, HIGH);
		digitalWrite(4, HIGH);
		digitalWrite(5, HIGH);
	}
	delay(100);
}
