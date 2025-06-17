#include "weatherapi.h"

WeatherApi::WeatherApi(const std::string& _url) {
    this->url = _url;
}

void WeatherApi::getWeatherByCord(const double& latitude, const double& longitude) {
    std::string responce;
    std::cout << this->url + "forecast?lat="+ std::to_string(latitude) +"&lon="+ std::to_string(longitude) +"&appid=" + WEATHERAPI_KEY << std::endl;
    CurlEasy::getInstance()->createRequest(this->url + "forecast?lat="+ std::to_string(latitude) +"&lon="+ std::to_string(longitude) +"&appid=" + WEATHERAPI_KEY, responce);
    std::cout << responce << std::endl;
}
