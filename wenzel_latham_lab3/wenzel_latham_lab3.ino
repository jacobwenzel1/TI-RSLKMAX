/*
 * Name(s): Jacob Wenzel, Grayson Latham
 * Class: ECGR 4161 Intro to Robotics
 * Lab: 3
 * Group: 1
 * Due Date: 2.2.23
 * 
 * Objective: The goal of the lab was to get some experience with coding 
 * microcontrollers and working with sensors. The challenge is to read the 
 * input from the six bump sensors provided on the RSLK robot and to perform 
 * a number of different tasks that corresponds to each sensor or a combination 
 * of those sensors. The tasks consisted of controlling red, green, and blue 
 * LED lights in an array of combinations and different timing sequences.
 */
#include "SimpleRSLK.h"

int bumperPressed = 10; //switching value used in switch case
unsigned long prevTime = 0; //value to store previous time in ms
unsigned long currentTime; //value to store the current time using millis()
int ledState = LOW; //sets initial state of an led to low
bool willRun = false; //used to store if button is pressed during specific sequence
int sequenceTime = 630; //time in between events in given sequence in ms
int bump = 10; //stores which button pressed


void setup() {
  // put your setup code here, to run once:
  setupRSLK(); //given for setup
  setupLed(RED_LED); //setup red
  setupLed(GREEN_LED); //setup green
  setupLed(BLUE_LED); //setup blue
}

void loop() {
  currentTime = millis(); //time in ms since program executed

  //if statement checks which bumper is pressed or which are pressed and sets appropriate bumperPressed value
  if (isBumpSwitchPressed(0))  { //checks for bumper 1
    if (isBumpSwitchPressed(1)) { //checks for bumpers 1 and 2
      if (isBumpSwitchPressed(2))  { //checks for bumpers 1, 2, and 3
      bumperPressed = 123;
      } else  {
        bumperPressed = 12; // sent to switch case
      }
    } else if (isBumpSwitchPressed(2))  { //checks for bumpers 1 and 3
      if (isBumpSwitchPressed(1))  { //checks for bumpers 1, 2, and 3
      bumperPressed = 123;
      } else  {
        bumperPressed = 13;
      }
    } else  {
      bumperPressed = 1;
    }
  } else if (isBumpSwitchPressed(1))  { //checks for bumper 2
    if (isBumpSwitchPressed(0)) { //checks for bumpers 1 and 2
      if (isBumpSwitchPressed(2))  { //checks for bumpers 1, 2, and 3
      bumperPressed = 123;
      } else  {
        bumperPressed = 12;
      }
    } else if (isBumpSwitchPressed(2))  { //checks for bumpers 2 and 3
      if (isBumpSwitchPressed(0))  { //checks for bumpers 1, 2, and 3
      bumperPressed = 123;
      } else  {
        bumperPressed = 23;
      }
    } else  {
      bumperPressed = 2;
    }
  } else if (isBumpSwitchPressed(2))  { //checks for bumper 3
    if (isBumpSwitchPressed(0)) { //checks for bumpers 1 and 3
      if (isBumpSwitchPressed(1))  { //checks for bumpers 1, 2, and 3
      bumperPressed = 123;
      } else  {
        bumperPressed = 13;
      }
    } else if (isBumpSwitchPressed(1))  { //checks for bumpers 2 and 3
      if (isBumpSwitchPressed(0))  { //checks for bumpers 1, 2, and 3
      bumperPressed = 123;
      } else  {
        bumperPressed = 23;
      }
    } else  {
      bumperPressed = 3;
    }
  } else if (isBumpSwitchPressed(3))  { //checks for bumper 4
    bumperPressed = 4;
  } else if (isBumpSwitchPressed(4))  { //checks for bumper 5
    bumperPressed = 5;
  }

  //switch case from bumerPressed value from above
  //used to call different light sequences
  switch(bumperPressed) {
    case 1:
    //blink red at 1 hz
    bumper1();
    break;
    case 2:
    //blink green at 2 hz
    bumper2();
    break;
    case 12:
    //blink red and green at 8 hz
    bumper12();
    break;
    case 3:
    //blink blue at 4 hz
    bumper3();
    break;
    case 13:
    //blinks red and blue at 16 hz
    bumper13();
    break;
    case 23:
    //blinks green and blue at 32 hz
    bumper23();
    break;
    case 123:
    //turns on all three colors constant
    bumper123();
    break;
    case 4:
    //blinks special given sequence
    bumper4();
    break;
    case 5:
    //turns off all LEDS
    bumper5();
    break;
  }
}
/*******************************************************************
 * Function Name: bumper1
 * Description: Sequence for when bumper 1 is pressed. Blinks the 
 *              red LED at 1 Hz
 * Input: none
 * Return: void
 *******************************************************************/
void bumper1(){
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    //blink red at 1 hz
    if(currentTime - prevTime >= 500) {
      prevTime = currentTime;
      if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(RED_LED, ledState);
    }
}
/*******************************************************************
 * Function Name: bumper2
 * Description: Sequence for when bumper 2 is pressed. Blinks the 
 *              green LED at 2 Hz
 * Input: none
 * Return: void
 *******************************************************************/
