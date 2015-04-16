#include <cstdlib>
#include <iostream>
#include <memory>     // for unique_ptr, etc
#include <exception>
#include <vector> 
#include <fstream>
#include "csvparser.h"

// MySQL Connector for C++
#include <mysql_driver.h>  
#include <mysql_connection.h> 

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql; 

/*
 * Format of CSV file:
 * 
 *   Number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
 *
 */
int main(int argc, char** argv) 
{
  
 if (argc != 2) {

     cerr << "Please re-run with the input file name as the first parameter.\n";
     return 0;
 } 

 CsvParser csv_parser(argv[1]);
   
 // TODO: A transaction support later.

 // Credentials: (url, user, password)
   
 unique_ptr<Connection> conn { get_driver_instance()->connect("tcp://127.0.0.1:3306", "petition", "kk0457") };
 
 // Set database to use.
 unique_ptr< Statement > stmt(conn->createStatement());
 
 stmt->execute("USE petition");
 
 conn->setAutoCommit(false);  // We will use transactions.
 
 unique_ptr<PreparedStatement> signer_info_stmt { conn->prepareStatement("INSERT INTO signer_info(signee_no, date, city, state, country) VALUES(?, ?, ?, ?, ?)") };

 unique_ptr<PreparedStatement> signer_comments_stmt { conn->prepareStatement("INSERT INTO signer_comments(signee_no, comments) VALUES(?, ?)") };

 unique_ptr<ResultSet> res { stmt->executeQuery("select max(signee_no) as max_signee FROM signer_info") };
 
 res->first();
 
 auto max_signee = res->getUInt("max_signee"); 
 
 while (csv_parser.hasmoreLines()) {  

   vector<string> strings = csv_parser.parseNextLine();     

   int signee_no = stoi(strings[0]);

   if (signee_no <= max_signee) { // check if it is already in DB.

   	continue;
   }

   try {
         
      for(int i = 0; i < strings.size(); ++i) {
          
        cout << strings[i] << endl;     
        
        bool isEmpty { strings[i].empty() };

        switch(i) {

           case 0:
             
             signer_info_stmt->setInt(1, signee_no);
             signer_comments_stmt->setInt(1, signee_no);

           break;
               
           case 1:    
           { // DATE: YYY-MM-DD
               string date { strings[1].substr(6, 4) + "-" + strings[1].substr(0, 2) + "-" + strings[1].substr(3, 2) };
               
               signer_info_stmt->setDateTime(2, std::move(date));
           }
           break; 
     
           case 2:    
           {   // First Name 
               
               if (isEmpty) {
                   
                    // According to http://forums.mysql.com/read.php?167,419402,421088#msg-421088, the 2nd parameter can simply be be 0.   
                    signer_info_stmt->setNull(3, 0); 
     
               } else {
     
                   signer_info_stmt->setString(3, strings[2]);
               }
           }
           break; 
     
           case 3:    
           {  // Last Name 
               
               if (isEmpty) {
     
                  signer_info_stmt->setNull(4, 0);
                   
               } else {
     
                  signer_info_stmt->setString(4, std::move(strings[3]));
               }
           }
           break; 
     
           case 4:    
           {   // City 
               
               if (isEmpty) {
     
                  signer_info_stmt->setNull(5, 0);
                   
               } else {
     
                  signer_info_stmt->setString(5, std::move(strings[4]));
               }
           }
           break; 
            
           case 5:    
              
               // Comments 
               if (isEmpty) {
     
                  signer_comments_stmt->setNull(2, 0);
                   
               } else {
           
                  signer_comments_stmt->setString(2, std::move(strings[5]));
               }
           
           break; 
           
           default:
            break;  
     
         } // end switch
       } // end for         
                   
       auto rc1 = signer_info_stmt->execute(); 
       auto rc2 = signer_comments_stmt->execute(); 
          
    } catch (SQLException & e) { 
        
        conn->rollback();              
        cerr << "Error code = " << e.getErrorCode() << endl;
              
        cerr << "MySQL State message = " << e.getSQLState() << endl;
        throw e;
              
    } catch (exception & e) {
                     
            // catch-all for C++11 exceptions 
        conn->rollback();                 
        cerr << "C++11 exception caught: " << e.what() << '\n';
        cerr << "Terminating" << "\n";
        throw e;
    } 
    
  }  // end while   
 
  conn->commit();
        
  return(0);
}
