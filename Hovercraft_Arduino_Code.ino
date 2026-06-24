#include <Servo.h>

Servo ESC_up;
Servo ESC_down;
const int receiver_pin_brushless_up = 3;
const int receiver_pin_brushless_down = 4;
const int brushless_up_pin = 6;
const int brushless_down_pin = 7;
unsigned long pulse_duration_2;
unsigned long pulse_duration_3;
const int duration_max_2 = 1985;
const int duration_min_2 = 1490;
const int duration_max_3 = 1980;
const int duration_min_3 = 1540;
int pwm_2;
int pwm_3;
#define led 11
const int trigger_pin = 9;
const int echo_pin = 10;
long duration;
long cm;
int threashold = 20;

void setup() {
  // put your setup code here, to run once:
  pinMode(receiver_pin_brushless_up,INPUT);
  pinMode(receiver_pin_brushless_down,INPUT);
  ESC_up.attach(brushless_up_pin,1000,2000);
  ESC_down.attach(brushless_down_pin,1000,2000);
  pinMode(led,OUTPUT);
  pinMode(trigger_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);
  cm = duration/58;

  if (cm > threashold){
    pulse_duration_2 = pulseIn(receiver_pin_brushless_up,HIGH);
    pwm_2 = map(pulse_duration_2,duration_min_2,duration_max_2,0,180);
    ESC_up.write(pwm_2);
  }
  else{
    ESC_up.write(0);
  }

  pulse_duration_3 = pulseIn(receiver_pin_brushless_down,HIGH);
  pwm_3 = map(pulse_duration_3,duration_min_3,duration_max_3,0,180);
  ESC_down.write(pwm_3);
  
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.00 / 1023.00) * 3; // Convert the reading values from 5v to suitable 12V i
  // If voltage is below 11V turn on the LED
  if (voltage < 11) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}
