
class ServoController {
    private:    
        Servo servo;
        bool clockwise;
        // servo angle is in degrees
        float p; // s^-1
        float pulleyDiameter; // cm
        float stringLength;   // cm
    public: 
        ServoController(int, bool, float, float, float);
        /**
         * @brief Sets servo speed to aim for target string length.
         * @param newStringLength The target length. 
        */
        void adjustString(float);
        /**
         * @brief Sets servo speed to aim for target angle.
         * @param newAngle The target angle.
         * @param currAngle The current angle. 
        */
        void setToAngle(float, float);
};

/**
 * @brief Converts an angle in degrees to be within the range of [-180, 180).
 * @param angle The angle in degrees to be converted.
*/
float shortestAngle(float);