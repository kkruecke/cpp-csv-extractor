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
    int latin_E_hex = 0xCB;

    string Latin_E = to_string(latin_E_hex);  // LATIN CAPITAL LETTER E WITH DIAERESIS. See http://www.w3.org/TR/MathML2/isolat1.html

    ifstream inp;

    if (argc != 2) {

        cerr << "You must enter the input file name as the first parameter. Please rerun\n";
        return 0;
    }

    inp.open(argv[1]);
    
    ofstream output(string("outputput.txt"));

    sregex_iterator it_end; // regular expression support requires g++-4.9.

    string line;
    
    /* 
     * The regex below
     * 
         ^(\d+),(\d\d-\d\d-\d\d\d\d),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*)$
     * 
     * when the backslash and quotes are escaped is written as:
     * 
       "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*)$"
     */
    int bad = 0;   
   
    regex csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*),(\"[^\"]*\"|[^,]*)$"};
            
    if (inp.is_open()) {
        
        while(inp.good()) {

            getline(inp, line);
                             
            /*
             * TODO: add a transformation of: convert double quotes to single quote
             */ 
                                
            try {
                
            smatch  match;
            
            if (regex_search(line, match, csv_regex) && match.size() > 1) {
                
                for(size_t i = 0; i < match.size(); ++i) {
                       
                    cout << string("submatch " ) << i << string(" is: ") << endl;
                      
                    cout << match[i] << endl;
                }
                
            } else {
                
               cout << "\n================\nBad Line: \n" << line << endl;
               cout << "\n=============" << endl;
               bad++; 
                
            }
                             
            } catch (exception & e) {
                
                cerr << "exception caught: " << e.what() << '\n';
                cerr << "Terminating" << "\n";
                return 0;
            }
        }
    }
    
    cout << string("There were ") << bad << string(" total missing hits") << endl;

    inp.close();
    output.close();

       
    return(0);
}

