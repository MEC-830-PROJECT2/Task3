#include <Servo.h>
#include "SR04.h"
//#include "IRremote.h"
#include "Stepper.h"

#define TRIG_PIN 7
#define ECHO_PIN 6
#define IR_PIN 2
#define SERVO_PIN 5
#define LED1_PIN 4
#define LED2_PIN 3
#define STEPS  32

Servo servo_1; // servo controller
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
Stepper stepper(STEPS, 8, 10, 9, 11);

double Dist;
int REV = 2048;
int fwd = 60, lft = 30, rgt = 90;
bool done = false;

void setup() {
  stepper.setSpeed(500); //Max seems to be 500
  servo_1.attach(SERVO_PIN);
  servo_1.write(fwd);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
}

void loop() {
  Dist = sr04.Distance();
  if (Dist < 10) {
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
  } else {
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
  }
  if ((!done) && (Dist < 30)) {
    delay(1000);
    obstacleAvoidance();
    done = true; //"done" is so that it doesnt repeat obstacle avoidance again
  } else if ((!done) && (Dist > 30)) {
    stepper.step(.1 * REV); //it looks for an obstacle
  } else if ((done) && (Dist > 10)) {
    stepper.step(.1 * REV); //after obstacle avoidance it keeps going to reach the end of track
  } else if ((done) && (Dist < 10)) {
    //place a wall at the end of the track so that it does nothing when it reaches it
  }

}

void obstacleAvoidance() {

  servo_1.write(rgt);
  stepper.step(.5 * REV);
  servo_1.write(fwd);
  stepper.step(REV);
  servo_1.write(lft);
  stepper.step(2.5 * REV);
  servo_1.write(fwd);
  stepper.step(.5 * REV);
  servo_1.write(rgt);
  stepper.step(.2 * REV);
  servo_1.write(fwd);
  stepper.step(REV);

}
