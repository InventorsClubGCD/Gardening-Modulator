#include "DHT.h"

#define DHTPIN A2
#define DHTTYPE DHT22
#define moisture_Sensor A0
#define rain_Sensor A1
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
 
  dht.begin();

  pinMode(moisture_Sensor,INPUT);
  pinMode(rain_Sensor,INPUT);
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print("  Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");

  float moisture_Read = analogRead(moisture_Sensor);
  float rain_Read = analogRead(rain_Sensor);

  Serial.print("  Moisture: "); 
  Serial.print(moisture_Read);
  Serial.print("  Rain: "); 
  Serial.println(rain_Read);
  
}
