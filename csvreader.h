#ifndef CSVREADER_H
#define	CSVREADER_H

#include <regex>
#include <string>
#include <fstream>
#include <string> // DEBUG ONLY
#include <regex> // DEBUG ONLY

class CsvReader {
    
    std::ifstream input;
    std::string   line;
    int           line_no;
    std::regex    csv_regex;
        
public:
    
    CsvReader(std::string file_name, const std::regex& reg);
    
    std::smatch test(const std::string& s, const std::regex& r); // DEBUG

    std::smatch getNextRegexMatches();
     std::smatch getNextRegexMatches(const std::regex& r);
    bool moreLines();
};

#endif	/* CSVREADER_H */
