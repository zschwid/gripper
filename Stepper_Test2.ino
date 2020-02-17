// Include the Arduino Stepper Library
#include <Stepper.h>
#include <rocs.hpp>

// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper step1(stepsPerRevolution, 4, 5, 6, 7);
Stepper step2(stepsPerRevolution, 8, 9, 10, 13);
Stepper step3(stepsPerRevolution, 11, 3, 12, 2);

enum stateType {
  forward,
  back,
  hold
};

stateType motor1State = hold;
stateType motor2State = hold;
stateType motor3State = hold;

void runMotor1(stateType state) {
  switch(state){
    case forward:
    step1.step(-1);
    break;
    case back:
    step1.step(1);
    break;
  }
  
}

void runMotor2(stateType state) {
  switch(state){
    case forward:
    step2.step(-1);
    break;
    case back:
    step2.step(1);
    break;
  }
}


void runMotor3(stateType state) {
  switch(state){
    case forward:
    step3.step(-1);
    break;
    case back:
    step3.step(1);
    break;
  }
}

stateType int2Enum (int i) {
  stateType ret;
  switch(i) {
    case 0:
      ret = back;
    break;
    case 1:
      ret = hold;
    break;
    case 2:
      ret = forward;
    break;
  }
  return ret;
}


void setup()
{
  // set the speed at 360 rpm:
  step1.setSpeed(300);
  step2.setSpeed(300);
  
  rocs::init(0x03, "ptaGripper", 10);
  rocs::set_write_handler(write_handler);
  
  // initialize the serial port:
  Serial.begin(9600);
  
  
}

void loop() 
{
  runMotor1(motor1State);
  runMotor2(motor2State);
  runMotor3(motor3State);
}
void write_handler(uint8_t reg, uint8_t val) {
  stateType newState = int2Enum(val);
  switch(reg) {
    case 1:
    motor1State = newState;
    break;
    case 2:
    motor2State = newState;
    break;
    case 3:
    motor3State = newState;
    break;
  }
}
