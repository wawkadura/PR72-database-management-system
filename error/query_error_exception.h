#ifndef QUERY_ERROR_EXCEPTION_H
#define QUERY_ERROR_EXCEPTION_H

class QueryErrorException
{
private:
    std::string msg_;

public:
    QueryErrorException(const std::string &msg) {}
    std::string getMessage() const;
    ~QueryErrorException() {}
};

#endif