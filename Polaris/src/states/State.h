#pragma once
#pragma once
#include "utility.hpp"

#define _STATE_CLASS_IMPLS_          \
private:                             \
	void initialize_impl() override; \
	void loop_impl() override;       \
	State *nextState_impl() override;
	StateId getId() override;

#include "Arduino.h"
#include "../utility.hpp" //why this again? 
#include <BasicLinearAlgebra.h>
#include <TelemetryBoard/XBeeProSX.h>
#include <EKF.h>

enum StateId {
  ID_PreLaunch = 0,
  ID_Stowed,
  ID_Freefall,
  ID_WindLeft,
  ID_HoldLeft,
  ID_WindRight,
  ID_HoldRight,
  ID_LandPrep,
  ID_Recovery,
  ID_Abort,
};

/**
 * @brief Abstract class representing a payload state.
 */
class State {
	public:
		/**
		 * @brief Code to be run once when the state begins.
		 */
		void initialize();
		/**
		 * @brief Code to be run every iteration of the loop while the payload is in this state.
		 */
		void loop();
		/**
		 * @brief Code run every iteration of the loop to determine the next state to transition to.
		 * @return The pointer to the next state or nullptr if the state has not changed.
		 */
		State *nextState();
		virtual enum StateId getId() = 0;
		virtual ~State() {}

		Utility::SensorPacket sensorPacket; //Protected? 
		Utility::TelemPacket telemPacket;

	protected:
		//! @brief number of milliseconds since the initialize call
		long long currentTime = 0;
		//! @brief number of milliseconds since the last loop call
		long long deltaTime = 0;
		long long loopCount = 0;
		XbeeProSX * xbee = new XbeeProSX(17); // CS GPIO17

	private:
		//! @brief number of milliseconds from boot to the initialize call
		long long startTime = 0;
		//! @brief number of milliseconds from boot to the previous loop call
		long long lastLoopTime = 0;
		virtual void initialize_impl() = 0;
		virtual void loop_impl() = 0;
		virtual State *nextState_impl() = 0;
};
