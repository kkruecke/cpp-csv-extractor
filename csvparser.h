#ifndef CSVPARSE_H_29437299847
#define CSVPARSE_H_29437299847

#include <vector>
#include <string>
#include <fstream>
#include <regex>

class CsvParser {
    
    const std::regex csv_regex;

    std::ifstream input;
    std::string   line;
    int           line_no;

    bool getNextSigner(std::string &);
   
    // Nested class to work with std::copy() to do emplace_back 
        
    class csv_back_inserter : public std::iterator<std::output_iterator_tag,void,void,void,void> {

      protected:
        std::vector<std::string>& container; 
     public:
        typedef std::vector<std::string> container_type;
      
        explicit csv_back_inserter (std::vector<std::string>& x) : container(x) {}
      
        csv_back_inserter& operator= (typename std::vector<std::string>::const_reference value);
      
        csv_back_inserter& operator* () { return *this; }
      
        csv_back_inserter& operator++ () { return *this; }
      
        csv_back_inserter operator++ (int) { return *this; }
      };
        
public:

    CsvParser(const std::string& file_name, const std::string& str);
    std::vector<std::string> parseNextLine();

    bool hasmoreLines();
};

inline bool CsvParser::hasmoreLines() 
{
    char c;
    
    input >> c;
    bool bResult = input.good();
    
    if (bResult) {
        
        input.putback(c);
    }
    
    return bResult; 
}

inline CsvParser::csv_back_inserter&  CsvParser::csv_back_inserter::operator= (typename std::vector<std::string>::const_reference value)
{
  // Remove enclosing quotes if present from submatches.
  if (value.front() == '"') {
              
    container.emplace_back(move(value.substr(1, value.length() - 2)) );
              
  } else {
                             
    container.emplace_back(move(value)); 
  }

  return *this;
}


/* Generalized template of the nested class above

template <class Container> // vector<string>
class csv_back_inserter : public std::iterator<std::output_iterator_tag,void,void,void,void> {
protected:

  Container* container; // vector<string>

public:
  typedef Container container_type;

  explicit csv_back_inserter (Container& x) : container(&x) {}

  csv_back_inserter<Container>& operator= (typename Container::const_reference value);

  csv_back_inserter<Container>& operator* () { return *this; }

  csv_back_inserter<Container>& operator++ () { return *this; }

  csv_back_inserter<Container> operator++ (int) { return *this; }
};

template <class Container> inline csv_back_inserter<Container>& csv_back_inserter<Container>::operator= (typename Container::const_reference value) // OK
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
