#include <Servo.h>

Servo ESC_up; // Create servo object to control the ESC for the thrust motor
Servo ESC_down; // Create servo object to control the ESC for the lift motor
const int receiver_pin_brushless_up = 3;
const int receiver_pin_brushless_down = 4;
const int brushless_up_pin = 6;
const int brushless_down_pin = 7;
unsigned long pulse_duration_2;
unsigned long pulse_duration_3;
const int duration_max_2 = 1985; // Define a variable for max pulse duration value from the controller for the thrust motor
const int duration_min_2 = 1490; // Define a variable for min pulse duration value from the controller for the thrust motor
const int duration_max_3 = 1980; // Define a variable for max pulse duration value form the controller for the lift motor
const int duration_min_3 = 1540; // Define a variable for min pulse duration value from the controller for the lift motor
int pwm_2;
int pwm_3;
#define led 11
const int trigger_pin = 9;
const int echo_pin = 10;
long duration;
long cm;
int threashold = 20; // Obstacle distance threashold in cm

// Perform once
void setup() {
  pinMode(receiver_pin_brushless_up,INPUT); // Receive signal from the controller for the thrust motor
  pinMode(receiver_pin_brushless_down,INPUT); // Receive signal from the controller for the lift motor
  ESC_up.attach(brushless_up_pin,1000,2000); // Send signal to the ESC for the thrust motor
  ESC_down.attach(brushless_down_pin,1000,2000); // Send signal to the ESC for the lift motor
  pinMode(led,OUTPUT);
  pinMode(trigger_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
}

// Perform repeatedly
void loop() {
  digitalWrite(trigger_pin, LOW); // Clear the trigger pin
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH); // Trigger the sensor
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW); // End the sound-wave transmission

  duration = pulseIn(echo_pin, HIGH); // Read pulse duration from the echo pin of the ultrasonic sensor
  cm = duration/58; // Convert pulse duration to distance in cm

  // Check the obstacle distance and control the thrust motor
  if (cm > threashold){
    pulse_duration_2 = pulseIn(receiver_pin_brushless_up,HIGH);
    pwm_2 = map(pulse_duration_2,duration_min_2,duration_max_2,0,180);
    ESC_up.write(pwm_2);
  }
  else{ 
    ESC_up.write(0);
  }

  // Control the lift motor
  pulse_duration_3 = pulseIn(receiver_pin_brushless_down,HIGH);
  pwm_3 = map(pulse_duration_3,duration_min_3,duration_max_3,0,180);
  ESC_down.write(pwm_3);
  
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.00 / 1023.00) * 3; // Convert the reading values from 5V to suitable 12V
  // Check the battery voltage and control the LED
  if (voltage < 11) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}
