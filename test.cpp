#include <cstdlib>
#include <memory>     // unique_ptr
#include <exception>
#include <vector> 
#include <fstream>
#include <iostream>               // debug
#include <regex>
#include <utility>

using namespace std;

bool hasmoreLines(ifstream& input);
string getNextLine(ifstream& input, const regex& csv_regex);

bool hasmoreLines(ifstream& input) 
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
  
auto fail_count = 0;

 while (1) {

   getline(input, line); // line is this->line
   cout << "getline() = " << line << endl;
   
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
       ++fail_count;
 
       if (fail_count >= 9) {

            throw logic_error("regex has failed 9 times ");
       } 
       cout << "regex_search() fail count is " << fail_count << " Re-attempting " << endl;
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
  string file_name {argv[1]};

  input.open(file_name);

  if (!input.is_open()) {
       
      throw logic_error("Could not open file" + file_name + "\n");
  }

/*
 * Format of CSV file:
 * 
 *   Signer number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
 */
  
const regex csv_regex{ R"(^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*)$)" };
   
int lineno = 1;

while (hasmoreLines(input)) {  

  try {

   string line = getNextLine(input, csv_regex); 
   cout << "After getNextLine() = " << line << endl;

    ++lineno;

  } catch (exception& e) {

    cerr << e.what() << endl;
    return 0;

  }
}  // end while   
 
  return(0);
}
