#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial /* Comment this out to disable prints and save space */

#define DHT11_PIN 4
#define DHTTYPE DHT11

DHT_Unified dht(DHT11_PIN, DHTTYPE);
uint32_t delayMS;

float humidity, temp;  // Values read from sensor
unsigned long previousMillis = 0;
const long interval = 15000;          // interval at which to read sensor / Update values

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "9dc40c70df194d6cbdf469efcfc2193e";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "GamerShrimp-25G";
char pass[] = "combatwombat$$$###combatwombat";



// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  1;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


BLYNK_WRITE(V1) {
  switch (param.asInt())
  {
    case 1: // Item 1
      Serial.println("Item 1 selected");
      break;
    case 2: // Item 2
      Serial.println("Item 2 selected");
      break;
    case 3: // Item 3
      Serial.println("Item 3 selected");
      break;
    default:
      Serial.println("Unknown item selected");
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

// initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  dht.begin();
 }

void gettemperature() {
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= interval) {
		// save the last time you read the sensor 
		previousMillis = currentMillis;

		// Reading temperature for humidity takes about 250 milliseconds!
		// Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
		
		// Get temperature event and print its value.
		sensors_event_t event;
		dht.temperature().getEvent(&event);
		if (isnan(event.temperature)) {
			Serial.println("Error reading temperature!");
		}
		else {
			Serial.print("Temperature: ");
			Serial.print(event.temperature);
			Serial.println(" *C");
		}
		// Get humidity event and print its value.
		dht.humidity().getEvent(&event);
		if (isnan(event.relative_humidity)) {
			Serial.println("Error reading humidity!");

		
		Blynk.virtualWrite(V0, event.temperature);
		Blynk.virtualWrite(V1, event.relative_humidity);

		// Check if any reads failed and exit early (to try again).
		if (isnan(event.relative_humidity) || isnan(event.temperature)) {
			Serial.println("Failed to read from DHT sensor!");
			return;
		}
	}
}


}

void loop()
{
  Blynk.run();
 
  gettemperature();
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    Serial.println ("On");
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    Serial.println ("Off");

	
  }
}
