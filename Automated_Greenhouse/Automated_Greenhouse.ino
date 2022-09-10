#include <Servo.h>
Servo servo_rain;
Servo servo_water;
#include "DHT.h"

#define DHTPIN A2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

int Moisture_Sensor = A0; 
int Rain_Sensor = A1;

int MoistureLimit = 200; 
int DetectRain = 500; 

void setup() {
  Serial.begin(9600);

  servo_rain.attach(3);
  servo_water.attach(12);

  servo_rain.write(5);  // Open rain cover
  servo_water.write(115);  // Close water

  dht.begin();
}

void loop() {
  float Rainfall = analogRead(Rain_Sensor);
  float Moisture = analogRead(Moisture_Sensor);

  Serial.print("Rainfall: ");
  Serial.print(Rainfall);
  Serial.print("   Moisture: ");
  Serial.print(Moisture);
  Temp_Humidity();
  
  if (Rainfall > DetectRain) {  // No rain
    servo_rain.write(5);  // Open rain cover
    
    if (Moisture < MoistureLimit) { // Enough water
      servo_water.write(115);  // Close water
    }
    else {  // Not enough water
      Serial.println("Watering Plant");
      servo_water.write(60);  // Open water
      delay(3000);
      servo_water.write(115);  // Close water
      delay(3000);
    }
  }
  
  else if (Rainfall <= DetectRain) { // Raining
    if (Moisture < MoistureLimit) {  // Enough water
      servo_rain.write(92);  // Close rain cover
      Serial.println("Blocking Rain");
    }
    else {  // not enough water
      servo_rain.write(5);  // Open rain cover
      Serial.println("Letting Rain Through");
      delay(3000);
      servo_rain.write(92);  // Close rain cover
      delay(3000);
    }
  }

  delay(100);
}
int Temp_Humidity(){ 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(false);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("   Humidity: "); 
  Serial.print(h);
  Serial.print(" %");
  Serial.print("   Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
}
