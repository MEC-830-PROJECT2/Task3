#include<Servo.h>
//Stepper Motor Variable Declaration
const int in1=9;
const int in2=10;
const int in3=11;
const int in4=12;
int k=0;
int step_num=0;

//Ultrasonic Sensor Variable Declaration
const int trigPin=6;
const int echoPin=8;
long duration;
double distance;

//Servo Motor Variable Declaration
Servo servo;
int Rot=0;


void setup() {
  // put your setup code here, to run once:
  //Stepper Motor Pins
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  //Ultrasonic Sensor Pins
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  //Servo Pins
  servo.attach(9);
  servo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  //read the distance and if its 15cm away from the can, start obstacle avoidance
  Dist();
  if (distance < 15) {
    obstacleAvoidance();
  }
}


void obstacleAvoidance() {
  int ServoLeftMax = 0, ServoRight45 = 90 + 45, ServoStraight = 90;
  //variables servoleftmax,servoright45,servostraight will be different for everyone.
  //start by turning the wheel all the way to the left
  //rotate stepper forward by ~2degrees and then turn the wheel right by 1 degree. repeat until wheel is 45 degrees right.
  for (int i = ServoLeftMax; i < ServoRight45 ; i++) {

    servo.write(i);
    while (k < 10) {
      OneStep(false);
      delay(2);
      k = k + 1;
    }
  }
  //then start straightening the car
  //move wheel back from 45 degrees right to straight
  for (int i = ServoRight45; i < ServoStraight ; i--) {
    servo.write(i);
    while (k < 10) {
      OneStep(false);
      delay(2);
      k = k + 1;
    }
  }
}

void Dist(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;
  Serial.print(distance);
  if (distance ==1196){
    distance=0;
    
  }

}



//Stepper Motor Control Per step
void OneStep(bool dir){
  if(dir){
    switch(step_num){
      case 0:
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
      case 1:
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
      case 2:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      break;
      case 3:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;
    }
  }
  else{
      switch(step_num){
      case 0:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;
      case 1:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      break;
      case 2:
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
      case 3:
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
    }
  }
  step_num++;
  if(step_num>3){
    step_num=0;
  }
}
