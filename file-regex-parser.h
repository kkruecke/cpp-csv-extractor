#ifndef FILE_REGEX_PARSER_1234
#define FILE_REGEX_PARSER_1234

#include <string>
#include <fstream>
#include <regex>

class FileRegexParser {

protected:
   bool file_empty; 
   std::ifstream input; 
   const std::regex reg_ex;
   int line_no;
   
   bool is_empty();
   
public:
      
    FileRegexParser(const std::string& file_name, const std::regex& r);
    const std::regex& get_regex();
    virtual std::smatch parseNextLine() = 0;

    virtual bool hasmoreLines() = 0;

    virtual ~FileRegexParser();
     

};

inline const std::regex& FileRegexParser::get_regex()
{
  return reg_ex;
}

inline FileRegexParser::~FileRegexParser()
{
   if (!is_empty()) { 

      input.close();
   }
}

inline bool FileRegexParser::is_empty()
{
    return file_empty;
}
#endif
