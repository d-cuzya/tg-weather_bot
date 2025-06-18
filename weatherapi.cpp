#include "weatherapi.h"


WeatherApi::WeatherApi(const std::string& _url) {
    this->url = _url;
}

// CurlEasy::getInstance()->createRequest(this->url + "forecast?lat="+ std::to_string(latitude) +"&lon="+ std::to_string(longitude) +"&appid=" + WEATHERAPI_KEY + "&lang=ru&cnt=6&units=metric", responce);
// https://api.openweathermap.org/data/2.5/weather?lat=54.165226&lon=37.564373&appid=866e386a75138b5efae8a5eaec6e53f9&lang=ru&units=metric
std::string WeatherApi::getCurrentWeatherByCord(const double& latitude, const double& longitude) {
    std::string response;
    CurlEasy::getInstance()->createRequest(this->url + "weather?lat=" + std::to_string(latitude) +"&lon="+ std::to_string(longitude) +"&appid=" + WEATHERAPI_KEY + "&lang=ru&cnt=6&units=metric",response);
    return response;
}

std::string WeatherApi::getForecastWeatherByCord(const double& latitude, const double& longitude) {
    std::string response;
    CurlEasy::getInstance()->createRequest(this->url + "forecast?lat="+ std::to_string(latitude) +"&lon="+ std::to_string(longitude) +"&appid=" + WEATHERAPI_KEY + "&lang=ru&cnt=6&units=metric", response);
    return response;
}
