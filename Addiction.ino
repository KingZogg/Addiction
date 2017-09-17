#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial /* Comment this out to disable prints and save space */

#define DHT11_PIN 15
#define DHTTYPE DHT11

#define PIN_Temperature V0
#define PIN_Humidity V1
bool isFirstConnect = true;

DHT_Unified dht(DHT11_PIN, DHTTYPE);




// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "9dc40c70df194d6cbdf469efcfc2193e";
BlynkTimer timer;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "GamerShrimp-25G";
char pass[] = "combatwombat$$$###combatwombat";

// Use Virtual pin 5 for uptime display


// This function tells Arduino what to do if there is a Widget
// which is requesting data for Virtual Pin (5)


// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  1;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void reconnectBlynk() {
	if (!Blynk.connected()) {
		if (Blynk.connect()) {
			BLYNK_LOG("Reconnected");
		}
		else {
			BLYNK_LOG("Not Connected");
		}
	}
}


void getTempHumid()
{
	getTemperatureAndHumidity();
	
}

void getTemperatureAndHumidity() {
	    int Humidity = 0;
	    int Temperature = 0;
	
		BLYNK_READ(PIN_Humidity);
		BLYNK_READ(PIN_Temperature);
				
		// Get temperature event and print its value.
		sensors_event_t event;
		Temperature = dht.temperature().getEvent(&event);
		
		if (isnan(event.temperature)) {
			Serial.println("Error reading temperature!");
		}
		else {
			Serial.print("Temperature: ");
			Serial.print(event.temperature);
			Serial.println(" *C");
		}
		// Get humidity event and print its value.
		Humidity = dht.humidity().getEvent(&event);
		if (isnan(event.relative_humidity)) {
			Serial.println("Error reading humidity!");
				
		Blynk.virtualWrite(PIN_Humidity, Temperature);
		Blynk.virtualWrite(PIN_Temperature, Humidity);
		
		
		// Check if any reads failed and exit early (to try again).
		if (isnan(event.relative_humidity) || isnan(event.temperature)) {
			Serial.println("Failed to read from DHT sensor!");
			return;
		}
	}
}


BLYNK_CONNECTED() {
	if (isFirstConnect) {
		Blynk.syncAll();
		Blynk.notify("STARTING");
		isFirstConnect = false;
	}
}

void setup()
{

	Serial.begin(9600);
	Serial.println("Serial Begin");

	Blynk.begin(auth, ssid, pass);
	// You can also specify server:
	//Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
	//Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

	timer.setInterval(1000L, getTempHumid);
	timer.setInterval(30000L, reconnectBlynk);  // check every 30s if still connected to server  
												// initialize the LED pin as an output:
	pinMode(ledPin, OUTPUT);
	// initialize the pushbutton pin as an input:
	pinMode(buttonPin, INPUT);

	dht.begin();

}



void loop()
{
	Blynk.run();
	timer.run(); // Initiates BlynkTimer
	
}
