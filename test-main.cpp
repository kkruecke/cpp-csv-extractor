#include <cstdlib>
#include <iostream>
#include <memory>     // for unique_ptr, etc
#include <vector> // DEBUG ONLY
#include <regex>  // DEBUG ONLY
#include "csvreader.h"

// MySQL++ headers
/*
#include <mysql++.h> 
#include <ssqls.h>
*/
//--
//--#include "mysql_driver.h" 
//--#include "mysql_connection.h" 
//--
//--// MySQL Connector for C++
//--#include <cppconn/driver.h>
//--#include <cppconn/exception.h>
//--#include <cppconn/resultset.h>
//--//--#include <cppconn/statement.h>
//--#include <cppconn/prepared_statement.h>
//--
// debug only
#include <locale>
using namespace std;
//--using namespace sql;

/* The expression: 

   test();

   is an rvalue */

smatch test(const string& input, const regex& csv_regex) 
{
   smatch match;

   auto transformed_line = regex_replace(input, regex{"(\"\")"}, string{"'"});

   bool hits = regex_search(transformed_line, match, csv_regex);

   cout << "---> In test(const string& line) <---" << "\n";

   for (auto &x : match ) {     // DEBUG START
          
        cout <<  x.str()  << endl;   
   }   
 
   return match;
}

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

   /*
    * Format of csv file: 
    *
    * Number,Date,"First Name","Last Name",City,State/Province,Country,"Why is this issue important to you?"
    *
    * regex for above format:
    *
    *  ^(\d+),(\d\d-\d\d-\d\d\d\d),(?:"[^"]*"|[^,"]*),(?:"[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),($|"[^"]+"|[^"]+)$
    *
    * Note: we don't capture the first and last name.
    * as a C string:
    *
    *  "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),($|\"[^\"]+\"|[^\"]+)$"
    *
    */ 
    /*
     
     */      
  
  regex csv_regex{ "^(\\d+),(\\d\\d-\\d\\d-\\d\\d\\d\\d),(?:\"[^\"]*\"|[^,\"]*),(?:\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*),(\"[^\"]*\"|[^,\"]*)$"};
                                        
  CsvReader reader(argv[1], csv_regex); 
    
   // TODO: A transaction support later.

  // Credentials: (url, user, password)
//--  unique_ptr<Connection> conn { get_driver_instance()->connect("tcp://127.0.0.1:3306", "petition", "kk0457") };

  // Set database to use.
//--  unique_ptr< Statement > stmt(conn->createStatement());
  
//--  stmt->execute("USE petition");
  
//--  unique_ptr<PreparedStatement> signer_info_stmt { conn->prepareStatement("INSERT INTO signer_info(signee_no, date, city, state, country) VALUES(?, ?, ?, ?, ?)") };

