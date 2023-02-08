/*
 * Name(s): Jacob Wenzel, Grayson Latham
 * Class: ECGR 4161 Intro to Robotics
 * Lab: 4
 * Group: 1
 * Due Date: 2.5.23
 * 
 * Objective: blah blah blah
 */
 
#include "SimpleRSLK.h"

#define WHEELSPEED_L 16 //default speed for left motor
#define WHEELSPEED_R 16 //default speed for right motor
#define PULSES_1CM 16 //number of pulses for 1cm straight
#define ENCODER_DIFF 16 //the difference between wheel encoders to cause an adjustment
#define COUNT_PER_REV 360 //encoder pulses in one wheel rotation
#define WHEEL_CIRC 22 //circumference of the wheels in cm

void setup() {
  // put your setup code here, to run once:
  setupRSLK();
  setupWaitBtn(LP_LEFT_BTN); //setup wait button
}

void loop() {
  // put your main code here, to run repeatedly: 
  waitBtnPressed(LP_LEFT_BTN,"",RED_LED); //wait until button is pressed
  //while (!objectDetected()) {
    driveStraight(100); //drive straight 100 cm
    //driveStraight();
    delay(1000); //delay for a second
  //}
  
}

/*******************************************************************
 * Function Name: driveStraight
 * Description: Drives straight for distancecm cm
 * Input: distancecm: distance to travel in cm
 * Return: void
 *******************************************************************/
void driveStraight(uint16_t distancecm) {
  uint16_t l_motor_speed = WHEELSPEED_L; //set speed for left motor
  uint16_t r_motor_speed = WHEELSPEED_R; //set speed for right motor
  uint16_t l_totalCount = 0; //initialises left count to zero
  uint16_t r_totalCount = 0; //initialises right count to zero
  uint16_t numPulses = 0; //total numper of pulses

  //comupute the number of pulses to drive distancecm cm
  numPulses = (uint16_t) (((float)distancecm * PULSES_1CM) + 0.5);

  resetLeftEncoderCnt(); resetRightEncoderCnt(); //reset encoder counts to zero
  setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD); //set motor direction to forward
  enableMotor(BOTH_MOTORS); //turn on the motors
  setMotorSpeed(LEFT_MOTOR, l_motor_speed); //set left motor speed
  setMotorSpeed(RIGHT_MOTOR, r_motor_speed); //set right motor speed

  //run while both wheel encoder counts are less than numPulses
  while( (l_totalCount < numPulses) || (r_totalCount < numPulses) ) {
    l_totalCount = getEncoderLeftCnt(); //set l_totalCount to current left encoder count
    r_totalCount = getEncoderRightCnt(); //set r_totalCount to current right encoder count

    //if the right motor is too fast, speed up left motor
    if((l_totalCount + ENCODER_DIFF) < r_totalCount) {
      setMotorSpeed(LEFT_MOTOR, ++l_motor_speed); //increase left motor speed by 1
      setMotorSpeed(RIGHT_MOTOR, r_motor_speed); //set right motor speed to preset value
    }
    //if the left motor is too fast, speed up right motor
    if((r_totalCount + ENCODER_DIFF) < l_totalCount) {
      setMotorSpeed(RIGHT_MOTOR, ++r_motor_speed); //increase right motor speed by 1
      setMotorSpeed(LEFT_MOTOR, l_motor_speed); //set left motor speed to preset value
    }

    //stop the motors if numPulses is reached
    if(l_totalCount >= numPulses) disableMotor(LEFT_MOTOR);
    if(r_totalCount >= numPulses) disableMotor(RIGHT_MOTOR);
  }
  delay(200);
}

/*******************************************************************
 * Function Name: driveStraight
 * Description: Drives straight until an object is detected
 * Input: distancecm: none
 * Return: void
 *******************************************************************/
void driveStraight() {
  uint16_t l_motor_speed = WHEELSPEED_L; //set speed for left motor
  uint16_t r_motor_speed = WHEELSPEED_R; //set speed for right motor
  uint16_t l_totalCount = 0; //initialises left count to zero
  uint16_t r_totalCount = 0; //initialises right count to zero


  resetLeftEncoderCnt(); resetRightEncoderCnt(); //reset encoder counts to zero
  setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD); //set motor direction to forward
  enableMotor(BOTH_MOTORS); //turn on the motors
  setMotorSpeed(LEFT_MOTOR, l_motor_speed); //set left motor speed
  setMotorSpeed(RIGHT_MOTOR, r_motor_speed); //set right motor speed


   l_totalCount = getEncoderLeftCnt(); //set l_totalCount to current left encoder count
   r_totalCount = getEncoderRightCnt(); //set r_totalCount to current right encoder count

   //if the right motor is too fast, speed up left motor
   if((l_totalCount + ENCODER_DIFF) < r_totalCount) {
     setMotorSpeed(LEFT_MOTOR, ++l_motor_speed); //increase left motor speed by 1
     setMotorSpeed(RIGHT_MOTOR, r_motor_speed); //set right motor speed to preset value
   }
   //if the left motor is too fast, speed up right motor
   if((r_totalCount + ENCODER_DIFF) < l_totalCount) {
     setMotorSpeed(RIGHT_MOTOR, ++r_motor_speed); //increase right motor speed by 1
     setMotorSpeed(LEFT_MOTOR, l_motor_speed); //set left motor speed to preset value
   }

   if (objectDetected()) {
     disableMotor(LEFT_MOTOR);
     disableMotor(RIGHT_MOTOR);
   }
}


/*******************************************************************
 * Function Name: turnCCW
 * Description: Turns the vehicle degrees degrees
 * Input: degrees: degrees to turn
 * Return: void
 *******************************************************************/
void turnCCW(uint16_t degree) {
  
}

/*******************************************************************
 * Function Name: objectDetected
 * Description: returns true if bump switch 3 or 4 are hit
 * Input: none
 * Return: bool
 *******************************************************************/
bool objectDetected() {
  if (isBumpSwitchPressed(2) || isBumpSwitchPressed(3)) {
    disableMotor(LEFT_MOTOR);
    disableMotor(RIGHT_MOTOR);
    return true;
  }
}

/*******************************************************************
 * Function Name: distanceTravelled
 * Description: 
 * Input: none
 * Return: int
 *******************************************************************/
int distanceTravelled(){
  uint16_t currentCount = (getEncoderLeftCnt() + getEncoderRightCnt()) / 2;
  float temp = (WHEEL_CIRC * currentCount) / COUNT_PER_REV;
  return temp;
}
