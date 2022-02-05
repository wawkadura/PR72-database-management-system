#ifndef QUERY_ERROR_H
#define QUERY_ERROR_H

class QueryError {
private:
    std::string message;
public:
    QueryError(std::string m);
    std::string getMessage();
};

#endif