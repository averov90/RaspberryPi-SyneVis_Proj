#pragma once
#include "dependents.h"
#include "mCurl.h"
class mCloudApi {
public:
	bool Initialize();

	std::string to_utf8(std::wstring &str);
	std::string Cloud_RussianTTS(std::wstring text, std::string lang);
	std::wstring Cloud_TranslateToRus(std::string text);
	std::wstring Cloud_ImageToTextReader(const cv::Mat &image, std::string &locale);
	std::string Cloud_ImageDescriptor(const cv::Mat &image);
	std::string getData();
private:
	mCurl curl;
	std::string data;
};