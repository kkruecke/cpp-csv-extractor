#ifndef FILE_REGEX_PARSER_1234
#define FILE_REGEX_PARSER_1234

#include <string>
#include <fstream>
#include <regex>

class FileRegexParser {

   std::ifstream input; 
   int line_no;
     
public:

    FileRegexParser(const std::string& file_name);

    virtual std::smatch parseNextLine();

    virtual bool hasmoreLines() = 0;

    virtual ~FileRegexParser();
};

inline FileRegexParser::~FileRegexParser()
{
   input.close();
}
#endif
