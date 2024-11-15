#pragma once 
// These constants define transitions between states and the conditions for those transitions
// magneticDip const used for EKF, unsure if it needs to be changed Oct 7 2024
constexpr static float magneticDip = 13.8 * (180/3.1415); // [rad] Magnetic Inclination of launch site
// PreLaunch -------------------------
// PreLaunch to Launch Conditions
    // average Z acceleration > LAUNCH_ACCEL_THRESHOLD
// Cannot go to Abort state from PreLaunch

// measured in G's
// checking if average Z acceleration is greater than 4 G's

// Pre-launch, measured in G's
#define LAUNCH_ACCEL_THRESHOLD 4

//LandPrep, measured in m/s
#define LANDING_VELOCITY 5.0

// Stowed, measured in meters
#define PAYLOAD_DEPLOY_HEIGHT 335 //Payload is considered deployed when falling below this height, 1099 feet

// Hold Right, in meters? - Kai 10/24/2024
#define MIN_ALT 61 //Lowest altitude before Land_prep, PLEASE CONFIRM 

//Payload Specific- will organize tonight 

#define PARACHUTE_SERVO_1 24 // wind counterclockwise in:2000   center:1493 wind out: 1100 RIGHT FRONT
#define PARACHUTE_SERVO_2 7 // wind clockwise in: 1100   center:1493 wind out: 2000 RIGHT BACK
#define PARACHUTE_SERVO_3 25 // wind counterclockwise in:2000   center:1493 wind out: 1100 LEFT BACK
#define PARACHUTE_SERVO_4 8 // wind clockwise in:1100  center:1493 wind out: 2000 LEFT FRONT

#define SERVO_CLOCK_WIND 1100
#define SERVO_CLOCK_UNWIND 1800

#define SERVO_COUNTER_WIND 1800
#define SERVO_COUNTER_UNWIND 1100

#define SERVO_CENTER 1493


#define PARACHUTE_SERVO_1_IN 20 //WOrking
#define PARACHUTE_SERVO_2_IN 21
#define PARACHUTE_SERVO_3_IN 16 //Not working 
#define PARACHUTE_SERVO_4_IN 17

#define PARACHUTE_SERVO_1_DIR true //Check these 
#define PARACHUTE_SERVO_2_DIR true
#define PARACHUTE_SERVO_3_DIR false
#define PARACHUTE_SERVO_4_DIR false

#define SERVO_GAIN 0.5

#define PULLEY_D 4.374
#define STRING_BASE_LENGTH 100

#define CAMERA_SERVO 33 //Also check this 
#define CAM_OUT 2012
#define CAM_RETRACT 0

#define IR_PIN 28

#define ALT_THRESHOLD_STOWED 396 //meters

#define MAX_STABILIZE_TIME 5000
#define MAX_FREEFALL_TIME 10000

#define MAX_SERVO_POS 0
#define MAX_SERVO_WIND_TIME 2000 

#define MAX_HOLD_TIME 8000

#define DESIRED_STRING_LENGTH 70

#define MAX_STOW_TIME 103000

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
