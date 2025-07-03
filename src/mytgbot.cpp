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
        PGresult* check = PostgresClient::getInstance()->requestSql("select exists(select 1 from users where telegramid = "+ std::to_string(message->from->id) +")");
        if (PQresultStatus(check) != PGRES_TUPLES_OK) {
            bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! Повторите запрос позже.\n" + (std::string)PQresultErrorMessage(check));
        } else {
            if (strcmp(PQgetvalue(check, 0, 0), "f") == 0) {
                PGresult* addUser = PostgresClient::getInstance()->requestSql("insert into users(telegramid) values("+std::to_string(message->from->id)+")");
                if (PQresultStatus(addUser) != PGRES_COMMAND_OK) {
                    bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [91]");
                }
            }
        }
    });
    bot->getEvents().onCommand("weather", [this](TgBot::Message::Ptr message) {
        std::cout << "weather\tThreadId:\t" << std::this_thread::get_id() << "\n";
        PGresult* res = PostgresClient::getInstance()->requestSql("SELECT EXISTS(SELECT 1 FROM coords WHERE userid = " + std::to_string(message->from->id) +")");
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! Повторите запрос позже.");
            return;
        } else {
            if (strcmp(PQgetvalue(res, 0, 0), "t") == 0) {
                TgBot::Message::Ptr msG = bot->getApi().sendMessage(message->chat->id, "Данные о геолокации взяты из прошлого запроса\\! Ожидаите\\.\\.\\.",nullptr, nullptr, nullptr, "MarkdownV2");
                std::cout << std::to_string(msG->messageId) << std::endl;

                PGresult* countCheck = PostgresClient::getInstance()->requestSql("SELECT count_msg, max_msg FROM users WHERE telegramid = "+std::to_string(message->from->id)+";");
                if (PQresultStatus(countCheck) != PGRES_TUPLES_OK) {
                    bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [84]");
                    return;
                }
                if (atoi(PQgetvalue(countCheck, 0, 0)) >= atoi(PQgetvalue(countCheck, 0, 1))) {
                    bot->getApi().sendMessage(message->chat->id, "У вас привышено количество запросов в день! Подождите сутки чтобы сбросилось количество отправленных запросов.");
                    return;
                }

                PGresult* coordGet = PostgresClient::getInstance()->requestSql("SELECT latitude, longitude FROM coords WHERE userid = "+std::to_string(message->from->id)+";");
                if (PQresultStatus(coordGet) != PGRES_TUPLES_OK) {
                    bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [85]");
                    return;
                }

                double latitude = std::stod(PQgetvalue(coordGet, 0, 0));
                double longitude = std::stod(PQgetvalue(coordGet, 0, 1));
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
                // bot->getApi().editMessageText(
                //     static_cast<int64_t>(message->chat->id),
                //     static_cast<int32_t>(msG->messageId),
                //     msg,
                //     "MarkdownV2",    // parseMode
                //     false,           // disableWebPagePreview
                //     nullptr          // replyMarkup
                // );
                bot->getApi().sendMessage(message->chat->id, msg, nullptr, nullptr, nullptr, "MarkdownV2");

                PGresult* incrementCount = PostgresClient::getInstance()->requestSql("UPDATE users SET count_msg = count_msg + 1 WHERE telegramid = "+std::to_string(message->from->id)+";");
                if (PQresultStatus(incrementCount) == PGRES_COMMAND_OK) {
                    printf("Команда UPDATE users SET count_msg = count_msg + 1 WHERE telegramid = $1; выполнена успешно\n");
                } else {
                    bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [89]");
                }
            } else if (strcmp(PQgetvalue(res, 0, 0), "f") == 0) {
                bot->getApi().sendMessage(message->chat->id, "Вы ещё не отправляли геолокацию! Отправьте свою геолокацию и я отправлю расписание погоды.");
            }
        }
    });
    bot->getEvents().onCommand("help", [this](TgBot::Message::Ptr message) {
        std::cout << "help\tThreadId:\t" << std::this_thread::get_id() << "\n";
        bot->getApi().sendMessage(message->chat->id, "Чтобы отправить геолокацию боту, вам нужно нажать на значёр прещепки рядом с полем ввода. Там выбрать \"Отправить геолокацию\".");
    });
    bot->getEvents().onCommand("forget_me", [this](TgBot::Message::Ptr message) {
        std::cout << "forget_me\tThreadId:\t" << std::this_thread::get_id() << "\n";
        PGresult* incrementCount = PostgresClient::getInstance()->requestSql("delete from coords where userid = "+std::to_string(message->from->id)+";");
        if (PQresultStatus(incrementCount) == PGRES_COMMAND_OK) {
            bot->getApi().sendMessage(message->chat->id, "Данные успешно удалены!");
        } else {
            bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [52]");
        }
    });
    bot->getEvents().onAnyMessage([this](TgBot::Message::Ptr message) {
        std::cout << "anyMsg\tThreadId:\t" << std::this_thread::get_id() << "\n";
        if (message->location) {
            PGresult* countCheck = PostgresClient::getInstance()->requestSql("SELECT count_msg, max_msg FROM users WHERE telegramid = "+std::to_string(message->from->id)+";");
            if (PQresultStatus(countCheck) != PGRES_TUPLES_OK) {
                bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [90]");
                return;
            }
            if (atoi(PQgetvalue(countCheck, 0, 0)) >= atoi(PQgetvalue(countCheck, 0, 1))) {
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

            PGresult* incrementCount = PostgresClient::getInstance()->requestSql("UPDATE users SET count_msg = count_msg + 1 WHERE telegramid = "+std::to_string(message->from->id)+";");
            if (PQresultStatus(incrementCount) == PGRES_COMMAND_OK) {
                printf("Команда UPDATE users SET count_msg = count_msg + 1 WHERE telegramid = $1; выполнена успешно\n");
            } else {
                bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [89]");
            }

            PGresult* saveCord = PostgresClient::getInstance()->requestSql("SELECT EXISTS(SELECT 1 FROM coords WHERE userid = " + std::to_string(message->from->id) +")");
            if (PQresultStatus(saveCord) != PGRES_TUPLES_OK) {
                bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [88]");
                return;
            } else {
                if (strcmp(PQgetvalue(saveCord, 0, 0), "t") == 0) {
                    PGresult* updateCoords = PostgresClient::getInstance()->requestSql("UPDATE coords SET latitude = "+ std::to_string(message->location->latitude) +", longitude = "+ std::to_string(message->location->longitude)+ " WHERE userid = "+std::to_string(message->from->id)+";");
                    if (PQresultStatus(updateCoords) != PGRES_COMMAND_OK) {
                        bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [87]");
                    }
                } else if (strcmp(PQgetvalue(saveCord, 0, 0), "f") == 0) {
                    PGresult* updateCoords = PostgresClient::getInstance()->requestSql("INSERT INTO coords(userid, latitude, longitude) values(" + std::to_string(message->from->id) + ", "+ std::to_string(message->location->latitude) +", "+ std::to_string(message->location->longitude)+ ");");
                    if (PQresultStatus(updateCoords) != PGRES_COMMAND_OK) {
                        bot->getApi().sendMessage(message->chat->id, "Внутренняя ошибка сервера! [86]");
                    }
                }
            }
        }
    });
}

void mytgbot::startBot() {
    try {
        // printf("Bot @%s was started.\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(*bot);
        while (true) {
            // std::cout << "longPoll\tThreadId:\t" << std::this_thread::get_id() << "\n";
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}
