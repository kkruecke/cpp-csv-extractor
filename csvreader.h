#ifndef CSVREADER_H
#define	CSVREADER_H

#include <regex>
#include <string>
#include <fstream>

class CsvReader {
    
    std::ifstream input;
    std::string   line;
    std::string   next_line;
    int      line_no;
    std::regex csv_regex;
        
public:
    
    CsvReader(std::string file_name, std::regex reg);
    
    std::sregex_iterator getIterator();
    bool eof() const;
        
};


#endif	/* CSVREADER_H */
