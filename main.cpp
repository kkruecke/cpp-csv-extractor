#include <cstdlib>
#include <memory>     // unique_ptr
#include <exception>
#include <vector> 
#include <fstream>
#include <regex>

// MySQL Connector for C++ headers
#include <mysql_driver.h>     // Its methods are in a static library libmysqlcppconn-static 
#include <mysql_connection.h> 

#include <cppconn/driver.h>   // Its methods are in a dynamic library libmysqlcppconn  
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "petition-parser.h"
#include "hidden/db_credentials.h" // database credentials
#include <iostream>
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
 */
PetitionParser csv_parser(argv[1]);
   
unique_ptr<Connection> conn { get_driver_instance()->connect(DB_Credentials::Url().c_str(), DB_Credentials::User().c_str(), DB_Credentials::Password().c_str()) };
 
// Set database to use petition database.
unique_ptr< Statement > stmt(conn->createStatement());
 
stmt->execute("USE petition");

//REMOVE conn->setAutoCommit(false);  // We will use transactions.
 
unique_ptr<PreparedStatement> signee_stmt { conn->prepareStatement("INSERT INTO signee(signee_no, date, city, state, country) VALUES(?, ?, ?, ?, ?)") };

unique_ptr<PreparedStatement> comments_stmt { conn->prepareStatement("INSERT INTO comments(signee_id, comments) VALUES(?, ?)") };

unique_ptr<Statement> last_insert_id_stmt { conn->createStatement() };  

// Get max(sigee_no) to determine if petition signers are already in the DB.
unique_ptr<ResultSet> max_signeeResultSet { stmt->executeQuery("select max(signee_no) as max_signee FROM signee") };
 
max_signeeResultSet->first();
 
auto max_signee = max_signeeResultSet->getUInt("max_signee"); 

int lineno = 1;

while (csv_parser.hasmoreLines()) {  

  smatch matches = csv_parser.parseNextLine(); 
  for (auto& x : matches) {
      
      cout << x << endl;
  }
  return 0;

  int signee_no = atoi(matches[1].str().c_str());

  if (signee_no <= max_signee) { // Skip if already present in DB. 

   	continue;
  }

  int col = 1;

  try  {
          
     for(; col < matches.size(); ++col) {
          
        bool isEmpty { matches[col].str().empty() };
        
        /*
         * Remove any enclosing double quotes.
         */
                
        if (matches[col].str().front() = '"' && matches[col].str().back() == '"') {
        
            //??? = matches[col].str().substr(1, str_ref.size() - 2);
        }
        
        // TODO: Set the string to the substring
        throw logic_error("See the TODO comment at" + __LINE__);
        /*
         * If column not signee_no or date-signed, then, if empty, call setNull(col + 1, 0)
         */
        if (col >= 2 && isEmpty) { 

            // According to http://forums.mysql.com/read.php?167,419402,421088#msg-421088, the 2nd parameter can simply be be 0.   
            if (col == 5) {

                comments_stmt->setNull(2, 0); 
 
            } else {

                signee_stmt->setNull(col, 0); 
            }

            continue;
        }
        
        switch(col) {

           case 1:
            // Signer #er              
            signee_stmt->setInt(col, signee_no);
            comments_stmt->setInt(col, signee_no);
            break;
               
           case 2:    
            // DATE: YYY-MM-DD
           {   
            const string& str = matches[col].str();
            signee_stmt->setDateTime(col, str.substr(6, 4) + "-" + str.substr(0, 2) + "-" + str.substr(3, 2));
           } 
            break; 
     
           case 3:   // City 
           case 4:   // State 
           case 5:   // Country 
            // TODO: touper() first words in each part of city name
            signee_stmt->setString(col, std::move(matches[col].str()));
            break; 
     
           case 6:    
            // Comments
            // TODO: Do any fixes to appearance of text.
            comments_stmt->setString(2, std::move(matches[col].str()));
            break; 
            
           default:
            break;  
     
         } // end switch
    } // end for         
    
    auto rc1 = signee_stmt->execute(); 

    // TODO: Test the next four lines.
    unique_ptr<ResultSet> lastIDResultSet { last_insert_id_stmt->executeQuery("SELECT LAST_INSERT_ID() as lastID") } ;
    
    lastIDResultSet->first();
    
    unsigned int last_signee_insertID = lastIDResultSet->getUInt("lastID"); // Get the result in column zero.

    comments_stmt->setUInt(1, last_signee_insertID);

    auto rc2 = comments_stmt->execute(); 

    cout << "line number " << lineno << " processed " << endl;
          
    } catch (SQLException & e) { 
        
       //REMOVE conn->rollback(); 
        cerr << "Error code = " << e.getErrorCode() << ". MySQL State message = " << e.getSQLState() << "\n";
        cerr << "Line number = " << lineno << ". Insert column = " << col << endl;
        throw e;
              
    } catch (exception & e) {
                     
        // catch-all for C++11 exceptions 
        conn->rollback();                 
        cerr << "C++11 exception caught: " << e.what() << ".\nLine number = " << lineno << ". Insert column = " << col << "\n";
        throw e;
    }
   
    ++lineno;
  }  // end while   
 
  //REMOVE conn->commit(); // commit after last line in input has been processed.
        
  return(0);
}
