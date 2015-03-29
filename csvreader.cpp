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

smatch CsvReader::getMatches() 
{    
 ++line_no;  
    
 string line;
 regex two_dbl_quotes{"(\"\")"};
                           
 smatch  match;

 try {
               
    string line, prior_line;
       
    while (1) {

       getline(input, line); 
   
       if (line.empty()) {
           break;
       }
       
       line = regex_replace(line, two_dbl_quotes, string{"'"});

          /*
           * For sregex_iterator example, see:
           *   http://en.cppreference.com/w/cpp/regex
           * 
           * See also:
           * https://www.topcoder.com/community/data-science/data-science-tutorials/using-regular-expressions-2/
           */ 
          /* No matches are being found 
          auto matches_iter = sregex_iterator(adjusted_line.begin(), adjusted_line.end(), csv_regex);

          auto matches_end = sregex_iterator();
    
          auto match_count = distance(matches_iter, matches_end);
        
          cout << "==> There are " << match_count << " sregex_iterator matches " << endl;
        
          for(; matches_iter != matches_end; ++matches_iter){ // TODO: Could not get this to work.
            
             smatch match = *matches_iter;
             
            
            cout << "Iterator matches: " <<  match.str() << endl;
            
          }
         */ 
                                
         bool hits = regex_search(line, match, csv_regex);

         if (!hits) {
               
             prior_line = line;
               
         } else {
               
             break;
         }
           
    } // end inner while(1)     
           
    // We now have the line. What do we want to return?            
    for(size_t i = 1; i < match.size(); ++i) {
                    
         cout << match.str(i) << endl; //Latin_E; cout was cout was output_file
                    
    }     // end for
    
    
  } catch (exception& e) {

  }

  return std::move(match);
}	  
