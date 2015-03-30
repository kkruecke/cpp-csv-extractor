#include "csvreader.h"
#include <iostream>
#include <utility>

using namespace std;

/*
Read and concatenate while regex does not fail
Return iterator or vector containing each field
*/
CsvReader::CsvReader(string file_name, const regex& rgexp) : csv_regex(rgexp), line_no(0)
{
    input.open(file_name);
 
    if (input.is_open()) {

       // TODO: Check for errors.
    }	   
}

smatch CsvReader::getRegexMatches() 
{    
 ++line_no;  
    
 string line;
 regex two_dbl_quotes{"(\"\")"};
                           
 smatch  match;

 try {
               
    string line, prior_line;
       
    while (1) {
        
        getline(input, line); 
   
        line = regex_replace(line, two_dbl_quotes, string{"'"});
        
        line = prior_line + line;

        bool hits = regex_search(line, match, csv_regex);
        
        if (!hits) { 
               
             prior_line = line;
               
        } else {
               
             break;
        }
           
    } 
           
    // TODO: Remove this debug code:
    //Start Debug code
    for(size_t i = 1; i < match.size(); ++i) {
                    
         cout << match.str(i) << endl; //Latin_E; cout was cout was output_file
                    
    }   // End Debug code
   
    
  } catch (exception& e) {

  }

  return std::move(match); // Is this implicit?
}	  
