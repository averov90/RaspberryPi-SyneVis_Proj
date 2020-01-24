#pragma once
class ButtonClickHandler {
public:	
	enum PressType { Click, LongClick };
	explicit ButtonClickHandler(unsigned char pin, void (*callback)(PressType));
	void update();
private:
	unsigned char pin, curr_val, prew_val, prew_state = 0;
	void(*callback)(PressType);
	std::chrono::time_point<std::chrono::system_clock> press_time;
};