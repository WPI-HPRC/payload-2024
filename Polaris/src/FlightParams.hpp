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

#define PARACHUTE_SERVO_1 6 // wind counterclockwise in:2000   center:1493 wind out: 1100 //
#define PARACHUTE_SERVO_2 7 // wind clockwise in: 1100   center:1493 wind out: 2000 //
#define PARACHUTE_SERVO_3 9 // wind counterclockwise in:2000   center:1493 wind out: 1100 //
#define PARACHUTE_SERVO_4 8 // wind clockwise in:1100  center:1493 wind out: 2000 //

#define PARACHUTE_SERVO_1_IN 20 //Working //Right
#define PARACHUTE_SERVO_2_IN 21 //working
#define PARACHUTE_SERVO_3_IN 16 //Not working //Left 
#define PARACHUTE_SERVO_4_IN 17 //Not working 

#define PARACHUTE_SERVO_1_DIR false //Check these 
#define PARACHUTE_SERVO_2_DIR true  // true = CW?
#define PARACHUTE_SERVO_3_DIR false
#define PARACHUTE_SERVO_4_DIR true

#define SERVO_GAIN 0.5

#define PULLEY_D 4.374
#define STRING_BASE_LENGTH 100

#define CAMERA_SERVO 33 //Also check this 
#define CAM_OUT 2012
#define CAM_RETRACT 988

#define IR_PIN 0

#define ALT_THRESHOLD_STOWED 396 //meters

#define MAX_STABALIZE_TIME 5000
#define MAX_FREEFALL_TIME 10000

#define MAX_SERVO_POS 0
#define MAX_SERVO_WIND_TIME 0 

#define MAX_HOLD_TIME 0

#define DESIRED_STRING_LENGTH 89

//Trajectory Constants 

#define GRAV 9.81
#define MASS 5.5; // [kg] Total system mass
#define D_P 1.8288; // [m] Diameter of Parachute
#define S_P (PI/4) * (D_P*D_P); // [m^2] Surface Area of Parachute 
#define C_D 0.7; // Coefficient of drag
#define W_P GRAV * MASS;
#define H_CP 2; // [m] Distance from center of mass to center of pressure

// Analog read for parachute motors at center (longest string length),
// and at 25 cm wound
const int
      MOTOR_1_CENTER = 289, // 245, 278, 
      MOTOR_2_CENTER = 389, // 386, 384, 
      MOTOR_3_CENTER =  38, //  38,  63, 
      MOTOR_4_CENTER = 755, // 733, 736, 
      MOTOR_1_25_CM = 894,
      MOTOR_2_25_CM = 995,
      MOTOR_3_25_CM = 669,
      MOTOR_4_25_CM = 321;   

// CW
// 262, 387,  43, 733
// 289, 405, 382, 749 ???
// 289, 405,  81, 749
// CCW
// 267, 367, 383, 743 ???
// 267, 367,  36, 743
// 267, 367,  36, 743