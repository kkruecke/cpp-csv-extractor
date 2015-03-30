#include <cstdlib>
#include "csvreader.h"

// MySQL++ headers
#include <mysql++.h> 
#include <ssqls.h>

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

    regex csv_regex {"^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),($|\"[^\"]+\"|[^\"]+)$"};
    //--regex csv_regex{"^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(?:($)|(\"[^\"]+\"|[^\"]+)$)"};
                            
    CsvReader reader(argv[1], csv_regex); 
    
    mysqlpp::Connection conn("petition", "localhost", "petition", "kk0457", 3306);
    
    // Template query
    mysqlpp::Query query = conn.query(string("INSERT INTO petition(signee_no, date, city, state, country, comments) VALUES(%0, %1, %2, %3, %4, %4)"));

    query.parse();
        
    // Begin transaction
    mysqlpp::Transaction trans(conn); // TODO: adjust input params. 

    while (reader.moreLines()) {

        cout << "-----------------------\n"; // Debug code
    
        smatch matches = reader.getRegexMatches();
        
        try {

           for(size_t i = 1; i < matches.size(); ++i) {
                    
              // TODO: Write to database.
               
              cout << matches.str(i) << endl; 
                    
           }  

        } catch (const mysqlpp::BadQuery& er) { 
              
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
            catch (exception & e) {
                
               // catch-all for C++11 exceptions 
               cerr << "C++11 exception caught: " << e.what() << '\n';
               cerr << "Terminating" << "\n";
               return 0;
          }

    }  // end while    
    
    return(0);
}
