/**
 * @file FlightParams.hpp
 * @author Daniel Pearson (djpearson@wpi.edu)
 * @brief Class holding all of the flight parameters for the payload
 * @version 0.1
 * @date 2024-02-18
 * 
 * @copyright Copyright WPI HPRC (c) 2024
 * 
 */

#pragma once

#include <utility.hpp>

class FlightParameters {

    public:

    constexpr static float mass = 5.5; // [kg] Total system mass
    constexpr static float D_p = 1.8288; // [m] Diameter of Parachute
    constexpr static float S_p = (PI/4) * (D_p*D_p); // [m^2] Surface Area of Parachute 
    constexpr static float C_d = 0.7; // Coefficient of drag
    constexpr static float W_p = Utility::g * mass;
    constexpr static float h_cp = 2; // [m] Distance from center of mass to center of pressure
};