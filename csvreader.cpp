#include "csvreader.h"

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
           
       
          // TODO: Consider changing from regex_search() to regex_iterator or maybe returning a vector<string> -- or whatever is right. 
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
