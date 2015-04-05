#include <cstdlib>
#include <iostream>
#include "csvreader.h"

// MySQL++ headers
/*
#include <mysql++.h> 
#include <ssqls.h>
*/

// debug only
#include <locale>
using namespace std;

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
               query_signee_info.execute(/* %01 data, %1 data, and so on */);                      

               query_signee_comments.execute(/* %01 data, %1 data, and so on */);                      
            }
            
            auto index = matches.size() - 1;
            string x{ matches.str(index)};
            cout << "~~~~~~~~~~~~~~~~\n" << x << "\n~~~~~~~~~~~\n" << endl; 

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
