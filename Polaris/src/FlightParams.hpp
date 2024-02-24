#pragma once 
// These constants define transitions between states and the conditions for those transitions

// PreLaunch -------------------------
// PreLaunch to Launch Conditions
    // average Z acceleration > LAUNCH_ACCEL_THRESHOLD
// Cannot go to Abort state from PreLaunch

// measured in G's
// checking if average Z acceleration is greater than 4 G's

#define LAUNCH_ACCEL_THRESHOLD 4.0

#define LANDING_VELOCITY 5.0

//Payload Specific- will organize tonight 

#define PARACHUTE_SERVO_1 10 //Check these
#define PARACHUTE_SERVO_2 13
#define PARACHUTE_SERVO_3 11
#define PARACHUTE_SERVO_4 12

#define PARACHUTE_SERVO_1_IN 16 //Check these
#define PARACHUTE_SERVO_2_IN 17
#define PARACHUTE_SERVO_3_IN 21
#define PARACHUTE_SERVO_4_IN 20

#define PARACHUTE_SERVO_1_DIR true //Check these 
#define PARACHUTE_SERVO_2_DIR false
#define PARACHUTE_SERVO_3_DIR true
#define PARACHUTE_SERVO_4_DIR false

#define SERVO_GAIN 0.5

#define PULLEY_D 4.374
#define STRING_BASE_LENGTH 100

#define CAMERA_SERVO 9 //Also check this 
#define CAM_OUT 0
#define CAM_RETRACT 0

#define IR_PIN 45

#define ALT_THRESHOLD_STOWED 396 //meters

#define MAX_STABALIZE_TIME 5000
#define MAX_FREEFALL_TIME 10000

#define MAX_SERVO_POS 0
#define MAX_SERVO_WIND_TIME 0 

#define MAX_HOLD_TIME 0

#define DESIRED_STRING_LENGTH 70

//Trajectory Constants 

#define GRAV 9.81
#define MASS 5.5; // [kg] Total system mass
#define D_P 1.8288; // [m] Diameter of Parachute
#define S_P (PI/4) * (D_P*D_P); // [m^2] Surface Area of Parachute 
#define C_D 0.7; // Coefficient of drag
#define W_P GRAV * MASS;
#define H_CP 2; // [m] Distance from center of mass to center of pressure



