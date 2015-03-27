#include "csvreader.h"
#include <iostream>

using namespace std;

bool CsvReader::eof() const
{
    return true;
}

/*
Read and concatenate while regex does not fail
Return iterator or vector containing each field
*/
CsvReader::CsvReader(string file_name, regex rgexp) : csv_regex(rgexp), line_no(0)
{
    input.open(file_name);

    if (input.is_open()) {

       // TODO: Check for errors.
    }	    
}

sregex_iterator CsvReader::getIterator() 
{    
  if (input.good()) {
    
     ++line_no;  
    
     string line;

     getline(input, line); 

     regex two_dbl_quotes{"(\"\")"};
     
     string adjusted_line = regex_replace(line, two_dbl_quotes, string{"'"});
                        
     try {
           
       smatch  match;
       string  output;

       if (!line.empty()) {
           
       
          /*
           * For sregex_iterator example, see:
           *   http://en.cppreference.com/w/cpp/regex
           * 
           * See also:
           * https://www.topcoder.com/community/data-science/data-science-tutorials/using-regular-expressions-2/
           */ 
            
          auto matches_iter = sregex_iterator(line.begin(), line.end(), csv_regex);

          auto matches_end = sregex_iterator();
    
          auto match_count = distance(matches_iter, matches_end);
        
          cout << "==> There are " << match_count << "sregex_iterator matches " << endl;
        
          for(; matches_iter != matches_end; ++matches_iter){
            
             smatch match = *matches_iter;
             
            
            cout << "Iterator matches: " <<  match.str() << endl;
            
          }
        
          if (regex_search(adjusted_line, match, csv_regex) && match.size() > 1) {
           
             for(size_t i = 1; i < match.size(); ++i) {
               
                
              }
           
           
           } else {

               // concatenate with prior line, continue loop                                    

           }
       }
     } catch (exception& e) {

     }
   }  // endif
}	  
