#include "mCurl.h"
#include <iostream>
mCurl::mCurl()
{
	list = nullptr;
	url = "";
	key = "";
	data = "";
}

/*mCurl::~mCurl()
{
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}*/

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{

	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

bool mCurl::Initialize()
{
	//curl_global_init(CURL_GLOBAL_DEFAULT);
	if (!curl) {
		return false;
	}
	return true;
}

void mCurl::setURL(std::string url)
{
	this->url = url;
	std::cout << this->url << std::endl;
}

std::string mCurl::getURL()
{
	return this->url;
}

void mCurl::setKey(std::string key)
{
	this->key = key;
}

std::string mCurl::getKey()
{
	return this->key;
}

void mCurl::setData(std::string data)
{
	this->data = data;
	std::cout << this->data << std::endl;
}

std::string mCurl::getData()
{
	return this->data;
}

void mCurl::setList(curl_slist *list)
{
	std::cout << "list was set" << std::endl;
	this->list = list;
}

curl_slist * mCurl::getList()
{
	return list;
}

void mCurl::setNewSession(CURL * session)
{
	curl = session;
}

CURL * mCurl::getCURL()
{
	return curl;
}

bool mCurl::setParams(std::string &data)
{
	if (!url.empty()) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	}
	else {
		return false;
	}
	if (!this->data.empty()) {
		curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, this->data.c_str());
	}
	else {
		std::cout << "not set data" << std::endl;
		return false;
	}
	if (list) {
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	}
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
	return true;
}

bool mCurl::sendRequest()
{

	if (curl_easy_perform(curl) != CURLcode::CURLE_OK) {
		return false;
	}
	curl_easy_cleanup(curl);
	return true;
}


