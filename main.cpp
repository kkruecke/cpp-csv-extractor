#include <cstdlib>
#include <regex>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <exception>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

/*
 *  Uses regular expression support in gcc-4.9 to extract comma separated text from file given in argv[1]. Requires g++-4.9 or higher.
 */
int main(int argc, char** argv) 
{
    ifstream inp;

    if (argc != 2) {

        cerr << "Enter the input file name as the first parameter\n";
        return 0;
    }

    inp.open(argv[1]);
    
    ofstream output(string("outputput.txt"));

    sregex_iterator it_end; // <-- requires g++-4.9

    string line;

    // regular expression for parsing .csv file.
    regex csv_regex{"^(?:(?:\"((?:\"\"|[^\"])+)\"|([^,]*))(?:$|,))+$"};
    
    if (inp.is_open()) {

        while(inp.good()) {

            getline(inp, line);

            try {
                
               sregex_iterator it(line.begin(), line.end(), csv_regex);
               
               if (it->str().empty()) {
                   continue;
               } 
               
               for (std::sregex_iterator i = it; i != it_end; ++i) {
                   
                    // process line
                    output << i->str() << '\n';
               }   
                             
                             
            } catch (exception & e) {
                
                cerr << "exception caught: " << e.what() << '\n';
                cerr << "Terminating" << "\n";
                return 0;
            }
        }
    }

    inp.close();
    output.close();

    /* MySQL Connector for C++ examples in:  /usr/local/src/mysql-connector-c++-1.1.3/examples/ */
   
    return(0);
}

