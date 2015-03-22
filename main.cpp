#include <cstdlib>
#include <regex>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <exception>

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

    // Latin captial letter Z with caron: Ž. See: http://www.ascii-code.com/
    // It will replace comma as the delimeter in output.txt
    string Latin_E = "Ž";  

    ofstream output_file(string("output.txt", ofstream::out));

    ifstream inp;

    inp.open(argv[1]);
        
    string line;
    
    vector<int> failed_lines;
    
    /* 
     * The raw regex below
     * 
         ^(\d+),(\d\d-\d\d-\d\d\d\d),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*)$
     * 
     * becomes, when both the backslash and quotes are escaped, this c-style string:
     * 
       "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*)$"
     */
   
    regex csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*)$"};
    
    bool regex_failed = false;   
    
    int line_no = 0;
    
    if (inp.is_open()) {
     
        while(inp.good()) {
         
          ++line_no;  

          getline(inp, line);

          // Replace two consecutive double quotes within quoted, comma-separated segments with the single quote mark.
          
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
               regex_failed = true;
               
               failed_lines.push_back(line_no);
            }
                             
          } catch (exception & e) {
                
               cerr << "exception caught: " << e.what() << '\n';
               cerr << "Terminating" << "\n";
               return 0;
          }
        }
    }
    
    inp.close();
    output_file.close();
    
    cout << line_no << " Total lines read.\n";

    if (regex_failed) {
            
        cerr << string("Regex failed on ") << failed_lines.size() << string(" lines:\n");
        
        copy(failed_lines.begin(), failed_lines.end(), ostream_iterator<int>(cout, "\n"));

        cerr << "Please manually corrected these lines and re-run\n";
    }

    /*
     *  Read and re-parse output.txt and write data to database using MySQL++.
     */

    return(0);
}
