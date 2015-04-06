#include <cstdlib>
#include <iostream>
#include <memory>     // for unique_ptr, etc
#include "csvreader.h"

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
    *  ^(\d+),(\d\d-\d\d-\d\d\d\d),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),($|"[^"]+"|[^"]+)$
    *
    * as a C string:
    *
    *  "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),($|\"[^\"]+\"|[^\"]+)$"
    *
    */ 
         
    //--regex csv_regex_alternative {"^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),($|\"[^\"]+\"|[^\"]+)$"};
        
    regex csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*)$"};
                                    
    CsvReader reader(argv[1], csv_regex); 
    
    /* For now
     * 
    mysqlpp::Connection conn("petition", "localhost", "petition", "kk0457", 3306);
    
    // Template queries
    mysqlpp::Query query_signee_info = conn.query(string("INSERT INTO signee_info(signee_no??, date, city, state, country) VALUES(%0, %1, %2, %3, %4)"));
      
    mysqlpp::Query query_signee_comments = conn.query(string("INSERT INTO signee_comments(signee_no, comments) VALUES(%0, %1, %2, %3, %4)"));

    query_signee_info.parse();
      
    query signee_comments.parse();  
        
    // Begin transaction
    mysqlpp::Transaction trans(conn); // TODO: adjust input params. 
    */
        
  unique_ptr<Connection> con { get_driver_instance()->connect("tcp://127.0.0.1:3306", "petition", "kk0457") };

  // Do I need to specify signee_no below?
  PreparedStatement signee_info = con->prepareStatement("INSERT INTO signee_info(signee_no, date, city, state, country) VALUES(?, ?, ?, ?, ?)");
  
  PreparedStatement signee_comments = con->prepareStatement("INSERT INTO signee_comments(signee_no, comments) VALUES(?, ?)"); 
 
  int lineno = 1;

  while (reader.moreLines()) {

      cout << lineno++ << endl; 

      smatch matches = reader.getNextRegexMatches();
      
      try {
           
         for(size_t i = 1; i < matches.size(); ++i) {
                  
            /* 
             * TODO: Write to database:
             * Idea 1
               ======
             * 1. Get the values for both template queries...
             * 2. converting the data in them to the MySQL-compatible format.
             *
             * TODO: Review MySQL escaping and quoting rules.
             * According to http://tangentsoft.net/mysql++/doc/html/userman/tutorial.html, we can convert our raw data into mysql++ types that are in the MySQL   
             * format, properly escaped and or quoted.
             *
             * Idea 2 
               ======
             * The support for inserting classes that represent fields seems the easiest, better documented technique to use. 
             * 
             * 
             * See:   http://tangentsoft.net/mysql++/doc/html/userman/tquery.html
             */ 
             /*
             query_signee_info.execute(%01 data, %1 data, and so on );                      

             query_signee_comments.execute( %01 data, %1 data, and so on);                      
             */
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
       * Debug code:
       * 
       *    cout << matches.str(i) << endl; 
       */
             
      string submatch = matches.str(index);       
      
      switch(i) {
          
          case 1:
              int signee_no = stoi(submatch);
              signee_info->setInt(2, signee_no);
              break;
              
          case 2:    

       
       /*
        * TODO: 
        Do any leading and ending double quote pairs, if present, remain in the C++11 string? Do I therefore need to remove them?
         
        As far as embedded single or double quotes goes, according to https://dev.mysql.com/doc/refman/5.0/en/string-literals.html        
               
         
      A “'” inside a string quoted with “"” needs no special treatment and need not be doubled or escaped. In the same way, “"” inside a string quoted
      with “'” needs no special treatment. 
        */
       SQLString date_time { };
       
       signee_info->setDateTime(3, date_time); // date

       SQLString city { };
       signee_info->setString(4, city); // city
       
       SQLString state { };
       
       signee_info->setString(5, state);  // state
       
       SQLString country { };
       
       signee_info->setString(6, country);  // country

       signee_comments-> 
       signee_comments->setBlob(3, istr); // setBlob is recommended for TEXT columns  
       
      } // end switch 
       

    }  // end for
         
    prepared_stmt->execute();     
           
      } 
      /*
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
            catch (exception & e) {
                
               // catch-all for C++11 exceptions 
               cerr << "C++11 exception caught: " << e.what() << '\n';
               cerr << "Terminating" << "\n";
               return 0;
          }

    }  // end while    
    
    return(0);
}
