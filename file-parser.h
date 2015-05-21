#ifndef FILE_PARSER_1234
#define FILE_PARSER_1234

#include <string>
#include <fstream>
#include <regex>

class FileParser {

protected:
   bool file_empty; 
   std::ifstream input; 
   int line_no;
   
   bool is_empty();
   
public:

    FileParser(const std::string& file_name);

    virtual std::smatch parseNextLine() = 0;

    virtual bool hasmoreLines() = 0;

    virtual ~FileParser();
};

inline FileParser::~FileParser()
{
   if (!is_empty()) { 

      input.close();
   }
}
inline bool FileParser::is_empty()
{
    return file_empty;
}
#endif
