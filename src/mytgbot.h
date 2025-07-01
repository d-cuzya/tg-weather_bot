#ifndef MYTGBOT_H
#define MYTGBOT_H

#include <tgbot/tgbot.h>

class mytgbot
{
public:
    static mytgbot* getInstance();
private:
    mytgbot();
    mytgbot(const mytgbot&) = delete;
    static mytgbot* instance;
    TgBot::Bot* bot;
};

#endif // MYTGBOT_H
