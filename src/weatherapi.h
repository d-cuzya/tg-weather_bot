#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <iostream>
#include <vector>
#include <string>
#include "cpr/cpr.h"

class WeatherApi
{
public:
    static WeatherApi* getInstance();

    std::string getCurrentWeatherByCord(const double& latitude, const double& longitude);
    std::string getForecastWeatherByCord(const double& latitude, const double& longitude);
    void setUrl(const std::string& _url);
private:
    WeatherApi();
    WeatherApi(const WeatherApi&) = delete;
    WeatherApi operator=(const WeatherApi&) = delete;
    ~WeatherApi();

    std::string url;
    static WeatherApi* instance;
};

#endif // WEATHERAPI_H
