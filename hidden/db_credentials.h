#ifndef DB_CREDENTIALS_H
#define	DB_CREDENTIALS_H

#include <unordered_map>
#include <string>

class DB_Credentials {
 private:
     
    static std::unordered_map<std::string, std::string> credentials;
    
public:
    static const std::string& get(const string& str);
    
     
};

inline const std::string& DB_Credentials::get(const string& str) 
{
     return credentials[str];
}
#endif	

