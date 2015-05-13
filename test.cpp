#include <cstdlib>
//#include <utility>
//#include <algorithm>
#include <iterator>
#include <regex>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void dumpLine(const string& line);
string parseLine(std::ifstream& input, const std::regex& csv_regex);
bool hasmoreLines(istream& input);

void dumpLine(const string& line)
{
  for (auto iter = line.begin(); iter != line.end(); ++iter) {

        int i = reinterpret_cast<char>(*iter);

        cout << *iter << " as int: " << i << endl;
  }
 
}

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

string parseLine(ifstream& input, const regex& csv_regex)
{
smatch match;
string prior_line;

int failed_count = 0;
smatch short_match;
ostringstream ostr;

string line;
   
 while (1) {

   getline(input, line); 
   
   if (input.fail()) {
       
       throw logic_error("no input to read");
   }

   if (failed_count && regex_search(line, short_match, regex {R"(^(\d+),(\d\d-\d\d-\d\d\d\d),)" })) {
       
        auto xx = ++short_match.begin();
        
        ostr << "\nRegex failed and next line is a new signer that starts with " << xx->str() << endl;

        throw logic_error(ostr.str());
   }

   // Replace any two consecutive double quotes with a single quote
   line = prior_line + regex_replace(line, regex {"(\"\")"}, string{"'"}); 
   
   cout << line << endl; 

   bool rc = regex_search(line, match, csv_regex);
 
   if (rc) { 
       
       // Skip first hit, the entire regex. We only want the submatches. 
       //copy(++(match.begin()), match.end(), emplace_inserter); 
       
      break;    
 
   } else {
       ++failed_count; 
       prior_line = std::move(line);
   }

 } 

 return line;
}

bool hasmoreLines(istream& input) 
{
    char c;
    
    input >> c;
    bool bResult = input.good();
    
    if (bResult) {
        
        input.putback(c);
    }
    
    return bResult; 
}

int main(int argc, char** argv) 
{    
  if (argc != 2) {
  
      cerr << "Please re-run with the input file name as the first parameter.\n";
      return 0;
  } 

  const string file_name(argv[1]);

  ifstream input;

  input.open(file_name);

  if (!input.is_open()) {
       
      throw logic_error("Could not open file" + file_name + "\n");
  }

  const regex csv_regex{ R"(^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*)$)"};
  
  try {
      
  
   while (hasmoreLines(input)) {
    
     string line = parseLine(input, csv_regex); 

     cout << line << '\n' << endl;
   }
  } catch (exception &e) {
      
      cerr << e.what() << endl;
  }
  return(0);
}
