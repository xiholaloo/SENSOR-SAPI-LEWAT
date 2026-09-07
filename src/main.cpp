#include <Arduino.h>
#include <ESP32Servo.h>

const int buzzerPin = 4;
const int PIRPin = 13;
const int ledPin = 2; 
Servo myservo;

bool previousPIRState = false;

void setup() {
  Serial.begin(115200);
  myservo.attach(18);
  pinMode(buzzerPin, OUTPUT);
  pinMode(PIRPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  myservo.write(90); //awal servo 90 derajat
  Serial.println("Menunggu sensor PIR untuk mendeteksi gerakan...");
}

void loop() {
 int pirState = digitalRead(PIRPin);
  if (pirState == HIGH) {
    if (!previousPIRState){                         // pakai (previousPIRState == false) juga bisa
      for (int i = 90; i >= 0; i--) {
        myservo.write(i);
        delay(15);
        }
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPin, HIGH); 
      Serial.println("Sapi Lewat");
      delay(2000);
      }
    previousPIRState = true;
  } 
  else {
    if(previousPIRState){
      for (int i = 0; i <= 90; i++) {
        myservo.write(i);
        delay(15);
        } 
    digitalWrite(buzzerPin, LOW);
    Serial.println("Tidak ada gerakan - Buzzer OFF"); 
    digitalWrite(ledPin, LOW);
    }
  previousPIRState = false;
  }
delay(100);
}