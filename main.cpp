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
    
    ofstream output(string("outputput.txt"));

    string line;
    
    /* 
     * The raw regex below
     * 
         ^(\d+),(\d\d-\d\d-\d\d\d\d),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*)$
     * 
     * becomes, when the backslash and quotes are escaped, this c-style string:
     * 
       "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*)$"
     */
   
    regex csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*)$"};
            
    if (inp.is_open()) {
       
        int regex_failed = 0;   

        int line_no = 0;
 
        while(inp.good()) {
         
          ++line_no;  

          getline(inp, line);
          
          regex two_dbl_quotes{"(\"\")"};
          
          string adjusted_line = regex_replace(line, two_dbl_quotes, string{"'"});
          
          /*
           * TODO: add a transformation of: convert two consecutive occurances of double quotes with an escaped double quoted.
           */                                                       
          
          try {
                
            smatch  match;
            string  output;
               
            if (regex_search(adjusted_line, match, csv_regex) && match.size() > 1) {
                
                for(size_t i = 1; i < match.size(); ++i) {
                       
                    cout << "submatch " << i << " is: " << endl;
                      
                    cout << match[i] << endl;
                }
                
            } else {
                
               cout << " ---- Regex Failed on line " << line_no << "------------\n" << adjusted_line << "\n---------------" << endl;
               regex_failed++; 
                
            }
                             
          } catch (exception & e) {
                
               cerr << "exception caught: " << e.what() << '\n';
               cerr << "Terminating" << "\n";
               return 0;
          }
        }

        cout << string("There were ") << regex_failed << string(" total missing hits") << endl;
    }
    

    inp.close();
    output.close();

       
    return(0);
}

