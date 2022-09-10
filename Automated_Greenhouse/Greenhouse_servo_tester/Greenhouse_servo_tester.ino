#include <Servo.h>
Servo servo_rain;
Servo servo_water;

int Moisture_Sensor = A0; 
int Rain_Sensor = A1;

int MoistureLimit = 400; 
int DetectRain = 300; 

void setup() {
  Serial.begin(9600);

  servo_rain.attach(3);
  servo_water.attach(12);

}

void loop() {

  float Rainfall = analogRead(Rain_Sensor);
  float Moisture = analogRead(Moisture_Sensor);
  
  Serial.print(Rainfall);
  Serial.println(Moisture);
  
  servo_rain.write(5);  // Open rain cover
  delay(2000);
  servo_rain.write(92);  // Close rain cover
  delay(2000);
  
  servo_water.write(110);  // Close water
  delay(2000);
  servo_water.write(60);  // Open water
  delay(2000);

}
