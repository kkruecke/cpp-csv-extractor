#include "csvparser.h"
#include <regex>
#include <stdexcept>
#include <iostream> // debug only

using namespace std;
//const regex CsvParser::csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(?:\"[^\"]*\"|[^,\"]*),(?:\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*)$"};

CsvParser::CsvParser(const string& file_name, const regex& rx) : line_no(0), csv_regex(rx)
{
   input.open(file_name);

   if (input.is_open()) {
       
      // TODO: Check for errors.
   }
}

bool CsvParser::hasmoreLines() 
{
    char c;
    
    input >> c;
    bool bResult = input.good();
    
    if (bResult) {
        
        input.putback(c);
    }
    
    return bResult; 
    
}
/*
vector<string> CsvParser::parseNextLine()
{
 vector<string> strings;
 
 if (!getNextSigner(this->line)) {

        return strings;
 }    
 
 string::const_iterator iter = line.begin();
 string::const_iterator end = line.end();
 
 int comma_cnt = 0;

 while (iter != end) {
 
   switch (comma_cnt) {
 
     case 0:

        while( *iter++ !=',');

       // cout << line.substr(0, iter - line.begin() - 1) << endl; debug code

        strings.push_back(line.substr(0, iter - line.begin() - 1));
 
        break;  
    
     case 1: // date is a fixed length and can therefore be calculated 
        
      // cout << line.substr(iter - line.begin(), date_length) << endl; // debug only
        
        strings.push_back(line.substr(iter - line.begin(), CsvParser::date_length));
 
        iter += 10; // Does it point to comma now or the next string?
        break;

     default:
            // All other cases are identical
         // Question: Does good properly handle empty strings?
     
         auto start_offset = ++iter - line.begin(); // Initially iter is pointing at a comma. Advance it... 
                    
         if (iter == end || *iter == ',') { // Are we at the end of the string, or do we have an substring empty?
             
             strings.push_back(string{""}); // insert an empty string
             break;
             
         }  else if (*++iter == '"') { // Check for enclosing quotes.
 
             while(*iter++ != '"'); // If string is enclosed in quotes, find terminating double quote...
 
             if (*iter++ != ',') { // ...and then check for the comma ...
 
             } else if (!*iter) { // ...or if end-of-string.

                  throw domain_error("string is not a proper csv string");
             }
 
        } else {

             // If no enclosing double quotes, go to comma or end of string 
             
             for(;iter != end; ++iter) {
                             
                 if (*iter == ',') {
                      break; // Bug
                 }
              }
        } 
        
        int length = iter - line.begin() - start_offset; // debug only, combine below later
         
        auto temp_str = std::move( line.substr(start_offset, length) ); 
         
        // Strip enclosing quotes.
        if (temp_str.front() == '"') {
      
             temp_str = temp_str.substr(1, temp_str.end() - temp_str.begin() - 2);
        } 

      // cout << temp_str << endl; debug code
 
        strings.push_back( temp_str );  
     
        break;
    
    } // end switch

    ++comma_cnt; 
 } // end while   
   
 return strings;
} // end function
*/

vector<string> CsvParser::parseNextLine()
{
smatch match;
string prior_line;
   
vector<string> strings;

   try {

      while (1) {

        getline(input, line);
        
        if (input.fail()) {
            
            return strings;
        }

        auto transformed_line = regex_replace(line, regex {"(\"\")"}, string{"'"});
   
        line = prior_line + transformed_line;

        bool hits = regex_search(line, match, CsvParser::csv_regex);
                  
        if (hits) { 

           for (auto iter = match.begin(); iter != match.end();) {
                
               ++iter;
               strings.push_back(*iter);
           }

           break;    
  
        } else {
             
            prior_line = line;
        }

      } // end while
   } catch (exception& e) {

   }
   return strings; 
}
/*
bool CsvParser::getNextSigner(string& line)
{
   string prior_line;

   while (1) { 

     if (!hasmoreLines()) {

         return false;
     }
 
     //
     // TODO: The logic is wrong. We need to read and concatenate until we have the complete line. We are only regex searching the first two fields, so
     // we really don't know if we have a complete line, only that the first two fields were present--not what we need to know.
   
     getline(input, line);

     string transformed_line = regex_replace(line, regex {"(\"\")"}, string{"'"}); 
   
     line = prior_line + transformed_line;
     
     cout << "The line is: \n" << line << endl;
     
     std::regex re("^\\d+,\\d\\d-\\d\\d-\\d\\d\\d\\d,");
     
     bool hits = std::regex_search(line, re);
         
     if (hits) { 
              
        cout << " --> In CsvParser::getNextSigner() <-- " << endl; // debug code

        break;    
  
     } else {
          
         prior_line = line;
     }

 } // end while
   
   return true;
}
*/