void bumper2(){
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    //blink green at 2 hz
    if(currentTime - prevTime >= 250) {
      //digitalWrite(RED_LED, HIGH);
      prevTime = currentTime;
      if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(GREEN_LED, ledState);
    }
}
/*******************************************************************
 * Function Name: bumper12
 * Description: Sequence for when bumpers 1 and 2 are pressed. Blinks the 
 *              red and green LED at 4 Hz
 * Input: none
 * Return: void
 *******************************************************************/
void bumper12(){
  digitalWrite(BLUE_LED, LOW);
  if(currentTime - prevTime >= 62.5) {
      prevTime = currentTime;
      if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(RED_LED, ledState);
    digitalWrite(GREEN_LED, ledState);
    }
    delay(200);
}
/*******************************************************************
 * Function Name: bumper3
 * Description: Sequence for when bumper 3 is pressed. Blinks the 
 *              blue LED at 4 Hz
 * Input: none
 * Return: void
 *******************************************************************/
void bumper3(){
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    //blink blue at 4 hz
    if(currentTime - prevTime >= 125) {
      prevTime = currentTime;
      if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(BLUE_LED, ledState);
    }
}
/*******************************************************************
 * Function Name: bumper13
 * Description: Sequence for when bumpers 1 and 3 are pressed. Blinks the 
 *              red and blue LED at 4 Hz
 * Input: none
 * Return: void
 *******************************************************************/
void bumper13(){
  digitalWrite(GREEN_LED, LOW);
  if(currentTime - prevTime >= 31.25) {
      prevTime = currentTime;
      if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(RED_LED, ledState);
    digitalWrite(BLUE_LED, ledState);
    }
    delay(200);
}
/*******************************************************************
 * Function Name: bumper23
 * Description: Sequence for when bumpers 2 and 3 are pressed. Blinks the 
 *              blue and green LED at 4 Hz
 * Input: none
 * Return: void
 *******************************************************************/
void bumper23(){
  digitalWrite(RED_LED, LOW);
  if(currentTime - prevTime >= 15.63) {
      prevTime = currentTime;
      if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(BLUE_LED, ledState);
    digitalWrite(GREEN_LED, ledState);
    }
    delay(200);
}
/*******************************************************************
 * Function Name: bumper123
 * Description: Sequence for when bumpers 1, 2, and 3 are pressed. 
 *              Turns on all three colors at constant
 * Input: none
 * Return: void
 *******************************************************************/

void bumper123(){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
  delay(200);
}
/*******************************************************************
 * Function Name: bumper4
 * Description: plays specific sequence given by lab with 0.63 
 *              seconds in between each stage
 * Input: none
 * Return: void
 *******************************************************************/
void bumper4(){
   //turns off all LEDs
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED, LOW);
   digitalWrite(BLUE_LED, LOW);
   delay(630); //delay for 0.63 seconds
   willRun = checkBumpers(); //checks for any bumper contacts
   digitalWrite(RED_LED, HIGH);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, HIGH);
   delay(630);
   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   //turns off all LEDs
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED, LOW);
   digitalWrite(BLUE_LED, LOW);
   delay(630);
   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, LOW);
   delay(630);
   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED, LOW);
   digitalWrite(BLUE_LED, HIGH);
   delay(630);
   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   digitalWrite(RED_LED, HIGH);
   digitalWrite(GREEN_LED, LOW);
   digitalWrite(BLUE_LED, LOW);
   delay(630);
   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   //turns off all LEDs
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED, LOW);
   digitalWrite(BLUE_LED, LOW);
   delay(630);
   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   digitalWrite(RED_LED, HIGH);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, LOW);
   delay(630);
   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   digitalWrite(RED_LED, HIGH);
   digitalWrite(GREEN_LED, LOW);
   digitalWrite(BLUE_LED, HIGH);
   delay(630);
   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, HIGH);
   delay(630);
   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   //turns off all LEDs
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED, LOW);
   digitalWrite(BLUE_LED, LOW);

   if(!willRun){
    willRun = checkBumpers(); //checks for any bumper contacts
   }
   if(willRun){
    bumperPressed = bump + 1; //sets bumper that was pressed early as next sequence up
   }
  }

/*******************************************************************
 * Function Name: bumper5
 * Description: Turns off all LEDS when pressed
 * Input: none
 * Return: void
 *******************************************************************/  
void bumper5(){
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

/*******************************************************************
 * Function Name: checkBumpers
 * Description: Check if any bumpers are pressed and if so, which one
 * Input: none
 * Return: void
 *******************************************************************/
bool checkBumpers(){
  for(int x = 0;x<TOTAL_BP_SW;x++)
    {
      /* Check if the bump switch was pressed */
      if(isBumpSwitchPressed(x) == true) {
        bump = x;
        return true;
      }
    }
}
