#include <cstdlib>
#include <memory>     // unique_ptr
#include <exception>
#include <vector> 
#include <fstream>

// MySQL Connector for C++ headers
#include <mysql_driver.h>     // Its methods are in a static library libmysqlcppconn-static 
#include <mysql_connection.h> 

#include <cppconn/driver.h>   // Its methods are in a dynamic library libmysqlcppconn  
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

//--#include "csvparser.h"
#include "petition-parser.h"
#include "hidden/db_credentials.h" // database credentials
#include <iostream>               // debug
using namespace std;
using namespace sql; 

int main(int argc, char** argv) 
{
    
  if (argc != 2) {
  
      cerr << "Please re-run with the input file name as the first parameter.\n";
      return 0;
  } 

/*
 * Format of CSV file:
 * 
 *   Signer number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
 *
 *   Regex returns: signer #er, date, city, state, country, comments.
 */
//--CsvParser csv_parser(argv[1], R"(^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*)$)" );
PetitionParser csv_parser(argv[1]);
   
int lineno = 1;

while (csv_parser.hasmoreLines()) {  

   smatch matches = csv_parser.parseNextLine(); 
   
  for(auto iter = ++matches.begin(); iter != matches.end(); ++iter) { // Not correct
      
      auto x = iter->str();
      
      cout << x << endl;
   }

   continue;
  
    ++lineno;
  }  // end while   
 
  return(0);
}
