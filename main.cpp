#include <iostream>
#include <tgbot/tgbot.h>
#include "weatherapi.h"

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

            weatherApi.getWeatherByCord(latitude, longitude);
            bot.getApi().sendMessage(message->chat->id, "Ok");
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
