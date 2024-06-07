#pragma once

#include <Arduino.h>

// IREC 2024 Rocket Global Definitions (4/16/2024)

constexpr static float magneticDip = 13.8 * (180/PI); // [rad] Magnetic Inclination of launch site
constexpr static float rocketMass = 22.745; // [kg] Rocket mass from ORK
constexpr static float C_d = 0.5; // Eyeball averaged from ORK
constexpr static float S_r = (PI/4) * (0.1524*0.1524) + (0.00088386*4); // [m^2] Cross Sectional Area -- Body Tube + 4 Fins

// Debug things
#define DEBUG_MODE
#ifdef DEBUG_MODE

//#define NO_TRANSITION
#define NO_FLASH
// #define NO_XBEE
// #define SERIAL_TELEMETRY
#define WAIT_FOR_SERIAL
#define NO_SDCARD
// #define PRINT_TIMINGS

#endif


#pragma once 
// These constants define transitions between states and the conditions for those transitions

// PreLaunch -------------------------
// PreLaunch to Launch Conditions
    // average Z acceleration > LAUNCH_ACCEL_THRESHOLD
// Cannot go to Abort state from PreLaunch

// measured in G's
// checking if average Z acceleration is greater than 4 G's

#define LAUNCH_ACCEL_THRESHOLD 3

#define LANDING_VELOCITY 5.0

//Payload Specific- will organize tonight 

#define PARACHUTE_SERVO_1 23 // wind counterclockwise in:2000   center:1493 wind out: 1100
#define PARACHUTE_SERVO_2 25 // wind clockwise in: 1100   center:1493 wind out: 2000
#define PARACHUTE_SERVO_3 24 // wind counterclockwise in:2000   center:1493 wind out: 1100
#define PARACHUTE_SERVO_4 22 // wind clockwise in:1100  center:1493 wind out: 2000

#define SERVO_CLOCK_WIND 1100
#define SERVO_CLOCK_UNWIND 1800

#define SERVO_COUNTER_WIND 1800
#define SERVO_COUNTER_UNWIND 1100

#define SERVO_CENTER 1493

// #define PARACHUTE_SERVO_1_IN 20 //WOrking
// #define PARACHUTE_SERVO_2_IN 21
// #define PARACHUTE_SERVO_3_IN 16 //Not working 
// #define PARACHUTE_SERVO_4_IN 17

#define PARACHUTE_SERVO_1_DIR false //Check these 
#define PARACHUTE_SERVO_2_DIR true
#define PARACHUTE_SERVO_3_DIR false
#define PARACHUTE_SERVO_4_DIR true

#define SERVO_GAIN 0.5

#define PULLEY_D 4.374
#define STRING_BASE_LENGTH 100

#define CAMERA_SERVO 28 //Also check this 
#define CAM_OUT 2012
#define CAM_RETRACT 988

#define IR_PIN 28

#define ALT_THRESHOLD_STOWED 396 //meters

#define MAX_STABALIZE_TIME 5000
#define MAX_FREEFALL_TIME 10000

#define MAX_SERVO_POS 0
#define MAX_SERVO_WIND_TIME 2000 

#define MAX_HOLD_TIME 8000

#define DESIRED_STRING_LENGTH 70

#define MAX_STOW_TIME 5

//Trajectory Constants 

#define GRAV 9.81
#define MASS 5.5; // [kg] Total system mass
#define D_P 1.8288; // [m] Diameter of Parachute
#define S_P (PI/4) * (D_P*D_P); // [m^2] Surface Area of Parachute 
#define C_D 0.7; // Coefficient of drag
#define W_P GRAV * MASS;
#define H_CP 2; // [m] Distance from center of mass to center of pressure