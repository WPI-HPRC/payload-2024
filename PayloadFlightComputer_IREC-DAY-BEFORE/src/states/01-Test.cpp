#include "State.h"
#include "01-Test.h"


Test::Test(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void Test::initialize_impl() {
	Serial.println("Initialized"); 
}

void Test::loop_impl()
{
	Serial.print("Servo 1 Analog:\t" + analogData.servo1);
	Serial.print("\tServo 2 Analog:\t" + analogData.servo2); 
	Serial.print("\tServo 3 Analog:\t" + analogData.servo3); 
	Serial.println("\tServo 4 Analog:\t" + analogData.servo4);   

    if(currentTime < 1500){
		this->servos->paraServo_3->writeServo(SERVO_COUNTER_WIND); 
		this->servos->paraServo_4->writeServo(SERVO_CLOCK_WIND);  
    }

    else if(currentTime > 1500 && currentTime < 3000){
		this->servos->paraServo_1->writeServo(SERVO_COUNTER_WIND); 
		this->servos->paraServo_2->writeServo(SERVO_CLOCK_WIND); 
	}

    else if(currentTime > 3000 && currentTime < 4500){
		this->servos->paraServo_1->writeServo(SERVO_CLOCK_WIND); 
		this->servos->paraServo_2->writeServo(SERVO_COUNTER_WIND); 
        this->servos->paraServo_3->writeServo(SERVO_CLOCK_WIND); 
		this->servos->paraServo_4->writeServo(SERVO_COUNTER_WIND); 
	}
    

	else{
		this->servos->paraServo_1->writeServo(SERVO_CENTER); 
		this->servos->paraServo_2->writeServo(SERVO_CENTER);  
        this->servos->paraServo_3->writeServo(SERVO_CENTER); 
		this->servos->paraServo_4->writeServo(SERVO_CENTER);  
	}
  
}

State *Test::nextState_impl()
{
    return nullptr;
}

enum StateId Test::getId()
{
    return StateId::ID_Test;
}
