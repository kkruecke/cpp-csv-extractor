#ifndef CSVPARSE_H_29437299847
#define CSVPARSE_H_29437299847

#include <vector>
#include <string>
#include <fstream>
#include <regex>

class CsvParser {
    
    static const int date_length = 10;
    const std::regex csv_regex;

    std::ifstream input;
    std::string   line;
    int           line_no;
    std::string   line_cache;

    bool getNextSigner(std::string &);
        
public:
    
   CsvParser(const std::string& file_name, const std::regex& rx);
//  CsvParser(std::string file_name);
// std::vector<std::string> parseNextLine();

    std::vector<std::string> parseNextLine();
    bool hasmoreLines();
};

#endif
