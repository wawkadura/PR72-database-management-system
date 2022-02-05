#include "query_error.h"

using namespace std;

QueryError::QueryError(string m) {
    QueryError::this.message = m ;
}

QueryError::getMessage() string {
    return QueryError::this.message
}