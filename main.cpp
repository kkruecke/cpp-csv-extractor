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
 * CSV Extractor: Uses regular expressions to extract comma separated text from argv[1]
 */
int main(int argc, char** argv) 
{
    ifstream inp;
    

    if (argc != 2) {

        cerr << "Enter the input file name as the first parameter\n";
    }

    inp.open(argv[1]);
    
    ofstream out(string("output.txt"));

    sregex_iterator it_end; // <-- requires g++-4.9

    string line;

    regex csv_regex{"^(?:(?:\"((?:\"\"|[^\"])+)\"|([^,]*))(?:$|,))+$"};

    if (inp.is_open()) {

        while(inp.good()) {

            getline(inp, line);

            try {
                
               sregex_iterator it(line.begin(), line.end(), csv_regex);
               
               if (it->str().empty()) {
                   continue;
               } 
               
               for (std::sregex_iterator i = it; i != it_end; ++i) {
                   
                    // process line
                    out << i->str() << '\n';
                    //cout << i->str() << '\n';
                }   
                             
                             
            } catch (exception & e) {
                
                cerr << "exception caught: " << e.what() << '\n';
                
            }

        }
    }

    inp.close();

    
    return(0);
}
