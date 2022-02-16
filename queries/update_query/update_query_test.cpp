#include <iostream>
#include <vector>
#include "db_info.cpp"
#include "update_query.cpp"
#include "query_error_exception.cpp"

using namespace std;
int main()
{
    DbInfo db("e");
    cout << "############### UNIT TEST : UPDATE QUERY CLASS #################" << endl;
    vector<test> tests = {
        {
            title:"All good",
            query: "table1 SET name='walid' WHERE id=1;",
            IsCorrect: true,
        },
        {
            title:" without SET option",
            query: "table1  WHERE id=1;",
            IsCorrect: true,
        }, 
    };
    for (int i = 0; i < tests.size(); i++)
    {
        cout<< "-------------------------------------" << endl;
        cout<< "TEST "+i<< " : " << tests[i].title<< endl;
        bool error = false;
        string message = "";
        try
        {
            UpdateQuery updateQuery = UpdateQuery(tests[i].query, db);
            updateQuery.check();
            updateQuery.execute();
        }
        catch(const QueryErrorException& e)
        {
            error = true;
            message = e.getMessage();
        }
        catch(const exception& e)
        {
            error = true;
            message ="Unkown error";
        }
        if (error == tests[i].IsCorrect)
        {
            cout << "FAILED :\n\t expected(IsCorrect="<< tests[i].IsCorrect <<") \n\treceived(IsCorrect="<< error <<") " << endl;
            if (message != "")
            {
                cout << "\t exception message :"<< message << endl;
            }
        }else{
            cout << "SUCCESS ! :\n\t error="<< error <<") \n\t message= "<< message << endl;
        }   
    }
    

    return 0;
}

struct test {
    string title;
    string query;
    bool IsCorrect;
};