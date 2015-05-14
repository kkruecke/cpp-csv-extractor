#include "petition-parser.h"
#include <regex>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <iostream>  // debug only

using namespace std;

const regex PetitionParser::csv_regex { R"(^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),(".+"|[^"])$)" }; 

PetitionParser::PetitionParser(const string& file_name) : line_no(0), file_initially_empty(false)
{
   input.open(file_name);

   if (!input.is_open()) {
       
      throw logic_error("Could not open file" + file_name + "\n");
   }
   
   // Test if file is empty
   char c;
    
   input >> c;
    
   //--file_initially_empty = input.good();
    
   if (input.good()) {
        
       input.putback(c);
       
   } else {
       file_initially_empty = true;
   }
}
      
bool PetitionParser::hasmoreLines() 
{
    bool rc = true;
    
    if (file_initially_empty) { // This handle empty file
        
        rc = false;
    }
            
    if (input.eof() && cached_line.empty()) { // This handles eof
        
        rc = false;
    }
    
    return rc;
        
    char c;
    
    input >> c;
    bool bResult = input.good();
    
    if (bResult) {
        
        input.putback(c);
    }
    
    return bResult; 
}

/*
 * Always returns a vector of six elements. Entries not in the petition will be empty.
 */
smatch PetitionParser::parseNextLine()
{
smatch match;
   
/*
 * Note: Doing strings.reserve(n) does not result in default ctor initializations unlike vector<string> strings(6). 
 * Also strings.begin() returns iterator to strings[0].
 */

 if (cached_line.empty()) {

    getline(input, line); 
    
 } else {

    line = move(cached_line); 
 }  
 
 if (input.fail()) {
     
     //--return strings;
     return smatch();
 }

 // Replace any two consecutive double quotes with a single quote
 line = regex_replace(line, regex {"(\"\")"}, string{"'"}); // BUG: Failing, I believe that iconv removed the two double quotes?
 
 bool rc = regex_search(line, match, PetitionParser::csv_regex);
 
 string submatch = match.str(6);
  
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
