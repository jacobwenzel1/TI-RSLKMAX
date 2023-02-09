/********************************************************************
 * Name(s): Jacob Wenzel, Grayson Latham
 * Class: ECGR 4161 Intro to Robotics
 * Lab: 4
 * Group: 1
 * Date: 2.9.23
 * File: wenzel_latham_lab4
 * Coded by Jacob Wenzel and Grayson Latham
 * with help from TI and the simpleRSLK library.
 * 
 * Objective: Wait until RIGHT button is pressed.
 * Drive straight until and object is detected.
 * Turn 180 degrees in place.
 * Drive straight back the same distance and turn 180.
 * Pose for a perfect score
 ********************************************************************/
 
#include "SimpleRSLK.h"

#define WHEELSPEED 6 //default wheelspeed both
#define WHEELSPEED_L 16 //default speed for left motor
#define WHEELSPEED_R 16 //default speed for right motor
#define PULSES_1CM 16 //number of pulses for 1cm straight
#define PULSESPERDEGREE 2 //number of pulses to turn one degree
#define ENCODER_DIFF 16 //the difference between wheel encoders to cause an adjustment
#define COUNT_PER_REV 360 //encoder pulses in one wheel rotation
#define WHEEL_CIRC 22 //circumference of the wheels in cm

uint16_t distanceTravelled = 0; //distance in cm based on encoder counts

void setup() {
  // put your setup code here, to run once:
  setupRSLK(); //setup functions given
  setupWaitBtn(LP_RIGHT_BTN); //setup wait button RIGHT
}

void loop() {
  // put your main code here, to run repeatedly: 
  waitBtnPressed(LP_RIGHT_BTN,"",RED_LED); //wait until button is pressed
  delay(2000); //delay for 2 seconds
  driveStraight(); //drive straight until an object is detected and record distance
  delay(3000); //delay for 3 seconds
  turnCCW(180); //turn 180 degrees counter clockwise
  delay(2000); //delay for 2 seconds
  driveStraight(distanceTravelled); //drivestraight distanceTravelled cm
  delay(2000); //delay 2 seconds
  turnCCW(180); //turn 180 degrees counter clockwise
  delay(2000); //delay(2000); //delay 2 seconds
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
  delay(200); //small delay
}

/*******************************************************************
 * Function Name: driveStraight
 * Description: Drives straight until an object is detected and
 * records the distance travelled in cm
 * Input: none
 * Return: void
 *******************************************************************/
void driveStraight() {
  uint16_t l_motor_speed = WHEELSPEED_L; //set speed for left motor
  uint16_t r_motor_speed = WHEELSPEED_R; //set speed for right motor
  uint16_t l_totalCount = 0; //initialises left count to zero
  uint16_t r_totalCount = 0; //initialises right count to zero
  uint16_t count = 0; //initialize count for distance calculation

  resetLeftEncoderCnt(); resetRightEncoderCnt(); //reset encoder counts to zero
    setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD); //set motor direction to forward
    enableMotor(BOTH_MOTORS); //turn on the motors
    setMotorSpeed(LEFT_MOTOR, l_motor_speed); //set left motor speed
    setMotorSpeed(RIGHT_MOTOR, r_motor_speed); //set right motor speed

  //while there is no object detected
  while(!objectDetected()) {
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
    count = (l_totalCount + r_totalCount) / 2; //get the average number of pulses between two encoders
  }
  distanceTravelled = (count - 0.5) / PULSES_1CM; //calculate distance in cm for global variable
  disableMotor(LEFT_MOTOR); //disable left motor
  disableMotor(RIGHT_MOTOR); //disable right motor
}

/*******************************************************************
 * Function Name: turnCCW
 * Description: Turns the vehicle degrees degrees CCW
 * Input: degrees:  turnDegrees degrees to turn
 * Return: void
 *******************************************************************/
void turnCCW(uint16_t turnDegrees) {
  uint16_t l_totalCount = 0; //pulse count for left motor
  uint16_t r_totalCount = 0; //pulse count for right motor
  uint16_t pulsesForTurn = turnDegrees * PULSESPERDEGREE; //calculate pulses needed for turn

  resetLeftEncoderCnt(); resetRightEncoderCnt(); //set encoders back to zero
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD); //set right motor direction to forward
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD); //set left motor direction to backward
  enableMotor(BOTH_MOTORS); //enable both motors
  setMotorSpeed(BOTH_MOTORS, WHEELSPEED); //set the motor speed

  //while the mototrs are less than pulsesForTurn
  while( (l_totalCount < pulsesForTurn) || (r_totalCount < pulsesForTurn) ) {
    //set the current encoder counts
    l_totalCount =  getEncoderLeftCnt(); r_totalCount = getEncoderRightCnt();

    //stop motors if pulses are reached
    if(l_totalCount >= pulsesForTurn) disableMotor(LEFT_MOTOR);
    if(r_totalCount >= pulsesForTurn) disableMotor(RIGHT_MOTOR);
  }
  delay(200); //small delay
}

/*******************************************************************
 * Function Name: objectDetected
 * Description: returns true if either of the middle two bump switches
 * are detected
 * Input: none
 * Return: bool detected
 *******************************************************************/
bool objectDetected() {
  bool button2 = isBumpSwitchPressed(2); //variable for bump switch 2
  bool button3 = isBumpSwitchPressed(3); //variable for bump switch 3
  bool detected = false; //return value
  //if either bump switch is pressed
  if (button2 || button3) {
    detected = true; //set detected to true
  }else {
    detected = false; //set detected to false
  }
  return detected;
}
