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

        cerr << "You must enter the input file name as the first parameter. Please rerun\n";
        return 0;
    }

    string Latin_E = ::to_string(0xCB);  // LATIN CAPITAL LETTER E WITH DIAERESIS. See http://www.w3.org/TR/MathML2/isolat1.html

    ifstream inp;

    inp.open(argv[1]);
    
    ofstream output(string("output.txt"));
    ofstream failed_log(string("Failed_lines.txt"));

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
    
    if (inp.is_open()) {
       
        int line_no = 0;
 
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
                       
                    //cout << "submatch " << i << " is: " << endl;
                      
                    //cout << match[i] << endl;
                }
                
            } else {
                              
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
    output.close();
    failed_log.close();
    
    if (regex_failed) {
            
        cout << string("Regex failed on ") << failed_lines.size() << string(" lines:\n");
        
        copy(failed_lines.begin(), failed_lines.end(), ostream_iterator<int>(cout, "\n"));
    }

    return(0);
}

