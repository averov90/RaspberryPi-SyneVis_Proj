#include "dependents.h"
#include "changer.h"
#include "NewPing.h"
#include "consts.h"
#include "CloudApi.h"
#include "wavplayer.h"
#include "wavutils.h"
#include "colormid.h"

extern WavUtils::SynGenData commonUltrasonicColorsStr;

void sonar_thr(CommonUltrasonic *cls, raspicam::RaspiCam_Cv *camera) {
	NewPing ping(GPIO_SONAR_TRIGGER, GPIO_SONAR_ECHO);
	mCloudApi api = mCloudApi();
	int distance;
	std::unique_lock<std::mutex> locker(cls->mtx);
	std::string lang;
	std::wstring text;
	cv::Mat frame;
	unsigned char rangeD2 = GPIO__PWM_RANGE >> 1;
	while (cls->thread_work)
	{
		while (cls->nsleep) cls->waiter.wait(locker);
		if (cls->clicked) {
			cls->clicked = false;
			digitalWrite(GPIO_LED, HIGH);
			delay(100);
			camera->grab();
			camera->retrieve(frame);
			digitalWrite(GPIO_LED, LOW);
			if (cls->textmode) {
				//text detect
				delay(50);
				softPwmWrite(GPIO_VIBRATE_PWM, 0);
				text = api.Cloud_ImageToTextReader(frame, lang);
				if (lang == "error")
					SNDPlayWaitD(cls->notext, cls->ntlen);
				else
					WavePlayWaitD(api.Cloud_RussianTTS(text, lang).c_str());
				
			} else {
				//label detect
				delay(50);
				softPwmWrite(GPIO_VIBRATE_PWM, 0);
				WavePlayWaitD(api.Cloud_RussianTTS(api.Cloud_TranslateToRus(api.Cloud_ImageDescriptor(frame)), "ru-ru").c_str());
			}
		}
		delay(50);
		distance = ping.ping_cm();
		if (distance == 0) continue;
		if (distance < 3) {
			delay(300);
			SNDPlayWaitD(cls->sound, cls->slen);
		} else if (distance > 400) {
			softPwmWrite(GPIO_VIBRATE_PWM, 0);
		} else {
			softPwmWrite(GPIO_VIBRATE_PWM, cls->sonar_pow[distance - 3]);
			std::cout << "vpow " << (int)cls->sonar_pow[distance - 3] << " dist " << distance << std::endl;

			if (distance < 10) {
				digitalWrite(GPIO_LED, HIGH);
				delay(100);
				softPwmWrite(GPIO_VIBRATE_PWM, 0);
				camera->grab();
				camera->retrieve(frame);
				digitalWrite(GPIO_LED, LOW);
				try
				{
					distance = Detectors_Easy_Recognise_color(frame);
				}
				catch (const std::exception&)
				{
					distance = false;
				}
				if (distance) {
					std::cout << "d3 " << distance - 1 << " " << commonUltrasonicColorsStr.sinessizes[distance - 1] << std::endl;
					SNDPlayWaitD(commonUltrasonicColorsStr.sines[distance - 1], commonUltrasonicColorsStr.sinessizes[distance - 1]);
				}
			}
		}
		delay(200);
	}
	delete[] cls->sonar_pow;
}

CommonUltrasonic::CommonUltrasonic(raspicam::RaspiCam_Cv *camera) {
	unsigned char vals = GPIO__PWM_RANGE - GPIO__PWM_OFFSET;
	float logv = log2f(397), coef = (vals / logv - 1) / logv;
	sonar_pow = new unsigned char[398];
	unsigned char *cp = sonar_pow;
	*cp++ = GPIO__PWM_RANGE - 1;
	for (unsigned short i = 2; i != 398; ++i, ++cp) {
		logv = log2f(i);
		*cp = GPIO__PWM_RANGE - roundf(GPIO__PWM_OFFSET + logv * (logv * coef + 1));
	}
	sound = WavUtils::LoadSND("/home/pi/projects/SyneVisLinux/bin/ARM/Debug/too_close.snd", slen);
	notext = WavUtils::LoadSND("/home/pi/projects/SyneVisLinux/bin/ARM/Debug/no_text.snd", ntlen);
	camera->grab();
	camera->retrieve(tmp);
	std::thread sonar(sonar_thr, this, camera);
	sonar.detach();
}

void CommonUltrasonic::start() {
	nsleep = false;
	waiter.notify_one();
}

void CommonUltrasonic::stop() {
	nsleep = true;
}

void CommonUltrasonic::click() {
	clicked = true;
}

void CommonUltrasonic::doubleClick() {
	textmode = !textmode;
}

unsigned char CommonUltrasonic::getMode() {
	return textmode;
}

CommonUltrasonic::~CommonUltrasonic() {
	thread_work = false;
}
