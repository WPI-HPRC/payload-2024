#pragma once

#include <Arduino.h>

// IREC 2024 Rocket Global Definitions (4/16/2024)

constexpr static float magneticDip = 13.8 * (180/PI); // [rad] Magnetic Inclination of launch site
constexpr static float rocketMass = 22.745; // [kg] Rocket mass from ORK
constexpr static float C_d = 0.5; // Eyeball averaged from ORK
constexpr static float S_r = (PI/4) * (0.1524*0.1524) + (0.00088386*4); // [m^2] Cross Sectional Area -- Body Tube + 4 Fins

// Debug things, general debugger 
#define DEBUG_MODE
#ifdef DEBUG_MODE

//#define NO_TRANSITION
#define NO_FLASH
// #define NO_XBEE
// #define SERIAL_TELEMETRY
#define WAIT_FOR_SERIAL
#define NO_SDCARD
#define PRINT_TIMINGS
#define TEST_STATE_MACHINE

#endif

//#define NO_CV
//#define NO_SERVOS

#pragma once 


//PAYLOAD DEFINITIONS AND FLIGHT PARAMETERS====================================================

//SERVO PIN and PWM DEFINITIONS 
#define PARACHUTE_SERVO_1 23 // wind counterclockwise in:2000   center:1493 wind out: 1100
#define PARACHUTE_SERVO_2 25 // wind clockwise in: 1100   center:1493 wind out: 2000
#define PARACHUTE_SERVO_3 24 // wind counterclockwise in:2000   center:1493 wind out: 1100
#define PARACHUTE_SERVO_4 22 // wind clockwise in:1100  center:1493 wind out: 2000

#define SERVO_CLOCK_WIND 1100
#define SERVO_CLOCK_UNWIND 1800

#define SERVO_COUNTER_WIND 1800
#define SERVO_COUNTER_UNWIND 1100

#define SERVO_CENTER 1493

#define PARACHUTE_SERVO_1_DIR false 
#define PARACHUTE_SERVO_2_DIR true
#define PARACHUTE_SERVO_3_DIR false
#define PARACHUTE_SERVO_4_DIR true

#define CAMERA_SERVO 28 
#define CAM_OUT 2012
#define CAM_RETRACT 988

#define MAX_SERVO_POS 0

//Max times for winding and holding servos 
#define MAX_SERVO_WIND_TIME 2000 //Could change to 1500 
#define MAX_HOLD_TIME 8000


//STATE CHANGE PARAMETERS (last updated 6/18/2024 by Colette Scott)

//Pre-launch, measured in G's 
#define LAUNCH_ACCEL_THRESHOLD 4

//LandPrep, measured in m/s
#define LANDING_VELOCITY 5.0

#define PAYLOAD_DEPLOY_HEIGHT 365 // [m] AGL. Payload is considered deployed when falling below this height
#define JERK 0.5 //in g's, may need to be adjusted 

#define MIN_ALT 200 //Lowest altitude before Land_prep, PLEASE CONFIRM 

//Timer Constants, for servos and abort state: 

//Max time to allow payload to stabilize 
#define MAX_STABALIZE_TIME 5000

//Max time to allow payload to fall freely  
#define MAX_FREEFALL_TIME 10000

//Max time payload should be stowed in the Rocket: THIS ONE NEEDS TO BE CHECKED 
#define MAX_STOW_TIME 159000 
//142 seconds + 15 for buffer
//Change stowed conditions to be abort based on time and change to wind based on altitude + buffer
//Maybe acceleration...buffer barometer to get vertical, expected is 20ft/s

//Times for state transitions with Debug: 
#define MAX_PRELAUNCH 3000
#define MAX_LANDPREP 8000

//Trajectory Constants 

#define GRAV 9.81
#define MASS 5.5; // [kg] Total system mass
#define D_P 1.8288; // [m] Diameter of Parachute
#define S_P (PI/4) * (D_P*D_P); // [m^2] Surface Area of Parachute 
#define C_D 0.7; // Coefficient of drag
#define W_P GRAV * MASS;
#define H_CP 2; // [m] Distance from center of mass to center of pressure
