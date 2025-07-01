#include "mytgbot.h"

mytgbot* mytgbot::instance = nullptr;

mytgbot::mytgbot() {
    this->bot = new TgBot::Bot((std::getenv("TG_TOKEN")));
}

mytgbot* mytgbot::getInstance() {
    if (!instance) {
        instance = new mytgbot();
    }
    return instance;
}
