#include <csvreader.h>

CsvReader::eof()
{
}

CsvReader::getNextIterator()
{
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
    csv_regex = rgexp;
}

CsvReader::getIterator()
{    
    if (input.good()) {
     
          ++line_no;  

          /*
           * TODO:  Replace ::getline() with a class that gets the complete comments, reading ahead to check whether the signers comments continue onto the next line.            *
           * and replacing double quotes in comments with single quotes. 
           */
	  string line;

          getline(input, line); 

          regex two_dbl_quotes{"(\"\")"};
          
          string adjusted_line = regex_replace(line, two_dbl_quotes, string{"'"});
                             
          try {
                
            smatch  match;
            string  output;

            if (!line.empty()) {


               if (regex_search(adjusted_line, match, csv_regex) && match.size() > 1) {
                
                  for(size_t i = 1; i < match.size(); ++i) {
                    
                    /*
                     * TODO: 1. Check whether signee_no exists in database. 
                             2. If not, insert new record, converting dates and strings to MySQL dates and strings, respectively.
                     */ 
                   }
                
                
                } else {

                    // concatenate with prior line, continue loop                                    

                }
	    }
	  } catch (exception& e) {

          }
    }	  
