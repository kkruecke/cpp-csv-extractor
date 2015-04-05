#include "csvreader.h"
#include <iostream>
#include <utility>

using namespace std;

CsvReader::CsvReader(string file_name, const regex& rgexp) : csv_regex(rgexp), line_no(0)
{
   input.open(file_name);

   if (input.is_open()) {
       
      // TODO: Check for errors.
   }
}
smatch CsvReader::getNextRegexMatches()
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
   
         bool hits = regex_search(line, match, csv_regex);
   
         //--cout << line << endl; // debug code
   
        if (!hits) {
   
               prior_line = line;

        } else {
   
               break;
        }

      } // end while
   } catch (exception& e) {

   }

   return std::move(match); // Is this implicit?
}

