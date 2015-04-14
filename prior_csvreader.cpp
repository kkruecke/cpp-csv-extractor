#include "csvreader.h"
#include <iostream>

using namespace std;

/*
 * Format of csv file: 
 *
 * Number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
 *
 * regex for above format:
 *
 *  ^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),($|"[^"]+"|[^"]+)$
 *
 * Note: we don't capture the first and last name.
 * as a C string:
 *
 *  "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),($|\"[^\"]+\"|[^\"]+)$"
 *
 * Actual regex as C/C++-style string: 
 *
 * regex csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(?:\"[^\"]*\"|[^,\"]*),(?:\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*)$"};
 */

CsvReader::CsvReader(string file_name, const regex& rgexp) : csv_regex(rgexp), line_no(0)
{
   input.open(file_name);

   if (input.is_open()) {
       
      // TODO: Check for errors.
   }
}

smatch CsvReader::test(const string &line) 
{
   smatch match;

   auto transformed_line = regex_replace(line,regex {"(\"\")"}, string{"'"});

   bool hits = regex_search(transformed_line, match, csv_regex);

   cout << "---> CsvReader::test(const string& line) <---" << "\n";

   for (auto &x : match ) {     // DEBUG START
          
        cout <<  x.str()  << endl;   
   }   
 
   return match;
}

smatch CsvReader::getNextRegexMatches()
{
   ++line_no;

   regex two_dbl_quotes{"(\"\")"};

   smatch match;

   string line, prior_line;

   while (1) {

     //--getline(input, line); // <-- BUG??
     input.getline(line); // <-- BUG??

     string transformed_line = regex_replace(line, two_dbl_quotes, string{"'"}); 
   
     line = prior_line + transformed_line;

     bool hits = regex_search(line, match, csv_regex);
         
     if (hits) { 
              
        cout << " --> In CsvReader::getNextRegexMatches() <-- " << endl; // debug code

        for (auto &x : match ) {     // DEBUG START
       
           cout <<  x.str()  << endl;   
        }   
        
        break;    
  
     } else {
          
         prior_line = line;
     }

   } // end while
   
   return match;
   // return std::move(match); // Is this implicit?
}

smatch CsvReader::getNextRegexMatches(const regex& param_regex)
{
   ++line_no;

   string line;

   regex two_dbl_quotes{"(\"\")"};

   smatch match;

   try {

      string line, prior_line;

      while (1) {

        getline(input, line);

        auto transformed_line = regex_replace(line, two_dbl_quotes, string{"'"});
   
        line = prior_line + transformed_line;

        bool hits = regex_search(line, match, param_regex);
   
        cout << "In CsvReader::getNextRegexMatches():" << endl; // debug code
            
        if (hits) { // TODO: Why is the regex not working suddently????????
            
           for (auto &x : match ) {     // DEBUG START
          
              cout <<  x.str()  << endl;   
           }   
           
           break;    
  
        } else {
             
            prior_line = line;
        }

      } // end while
   } catch (exception& e) {

   }
   
   return match;
   // return std::move(match); // Is this implicit?
}

bool CsvReader::moreLines() 
{
    char c;
    
    input >> c;
    bool bResult = input.good();
    
    if (bResult) {
        
        input.putback(c);
    }
    
    return bResult;
}
