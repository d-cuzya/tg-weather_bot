#include "mytgbot.h"

mytgbot* mytgbot::instance = nullptr;

mytgbot::~mytgbot() {
    delete bot;
    delete instance;
}

mytgbot::mytgbot() {}

mytgbot* mytgbot::getInstance() {
    if (!instance) {
        instance = new mytgbot;
    }
    return instance;
}

void mytgbot::setToken(const std::string& _token) {
    bot = new TgBot::Bot(_token);
}

void mytgbot::initLogic() {
    bot->getEvents().onCommand("start", [this](TgBot::Message::Ptr message) {
        bot->getApi().sendMessage(message->chat->id,"Привет, " + message->from->firstName +
                                                        "!\nЯ бот, который поможет тебе узнать погоду.\n"
                                                        "Просто отправь мне свою геолокацию, и я пришлю тебе актуальный прогноз.\n"
                                                        "Или введите команду /weather, чтобы использовать геолокацию из предыдущего запроса.\n"
                                                        "Команда /help расскажет вам про устроитсво этого бота.\n"
                                                        "(Данные будут сохранены, если хотите удалить, введите /forget_me)");
        if (!PostgresClient::getInstance()->existsUser(message->from->id)) {
            if (!PostgresClient::getInstance()->addUser(message->from->id)) {
                bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [91]");
            }
        }
    });
    bot->getEvents().onCommand("weather", [this](TgBot::Message::Ptr message) {
        if (PostgresClient::getInstance()->existsCoord(message->from->id)) {
            TgBot::Message::Ptr msG = bot->getApi().sendMessage(message->chat->id, "Данные о геолокации взяты из прошлого запроса\\! Ожидаите\\.\\.\\.",nullptr, nullptr, nullptr, "MarkdownV2");
            if (PostgresClient::getInstance()->checkLimit(message->from->id)) {
                bot->getApi().sendMessage(message->chat->id, "У вас привышено количество запросов в день! Подождите сутки чтобы сбросилось количество отправленных запросов.");
                return;
            }
            double latitude;
            double longitude;
            if (!PostgresClient::getInstance()->getCoords(message->from->id, &latitude, &longitude)) {
                bot->getApi().sendMessage(message->chat->id, "Произошла ошибка во время получения координат, повторите запрос позже или обратитесь в поддержку!");
            }
            std::string msg = "";
            std::string currentWeather = WeatherApi::getInstance()->getCurrentWeatherByCord(latitude, longitude);
            nlohmann::json currentWeatherData = nlohmann::json::parse(currentWeather);
            msg += "☁️ Текущая погода ☁️\n";
            msg += "```\n";
            msg += "🌡 " + std::format("{:.2f}", currentWeatherData["main"]["temp"].get<double>()) + "°C\n";
            msg += "🖼 " + currentWeatherData["weather"][0]["description"].get<std::string>() + "\n";
            msg += "```\n";
            std::string forecastWeathe = WeatherApi::getInstance()->getForecastWeatherByCord(latitude, longitude);
            nlohmann::json forecastWeatheData = nlohmann::json::parse(forecastWeathe);
            msg += "☁️ Прогноз погоды ☁️\n";
            for (auto& item : forecastWeatheData["list"]) {
                msg += "```\n";
                msg += "⏱️ " + item["dt_txt"].get<std::string>() + "\n";
                msg += "🌡 " + std::format("{:.2f}", item["main"]["temp"].get<double>()) + "°C\n";
                msg += "🖼 " + item["weather"][0]["description"].get<std::string>();
                msg += "```\n";
            }
            bot->getApi().editMessageText(
                msg,
                message->chat->id,
                msG->messageId,
                "",
                "MarkdownV2"
            );
            PostgresClient::getInstance()->countIncrement(message->from->id);
        } else {
            bot->getApi().sendMessage(message->chat->id, "Вы ещё не отправляли геолокацию! Отправьте свою геолокацию и я отправлю расписание погоды.");
        }
    });
    bot->getEvents().onCommand("help", [this](TgBot::Message::Ptr message) {
        bot->getApi().sendMessage(message->chat->id, "Чтобы отправить геолокацию боту, вам нужно нажать на значёр прещепки рядом с полем ввода. Там выбрать \"Отправить геолокацию\".");
    });
    bot->getEvents().onCommand("forget_me", [this](TgBot::Message::Ptr message) {
        PGresult* incrementCount = PostgresClient::getInstance()->requestSql("delete from coords where userid = "+std::to_string(message->from->id)+";");
        if (PQresultStatus(incrementCount) == PGRES_COMMAND_OK) {
            bot->getApi().sendMessage(message->chat->id, "Данные успешно удалены!");
        } else {
            bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [52]");
        }
    });
    bot->getEvents().onAnyMessage([this](TgBot::Message::Ptr message) {
        if (message->location) {
            if (PostgresClient::getInstance()->checkLimit(message->from->id)) {
                bot->getApi().sendMessage(message->chat->id, "У вас привышено количество запросов в день! Подождите сутки чтобы сбросилось количество отправленных запросов.");
                return;
            }
            double latitude = message->location->latitude;
            double longitude = message->location->longitude;
            std::string msg = "";
            std::string currentWeather = WeatherApi::getInstance()->getCurrentWeatherByCord(latitude, longitude);
            nlohmann::json currentWeatherData = nlohmann::json::parse(currentWeather);
            msg += "☁️ Текущая погода ☁️\n";
            msg += "```\n";
            msg += "🌡 " + std::format("{:.2f}", currentWeatherData["main"]["temp"].get<double>()) + "°C\n";
            msg += "🖼 " + currentWeatherData["weather"][0]["description"].get<std::string>() + "\n";
            msg += "```\n";
            std::string forecastWeathe = WeatherApi::getInstance()->getForecastWeatherByCord(latitude, longitude);
            nlohmann::json forecastWeatheData = nlohmann::json::parse(forecastWeathe);
            msg += "☁️ Прогноз погоды ☁️\n";
            for (auto& item : forecastWeatheData["list"]) {
                msg += "```\n";
                msg += "⏱️ " + item["dt_txt"].get<std::string>() + "\n";
                msg += "🌡 " + std::format("{:.2f}", item["main"]["temp"].get<double>()) + "°C\n";
                msg += "🖼 " + item["weather"][0]["description"].get<std::string>();
                msg += "```\n";
            }
            bot->getApi().sendMessage(message->chat->id, msg, nullptr, nullptr, nullptr, "MarkdownV2");
            PostgresClient::getInstance()->countIncrement(message->from->id);
            if (PostgresClient::getInstance()->existsCoord(message->from->id)) {
                PostgresClient::getInstance()->updateCoord(message->from->id,  &latitude, &longitude);
            } else {
                PostgresClient::getInstance()->saveCoord(message->from->id,  &latitude, &longitude);
            }
        }
    });
}

void mytgbot::startBot() {
    try {
        TgBot::TgLongPoll longPoll(*bot);
        printf("Bot @%s was started.\n", bot->getApi().getMe()->username.c_str());
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}
