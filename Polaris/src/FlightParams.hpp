#pragma once //This is obviously all Rocket stuff- needs to change, will do so Thursday night 
// These constants define transitions between states and the conditions for those transitions

// PreLaunch -------------------------
// PreLaunch to Launch Conditions
    // average Z acceleration > LAUNCH_ACCEL_THRESHOLD
// Cannot go to Abort state from PreLaunch

// measured in G's
// checking if average Z acceleration is greater than 4 G's
#define LAUNCH_ACCEL_THRESHOLD 4.0

// Launch -------------------------
// Launch to Coast Conditions
    // time in Launch >= MOTOR_BURN_TIME
    // and
    // average Z acceleration < BURNOUT_THRESHOLD
// Launch to Abort Conditions
    // time in Launch > 2 * MOTOR_BURN_TIME

// 3.1 second timeout, as defined in OpenRocket for Test Launch 2/17
#define MOTOR_BURN_TIME 3.1 * 1000.0

// Acceleration threshold for burnout detection, in G's
// checking if average Z acceleration is less than 0.3 G's
#define BURNOUT_THRESHOLD 0.3

// Coast -------------------------
// Coast to DrogueDescent Conditions
    // average vertical velocity <= 0
// Coast to Abort Conditions
    // time in Coast > 1.5 * TIME_IN_COAST

// seconds, OpenRocket for Test Launch 2/17
#define TIME_IN_COAST 18.4 * 1000.0

// DrogueDescent -------------------------
// DrogueDescent to MainDescent Conditions
    // average vertical velocity <= MAIN_DEPLOY_VELOCITY
// DrogueDescent to Abort Conditions
    // time in DrogueDescent > 1.2 * TIME_IN_DROGUE_DESCENT

// converts ft/s to m/s, OpenRocket sim Test Launch 2/17
#define FPS_TO_MPS 3.281

// Given in FPS from OpenRocket, convert to m/s
// checking if average vertical velocity is less than or equal to 82.6 ft/s
#define MAIN_DEPLOY_VELOCITY 82.6 / FPS_TO_MPS

// seconds, OpenRocket for Test Launch 2/17
#define TIME_IN_DROGUE_DESCENT 67.6 * 1000.0

// MainDescent -------------------------
// MainDescent to Recovery Conditions
    // average vertical velocity < LANDING_VELOCITY
// MainDescent to Abort Conditions
    // time in MainDescent > 1.1 * TIME_IN_MAIN_DESCENT

// 88 seconds, OpenRocket for Test Launch 2/17
#define TIME_IN_MAIN_DESCENT 90.0 * 1000.0

// Upper bound for landing velocity
// checking if average vertical velocity is less than 5 m/s
#define LANDING_VELOCITY 5.0

// Recovery -------------------------

// Abort -------------------------

//Payload Specific- will organize tonight 

#define PARACHUTE_SERVO_1 0
#define PARACHUTE_SERVO_2 0
#define PARACHUTE_SERVO_3 0
#define PARACHUTE_SERVO_4 0

#define PARACHUTE_SERVO_INPUT_1 0
#define PARACHUTE_SERVO_INPUT_2 0
#define PARACHUTE_SERVO_INPUT_3 0
#define PARACHUTE_SERVO_INPUT_4 0

#define CAMERA_SERVO 0

#define IR_PIN 0

#define ALT_THRESHOLD_STOWED 1300 //feet

#define MAX_STABALIZE_TIME 5
#define MAX_FREEFALL_TIME 10

#define MAX_SERVO_POS 0
#define MAX_SERVO_WIND_TIME 0 

#define MAX_HOLD_TIME 0



