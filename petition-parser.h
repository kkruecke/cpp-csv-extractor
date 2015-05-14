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
    
    std::string cached_line;
    
    bool file_initially_empty;
   
public:

    PetitionParser(const std::string& file_name);
    std::smatch parseNextLine();

    bool hasmoreLines();
};
#endif
