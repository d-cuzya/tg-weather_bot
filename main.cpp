#include <iostream>
#include <tgbot/tgbot.h>
#include <format>
#include "weatherapi.h"
#include "json.hpp"
// #include <boost/date_time/local_time/local_time.hpp>

WeatherApi weatherApi("https://api.openweathermap.org/data/2.5/");

int main()
{
    TgBot::Bot bot(TG_TOKEN);

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Привет, " + message->from->firstName + "!\nЯ бот, который поможет тебе узнать погоду. Просто отправь мне свою геолокацию, и я пришлю тебе актуальный прогноз. (Данные будут сохранены, если хотите удалить, введите /forget_me )");
    });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (message->location) {
            double latitude = message->location->latitude;
            double longitude = message->location->longitude;
            std::string msg = "";
            std::string currentWeather = weatherApi.getCurrentWeatherByCord(latitude, longitude);
            nlohmann::json currentWeatherData = nlohmann::json::parse(currentWeather);
            msg += "☁️ Текущая погода ☁️\n";
            msg += "```\n";
            msg += "🌡 " + std::format("{:.2f}", currentWeatherData["main"]["temp"].get<double>()) + "°C\n";
            msg += "🖼 " + currentWeatherData["weather"][0]["description"].get<std::string>() + "\n";
            msg += "```\n";
            std::string forecastWeathe = weatherApi.getForecastWeatherByCord(latitude, longitude);
            nlohmann::json forecastWeatheData = nlohmann::json::parse(forecastWeathe);
            msg += "☁️ Прогноз погоды ☁️\n";
            for (auto& item : forecastWeatheData["list"]) {
                msg += "```\n";
                msg += "⏱️ " + item["dt_txt"].get<std::string>() + "\n";
                msg += "🌡 " + std::format("{:.2f}", item["main"]["temp"].get<double>()) + "°C\n";
                msg += "🖼 " + item["weather"][0]["description"].get<std::string>();
                // msg += "\n";
                msg += "```\n";
            }

            bot.getApi().sendMessage(message->chat->id, msg, nullptr, nullptr, nullptr, "MarkdownV2");
        }
    });

    try {
        printf("Bot @%s was started.\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
