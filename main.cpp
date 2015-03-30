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
    * Number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
    *
    * Prospective regex for above format:
    *
    *  ^(\d+),(\d\d-\d\d-\d\d\d\d),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),($|"[^"]+"|[^"]+)$
    *
    * And as a C string:
    *
    *  "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),($|\"[^\"]+\"|[^\"]+)$"
    *
    */ 

    regex csv_regex {"^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),($|\"[^\"]+\"|[^\"]+)$"};
                            
    CsvReader reader(argv[1], csv_regex); 
    
    mysqlpp::Connection conn("petition", "localhost", "petition", "kk0457", 3306);
    
    // Template query
    mysqlpp::Query query = conn.query(string("INSERT INTO petition(signee_no, date, city, state, country, comments) VALUES(%0, %1, %2, %3, %4, %4)"));

    query.parse();
        
    // Begin transaction
    mysqlpp::Transaction trans(conn); // TODO: adjust input params. 
    smatch matches;
 
    while (!reader.eof()) {
            
        matches = reader.getMatches();
        int debug = 10;
    }

    // Latin captial letter Z with caron: Ž. See: http://www.ascii-code.com/
    // It will replace comma as the delimeter in output.txt
    /*
    string Latin_E = "Ž";  

    ofstream output_file(string("output.txt", ofstream::out));

    ifstream inp;

    inp.open(argv[1]);
        
    string line;
    
    vector<int> failed_lines;
          
    regex csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*)$"};
    
    int line_no = 0;
    
    if (inp.is_open()) {
        
        mysqlpp::Connection conn("petition", "localhost", "user", "password", 3306);
        
        // Template query
        mysqlpp::Query query = conn.query(string("INSERT INTO petition(signee_no, date, city, state, country, comments) VALUES(%0, %1, %2, %3, %4, %4)"));

        query.parse();
        
        // Begin transaction
        mysqlpp::Transaction trans(conn); // TODO: adjust input params.
     
        while(inp.good()) {
         
          ++line_no;  

          getline(inp, line); 

          regex two_dbl_quotes{"(\"\")"};
          
          string adjusted_line = regex_replace(line, two_dbl_quotes, string{"'"});
                             
          try {
                
            smatch  match;
            string  output;
               
            if (regex_search(adjusted_line, match, csv_regex) && match.size() > 1) {
                
                for(size_t i = 1; i < match.size(); ++i) {
                    
                    output_file << match.str(i) << Latin_E;
                }
                
                output_file << "\n"; 
                
            } else if (!line.empty() && inp.good()) { // if regex failed, it may be due to reading the last line, which will be an empty string; so we 
                                                      // check that the input was not empty, and we are not at eof.
               failed_lines.push_back(line_no); // TODO: get rid of this when the line-reader class is done.
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
        }
    }
    
    inp.close();
    output_file.close();
    
    cout << line_no << " Total lines read.\n";

    if (failed_lines.size() > 0) {
            
        cerr << string("Regex failed on ") << failed_lines.size() << string(" lines:\n");
        
        copy(failed_lines.begin(), failed_lines.end(), ostream_iterator<int>(cout, "\n"));

        cerr << "Please manually corrected these lines and re-run\n";
    }
    */ 

    
    return(0);
}
