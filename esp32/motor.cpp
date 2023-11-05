#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>

const char* ssid = "Xiao Izzy (SM-G950W6332)";
const char* password = "spy0961";
WebServer server(80);
const int TRIG_PIN = 33;
const int ECHO_PIN = 35;
const int MOTOR_IN1 = 17;
const int MOTOR_IN2 = 16;
const int WHEEL_ENABLE_A = 4;
    int speed = 5;

const unsigned int MAX_DIST = 200;

NewPing sensor(TRIG_PIN, ECHO_PIN, MAX_DIST);

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.on("start", HTTP_GET, []() {
    server.send(200, "text/plain", "Motor started");
    goVroom();
  });

  // Route to handle stopping the motor
  server.on("stop", HTTP_GET, []() {
    server.send(200, "text/plain", "Motor stopped");
    digitalWrite(motorPin, LOW); // Stop the motor
  });
  server.begin();
  
}

void goVroom(){
  float cm;
  float inches;
  cm = sensor.ping_cm();
  inches = sensor.ping_in();
  // Print out results
  if ( cm < 5 && cm > 0) {
    // too close
    speed = 0;
    digitalWrite(WHEEL_ENABLE_A, LOW);
  } else {
    analogWrite(WHEEL_ENABLE_A, speed);
    // digitalWrite(WHEEL_ENABLE_A, HIGH);
    if (speed < 250){
    speed += 5;
    }
  }
    Serial.print(cm);
    Serial.println(" cm \t");

  // Wait at least 60ms before next measurement
    delay(60);
}

void setup() {
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(WHEEL_ENABLE_A, OUTPUT);
  digitalWrite(MOTOR_IN1, LOW); // need to check direction
  digitalWrite(MOTOR_IN2, HIGH);
  digitalWrite(WHEEL_ENABLE_A, LOW);
  connectToWiFi();
  Serial.begin(115200);
}

void loop() {

  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://localhost:${3000}"); 
    int httpCode = http.GET();

    if(httpCode == 300) {
      String response = http.getString();
      if(response == "true") {
        delay(1000); 
        goVroom();
      }else{
        delay(1000); 
        digitalWrite(WHEEL_ENABLE_A, LOW);
      }
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  }
  delay(10000); 
}


