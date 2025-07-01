#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <iostream>
#include <vector>
#include <string>
#include "curleasy.h"

class WeatherApi
{
public:
    std::string getCurrentWeatherByCord(const double& latitude, const double& longitude);
    std::string getForecastWeatherByCord(const double& latitude, const double& longitude);
    WeatherApi(const std::string& _url);
private:
    std::string url;
};

#endif // WEATHERAPI_H
