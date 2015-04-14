#include <cstdlib>
#include <iostream>
#include <memory>     // for unique_ptr, etc
#include <exception>
#include <vector> 
#include <fstream>
#include "csvparser.h"

//--#include "mysql_driver.h" 
//--#include "mysql_connection.h" 

// MySQL Connector for C++
//--#include <cppconn/driver.h>
//--#include <cppconn/exception.h>
//--#include <cppconn/resultset.h>
//--#include <cppconn/statement.h>
//--#include <cppconn/prepared_statement.h>
//--
// debug only
#include <locale>
using namespace std;
//--using namespace sql;

/*
 * 
 * Format of CSV file:
 * 
 * Number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
 *
 * Examples
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
  //--unique_ptr<Connection> conn { get_driver_instance()->connect("tcp://127.0.0.1:3306", "petition", "kk0457") };
//--
  //--// Set database to use.
  //--unique_ptr< Statement > stmt(conn->createStatement());
  //--
  //--stmt->execute("USE petition");
  //--
  //--unique_ptr<PreparedStatement> signer_info_stmt { conn->prepareStatement("INSERT INTO signer_info(signee_no, date, city, state, country) VALUES(?, ?, ?, ?, ?)") };
//--
  //--unique_ptr<PreparedStatement> signer_comments_stmt { conn->prepareStatement("INSERT INTO signer_comments(signee_no, comments) VALUES(?, ?)") };

while (csv_parser.hasmoreLines()) {  

   vector<string> strings = csv_parser.parseNextLine();     

   try {
   
          /* 
         switch(i) {
             
             case 1:
             {
               int signee_no = stoi(submatch);
               
               signer_info_stmt->setInt(1, signee_no);
               signer_comments_stmt->setInt(1, signee_no);
             }
             break;
                 
             case 2:    
             { // DATE: YYY-MM-DD
                 string date { submatch.substr(6, 4) + "-" + submatch.substr(0, 2) + "-" + submatch.substr(3, 2) };
                 
                 signer_info_stmt->setDateTime(2, date);
             }
             break; 
   
             case 3:    
             {   // First Name 
                 
                 if (submatch.empty()) {
                      // Per http://forums.mysql.com/read.php?167,419402,421088#msg-421088, the 2nd parameter cab be be 0.   
	              signer_info_stmt->setNull(3, 0); 
   
                 } else {
   
                     signer_info_stmt->setString(3, submatch);
                 }
             }
             break; 
   
             case 4:    
             {  // Last Name 
                 
                 if (submatch.empty()) {
   
                    signer_info_stmt->setNull(4, 0);
                     
                 } else {
   
                    signer_info_stmt->setString(4, submatch);
                 }
             }
             break; 
   
             case 5:    
             {   // City 
                 
                 if (submatch.empty()) {
   
                    signer_info_stmt->setNull(5, 0);
                     
                 } else {
   
                    signer_info_stmt->setString(5, submatch);
                 }
             }
             break; 
              
             case 6:    
                
                 // Comments 
                 if (submatch.empty()) {
   
                    signer_comments_stmt->setNull(2, 0);
                     
                 } else {
             
                    signer_comments_stmt->setString(2, submatch);
                 }
             
             break; 
             
             default:
              break;  
   
         } // end switch
           
       */   
       /*     
       auto rc1 = signer_info_stmt->execute(); 
       auto rc2 = signer_comments_stmt->execute(); 
         
       cout << "Result of signer_info_stmt->execute() = " << rc1 << endl;
       cout << "Result of signer_comments_stmt->execute() = " << rc2 << endl;
       */ 
   } catch (std::length_error &e) {
       
          cerr << "length_error exception caught: " << e.what() << '\n';
          cerr << "Terminating" << "\n";
          throw e;
   
   } catch (exception & e) {
                   
                  // catch-all for C++11 exceptions 
                  cerr << "C++11 exception caught: " << e.what() << '\n';
                  cerr << "Terminating" << "\n";
                  throw e;
   }
   /* catch (SQLException & e) { Make this the first exception
              
            cerr << "Error code = " << e.getErrorCode() << endl;
            
            cerr << "MySQL State message = " << e.getSQLState() << endl;
            
        }*/
        
  }  // end while    
       
  return(0);
}
