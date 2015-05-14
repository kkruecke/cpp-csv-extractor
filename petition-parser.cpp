#include "petition-parser.h"
#include <regex>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <iostream>  // debug only

using namespace std;

const regex PetitionParser::csv_regex { R"(^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),(".+"|[^"])$)" }; 

PetitionParser::PetitionParser(const string& file_name) : line_no(0)
{
   input.open(file_name);

   if (!input.is_open()) {
       
      throw logic_error("Could not open file" + file_name + "\n");
   }
}
      
/*
 * Always returns a vector of six elements. Entries not in the petition will be empty.
 */
vector<string> PetitionParser::parseNextLine()
{
smatch match;
//--string prior_line;
   
vector<string> strings;
/*
 * Note: Doing strings.reserve(n) does not result in default ctor initializations unlike vector<string> strings(6). 
 * Also strings.begin() returns iterator to strings[0].
 */
strings.reserve(6);  

emplace_back_inserter emplace_inserter(strings);

 if (cached_line.empty()) {

    getline(input, line); 
    
 } else {

    line = move(cached_line); 
 }  
 
 if (input.fail()) {
     
     return strings;
 }

 // Replace any two consecutive double quotes with a single quote
 line = regex_replace(line, regex {"(\"\")"}, string{"'"}); // BUG: Failing, I believe that iconv removed the two double quotes?
 
 bool rc = regex_search(line, match, PetitionParser::csv_regex);
 
 string submatch = match.str(6);
 bool not_empty = !submatch.empty();
 
 if (not_empty && submatch.back() == '"' ) { // Is there a matching end double quote?
     
     copy(++(match.begin()), match.end(), emplace_inserter); // then the comments are all contained on this line...
    
 } else if (not_empty) { //...otherwise; are the remaining lines of the comments.
                 
     // Move line into prior line?
     //--prior_line = std::move(line);

     do {

         getline(input, cached_line);

         bool rc = regex_search(cached_line, regex{ R"(^\d+,\d\d-\d\d-\d\d\d\d,)" });

         if (rc) {

              break;
         } 

         line += move(cached_line);

     } while (!rc);

     copy(++(match.begin()), match.end(), emplace_inserter); 
     
 }

 return strings; 
}


