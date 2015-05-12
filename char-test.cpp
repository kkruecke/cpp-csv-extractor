#include <cstdlib>
#include <memory>     // unique_ptr
#include <exception>
#include <vector> 
#include <fstream>


#include "csvparser.h"
#include <iostream>               // debug
using namespace std;

inline bool hasmoreLines(ifstream& input) 
{
    char c;
    
    input >> c;
    bool bResult = input.good();
    
    if (bResult) {
        
        input.putback(c);
    }
    
    return bResult; 
}

string getNextLine(ifstream& input, const regex& csv_regex)
{
smatch match;
string prior_line, line;
 
 while (1) {

   getline(input, line); // line is this->line
   
   if (input.fail()) {
       
       return string();
   }

   // Replace any two consecutive double quotes with a single quote
   line = prior_line + regex_replace(line, regex {"(\"\")"}, string{"'"}); // BUG: Failing, I believe that iconv removed the two double quotes?
   
   //cout << line << endl; // debug only

   bool rc = regex_search(line, match, csv_regex);
 
   if (rc) { 
       
       break;    
 
   } else {
        
       prior_line = std::move(line);
   }
 } 

 return line; 
}



int main(int argc, char** argv) 
{
    
  if (argc != 2) {
  
      cerr << "Please re-run with the input file name as the first parameter.\n";
      return 0;
  } 
  
  ifstream input;

  input.open(file_name);

  if (!input.is_open()) {
       
      throw logic_error("Could not open file" + file_name + "\n");
  }

/*
 * Format of CSV file:
 * 
 *   Signer number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
 */
  
regex { R"(^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*)$)" };
   
int lineno = 1;

while (hasmoreLines(input)) {  

   string line = parseNextLine(input, c); // Bug due to regex failure, due to unconverted/filtered quotes marks, etc.

  /* Debug 
   cout << "--------\n";
   
   for(const auto& x : strings) {
       
       cout << x << endl;
   }
   continue;
  */
 
    ++lineno;
  }  // end while   
 
  return(0);
}
