#include "include/petition-parser.h"
#include <regex>
#include <stdexcept>
#include <memory>
#include <algorithm>

using namespace std;

/*
 * Always returns a vector of six elements. Entries not in the petition will be empty.
 */
smatch PetitionParser::getNextMatches()
{
smatch match;

 if (cached_line.empty()) {

    getline(input, line); 
         
    if (input.fail()) {      
       
       return smatch();
    }
     
 } else {
    /* 
       Note: Since string& string::operator=(string && str) does this->swap(str), 
             cached_line.clear() alos needs to be called. 
     */
    line = move(cached_line); 
    cached_line.clear();
 } 

 // Replace any two consecutive double quotes with a single quote
 line = regex_replace(line, regex {"(\"\")"}, string{"'"}); // BUG? Failing, I believe that iconv removed the two double quotes?
 
 bool rc = regex_search(line, match, reg_ex);
 
 string submatch = match[6].str(); // Get comments submathch.

 if ( !submatch.empty() ) { /* 
                             Read ahead in case the comments are continue on subsequent lines. Read lines ahead until we encounter either 
                                 1.) the next line or 2.) eof
                             */
     do {

         getline(input, cached_line);

         if (regex_search(cached_line, regex{ R"(^\d+,\d\d-\d\d-\d\d\d\d,)" })) { // Tests if we have an entirely new csv entry, which means we are done.

              break;
         } 

         line += move(cached_line); // otherwise, append it. Q: Do I append it to "line" or to "match"? Is this effectively the same thing?

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
