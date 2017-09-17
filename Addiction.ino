// This is code for ESP8266 with DHT22 senzor on port D4 (IO2) using blynk cloud solution for data representation with OLED wemos D1 mini shield.
// Version 1.0
// by Miro Smola, smolam@gmail.com
#define BLYNK_PRINT Serial  // you can comment out, its for terminal window only
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
//#include <Wire.h>


#define DHTPIN 4                                            // port where DTH22 is connected (D4 is IO2 on wemos D1 mini)
#define DHTTYPE DHT11                                       // I use DHT22, change to other DHT senzor if you use other one
DHT dht(DHTPIN, DHTTYPE);                                   // enabled DHT sensor

char auth[] = "9dc40c70df194d6cbdf469efcfc2193e";                                       // Your Blynk authentication string

char ssid[] = "GamerShrimp-25G";
char pass[] = "combatwombat$$$###combatwombat";

SimpleTimer timer;                                          // enable simple timer


void setup()
{
	Serial.begin(9600);                                       // Enabled serial debugging output
	Blynk.begin(auth, ssid, pass);                            // Connects to wifi and Blynk services


	timer.setInterval(1000L, sendTemperature);               // every 10 seconds run function sendTemperature

}

void sendTemperature()                                      // function send temperature
{
	float h = dht.readHumidity();                             // reads humidity from senzor and save to h
	float t = dht.readTemperature();                          // reads temperature from senzor and save to t

	Serial.println(t);
	Serial.println(h);

	if (isnan(h) || isnan(t)) {                               // checks if readings from sensors were obtained
		Serial.println("Can't read sensor");// cant read sensor
	}
	else {
		Blynk.virtualWrite(0, t);                                 // send to Blynk virtual pin 1 temperature value
		Blynk.virtualWrite(1, h);                                 // send to Blynk virtual pin 3 humidity value

	}
}

void loop()
{
	Blynk.run();                                              // run blynk
	timer.run();                                              // run timer
}
