#include <Servo.h>
#include <stdlib.h>
#include "ServoController.h"

// const float pulleyDiameter = 4.374;
// const float stringLength = 100.;
// const float pGain = 5.;

ServoController::ServoController(int pin, bool clockwise, float p,
        float pulleyDiameter, float stringLength) {
    this->clockwise = clockwise;
    this->servo.attach(pin);
    this->p = p;
    this->pulleyDiameter = pulleyDiameter;
    this->stringLength = stringLength;
    // Set servo to be still
    this->servo.write(90.);
}

void ServoController::adjustString(float newStringLength) {
    const angleOffset = 0.0;
    float currAngle = servo.read();
    float currStringLength = shortestAngle(currAngle - angleOffset) *
                             PI/180.*(0.5*this->pulleyDiameter);
    float newAngle = newStringLength/(0.5*this->pulleyDiameter)*(180./PI) +
                     angleOffset;
    
    setToAngle(newAngle, currAngle);
}

void ServoController::setToAngle(float newAngle, float currAngle) {
    float angleDiff = shortestAngle((newAngle - currAngle));
    float degreesPerSec = (this->clockwise ? -1. : 1.)*(this->p)*angleDiff;
    const reduction = 1. / 1.;
    this->servo.write(constrain(90. + (0.085*90./60.)/reduction*degreesPerSec,
                                0., 180.));
}

float shortestAngle(float angleDiff) {
    return mod(angleDiff + 180.,360.) - 180.;
}

/*
#include <Servo.h>

// Constants
const int servoPin = 9;              // Servo pin
const float pulleyDiameter = 4.375;   // Diameter of the pulley in inches
const float stringLength = 12.0;      // Initial length of the string in inches
const int servoMinPulse = 1000;       // Example minimum pulse width (adjust as needed)
const int servoMaxPulse = 2000;       // Example maximum pulse width (adjust as needed)
const float pGain = 5.0;              // P-controller gain (adjust as needed)

class ServoController {
public:
    ServoController() {
        // Attach the servo to the specified pin
        servo.attach(servoPin);
    }

    // Function to set the desired rotation angle
    void setDesiredAngle(float angle) {
        desiredAngle = angle;
    }

    // Function to update the servo position using P-controller
    void updateServo() {
        // Read the current rotation angle
        float currentAngle = map(servo.read(), servoMinPulse, servoMaxPulse, 0.0, 180.0);

        // Calculate the error
        float error = desiredAngle - currentAngle;

        // Calculate the proportional output
        float pOutput = pGain * error;

        // Map the output to servo pulse
        int servoPulse = map(pOutput, -90.0, 90.0, servoMinPulse, servoMaxPulse);

        // Move the servo to the specified pulse
        servo.writeMicroseconds(servoPulse);
    }

private:
    Servo servo;
    float desiredAngle;
};

// Example usage
ServoController parachuteController;

void setup() {
    // Initialization code if needed
}

void loop() {
    // Example: Set the desired angle to 90 degrees
    parachuteController.setDesiredAngle(90.0);
    parachuteController.updateServo();

    // Example: Set the desired angle to -45 degrees
    parachuteController.setDesiredAngle(-45.0);
    parachuteController.updateServo();
    
    // Add more control logic as needed
}

*/
