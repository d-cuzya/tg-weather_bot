#ifndef POSTGRESCLIENT_H
#define POSTGRESCLIENT_H

#include <libpq-fe.h>
#include <cstdint>
#include <string>
#include <iostream>
#include <cstring>

class PostgresClient
{
public:
    bool connectToBD(const std::string& connectInfo);
    bool getCoords(const std::int64_t& userId, double *latitude, double *longitude);
    bool addUser(const std::int64_t& userId);
    bool saveCoord(const std::int64_t& userId, double *latitude, double *longitude); // dodelat
    bool updateCoord(const std::int64_t& userId, double *latitude, double *longitude); // dodelat
    bool existsUser(const std::int64_t& userId);
    bool existsCoord(const std::int64_t& userId);
    //false - No limit
    // true - The limit has been exceeded
    bool checkLimit(const std::int64_t& userId);
    void countIncrement(const std::int64_t& userId);
    PGresult* requestSql(const std::string& query);
    PGconn* getConnection();

    static PostgresClient* getInstance();
    ~PostgresClient();
private:
    PostgresClient();
    PostgresClient(const PostgresClient&) = delete;
    PostgresClient operator=(const PostgresClient&) = delete;
    static PostgresClient* instance;

    PGconn* connection;
};

#endif // POSTGRESCLIENT_H
