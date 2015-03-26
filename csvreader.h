/* 
 * File:   csvreader.h
 * Author: kurt
 *
 * Created on March 26, 2015, 6:09 PM
 */

#ifndef CSVREADER_H
#define	CSVREADER_H
class CsvReader {
    
    ifstream input;
    string   line;
    string   next_line;
    int      line_number;
        
public:
    
    CsvReader(std::string file_name);
    std::string getNextSigner();
    
    int getLine() const;
};


#endif	/* CSVREADER_H */

