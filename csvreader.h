#ifndef CSVREADER_H
#define	CSVREADER_H

#include <regex>
#include <string>
#include <fstream>

class CsvReader {
    
    std::ifstream input;
    std::string   line;
    int           line_no;
    std::regex    csv_regex;
        
public:
    
    CsvReader(std::string file_name, const std::regex& reg);
    
    std::smatch getNextRegexMatches();
    bool moreLines();
};

#endif	/* CSVREADER_H */
