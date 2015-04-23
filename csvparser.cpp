#include "csvparser.h"
#include <regex>
#include <stdexcept>
#include <iostream> // debug only
#include <memory>
using namespace std;

const regex CsvParser::csv_regex{ R"(^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*)$)"};

CsvParser::CsvParser(const string& file_name) : line_no(0)
{
   input.open(file_name);

   if (!input.is_open()) {
       
      throw logic_error("Could not open file" + file_name + "\n");
   }
}
/*
 * Always returns a vector of six 6. Some entries may be empty.
 */
vector<string> CsvParser::parseNextLine()
{
smatch match;
string prior_line;
   
vector<string> strings; 
strings.reserve(6);  // reserve does not result in default ctor initializations

auto insert_pos = strings.begin();

 while (1) {

   getline(input, line); // line is this->line
   
   if (input.fail()) {
       
       return strings;
   }
   // replace two consecutive double quotes with a single quote
   line = prior_line + regex_replace(line, regex {"(\"\")"}, string{"'"});

   bool hits = regex_search(line, match, CsvParser::csv_regex);
             
   if (hits) { 
       
       for (auto iter = ++(match.begin()); iter != match.end(); ++iter, ++insert_pos) {

          // Remove enclosing quotes if present from submatch.
          const string& const_ref = *iter;
          
          if (const_ref.front() == '"') {
              
              strings.emplace_back(move(const_ref.substr(1, const_ref.length() - 2)) );
              
          } else {
                             
               strings.emplace_back(move(*iter)); 
          }
      }

      break;    
 
   } else {
        
       prior_line = move(line);
   }

 } // end while

 return strings; 
}
