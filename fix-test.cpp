#include "include/fix-text.h" 
#include <iostream>
#include <regex>
#include <exception>

using namespace std;

/*
 TODO: Calculate start of character to capitalize
 */

void fixText(string& s)
{
   try {
      
    regex r { R"((?:\.|\?|!)(\s+)[a-z])"};   
    
    int total_offset = 0;
    
    for(auto iter =  sregex_iterator(s.begin(), s.end(), r);
                        iter != sregex_iterator(); ++iter ) {
        smatch m = *iter;

        cout << '"' << m.str() << '"' << " -- at offset " << total_offset + m.position() << " from total offset of " << total_offset << '\n';

        int index = total_offset + m.position() + m.length() - 1;

        cout << "'" << s.at(index) << "'" << " -- at offset " << index << " from total offset of " << total_offset << '\n';

   
      for(auto& sub : m) {
          
           cout << "submatch sub.str() " << '"' << sub.str() << '"' <<  " -- has length of " << sub.length() << '\n';
      }
        
      total_offset += m.position() + m[0].length();
      
    }
    
  } catch (exception& e) {
   
      cout << "Exception in fix-text.cpp...." << e.what() << endl;
  }    
  
}
