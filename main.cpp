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
 *  Uses regular expression support in gcc-4.9 to extract comma separated text from file given in argv[1]. Requires g++-4.9 or higher.
 */
int main(int argc, char** argv) 
{
    ifstream inp;

    if (argc != 2) {

        cerr << "Enter the input file name as the first parameter\n";
        return 0;
    }

    inp.open(argv[1]);
    
    ofstream output(string("outputput.txt"));

    sregex_iterator it_end; // <-- requires g++-4.9

    string line;

    // regular expression for parsing .csv file.
    regex csv_regex{"^(?:(?:\"((?:\"\"|[^\"])+)\"|([^,]*))(?:$|,))+$"};
    
    if (inp.is_open()) {

        while(inp.good()) {

            getline(inp, line);

            try {
                
               sregex_iterator it(line.begin(), line.end(), csv_regex);
               
               if (it->str().empty()) {
                   continue;
               } 
               
               for (auto i = 0; i != it_end; ++it, ++i) {
                   
                    switch (i) {

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
                      
                    // process line
                    output << it->str() << '\n';
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

    /* MySQL++3 code not yet begun. */ 
   
    return(0);
}

