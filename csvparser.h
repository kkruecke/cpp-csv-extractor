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
    std::string   line_cache;

    bool getNextSigner(std::string &);
        
public:

    CsvParser(const std::string& file_name, const std::regex& rexp);
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

#endif
