#ifndef CURLEASY_H
#define CURLEASY_H

#include <curl/curl.h>
#include <iostream>

class CurlEasy
{
public:
    static CurlEasy* getInstance();
    bool createRequest(const std::string& url, std::string& response);
private:
    CurlEasy();
    CurlEasy(const CurlEasy&) = delete;
    CurlEasy operator=(const CurlEasy&) = delete;
    static CurlEasy* instance;

    // static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
    bool fetchData(const std::string& url, std::string& response);
};

#endif // CURLEASY_H
