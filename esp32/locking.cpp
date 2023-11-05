/*
Steps

Start signal:
- Servo turns 90 degrees upon getting start signal

Stop signal:
- Stop signal is retrieve
    - Photoresistor senses to see if theres light 
        - If light is sensed then buzzer will start buzzing 
        - Else if no light is sensed then servo will turn 90 degrees backwards to original position
*/


#include <Servo.h>

const int servoPin = 9; 
const int buzzerPin = 8; 
const int photoresistorPin = A0; 
const int lightThreshold = 500;

bool isStarted = false;

Servo myServo;
void setup(){
    myServo.attach(servoPin);
    pinMode(buzzerPin, OUTPUT);
    pinMode(photoresistorPin, INPUT);
    Serial.begin(9600);
}

void loop(){
    if (Serial.avaliable() > 0){
        char command = Serial.read(); 

        if(command == 'start'){
            myServo.write(90);
            isStarted = ture;
        }else if(command == 'stop'){
            checkPhotoresistor();
        }
    }
}

void checkPhotoresistor(){
    int lightlevel = analogRead(photoresistorPin);
    Serial.print("Light level: ");
    Serial.println(lightlevel);

    if(lightLevel > lightThreshold){
        digitalWrite(buzzerPin, HIGH);
    }else{
        if(isStarted){
            myServo.write(0);
            isStarted = false;
        }
        digitalWrite(buzzerPin, LOW);
    }

}