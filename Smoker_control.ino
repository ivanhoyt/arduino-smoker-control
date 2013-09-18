#include <Servo.h>

Servo damperServo;
//const int sensorPin = A0;
const int damperServoPin = 9;
const int fanPin = 3;
const int fanFull = 255;
const int fanHalf = 127;
const int fanOff = 0;
const float targetTempF = 225.0;
const int damperFullOpen = 179;
const int damperThreeQuarters = 134;
const int damperHalf = 89;
const int damperQuarter = 44;
const int damperClosed = 0;
const int firePin = A1;
int firePotVal;
int temperatureF;

void setup(){
  // open a serial port
  Serial.begin(9600);

  // attach servo to digital pin
  damperServo.attach(damperServoPin);
  
  // set fanPin to be an OUTPUT
  pinMode(fanPin, OUTPUT);
}

void loop(){
  // set firePotVal to value from firePin (analog pin)
  firePotVal = analogRead(firePin);
  
  // map firePotVal to degrees in F range
  temperatureF = map(firePotVal, 0, 1023, 65, 350);
//  
//  // setting sensorVal to be equal to value of sensor pin
//  int sensorVal = analogRead(sensorPin);
//  
//  Serial.print("\nSensor Value: ");
//  Serial.print(sensorVal);
//  
//  // setting voltage from sensorVal
//  float voltage = (sensorVal/1024.0) * 5.0;
//  
//  Serial.print(", Volts: ");
//  Serial.print(voltage);
//  
//  // setting temperature C from voltage
//  float temperatureC = (voltage - .5) * 100;
//   
//  Serial.print(", degrees C: ");
//  Serial.print(temperatureC);
//  
//  // setting temperature F from temperature C
//  float temperatureF = (temperatureC * 1.8) + 32.0;
  
  Serial.print("\nDegrees F: ");
  Serial.print(temperatureF);
  
  if(temperatureF >= 300){
    damperServo.write(damperClosed);
    analogWrite(fanPin, fanOff);
  } else if(temperatureF < 300 && temperatureF >= 265){
    damperServo.write(damperQuarter);
    analogWrite(fanPin, fanOff);
  } else if(temperatureF < 265 && temperatureF >= 225){
    damperServo.write(damperHalf);
    analogWrite(fanPin, fanOff);
  } else if(temperatureF < 225 && temperatureF >= 180){
    damperServo.write(damperThreeQuarters);
    analogWrite(fanPin, fanHalf);
  } else {
    damperServo.write(damperFullOpen);
    analogWrite(fanPin, fanFull);
  }
  
  delay(1000);
}
