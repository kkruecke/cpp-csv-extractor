#include "include/fix-text.h" 
#include <iostream>
#include <regex>
#include <exception>
#include <cctype>
#include <clocale>

using namespace std;

void fixText(string& s)
{
   setlocale(LC_ALL, "en_US.iso88591"); 
     
   try {
          
    int total_offset = 0;
    /*
     * Look for '.' or '!' or '?" followed by whitespace, followed by lowercase a-z.
     */
    /*
     * TODO: convert to 
     * 
      transform( sregex_iterator(s.begin(), s.end(), regex { R"((?:\.|\?|!)(\s+)[a-z])"},
                 sregex_iterator(), [] (smatch &m) {
      
                                     int index = total_offset + m.position() + m.length() - 1;
      
                                     s[index] = toupper(s[index]);

                                      total_offset += m.position() + m[0].length();
     *                                });
     */
    for(auto iter =  sregex_iterator(s.begin(), s.end(), regex { R"((?:\.|\?|!)(\s+)[a-z])"} );
                        iter != sregex_iterator(); ++iter ) {

        smatch m = *iter; //

        int index = total_offset + m.position() + m.length() - 1;
        
        s[index] = toupper(s[index]);

        total_offset += m.position() + m[0].length();
    }
    
  } catch (exception& e) {
   
      cout << "Exception in fix-text.cpp...." << e.what() << endl;
  }    
}
