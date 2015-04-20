#include "csvparser.h"
#include <regex>
#include <stdexcept>
#include <iostream> // debug only
#include <memory>

using namespace std;
// regex as a raw string: R"(<contents of regex>)"
const regex CsvParser::csv_regex{ R"(^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*)$)"};

CsvParser::CsvParser(const string& file_name) : line_no(0)
{
   input.open(file_name);

   if (!input.is_open()) {
       
      throw logic_error("Could not open file" + file_name + "\n");
   }
}

vector<string> CsvParser::parseNextLine()
{
smatch match;
string prior_line;
   
vector<string> strings; // TODO: allocate room for six strings and use emplace(iter, ctor args)

 while (1) {

   getline(input, line);
   
   if (input.fail()) {
       
       return strings;
   }
 
   line = prior_line + regex_replace(line, regex {"(\"\")"}, string{"'"});

   bool hits = regex_search(line, match, CsvParser::csv_regex);
             
   if (hits) { 
       
       for (auto iter = ++(match.begin()); iter != match.end(); ++iter) {

          // Remove enclosing quotes if present from submatch.
          const string& const_ref = *iter;
                        
          if (const_ref.front() == '"') {
              
              strings.push_back(const_ref.substr(1, const_ref.length() - 2));
              
          } else {
                    
              strings.push_back(std::move(*iter)); 
          }
      }

      break;    
 
   } else {
        
       prior_line = std::move(line);
   }

 } // end while

 return strings; 
}
/* parse directly without using a regex.
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

        strings.push_back(line.substr(0, iter - line.begin() - 1));
        break;  
    
     case 1: // date is a fixed length and can therefore be calculated 
        
        strings.push_back(line.substr(iter - line.begin(), CsvParser::date_length));
        iter += 10; // Does it point to comma now or the next string?
        break;

     default:
            // All other cases are identical
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
