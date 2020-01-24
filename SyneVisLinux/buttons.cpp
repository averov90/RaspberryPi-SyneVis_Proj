#include "dependents.h"
#include "buttons.h"

ButtonClickHandler::ButtonClickHandler(unsigned char pin, void(*callback)(ButtonClickHandler::PressType)):pin(pin), callback(callback) {
	pinMode(pin, INPUT);
	digitalWrite(pin, 0);
}

void ButtonClickHandler::update() {
	do {
		prew_val = digitalRead(pin);
		delay(10);
		curr_val = digitalRead(pin);
	} while (curr_val != prew_val);
	if (curr_val != prew_state) {
		if (curr_val)
			press_time = std::chrono::system_clock::now();
		else {
			if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - press_time).count() > 700)
				callback(ButtonClickHandler::PressType::LongClick);
			else 
				callback(ButtonClickHandler::PressType::Click);
		}
		prew_state = curr_val;
	}
}
