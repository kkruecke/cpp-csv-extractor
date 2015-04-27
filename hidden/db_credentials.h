#ifndef DB_CREDENTIALS_H
#define	DB_CREDENTIALS_H

#include <unordered_map>
#include <string>

class DB_Credentials {
 private:
     
    static std::unordered_map<std::string, std::string> credentials;
    
    static const std::string& get(const char *p);
    
public:
    static const std::string& User();
    static const std::string& Password();
    static const std::string& Url();
        
};

inline const std::string& DB_Credentials::get(const char *p) 
{
     return credentials[p];
}

inline const std::string& DB_Credentials::User()
{
    return get("user");
}

inline const std::string& DB_Credentials::Password()
{
    return get("password");
}

inline const std::string& DB_Credentials::Url()
{
    return get("url");
}
 
#endif	

