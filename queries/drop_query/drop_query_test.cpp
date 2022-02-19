#include <iostream>
#include <vector>
#include "drop_table_query.cpp"

using namespace std;

struct test
{
    string title;
    string query;
    bool IsCorrect;
};

int main()
{
    DbInfo db("e");
    cout << "############### UNIT TEST : UPDATE QUERY CLASS #################" << endl;
    vector<test> tests = {
        {
            title : "All good",
            query : "table1;",
            IsCorrect : true,
        },
    };
    for (int i = 0; i < tests.size(); i++)
    {
        cout << "-------------------------------------" << endl;
        cout << "TEST " << i + 1 << " : " << tests[i].title << endl;
        bool error = false;
        string message = "";
        try
        {
            DropTableQuery query = DropTableQuery(tests[i].query, db);
            query.execute();
        }
        catch (const QueryErrorException &e)
        {
            error = true;
            message = e.getMessage();
        }
        catch (const exception &e)
        {
            error = true;
            message = "Unkown error";
        }
        if (error == tests[i].IsCorrect)
        {
            cout << "FAILED :\n\t expected(IsCorrect=" << tests[i].IsCorrect << ") \n\treceived(IsCorrect=" << !error << ") " << endl;
            if (message != "")
            {
                cout << "\t exception message :" << message << endl;
            }
        }
        else
        {
            cout << "SUCCESS ! :\n\t (error=" << error << ") \n\t (message= " << message << ")" << endl;
        }
    }

    return 0;
}
