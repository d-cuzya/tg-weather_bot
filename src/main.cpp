#include <iostream>
#include <format>
#include <thread>
#include "json.hpp"
#include <stdlib.h>
#include <libpq-fe.h>
#include "weatherapi.h"
#include "postgresclient.h"
#include "dotenv.h"
#include "mytgbot.h"

int main()
{
    dotenv::init("./../../.env");
    mytgbot::getInstance()->setToken(std::getenv("TG_TOKEN"));
    mytgbot::getInstance()->initLogic();
    WeatherApi::getInstance()->setUrl("https://api.openweathermap.org/data/2.5/");
    if (!PostgresClient::getInstance()->connectToBD("host=" + std::string(std::getenv("DB_HOST")) + " port="+ std::string(std::getenv("DB_PORT")) +" dbname=" + std::string(std::getenv("DB_NAME")) +" user="+ std::string(std::getenv("DB_USER")) +" password=" + std::string(std::getenv("DB_PASSWORD")))) {
        return 1;
    }

    mytgbot::getInstance()->startBot();
    return 0;
}
