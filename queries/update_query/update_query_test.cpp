#include <iostream>
#include <vector>
#include "../../db_info.cpp"
#include "../query_factory.cpp"
#include "../../error/query_error_exception.h"

using namespace std;

struct test
{
    string title;
    string query;
    bool IsCorrect;
};

void display(SQLDETAILS details)
{
    cout << "DETAILS : ";
    map<string, string>::iterator it;

    for (it = details.setColumnsMapper.begin(); it != details.setColumnsMapper.end(); it++)
    {
        std::cout << it->first // string (key)
                  << ':'
                  << it->second << ",";// string's value
    }

    cout<< endl;
}
int main()
{
    DbInfo db("e");
    cout << "############### UNIT TEST : UPDATE QUERY CLASS #################" << endl;
    vector<test> tests = {
        {
            title : "All good",
            query : "UPDATE table1 SET name='walid' WHERE id=1;",
            IsCorrect : true,
        },
        {
            title : " without SET option",
            query : "UPDATE table1  WHERE id=1;",
            IsCorrect : false,
        },
        {
            title : " without setters",
            query : "UPDATE table1 SET  WHERE id=1;",
            IsCorrect : false,
        },
        {
            title : " invalid setters",
            query : "UPDATE table1 SET  name walid WHERE id=1;",
            IsCorrect : false,
        },
        {
            title : "2 + setters",
            query : "UPDATE table1 SET  name=\"walid\",value=20,age=3 WHERE id=1;",
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
            QueryFactory factory;
            SqlQuery *updateQuery = factory.generate_query(tests[i].query, db);
            display(updateQuery->getSqlDetails());
            updateQuery->check();
            updateQuery->execute();
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
