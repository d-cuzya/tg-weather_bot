#ifndef POSTGRESCLIENT_H
#define POSTGRESCLIENT_H

#include <libpq-fe.h>
#include <string>

class PostgresClient
{
public:
    bool connectToBD(const std::string& connectInfo);
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
