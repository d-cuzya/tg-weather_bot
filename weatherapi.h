#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <iostream>
#include "curleasy.h"

class WeatherApi
{
public:
    void getWeatherByCord(const double& latitude, const double& longitude);
    WeatherApi(const std::string& _url);
private:
    std::string url;
};

#endif // WEATHERAPI_H
