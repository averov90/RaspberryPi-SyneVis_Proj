#include "CloudApi.h"
#include <iostream>

bool mCloudApi::Initialize()
{
	if (!curl.Initialize()) {
		return false;
	}
	return true;
}

std::string mCloudApi::to_utf8(std::wstring & str)
{
	static std::wstring_convert<std::codecvt_utf8<wchar_t>> u8;
	return u8.to_bytes(str);
}


std::string mCloudApi::Cloud_RussianTTS(std::wstring text, std::string lang)
{
	data = "";
	curl.setList(nullptr);
	std::string s = to_utf8(text);
	curl.setNewSession(curl_easy_init());
	curl.setURL("http://api.voicerss.org/");
	curl.setData("key=2154d4bb1de543d0b01e91126fd6fc2b&hl=" + lang + "&src=" + s + "&b64=true&c=WAV&f=11khz_16bit_mono&r=-1");
	curl.setParams(data);
	curl.sendRequest();
	std::ofstream file("wave.wav", std::ios::out | std::ios::binary);
	
	s = base64_decode(data.substr(data.find_first_of(',') + 1));
	file.write(s.c_str(), s.size());
	return s;
}

std::wstring mCloudApi::Cloud_TranslateToRus(std::string text)
{
	data = "";
	curl.setList(nullptr);
	curl.setNewSession(curl_easy_init());
	curl.setURL("https://translation.googleapis.com/language/translate/v2?key=AIzaSyDLx_JXD42FH7xz8nKlVVFxb3J1-R-iOd4");
	curl.setData("&q=" + text + "&source=en&target=ru&format=text");
	curl.setParams(data);
	if (!curl.sendRequest()) {
		std::cout << "error" << std::endl;
	}
	unsigned int fpos = (unsigned int)data.find("t\":") + 5;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(data.substr(fpos, data.find_last_of('\"') - fpos));
}

std::wstring mCloudApi::Cloud_ImageToTextReader(const cv::Mat & image, std::string &locale)
{
	data = "";
	curl.setList(nullptr);
	unsigned char *jpegBuf = nullptr;
	unsigned long jpegSize = 0;
	tjhandle tjInstance = tjInitCompress();
	if (!tjInstance) return L"";
	if (tjCompress2(tjInstance, image.data, image.cols, 0, image.rows, TJPF_BGR, &jpegBuf, &jpegSize, TJSAMP_422, 90, TJFLAG_FASTDCT) < 0) return L"";
	tjDestroy(tjInstance);
	std::string img_encoded = base64_encode(jpegBuf, (unsigned int)jpegSize);
	tjFree(jpegBuf);
	curl.setNewSession(curl_easy_init());
	curl.setURL("https://vision.googleapis.com/v1/images:annotate?key=AIzaSyDLx_JXD42FH7xz8nKlVVFxb3J1-R-iOd4");
	curl.setData("{'requests':[{'image':{'content':'" + img_encoded + "'},'features':[{'type':'DOCUMENT_TEXT_DETECTION'}]}]}");
	curl.setList(curl_slist_append(nullptr, "Content-Type: application/json"));
	curl.setParams(data);
	curl.sendRequest();
	unsigned int fpos = (unsigned int)data.find("e\":") + 5;
	locale = data.substr(fpos, data.find_first_of(',', fpos) - fpos - 1);
	if (locale == "ru") {
		locale = "ru-ru";
	}
	else if (locale == "en") {
		locale = "en-us";
	}
	else {
		locale = "error";
	}
	fpos = (unsigned int)data.find("n\":", fpos) + 5;
	std::string text = data.substr(fpos, data.find_first_of('\"', fpos) - fpos);
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(text);
}

std::string mCloudApi::Cloud_ImageDescriptor(const cv::Mat & image)
{
	unsigned char *jpegBuf = nullptr;
	unsigned long jpegSize = 0;
	tjhandle tjInstance = tjInitCompress();
	if (!tjInstance) return "";
	if (tjCompress2(tjInstance, image.data, image.cols, 0, image.rows, TJPF_BGR, &jpegBuf, &jpegSize, TJSAMP_422, 85, TJFLAG_FASTDCT) < 0) return "";
	tjDestroy(tjInstance);
	std::string img_encoded = base64_encode(jpegBuf, (unsigned int)jpegSize);
	tjFree(jpegBuf);
	curl.setNewSession(curl_easy_init());
	curl.setURL("https://vision.googleapis.com/v1/images:annotate?key=AIzaSyDLx_JXD42FH7xz8nKlVVFxb3J1-R-iOd4");
	curl.setData("{'requests':[{'image':{'content':'" + img_encoded + "'},'features':[{'type':'LABEL_DETECTION'}]}]}");
	curl.setList(curl_slist_append(nullptr, "Content-Type: application/json"));
	curl.setParams(data);
	curl.sendRequest();
	std::string result = "Found ";
	std::string tmp;
	unsigned int pos1 = (unsigned int)data.find("n\":") + 5, pos2 = (unsigned int)data.find_first_of('\"', pos1); //Finding "description" by latest symbols
	result += data.substr(pos1, pos2 - pos1);
	pos1 = (unsigned int)data.find("e\":", pos2) + 4; pos2 = (unsigned int)data.find_first_of(',', pos1); //Finding "score" by latest symbols
	float msc = std::stof(data.substr(pos1, pos2 - pos1));
	for (char i = 0; i != 10; ++i)
	{
		pos1 = (unsigned int)data.find("n\":", pos2) + 5; pos2 = (unsigned int)data.find_first_of('\"', pos1); //Finding "description" by latest symbols
		tmp = data.substr(pos1, pos2 - pos1);
		pos1 = (unsigned int)data.find("e\":", pos2) + 4; pos2 = (unsigned int)data.find_first_of(',', pos1); //Finding "score" by latest symbols
		if (msc - std::stof(data.substr(pos1, pos2 - pos1)) < 0.1)
			result += " or " + tmp;
		else break;
	}
	return result;
}

std::string mCloudApi::getData()
{
	return this->data;
}