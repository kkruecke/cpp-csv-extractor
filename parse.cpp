#include "parse.h"
#include <stdexcept>

using namespace std;

static const int date_length = 10;

vector<string> parse(string line)
{
vector<string> strings;

 string::const_iterator iter = line.begin();
 string::const_iterator end = line.end();
 
   //--for(int comma_cnt = 0; comma_cnt < 8; ++comma_cnt) { // OR while(*iter) {

   int comma_cnt = 0;

   while (iter != end) {
   
     switch (comma_cnt) {
   
       case 0:
       {
               while( *iter++ !=',');
               
               auto length =  iter - line.begin();
   
               strings.push_back(line.substr(0, length));
       }       
   
               break;  
      
       case 1: // date is a fixed length and can therefore be calculated 
             {
               auto start = ++iter; // for debugging
               
               string str = line.substr(iter - line.begin(), date_length);
               
               strings.push_back( str );
   
               iter += 10; // Does it point to comma now or the next string?
              }
               break;

       default:
              // All other cases are identical
          {
           auto start_offset = ++iter - line.begin(); // Initially iter is pointing at a comma. Advance it... 
          
            if (*++iter == '"') { // ... and check fo enclosing quotes.
   
               while(*iter++ != '"'); // If string is enclosed in quotes, go to ending double quote...
   
               if (*iter++ != ',') { // ...and check for comma or end of string, or ...
   
               } else if (!*iter) { // end-of-string.

                    throw domain_error("string is not a proper csv string");
               }
   
            } else {

               // otherwise go to comma or end of string 
               while(*iter++ || *iter != ',');
            } 
   
           strings.push_back( line.substr(start_offset, ???iter - start) );  
          }
           break;
      
  
        case 6:  
           break;
   
        default:
           break;
      }

      ++comma_cnt; 
    } // end while   
   
} // end function
