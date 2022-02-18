#include <iostream>
#include "db_info.cpp"
#include "queries/query_factory.cpp"
#include "utils.h"
#include <map>

int main()
{
    DbInfo db("db");
    cout << "-- Welcome to ooooouuuu database management system -- " << endl;
    bool start = true;
    while (1)
    {
        bool error = false;
        string errorMessage = "";
        string input = "";

        if (start)
        {
            cout << "Here are all the tables available :  " << endl;
            vector<string> tables = db.getTables();
            for (auto table : tables) cout << "\t- " << table << endl;
            if (tables.size() == 0)cout << "none" << endl;
            
            // display the list of tables
            start = false;
        }
        cout << "please enter a sql query (or tap exit) :" << endl;
        cin >> input; // get user input from the keyboard

        if (input == "exit")
            break;
        try
        {
            QueryFactory factory;
            SqlQuery *query = factory.generate_query(input, db);
            query->check();
            query->execute();
        }
        catch (const QueryErrorException &e)
        {
            error = true;
            errorMessage = e.getMessage();
        }
        catch (const exception &e)
        {
            error = true;
            errorMessage = "Unkown error : please try again";
        }

        if (error)
        {
            cout << "Error : " << errorMessage << endl;
            cout << "try another query :" << endl;
        }
        else
        {
            cout << "Your query have been successfuly executed !" << endl;
        }
    }

    cout << " -- exiting oooouuu database management system ----" << endl;
    return 0;
}
