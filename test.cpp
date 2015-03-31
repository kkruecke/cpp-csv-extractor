#include "test.h"
#include <string>

using namespace std;

smatch getMatch()
{   
    smatch match;
    string input, line, prior_line
    
    while (1) {
        
        getline(input, line); 
   
        line = regex_replace(line, two_dbl_quotes, string{"'"});
        
        line = prior_line + line;

        bool hits = regex_search(line, match, csv_regex);

        cout << line << endl; // debug code
        
        if (!hits) { 
               
             prior_line = line;
               
        } else {
               
             break;
        }
           
    } // end while 
    
    return std::move(match);
}
