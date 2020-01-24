#pragma once
#include "wavutils.h"

class Change_base {
public:
	Change_base() { };
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void click() = 0;
	virtual void doubleClick() = 0;
	virtual unsigned char getMode() {};
	virtual ~Change_base() {};
};

class CommonUltrasonic : public Change_base {
	friend void sonar_thr(CommonUltrasonic*, raspicam::RaspiCam_Cv*);
public:
	CommonUltrasonic(raspicam::RaspiCam_Cv *camera);
	void start();
	void stop();
	void click();
	void doubleClick();
	unsigned char getMode();
	~CommonUltrasonic();
private:
	CommonUltrasonic();
	std::mutex mtx;
	std::condition_variable waiter;
	bool nsleep = true, thread_work = true;
	bool textmode = false;
	bool clicked = false;
	unsigned char *sonar_pow;
	short *sound, *notext; unsigned int slen, ntlen;
};

