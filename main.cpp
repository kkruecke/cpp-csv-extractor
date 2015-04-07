#include <cstdlib>
#include <iostream>
#include <memory>     // for unique_ptr, etc
#include "csvreader.h"
#include "utility.h"

// MySQL++ headers
/*
#include <mysql++.h> 
#include <ssqls.h>
*/

#include "mysql_driver.h" 
#include "mysql_connection.h" 

// MySQL Connector for C++
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
//--#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

// debug only
#include <locale>
using namespace std;
using namespace sql;

/*
 * 
 * Format of CSV file:
 * 
 * Number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
 *
 * Examples
 */
int main(int argc, char** argv) 
{
    
  if (argc != 2) {

      cerr << "Please re-run with the input file name as the first parameter.\n";
      return 0;
  }

   /*
    * Format of csv file: 
    *
    * Number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
    *
    * regex for above format:
    *
    *  ^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),($|"[^"]+"|[^"]+)$
    *
    * Note: we don't capture the first and last name.
    * as a C string:
    *
    *  "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),($|\"[^\"]+\"|[^\"]+)$"
    *
    */ 
    /*
     
     */      
    regex csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(?:\"[^\"]*\"|[^,\"]*),(?:\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*)$"};
                                        
    CsvReader reader(argv[1], csv_regex); 
    
   // TODO: A transaction support later.

  // Credentials: (url, user, password)
  unique_ptr<Connection> conn { get_driver_instance()->connect("tcp://127.0.0.1:3306", "petition", "kk0457") };

  // Set database to use.
  unique_ptr< Statement > stmt(conn->createStatement());
  
  stmt->execute("USE petition");
  
  unique_ptr<PreparedStatement> signer_info_stmt { conn->prepareStatement("INSERT INTO signer_info(signee_no, date, city, state, country) VALUES(?, ?, ?, ?, ?)") };

  unique_ptr<PreparedStatement> signer_comments_stmt { conn->prepareStatement("INSERT INTO signer_comments(signee_no, comments) VALUES(?, ?)") };

  int lineno = 1;

  while (reader.moreLines()) {

      cout << lineno++ << endl; 

      smatch matches = reader.getNextRegexMatches();
      
      try {
           
         for(size_t i = 1; i < matches.size(); ++i) {
                  
  /* 
  From
  <cppconn/prepared_statement.h>

      virtual void setBigInt(unsigned int parameterIndex, const sql::SQLString& value) = 0;

      virtual void setBlob(unsigned int parameterIndex, std::istream * blob) = 0;

      virtual void setBoolean(unsigned int parameterIndex, bool value) = 0;

      virtual void setDateTime(unsigned int parameterIndex, const sql::SQLString& value) = 0;

      virtual void setDouble(unsigned int parameterIndex, double value) = 0;

      virtual void setInt(unsigned int parameterIndex, int32_t value) = 0;

      virtual void setUInt(unsigned int parameterIndex, uint32_t value) = 0;

      virtual void setInt64(unsigned int parameterIndex, int64_t value) = 0;

      virtual void setUInt64(unsigned int parameterIndex, uint64_t value) = 0;

      virtual void setNull(unsigned int parameterIndex, int sqlType) = 0;

      virtual void setString(unsigned int parameterIndex, const sql::SQLString& value) = 0;
*/
             
   /*
        TODO: 
        When a field can be empty/NULL fields, check for this.

        Do I need to do anything with embedded single quotes?
        Answer: according to https://dev.mysql.com/doc/refman/5.0/en/string-literals.html, no.
    */
 
      string submatch = matches[i].str();   
         
      
      /*
       * Remove any enclosing double quotes
       */
      
      if (submatch.front() == '"' && submatch.back() == '"') {
        
        submatch = submatch.substr(1, submatch.end() - submatch.begin() - 2);
             
      } 
        
      switch(i) {
          
          case 1:
          {
            int signee_no = stoi(submatch);
            
            signer_info_stmt->setInt(1, signee_no);
            signer_comments_stmt->setInt(1, signee_no);
          }
          break;
              
          case 2:    
          { // DATE: YYY-MM-DD
              string date { submatch.substr(6, 4) + "-" + submatch.substr(0, 2) + "-" + submatch.substr(3, 2) };
              
              signer_info_stmt->setDateTime(2, date);
          }
          break; 

          case 3:    
          {   // First Name 
              
              if (submatch.empty()) {
                      
	           signer_info_stmt->setNull(3, 2); // TODO: What should the second parameter be?

              } else {

                  signer_info_stmt->setString(3, submatch);
              }
          }
          break; 

          case 4:    
          {  // Last Name 
              
              if (submatch.empty()) {
                  
              }
              signer_info_stmt->setString(4, submatch);
          }
          break; 

          case 5:    
          {   // City 
              
              if (submatch.empty()) {
                  
              }
              signer_info_stmt->setString(5, submatch);
          }
          break; 
           
          case 6:    
             
              // Comments 
              if (submatch.empty()) {
                  
              }
          
            signer_comments_stmt->setString(2, submatch);
          
          break; 
          
          default:
           break;  

      } // end switch
       
       
    } // end for 
         
    auto rc1 = signer_info_stmt->execute(); 
    auto rc2 = signer_comments_stmt->execute(); 
      
    cout << "Result of signer_info_stmt->execute() = " << rc1 << endl;
    cout << "Result of signer_comments_stmt->execute() = " << rc2 << endl;
    //--prepared_stmt->execute();     
           
    } // end try 
      /* TODO: Check these exceptions that are Mysql++ exceptions to libmysqlcppconn7 exceptions.
      catch (const mysqlpp::BadQuery& er) { 
            
      	// Handle any query errors
      	cerr << "Query error: " << er.what() << endl;
      	return -1;
          } 
          catch (const mysqlpp::BadConversion& er) {
              
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
				"\tretrieved data size: " << er.retrieved <<
				", actual size: " << er.actual_size << endl;
		return -1;
	    }
	    catch (const mysqlpp::Exception& er) {
                
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return -1;
	    }
         */ 
       catch (SQLException & e) {
           
         cerr << "Error code = " << e.getErrorCode() << endl;
         
         cerr << "MySQL State message = " << e.getSQLState() << endl;
         
       }
       catch (exception & e) {
                
               // catch-all for C++11 exceptions 
               cerr << "C++11 exception caught: " << e.what() << '\n';
               cerr << "Terminating" << "\n";
               return 0;
       }

    }  // end while    
    
    return(0);
}
