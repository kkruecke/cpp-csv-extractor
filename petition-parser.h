#ifndef PETITION_PARSER_1234
#define PETITION_PARSER_1234

#include <vector>
#include <string>
#include <fstream>
#include <regex>

class PetitionParser {
    
    static const std::regex csv_regex;

    std::ifstream input;
    std::string   line;
    int           line_no;

    bool getNextSigner(std::string &);
   
    // This nested class allows use to do copy(++(match.begin()), match.end(), emplace_inserter) to do emplace_back into vector<string> 
        
    class emplace_back_inserter : public std::iterator<std::output_iterator_tag,void,void,void,void> {
      private: 
         std::vector<std::string>& container; 
      public:
         typedef std::vector<std::string> container_type;
      
         explicit emplace_back_inserter (std::vector<std::string>& x) : container(x) {}
      
         emplace_back_inserter& operator= (typename std::vector<std::string>::const_reference value);
               
         emplace_back_inserter& operator* () { return *this; }
      
         emplace_back_inserter& operator++ () { return *this; }
      
         emplace_back_inserter operator++ (int) { return *this; }
      };
     
public:

    PetitionParser(const std::string& file_name);
    std::vector<std::string> parseNextLine();

    bool hasmoreLines();
};

inline bool PetitionParser::hasmoreLines() 
{
    char c;
    
    input >> c;
    bool bResult = input.good();
    
    if (bResult) {
        
        input.putback(c);
    }
    
    return bResult; 
}

inline PetitionParser::emplace_back_inserter&  PetitionParser::emplace_back_inserter::operator=(typename std::vector<std::string>::const_reference value)
{
  // Remove enclosing quotes if present from submatches.
  if (value.front() == '"') {
              
    container.emplace_back(move(value.substr(1, value.length() - 2)) );
              
  } else {
                             
    container.emplace_back(move(value)); 
  }

  return *this;
}


/* Below is a generalized template of the nested class above. It works with an arbitary container supporting emplace_back.

template <class Container> 
class emplace_back_inserter : public std::iterator<std::output_iterator_tag,void,void,void,void> {

 protected:

    Container* container; // vector<string>

 public:
   using Container container_type;

   explicit emplace_back_inserter (Container& x) : container(&x) {}

   emplace_back_inserter<Container>& operator= (typename Container::const_reference value);

   emplace_back_inserter<Container>& operator* () { return *this; }

   emplace_back_inserter<Container>& operator++ () { return *this; }

   emplace_back_inserter<Container> operator++ (int) { return *this; }
};

template <class Container> inline emplace_back_inserter<Container>& emplace_back_inserter<Container>::operator= (typename Container::const_reference value) // OK
{
 // Remove enclosing quotes if present from submatches.
 if (value.front() == '"') {
              
    (*container).emplace_back(move(value.substr(1, value.length() - 2)) );
              
 } else {
                             
    (*container).emplace_back(move(value)); 
 }

 return *this; 
}
*/
#endif
