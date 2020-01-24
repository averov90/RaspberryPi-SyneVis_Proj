#pragma once
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include "dependents.h"
#define MAX_SENSOR_DISTANCE 500 // Maximum sensor distance can be as high as 500cm, no reason to wait for ping longer than sound takes to travel this distance and back.
#define US_ROUNDTRIP_IN 146     // Microseconds (uS) it takes sound to travel round-trip 1 inch (2 inches total), uses integer to save compiled code space.
#define US_ROUNDTRIP_CM 57      // Microseconds (uS) it takes sound to travel round-trip 1cm (2cm total), uses integer to save compiled code space.

// Probably shoudln't change these values unless you really know what you're doing.
#define NO_ECHO 0               // Value returned if there's no ping echo within the specified MAX_SENSOR_DISTANCE or max_cm_distance.
#define MAX_SENSOR_DELAY 18000  // Maximum uS it takes for sensor to start the ping (SRF06 is the highest measured, just under 18ms).

// Conversion from uS to distance (round result to nearest cm or inch).
#define NewPingConvert(echoTime, conversionFactor) (std::max(((unsigned)echoTime + conversionFactor / 2) / conversionFactor,(unsigned) (echoTime ? 1 : 0)))

class NewPing {
public:
	NewPing(uint8_t trigger_pin, uint8_t echo_pin, int max_cm_distance = MAX_SENSOR_DISTANCE);
	unsigned int ping();
	unsigned int ping_in();
	unsigned int ping_cm();
	unsigned int convert_in(unsigned int echoTime);
	unsigned int convert_cm(unsigned int echoTime);
private:
	bool ping_trigger();
	uint8_t _triggerPin;
	uint8_t _echoPin;
	std::chrono::system_clock::time_point start;
	unsigned int _maxEchoTime;
	unsigned long _max_time;
};