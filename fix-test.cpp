#include "include/fix-text.h" 
#include <iostream>
#include <regex>
#include <exception>
/*
void fixTextTest(string& s)
{
    std::string s = "123 apples 456 oranges 789 bananas oranges bananas";
    std::regex r("[a-z]+");

    for(std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), r);
                            i != std::sregex_iterator();
                            ++i )
    {
        std::smatch m = *i;
        std::cout << m.str() << " at position " << m.position() << '\n';

      for(submatch& sub : m) {
           cout << "submatch sub.str() " << sub.str() << " length of " << sub.length() << '\n';
      }
    }
}
*/
using namespace std;

void fixText(string& s)
{
   try {
      
    //std::regex r { R"((?:\.|\?|!)(\s+)[a-z]+)"};
    std::regex r { R"((?:\.|\?|!)(\s+)[a-z])"};   
    
    for(std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), r);
                            i != std::sregex_iterator();
                            ++i )
    {
        std::smatch m = *i;
        std::cout << m.str() << " at position " << m.position() << '\n';

    /*
    TODO: We only care about  m[1] below--I think
     */

      for(auto& sub : m) {
          
           cout << "submatch sub.str() " << '"' << sub.str() << '"' <<  " length of " << sub.length() << '\n';
      }
    }
    
  } catch (exception& e) {
   
      cout << "Exception in fix-text.cpp...." << e.what() << endl;
  }    
  
}
