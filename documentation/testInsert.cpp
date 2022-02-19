#include <iostream>

#include "../queries/insert_query.cpp"

using namespace std;

int main()
{
    cout << "Commencons" << endl;
    DbInfo d("db");
    try
    {
        InsertQuery p("insert INTO tb1 values", d);
    }
    catch (const QueryErrorException &e)
    {
        std::cout << e.getMessage() << '\n';
    }
    return 0;
}