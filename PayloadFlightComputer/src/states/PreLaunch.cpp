// #include "PreLaunch.h"
// #include "State.h"
// #include "Stowed.h"
// #include "Debug.h"
// #include "Sensors.h"

// PreLaunch::PreLaunch(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip) : State(sensors, stateEstimator, flashChip) {}

// float PreLaunch::avgAccelZ()
// {
//     float sum = 0;
//     uint8_t len = sizeof(this->accelReadingBuffer) / sizeof(float);

//     for (uint8_t i = 0; i < len; i++)
//     {
//         sum += this->accelReadingBuffer[i];
//     }

//     return sum / len;
// }

// void PreLaunch::initialize_impl() {}

// void PreLaunch::loop_impl()
// {
//     if (!sensorPacket.gpsLock)
//     {
//         // Serial.println("Acquiring Gps Lock...");
//         // delay(100);
//         return;
//     };

//     if (this->stateEstimatorInitialized)
//     {
//         this->accelReadingBuffer[this->buffIdx++] = this->sensorPacket.accelZ;
//         this->buffIdx %= sizeof(this->accelReadingBuffer) / sizeof(float);
//         return;
//     }

//     // float r_adj = Utility::r_earth + sensorPacket.gpsAltMSL; // [m]
//     float N_earth = Utility::a_earth / sqrt(1 - pow(Utility::e_earth, 2) * pow(sin(sensorPacket.gpsLat), 2));

//     float X_0 = (N_earth + sensorPacket.gpsAltAGL) * cos(sensorPacket.gpsLat * DEG_TO_RAD) * cos(sensorPacket.gpsLong * DEG_TO_RAD);
//     float Y_0 = (N_earth + sensorPacket.gpsAltAGL) * cos(sensorPacket.gpsLat * DEG_TO_RAD) * sin(sensorPacket.gpsLong * DEG_TO_RAD);
//     float Z_0 = (((Utility::b_earth * Utility::b_earth) / (Utility::a_earth * Utility::a_earth)) * N_earth + sensorPacket.gpsAltAGL) * sin(sensorPacket.gpsLat * DEG_TO_RAD);
//     // float Z_0 = (N_earth*(1-pow(Utility::e_earth,2))+sensorPacket.gpsAltAGL)*sin(sensorPacket.gpsLat);

//     Serial.println("[Pre-Launch] Initial GPS Position Acquired!");
//     Serial.print("Latitude: ");
//     Serial.println(sensorPacket.gpsLat, 4);
//     Serial.print("Longitude: ");
//     Serial.println(sensorPacket.gpsLong, 4);
//     Serial.print("Initial Position: <");
//     Serial.print(X_0, 4);
//     Serial.print(", ");
//     Serial.print(Y_0, 4);
//     Serial.print(", ");
//     Serial.print(Z_0, 4);
//     Serial.println(">");

//     // Intialize EKF
//     BLA::Matrix<10> x_0 = {1, 0, 0, 0, X_0, Y_0, Z_0, 0, 0, 0};
//     // BLA::Matrix<4> x_0 = {1,0,0,0};
//     this->ekf = new StateEstimator(x_0, 0.025);

//     this->stateEstimatorInitialized = true;
// }

// //! @details If we are separating this from `Launch`, we need a time limit on this state or something
// State *PreLaunch::nextState_impl()
// {

//     // DO NOT MOVE TO NEXT STATE UNTIL GPS LOCK IS ACQUIRED
//     if (DEBUG_MODE && sensorPacket.gpsLock)
//     {
//         return new Debug(this->sensors, this->ekf);
//     }

//     if (sensorPacket.gpsLock && this->avgAccelZ() > LAUNCH_ACCEL_THRESHOLD)
//     {
//         return new Stowed(sensors, stateEstimator, flashChip);
//     }
//     return nullptr;
// }


#include "PreLaunch.h"
#include "State.h"
#include "Debug.h"
#include "Sensors.h"
#include "Stowed.h"

#define IN_FOISE true

PreLaunch::PreLaunch(struct Sensors *sensors) : State(sensors) {}

void PreLaunch::initialize_impl() {
}

void PreLaunch::loop_impl() {
	// Read bno for example
	if(!sensorPacket.gpsLock && !IN_FOISE) {
		Serial.println("[PreLaunch] Gps Lock Failed...");
		
		delay(100);
		return;
	} else if(IN_FOISE) {
		Serial.println("[PreLaunch] I am sorry to hear you are in Foise, no GPS for you :D");
		BLA::Matrix<10> x_0 = {1,0,0,0,0,0,0,0,0,0};
		ekf = new StateEstimator(x_0, 0.025);

		return;
	}

	// float r_adj = Utility::r_earth + sensorPacket.gpsAltMSL; // [m]
	float N_earth = Utility::a_earth / sqrt(1 - pow(Utility::e_earth,2) * pow(sin(sensorPacket.gpsLat), 2));

	float X_0 = (N_earth + sensorPacket.gpsAltAGL) * cos(sensorPacket.gpsLat * DEG_TO_RAD) * cos(sensorPacket.gpsLong * DEG_TO_RAD);
	float Y_0 = (N_earth + sensorPacket.gpsAltAGL) * cos(sensorPacket.gpsLat * DEG_TO_RAD) * sin(sensorPacket.gpsLong * DEG_TO_RAD);
	float Z_0 = (((Utility::b_earth*Utility::b_earth)/(Utility::a_earth*Utility::a_earth))*N_earth + sensorPacket.gpsAltAGL) * sin(sensorPacket.gpsLat * DEG_TO_RAD);
	// float Z_0 = (N_earth*(1-pow(Utility::e_earth,2))+sensorPacket.gpsAltAGL)*sin(sensorPacket.gpsLat);


	Serial.println("[Pre-Launch] Initial GPS Position Acquired!");
	Serial.print("Latitude: "); Serial.println(sensorPacket.gpsLat, 4);
	Serial.print("Longitude: "); Serial.println(sensorPacket.gpsLong, 4);
	Serial.print("Initial Position: <"); Serial.print(X_0,4); Serial.print(", "); Serial.print(Y_0,4); Serial.print(", "); Serial.print(Z_0,4); Serial.println(">");

	// Intialize EKF
	BLA::Matrix<10> x_0 = {1,0,0,0, 0, 0, 0, 0,0,0};
	ekf = new StateEstimator(x_0, 0.025);
	// ekf = new StateEstimator(x_0, 0.025);
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *PreLaunch::nextState_impl()
{

	// DO NOT MOVE TO NEXT STATE UNTIL GPS LOCK IS ACQUIRED
	if(DEBUG_MODE && (sensorPacket.gpsLock || IN_FOISE)) {
		return new Debug(sensors,this->ekf);
	}

	if (this->currentTime > MAX_PRELAUNCH_TIME && sensorPacket.gpsLock)
	{
		return new Stowed(sensors);
	}
	return nullptr;
}