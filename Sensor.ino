#include <PID_v1.h>
#include <NewPing.h>

// Pins
const int TRIG_PIN = 33;
const int ECHO_PIN = 35;
const int MOTOR_IN1 = 17;
const int MOTOR_IN2 = 16;
const int WHEEL_ENABLE_A = 4;
    int speed = 5;


// Anything over 200cm is cutoff
const unsigned int MAX_DIST = 200;

NewPing sensor(TRIG_PIN, ECHO_PIN, MAX_DIST);

void setup() {


  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(WHEEL_ENABLE_A, OUTPUT);

  digitalWrite(MOTOR_IN1, LOW); // need to check direction
  digitalWrite(MOTOR_IN2, HIGH);
  digitalWrite(WHEEL_ENABLE_A, LOW);

  //p17 to in2
  //p16 to in1
  //emable to 4

  /*
  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  //Set Echo pin as input to measure the duration of 
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN, INPUT);

  // We'll use the serial monitor to view the sensor output
  */
  Serial.begin(115200);
}

void loop() {

  float cm;
  float inches;
  /*
  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;

  */
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
