#include "petition-parser.h"
#include <regex>
#include <stdexcept>
#include <memory>
#include <algorithm>

using namespace std;

/*
 * Always returns a vector of six elements. Entries not in the petition will be empty.
 */
smatch PetitionParser::parseNextLine()
{
smatch match;

 if (cached_line.empty()) {

    getline(input, line); 
        
    if (input.fail()) {      
       
       return smatch();
    }
     
 } else {
    // Note: string& string::operator=(string && str) does this->swap(str);   
    line = move(cached_line); 
    cached_line.clear();
 } 

 // Replace any two consecutive double quotes with a single quote
 line = regex_replace(line, regex {"(\"\")"}, string{"'"}); // BUG: Failing, I believe that iconv removed the two double quotes?
 
 bool rc = regex_search(line, match, reg_ex);
 
 string submatch = match[6].str(); // Recall match[0] is the entire regex match.
  
 if ( !submatch.empty() ) { // Read ahead until we encounter ether 1.) the next line or 2.) eof
                 
     do {

         getline(input, cached_line);

         if (regex_search(cached_line, regex{ R"(^\d+,\d\d-\d\d-\d\d\d\d,)" })) {

              break;
         } 

         line += move(cached_line); 

     } while (!rc);
     
 }

 return match;
}
      
bool PetitionParser::hasmoreLines() 
{
    bool rc = true;
    
    if (is_empty()) { // This handle empty file
        
        rc = false;
        
    } else if (input.eof() && cached_line.empty()) { // This handles eof
        
        rc = false;
    }
    
    return rc;
}
