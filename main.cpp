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

#include "csvparser.h"
#include "hidden/db_credentials.h" // database credentials

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
 */
CsvParser csv_parser(argv[1], R"(^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*)$)");
   
// Credentials: (url, user, password)
   
unique_ptr<Connection> conn { get_driver_instance()->connect(DB_Credentials::Url().c_str(), DB_Credentials::User().c_str(), DB_Credentials::Password().c_str()) };
 
// Set database to use.
unique_ptr< Statement > stmt(conn->createStatement());
 
stmt->execute("USE petition");
 
conn->setAutoCommit(false);  // We will use transactions.
 
unique_ptr<PreparedStatement> signee_stmt { conn->prepareStatement("INSERT INTO signee(signee_no, date, city, state, country) VALUES(?, ?, ?, ?, ?)") };

unique_ptr<PreparedStatement> comments_stmt { conn->prepareStatement("INSERT INTO comments(signee_id, signee_no, comments) VALUES(?, ?, ?)") };

// Get max(sigee_no) to determine if petition signers are already in the DB.
unique_ptr<ResultSet> resultSet { stmt->executeQuery("select max(signee_no) as max_signee FROM signer_info") };
 
resultSet->first();
 
auto max_signee = resultSet->getUInt("max_signee"); 

int lineno = 1;

while (csv_parser.hasmoreLines()) {  

   vector<string> strings = csv_parser.parseNextLine(); 

  /* Debug 
   cout << "--------\n";
   
   for(const auto& x : strings) {
       
       cout << x << endl;
   }
   continue;
  */

   int signee_no = atoi(strings[0].c_str());
        
   if (signee_no <= max_signee) { // Skip if already present in DB. 

   	continue;
   }

   int col = 0;

   try {
          
      for(; col < strings.size(); ++col) {
          
        bool isEmpty { strings[col].empty() };
        
        /*
         * If column not signee_no or date-signed, then, if empty, call setNull(col + 1, 0)
         */
        if (col >= 2 && isEmpty) { 

            // According to http://forums.mysql.com/read.php?167,419402,421088#msg-421088, the 2nd parameter can simply be be 0.   
            if (col == 5) {

                comments_stmt->setNull(2, 0); 
 
            } else {

                signee_stmt->setNull(col + 1, 0); 
            }

            continue;
        }

        switch(col) {

           case 0:
            // Signer #er              
            signee_stmt->setInt(col + 1, signee_no);
            comments_stmt->setInt(col + 1, signee_no);
            break;
               
           case 1:    
            // DATE: YYY-MM-DD
            signee_stmt->setDateTime(col + 1, strings[col].substr(6, 4) + "-" + strings[col].substr(0, 2) + "-" + strings[col].substr(3, 2));
            break; 
     
           case 2:    
            // First Name 
            signee_stmt->setString(col + 1, strings[col]);
            break; 
     
           case 3:    
            // Last Name 
            signee_stmt->setString(col + 1, std::move(strings[col]));
            break; 
     
           case 4:    
               // City 
            // TODO: touuper() first words in city name
            signee_stmt->setString(col + 1, std::move(strings[col]));
            break; 
            
           case 5:    
            // State 
            comments_stmt->setString(2, std::move(strings[col]));
            break; 
            
           case 6:    
            // Country 
            ?????????->setString(2, std::move(strings[5]));
            break; 
           

           default:
            break;  
     
         } // end switch
       } // end for         
                   
       auto rc1 = signee_stmt->execute(); 
       // TODO: Retrieve id of last row just inserted above into signee table
       // and do comments->setInt(...) with it.
      auto rc2 = comments_stmt->execute(); 
          
    } catch (SQLException & e) { 
        
        conn->rollback();              
        cerr << "Error code = " << e.getErrorCode() << ". MySQL State message = " << e.getSQLState() << "\n";
        cerr << "Line number = " << lineno << ". Insert column = " << col+1 << endl;
        throw e;
              
    } catch (exception & e) {
                     
            // catch-all for C++11 exceptions 
        conn->rollback();                 
        cerr << "C++11 exception caught: " << e.what() << ".\nLine number = " << lineno << ". Insert column = " << col+1 << "\n";
        throw e;
    }
   
    ++lineno;
  }  // end while   
 
  conn->commit(); // commit after last line in input has been processed.
        
  return(0);
}
