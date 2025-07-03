#ifndef MYTGBOT_H
#define MYTGBOT_H

#include <tgbot/tgbot.h>
#include <libpq-fe.h>
#include <json.hpp>
#include "weatherapi.h"
#include "postgresclient.h"

class mytgbot
{
public:
    void setToken(const std::string& _url);
    void initLogic();
    void startBot();
    static mytgbot* getInstance();
    ~mytgbot();
private:
    static mytgbot* instance;
    mytgbot();
    mytgbot(const mytgbot&) = delete;
    mytgbot operator=(const mytgbot&) = delete;

    TgBot::Bot* bot;
};

#endif // MYTGBOT_H
