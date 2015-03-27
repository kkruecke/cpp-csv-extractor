#ifndef CSVREADER_H
#define	CSVREADER_H

#include <regex>
class CsvReader {
    
    ifstream input;
    string   line;
    string   next_line;
    int      line_number;
    std::regex csv_regex;
        
public:
    
    CsvReader(std::string file_name, std::regex reg);
    std::string getNextSigner();
    
    int getLine() const;
};


#endif	/* CSVREADER_H */
