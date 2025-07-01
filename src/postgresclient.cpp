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

PGresult* PostgresClient::requestSql(const std::string& query) {
    return PQexec(connection, query.c_str());
}

PGconn* PostgresClient::getConnection() {
    return connection;
}
