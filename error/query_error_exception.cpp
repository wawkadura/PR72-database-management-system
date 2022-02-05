#include "query_error_exception.h"

using namespace std;

QueryErrorException::QueryErrorException(const string &msg) : msg_(msg) {}

string QueryErrorException::getMessage() const { return (msg_); }