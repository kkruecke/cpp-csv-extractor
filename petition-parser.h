#ifndef PETITION_PARSER_1234
#define PETITION_PARSER_1234

#include "file-parser.h"
#include <string>
#include <fstream>
#include <regex>

class PetitionParser : public FileParser {
    
    static const std::regex csv_regex;

    std::string   line;
    std::string cached_line;
    bool file_initially_empty;
    
public:

    PetitionParser(const std::string& file_name);

   /* returns smatch with these values:
    * [0] is entire match of all values below
    * [1] is signee number
    * [2] is date 
    * [3] is city 
    * [4] is state  
    * [4] is country
    * [6] is comments
    */
    std::smatch parseNextLine() override;

    bool hasmoreLines() override;
};

inline PetitionParser::PetitionParser(const std::string& file_name) : FileParser(file_name) 
{
}
#endif
