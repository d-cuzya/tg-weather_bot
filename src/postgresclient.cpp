#include "postgresclient.h"

PostgresClient* PostgresClient::instance = nullptr;

PostgresClient::PostgresClient() {}
PostgresClient::~PostgresClient() {
    PQfinish(connection);
}

PostgresClient* PostgresClient::getInstance() {
    if (!instance) {
        instance = new PostgresClient();
    }
    return instance;
}

bool PostgresClient::connectToBD(const std::string& connectInfo) {
    this->connection = PQconnectdb(connectInfo.c_str());
    if (PQstatus(this->connection) != CONNECTION_OK) {
        printf("PQ Error: %s\n", PQerrorMessage(connection));
        return false;
    }
    return true;
}

bool PostgresClient::getCoords(const std::int64_t& userId, double *latitude, double *longitude) {
    PGresult* res = PostgresClient::getInstance()->requestSql("SELECT latitude, longitude FROM coords WHERE userid = "+std::to_string(userId)+";");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        return false;
    }
    *latitude = std::stod(PQgetvalue(res, 0, 0));
    *longitude = std::stod(PQgetvalue(res, 0, 1));
    PQclear(res);
    return true;
}

bool PostgresClient::addUser(const std::int64_t& userId) {
    PGresult* res = PQexec(connection, ("insert into users(telegramid) values (" + std::to_string(userId) + ")").c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        return false;
    }
    PQclear(res);
    return true;
}

bool PostgresClient::existsUser(const std::int64_t& userId) {
    PGresult* res = PostgresClient::getInstance()->requestSql("select exists(select 1 from users where telegramid = "+ std::to_string(userId) +")");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        return false;
    }
    bool result = strcmp(PQgetvalue(res, 0, 0), "t") == 0;
    PQclear(res);
    return result;
}

bool PostgresClient::existsCoord(const std::int64_t& userId) {
    PGresult* res = PostgresClient::getInstance()->requestSql("select exists(select 1 from coords where userid = "+ std::to_string(userId) +")");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        // fprintf(stderr, "DECLARE CURSOR failed: %s", PQerrorMessage(connection));
        PQclear(res);
        return false;
    }
    bool result = strcmp(PQgetvalue(res, 0, 0), "t") == 0;
    PQclear(res);
    return result;
}

// false - No limit
// true - The limit has been exceeded
bool PostgresClient::checkLimit(const std::int64_t& userId) {
    PGresult* res = PostgresClient::getInstance()->requestSql("SELECT count_msg, max_msg FROM users WHERE telegramid = "+std::to_string(userId)+";");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        return false;
    }
    bool result = atoi(PQgetvalue(res, 0, 0)) < atoi(PQgetvalue(res, 0, 1));
    PQclear(res);
    return !result;
}

void PostgresClient::countIncrement(const std::int64_t& userId) {
    PGresult* res = PostgresClient::getInstance()->requestSql("UPDATE users SET count_msg = count_msg + 1 WHERE telegramid = "+std::to_string(userId)+";");
    if (!PQresultStatus(res) == PGRES_COMMAND_OK) {
        std::cout << "Error SQL increment: " << PQerrorMessage(connection) << std::endl;
    }
    PQclear(res);
    return;
}

bool PostgresClient::saveCoord(const std::int64_t& userId, double *latitude, double *longitude) {
    PGresult* addCoords = PostgresClient::getInstance()->requestSql("INSERT INTO coords(userid, latitude, longitude) values(" + std::to_string(userId) + ", "+ std::to_string(*latitude) +", "+ std::to_string(*longitude)+ ");");
    if (PQresultStatus(addCoords) != PGRES_COMMAND_OK) {
        PQclear(addCoords);
        return false;
    }
    PQclear(addCoords);
    return true;
}

bool PostgresClient::updateCoord(const std::int64_t& userId, double *latitude, double *longitude) {
    PGresult* updateCoords = PostgresClient::getInstance()->requestSql("UPDATE coords SET latitude = "+ std::to_string(*latitude) +", longitude = "+ std::to_string(*longitude)+ " WHERE userid = "+std::to_string(userId)+";");
    if (PQresultStatus(updateCoords) != PGRES_COMMAND_OK) {
        PQclear(updateCoords);
        return false;
    }
    PQclear(updateCoords);
    return true;
}

PGresult* PostgresClient::requestSql(const std::string& query) {
    return PQexec(connection, query.c_str());
}

PGconn* PostgresClient::getConnection() {
    return connection;
}
