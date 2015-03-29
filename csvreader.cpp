#include "csvreader.h"
#include <iostream>

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

// TODO: Design main getline/search_regex loop(s). 
sregex_iterator CsvReader::getIterator() 
{    
   ++line_no;  
    
   string line;
   regex two_dbl_quotes{"(\"\")"};
   
   bool search_result = false;
                        
   try {

    while (!search_result)  {
           
       smatch  match;
       string  output;

       getline(input, line); 
   
       if (!line.empty()) {

         string adjusted_line = regex_replace(line, two_dbl_quotes, string{"'"});

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
        
          for(; matches_iter != matches_end; ++matches_iter){
            
             smatch match = *matches_iter;
             
            
            cout << "Iterator matches: " <<  match.str() << endl;
            
          }
           */ 
           cout << "Line: " << adjusted_line << endl;
           
           search_result = regex_search(adjusted_line, match, csv_regex); // debug
           
           if (search_result && match.size() > 1) {
           
             
             for(size_t i = 1; i < match.size(); ++i) {
                    
                cout << match.str(i) << endl; //Latin_E; cout was cout was output_file
             }
                
             cout << "\n"; // cout was output_file
                      
           } else {

               // concatenate with prior line, continue loop                                    
               cout << "regex_search() failed" << endl;

           }
       } // endif
      }  // end while
     } catch (exception& e) {

     }
}	  