//--  unique_ptr<PreparedStatement> signer_comments_stmt { conn->prepareStatement("INSERT INTO signer_comments(signee_no, comments) VALUES(?, ?)") };

  int lineno = 1;
  smatch matches;

  while (reader.moreLines()) {
/*
  vector<string> v{ "3,01-11-2011,carmen,Fogliano,\"West Chester\",Pennsylvania,\"United States\",\"I had LASIK on 10-23-10. Since then ( and prior to! ) had dry eyes. Burning in my one eye. Starbursts and halos too... It's important to stop this cause of present problems and future unknown problems! My doctor said I was a good candidate.  Well I was not and he doesn't wanna hear about my \"\" problems\"\".\"",
"5,01-11-2011,belinda,brown,knoxville,Tennessee,\"United States\",\"My eyes were ruined from lasik\"",
"8,01-11-2011,Lynn,Hamilton,Ashland,Virginia,\"United States\",\"I am permanently disabled as a result of Lasik.  My vision is 20/20 according to the ophthalmologist who mutilated my corneas.  He tells me the procedure was successful; however, while viewing an object I see six (6) ghost images, starbursts and halos around EVERY light source and the severe dryness negates the 20/20 correction.  My quality of my life has been RUINED, thanks to LASIK.\"",
"23,01-11-2011,Dominic,Morgan,Marlton,\"New Jersey\",\"United States\",\"As a LASIK casualty I experience the inadequecies of the FDA's lack of protection on a daily basis. With my websites (lasikdecision.com), I see a tremendous amount of traffic by those seeking help to corrrect the problems by doctors who don't abide by established rules and procedures. Too many people are needlessly damaged.\"",
"28,01-11-2011,Laura,Lelievre,\"Fall City\",Washington,\"United States\",\"Because of my unfortunate knowledge of doing anything to the eyes permanently which result in pain and less visible spectrum.\"",
"35,01-11-2011,Scott,Schulz,Kennesaw,Georgia,\"United States\",\"My girlfriend of 3 years has had her life turned upside down by this awful surgery.  She scouted one of the top locations in the region and paid top dollar only to be left with seemingly permanent after effects.  Down with LASIK and my support to your petition.\"",
"40,01-11-2011,Jacques,Oyharcabal,Burlingame,California,\"United States\",\"I am having many complications as a result of LASIK\"" };
*/

 vector<string> v{ "28,01-11-2011,Laura,Lelievre,\"Fall City\",Washington,\"United States\",\"Because of my unfortunate knowledge of doing anything to the eyes permanently which result in pain and less visible spectrum.\"" ,
 "29,01-11-2011,Laura,Lelievre,\"Fall City\",Washington,\"United States\",\"Because of my unfortunate knowledge of doing anything to the eyes permanently which result in pain and less visible spectrum.\"" };

 /*
  for(const auto & str : v) { //DEBUG    
      
     //-- smatch matches { reader.getNextRegexMatches() }; RE-ENABLE

      cout << " test(): \n" << str << endl;

      smatch matches = test(str, csv_regex); 

      //reader.getNextRegexMatches(matches); 
      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // DEBUG
      
      cout << "==> main.cpp test() <==" << endl; // debug code
      
      for (auto &x : matches ) {     // DEBUG START
          
           cout <<  x.str()  << endl;   
      }
  */
 
      smatch matches = reader.getNextRegexMatches(csv_regex);  

      cout << "==> main.cpp reader.test(str) <==" << endl; // debug code
      
      for (auto &x : matches ) {     // DEBUG START
          
           cout <<  x.str()  << endl;   
      }
      

   continue; // DEBUG END
   
   try {
           
      for(size_t i = 1; i < matches.size(); ++i) {
                  
 
           string submatch = matches[i].str();   
           cout << submatch << endl;
                 
      
      /*
       * Remove any enclosing double quotes
       */
      cout << "Before:   " << submatch << endl;
      
      if (submatch.front() == '"' && submatch.back() == '"') {
        
        submatch = submatch.substr(1, submatch.end() - submatch.begin() - 2);
             
      } 
      
      cout << "After:   " << submatch << endl;     
      
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
        
       
    } // end for 
         
    return 0; // DEBUG
    
    auto rc1 = signer_info_stmt->execute(); 
    auto rc2 = signer_comments_stmt->execute(); 
      
    cout << "Result of signer_info_stmt->execute() = " << rc1 << endl;
    cout << "Result of signer_comments_stmt->execute() = " << rc2 << endl;
    //--prepared_stmt->execute();     
*/  
      } // end for
    } catch (exception & e) {
                
               // catch-all for C++11 exceptions 
               cerr << "C++11 exception caught: " << e.what() << '\n';
               cerr << "Terminating" << "\n";
               return 0;
    }
      /* TODO: Check these exceptions that are Mysql++ exceptions to libmysqlcppconn7 exceptions.
      catch (const mysqlpp::BadQuery& er) { 
            
      	// Handle any query errors
      	cerr << "Query error: " << er.what() << endl;
      	return -1;
          } 
          catch (const mysqlpp::BadConversion& er) {
              
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
				"\tretrieved data size: " << er.retrieved <<
				", actual size: " << er.actual_size << endl;
		return -1;
	    }
	    catch (const mysqlpp::Exception& er) {
                
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return -1;
	    }
         */ 
//--        catch (SQLException & e) {
//--            
//--          cerr << "Error code = " << e.getErrorCode() << endl;
//--          
//--          cerr << "MySQL State message = " << e.getSQLState() << endl;
//--          
//--        

    } // end while
    return(0);
}
