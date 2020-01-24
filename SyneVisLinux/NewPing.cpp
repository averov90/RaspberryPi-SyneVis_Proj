#include "NewPing.h"

NewPing::NewPing(uint8_t trigger_pin, uint8_t echo_pin, int max_cm_distance) {
	wiringPiSetup();
	_triggerPin = trigger_pin;
	_echoPin = echo_pin;
 	pinMode(_triggerPin, OUTPUT);// Set trigger pin to output.
	pinMode(_echoPin, INPUT);// Set echo pin to input.
	_maxEchoTime = std::min(max_cm_distance, MAX_SENSOR_DISTANCE) * US_ROUNDTRIP_CM + (US_ROUNDTRIP_CM / 2); // Calculate the maximum distance in uS.
	start = std::chrono::high_resolution_clock::now();
}


// ---------------------------------------------------------------------------
// Standard ping methods
// ---------------------------------------------------------------------------

unsigned int NewPing::ping() {
	if (!ping_trigger()) return NO_ECHO;                // Trigger a ping, if it returns false, return NO_ECHO to the calling function.
	while (digitalRead(_echoPin) == HIGH)                            // Wait for the ping echo.
		if (micros() > _max_time) return NO_ECHO;       // Stop the loop and return NO_ECHO (false) if we're beyond the set maximum distance.
	/*std::cout << "time from start: " << micros() << std::endl;
	std::cout << "max time: " << _max_time << std::endl;
	std::cout << "max echo time: " << _maxEchoTime << std::endl;
	std::cout << "result: " << (micros() - (_max_time - _maxEchoTime) - 5) << std::endl;*/
	return (micros() - (_max_time - _maxEchoTime) - 5); // Calculate ping time, 5uS of overhead.
}


unsigned int NewPing::ping_in() {
	unsigned long echoTime = NewPing::ping();          // Calls the ping method and returns with the ping echo distance in uS.
	return NewPingConvert(echoTime, US_ROUNDTRIP_IN); // Convert uS to inches.
}


unsigned int NewPing::ping_cm() {
	unsigned long echoTime = NewPing::ping();          // Calls the ping method and returns with the ping echo distance in uS.
	return NewPingConvert(echoTime, US_ROUNDTRIP_CM); // Convert uS to centimeters.
}

bool NewPing::ping_trigger() {
	digitalWrite(_triggerPin, LOW);// Set the trigger pin low, should already be low, but this will make sure it is.
	delayMicroseconds(4);            // Wait for pin to go low, testing shows it needs 4uS to work every time.
	digitalWrite(_triggerPin, HIGH);// Set trigger pin high, this tells the sensor to send out a ping.
	delayMicroseconds(10);           // Wait long enough for the sensor to realize the trigger pin is high. Sensor specs say to wait 10uS.
	digitalWrite(_triggerPin, LOW); // Set trigger pin back to low.

	_max_time = micros() + MAX_SENSOR_DELAY;                  // Set a timeout for the ping to trigger.
	while (digitalRead(_echoPin)== HIGH && micros() < _max_time) {} // Wait for echo pin to clear.
	while (digitalRead(_echoPin) == LOW)                          // Wait for ping to start.
		if (micros() > _max_time) return false;                // Something went wrong, abort.

	_max_time = micros() + _maxEchoTime; // Ping started, set the timeout.
	return true;                         // Ping started successfully.
}


unsigned int NewPing::convert_in(unsigned int echoTime) {
	return NewPingConvert(echoTime, US_ROUNDTRIP_IN); // Convert uS to inches.
}


unsigned int NewPing::convert_cm(unsigned int echoTime) {
	return NewPingConvert(echoTime, US_ROUNDTRIP_CM); // Convert uS to centimeters.
}
