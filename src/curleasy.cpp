#include "curleasy.h"

CurlEasy* CurlEasy::instance = nullptr;
CurlEasy::CurlEasy() {}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

CurlEasy* CurlEasy::getInstance() {
    if (!instance) {
        instance = new CurlEasy();
    }
    return instance;
}

bool CurlEasy::fetchData(const std::string& url, std::string& response) {
    CURL* curl = curl_easy_init();
    if(!curl) return false;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return false;
    }
    return true;
}

bool CurlEasy::createRequest(const std::string& url, std::string& response) {
    if(!fetchData(url, response)) {
        std::cerr << "Failed to fetch data" << std::endl;
        return false;
    }
    return true;
}
