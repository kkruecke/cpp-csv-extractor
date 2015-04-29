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

/*
 * Used to insert smatch results into vector<string>
 */

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
#endif
