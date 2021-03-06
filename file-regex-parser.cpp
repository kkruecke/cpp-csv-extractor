#include "include/file-regex-parser.h"
#include <regex>
#include <stdexcept>
#include <memory>
#include <algorithm>

using namespace std;

FileRegexParser::FileRegexParser(const string& file_name, const std::regex& r) : reg_ex(r), line_no(1), file_empty(false)
{
   input.open(file_name);

   if (!input.is_open()) {
       
      throw logic_error("Could not open file" + file_name + "\n");
   }
   
   // Test if file is empty
   char c;
    
   input >> c;
    
   if (input.good()) {
        
       input.putback(c);
       
   } else {
       
       file_empty = true;
   }
}
