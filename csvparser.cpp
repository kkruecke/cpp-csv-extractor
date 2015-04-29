#include "csvparser.h"
#include <regex>
#include <stdexcept>
#include <memory>

using namespace std;

CsvParser::CsvParser(const string& file_name, const string& rgex) : line_no(0), csv_regex(rgex)
{
   input.open(file_name);

   if (!input.is_open()) {
       
      throw logic_error("Could not open file" + file_name + "\n");
   }
}
      
/*
 * Always returns a vector of six elements. Entries not in the petition will be empty.
 */
vector<string> CsvParser::parseNextLine()
{
smatch match;
string prior_line;
   
vector<string> strings;
/*
 * Note: strings.reserve(n) does not result in default ctor initializations unlike vector<string> strings(6). 
 * Also strings.begin() points to string[0].
 */
strings.reserve(6);  

//--csv_back_inserter<vector<string>> emplace_inserter(strings);
csv_back_inserter emplace_inserter(strings);

 while (1) {

   getline(input, line); // line is this->line
   
   if (input.fail()) {
       
       return strings;
   }

   // Replace any two consecutive double quotes with a single quote
   line = prior_line + regex_replace(line, regex {"(\"\")"}, string{"'"});

   if (regex_search(line, match, csv_regex)) { 
       
       // Skip first hit, the entire regex. We only want the submatches. 
       copy(++(match.begin()), match.end(), emplace_inserter); 
       
      break;    
 
   } else {
        
       prior_line = move(line);
   }
 } 

 return strings; 
}


