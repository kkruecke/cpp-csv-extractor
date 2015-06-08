#include "include/fix-text.h" 
#include <iostream>
#include <algorithm>
#include <regex>
#include <exception>
#include <cctype>
#include <clocale>

using namespace std;

void ucfirstword_sentences(string& s)
{
   setlocale(LC_ALL, "en_US.iso88591"); 
   
   regex r { R"((?:\.|\?|!)(\s+)[a-z])"};
      
   int total_offset = 0;
    
  /*
   * Look for '.' or '!' or '?" followed by whitespace, followed by lowercase a-z.
   */
   for(auto iter =  sregex_iterator(s.begin(), s.end(), r);
                      iter != sregex_iterator(); ++iter ) {
       
        smatch m = *iter;

        int index = total_offset + m.position() + m.length() - 1;
        
        s[index] = toupper(s[index]);

        total_offset += m.position() + m[0].length();
    }
}
