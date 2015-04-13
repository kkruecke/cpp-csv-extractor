#include "parse.h"
#include <regex>
#include <stdexcept>

#include <iostream> // debug only

using namespace std;

static const int date_length = 10;

vector<string> parse(string line)
{
vector<string> strings;

 string::const_iterator iter = line.begin();
 string::const_iterator end = line.end();
 
 int comma_cnt = 0;
 try {  // for debug

   while (iter != end) {
   
     switch (comma_cnt) {
   
       case 0:

          while( *iter++ !=',');

          cout << line.substr(0, iter - line.begin() - 1) << endl;

          strings.push_back(line.substr(0, iter - line.begin() - 1));
   
          break;  
      
       case 1: // date is a fixed length and can therefore be calculated 
          
          cout << line.substr(iter - line.begin(), date_length) << endl; // debug only
          
          strings.push_back(line.substr(iter - line.begin(), date_length));
   
          iter += 10; // Does it point to comma now or the next string?
          break;

       default:
              // All other cases are identical
           // Question: Does good properly handle empty strings?
       
           auto start_offset = ++iter - line.begin(); // Initially iter is pointing at a comma. Advance it... 
           
           if (iter == end) { // Are we at the end of the string?
               strings.push_back(string{""}); // insert an empty string
               break;
           }
          
           // Question: Are we handling empty strings correctly?
           
           if (*++iter == '"') { // ... and check for enclosing quotes.
   
               while(*iter++ != '"'); // If string is enclosed in quotes, go to terminating double quote...
   
               if (*iter++ != ',') { // ...and check for comma...
   
               } else if (!*iter) { // ...or end-of-string.

                    throw domain_error("string is not a proper csv string");
               }
   
           } else {

               // If no enclosing double quotes, go to comma or end of string 
               if (comma_cnt == 6) {
                   auto debug = 10;
               }
               
               for(;iter != end; ++iter) {
                               
                   if (*iter == ',') {
                        break; // Bug
                   }
                }
           } 
           
           int length = iter - line.begin() - start_offset; // debug only, combine below later
           
           auto temp_str = std::move( line.substr(start_offset, length) ); 
           
           // Strip enclosing quotes.
            if (temp_str.front() == '"') {
        
                  temp_str = temp_str.substr(1, temp_str.end() - temp_str.begin() - 2);
            } 

           cout << temp_str << endl;
 
           strings.push_back( temp_str );  
       
           break;
      
      } // end switch

      ++comma_cnt; 
    } // end while   
 }  catch(exception& e) {// end try  
     
        // catch-all for C++11 exceptions 
        cerr << "Exception caught in parse(line): " << e.what() << '\n';
                  
 }
   
   return strings;
   
} // end function
