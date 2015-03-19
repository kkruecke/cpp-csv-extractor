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
     * This regex 
     * 
         ^(\d+),(\d\d-\d\d-\d\d\d\d),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*),("[^"]*"|[^,]*)$
     * 
     * when the backslash and quotes are escaped is written as:
     * 
       "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\\\"[^\\\"]*\\\"|[^,]*),(\\\"[^\\\"]*\\\"|[^,]*),(\\\"[^"]*\\\"|[^,]*),(\\\"[^\\\"]*"|[^,]*),(\\\"[^\\\"]*\\\"|[^,]*),(\\\"[^\\\"]*\\\"|[^,]*)$"
     */
    int bad = 0;   
   
    string csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),\"(\\\"[^\\\"]*\\\"|[^,]*),\"(\\\"[^\\\"]*\\\"|[^,]*),\"(\\\"[^\\\"]*\\\"|[^,]*),\"(\\\"[^\\\"]*\\\"|[^,]*).\"(\\\"[^\\\"]*\\\"|[^,]*),\"(\\\"[^\\\"]*\\\"|[^,]*)";
            
    if (inp.is_open()) {
        
        while(inp.good()) {

            getline(inp, line);
            
            // TODO: Transform any embedded double quotes to a single quote.
            // <--  
            try {
                
               //sregex_iterator it(line.begin(), line.end(), csv_regex);
               
               smatch match;
               
               string result;
               
               if (regex_search(line, match, csv_regex) && match.size() > 1) {
                   
                   cout << line << endl;
                   
                   for(size_t i = 0; i< match.size(); ++i) {
                       
                      cout << string("submatch " ) << i << string(" is: ") << endl;
                      
                      cout << match[i] << endl;
                   }
                                 
               } else {
                   
                     cout << "-----------No Regex Match found on line:-----------"   << endl << line << string("\n----------------------------------\n") << endl;
                     bad++;
               } 
               /* 
               if (it->str().empty()) {

                   continue;
               } 
               
               while (it != it_end) {
                   
                 std::smatch match = *it;
                 
                 std::cout << match.str() << "\n";
                 
                 it++;
               } 
               // Process hits                    
               for (auto i = 0; it != it_end; ++it, ++i) {
                 
                    switch (i) {
     int bad = 0;  
			case 0: // #er
			    break;

			case 1: // date
			    break;

			case 2: // fname
			    break;

			case 3: // lname
			    break;

			case 4:
			    break;

                        default:
			    break;
                    }
                    
                      
                    // write line
                   string debug {it->str() };
                   int d = 10;
                   output << it->str() << Latin_E << '\n';
               }   
               */               
                             
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

    /* MySQL++3 code not yet begun. */ 
   
    return(0);
}

