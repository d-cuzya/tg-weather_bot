#include "weatherapi.h"

WeatherApi* WeatherApi::instance = nullptr;
WeatherApi* WeatherApi::getInstance() {
    if (!instance) {
        instance = new WeatherApi;
    }
    return instance;
}
WeatherApi::WeatherApi() {}
WeatherApi::~WeatherApi() {
    delete instance;
}
void WeatherApi::setUrl(const std::string& _url) {
    url = _url;
}

std::string WeatherApi::getCurrentWeatherByCord(const double& latitude, const double& longitude) {
    cpr::Response r = cpr::Get(cpr::Url{this->url + "weather"},
                               cpr::Parameters{{"lat", std::to_string(latitude)},
                                               {"lon", std::to_string(longitude)},
                                               {"appid", std::getenv("WEATHERAPI_KEY")},
                                               {"lang", "ru"},
                                               {"cnt", "6"},
                                               {"units", "metric"}});
    return r.text;
}
std::string WeatherApi::getForecastWeatherByCord(const double& latitude, const double& longitude) {
    cpr::Response r = cpr::Get(cpr::Url{this->url + "forecast"},
                               cpr::Parameters{{"lat", std::to_string(latitude)},
                                               {"lon", std::to_string(longitude)},
                                               {"appid", std::getenv("WEATHERAPI_KEY")},
                                               {"lang", "ru"},
                                               {"cnt", "6"},
                                               {"units", "metric"}});
    return r.text;
}
