#include "CloudApi.h"
#include "wavplayer.h"
#include "dependents.h"
#include <stdio.h>
#include <stdint.h>
#include "NewPing.h"
#include "buttons.h"
#include "changer.h"
#include "consts.h"
#include "wavutils.h"
#include "CloudApi.h"

mCloudApi api;
cv::Mat image;

Change_base *ultrasonic;

void button1Clicked(ButtonClickHandler::PressType press_type) {
	if (ultrasonic->getMode() == 1) ultrasonic->doubleClick();
	ultrasonic->click();
}

void button2Clicked(ButtonClickHandler::PressType press_type) {
	if (ultrasonic->getMode() == 0) ultrasonic->doubleClick();
	ultrasonic->click();
}

raspicam::RaspiCam_Cv Camera;

WavUtils::SynGenData commonUltrasonicColorsStr;

int main()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	Pa_Initialize();
	if (!Camera.open()) { std::cout << "Error opening the camera" << std::endl; return -1; }
	wiringPiSetup();
	pinMode(GPIO_VIBRATE_PWM, OUTPUT);
	pinMode(GPIO_LED, OUTPUT);
	pinMode(GPIO_BTN_1, INPUT);
	pinMode(GPIO_BTN_2, INPUT);
	softPwmCreate(GPIO_VIBRATE_PWM, 0, GPIO__PWM_RANGE);
	ButtonClickHandler Btn1(GPIO_BTN_1, button1Clicked);
	ButtonClickHandler Btn2(GPIO_BTN_2, button2Clicked);
	WavUtils::LoadSNDPacket("/home/pi/projects/SyneVisLinux/bin/ARM/Debug/colors/collect.txt", "/home/pi/projects/SyneVisLinux/bin/ARM/Debug/colors", commonUltrasonicColorsStr);
	{
		unsigned int sd;
		short *n = WavUtils::LoadSND("/home/pi/projects/SyneVisLinux/bin/ARM/Debug/hi.snd", sd);
		SNDPlayWaitD(n, sd);
		delete[] n;
	}
	ultrasonic = new CommonUltrasonic(&Camera);
	
	ultrasonic->start();
	
	while (true) {
		delay(50);
		Btn1.update();
		Btn2.update();
		Camera.grab();
		Camera.retrieve(image);
	}
}

/*
int main()
{
	cv::VideoCapture cap;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	Pa_Initialize();
	Syne_Initialise()
	cap = cv::VideoCapture("v4l2src ! video/x-raw,format=NV12,width=640,height=480 ! videoconvert ! appsink");
	camera_capture_syne = cap;
	{cv::Mat frame;
	camera_capture_syne >> frame; }
	Syne_Start(); 

	cv::Mat frame;
	cap.read(frame);

	wiringPiSetup();
	pinMode(22, OUTPUT);
	pinMode(24, INPUT);
	while (true)
	{
		Pa_Sleep(50);
		cap >> frame; 

	}

	

    return 0;
}
*/