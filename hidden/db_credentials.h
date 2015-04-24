#ifndef DB_CREDENTIALS_H
#define	DB_CREDENTIALS_H

#include <unordered_map>
#include <string>

class DB_Credentials {
 private:
     
    static std::unordered_map<std::string, std::string> credentials;
    
public:
    
    static const std::string& User();
    static const std::string& Password();
     
};

inline const std::string& DB_Credentials::User() 
{
    return credentials["user"];
    
}

inline const std::string&  DB_Credentials::Password() 
{
    return credentials["password"];
}
#endif	

