#pragma once
#include "dependents.h"

#pragma once

class mCurl {
public:
	mCurl();
	//~mCurl();
	
	bool Initialize();

	void setURL(std::string url);
	std::string getURL();

	void setKey(std::string key);
	std::string getKey();

	void setData(std::string data);
	std::string getData();

	void setList(curl_slist *list);
	curl_slist *getList();

	void setNewSession(CURL* session);

	CURL *getCURL();

	bool setParams(std::string &data);
	bool sendRequest();
private:
	CURL *curl;
	std::string url;
	std::string key;
	std::string data;
	curl_slist *list;
};