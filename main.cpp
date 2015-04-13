#include <cstdlib>
#include <iostream>
#include <memory>     // for unique_ptr, etc
#include <exception>
#include <vector> // DEBUG ONLY
#include <regex>
#include <fstream>
#include "parse.h"

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

bool moreLines(ifstream& input) 
{
    char c;
    
    input >> c;
    
    bool bResult = input.good();
    
    if (bResult) {
        
        input.putback(c);
    }
    
    return bResult;
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
  vector<string> v {"1,01-11-2011,Kelly,Cunningham,Irving,Texas,\"United States\",\"I have friends whose eyes have been permanently disfigured and lenses marred by this surgery - resulting in chronic dry-eye and irreparable poor vision.\"",
"2,01-11-2011,Paula,Cofer,Mango,Florida,\"United States\",\"I suffered permanent, life-altering complications from LASIK.  I know of thousands of people who also had a bad outcome from LASIK.  Medical studies demonstrate that LASIK 'side effects' are common, and that adverse effects are universal.  LASIK surgeons do not fully inform potential patients, and are engaged in a cover-up. Clinical trials that the FDA relied upon were tainted by dishonest investigators.\"",
"3,01-11-2011,carmen,Fogliano,\"West Chester\",Pennsylvania,\"United States\",\"I had LASIK on 10-23-10. Since then ( and prior to! ) had dry eyes. Burning in my one eye. Starbursts and halos too... It's important to stop this cause of present problems and future unknown problems! My doctor said I was a good candidate.  Well I was not and he doesn't wanna hear about my ' problems'.\"",
"4,01-11-2011,Brent,Russo,Alhambra,California,\"United States\",",
"5,01-11-2011,belinda,brown,knoxville,Tennessee,\"United States\",\"My eyes were ruined from lasik\""};

vector<string> result;

for (auto& line : v) {
    
    string transformed_line = regex_replace(line, regex {"(\"\")"}, string{"'"}); 
    
    vector<string> results = parse(transformed_line);
    
    cout << "Substrings are:\n";
    int size = results.size();
    
    for (auto iter = results.begin(); iter != results.end(); ++iter)  {     // debug
        
        string s = *iter;
        cout << s << endl;    
    }
    
    cout << "----------" << endl;
}
    
  return 0;

  ifstream  input;
  
  if (argc != 2) {

      cerr << "Please re-run with the input file name as the first parameter.\n";
      return 0;
      
  } 
      
  input.open(argv[1]);
  
  if (!input.is_open()) {
      
      cerr << "Could not open file " << argv[1] << "\n";
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
                                        
  //--CsvReader reader(argv[1], csv_regex); 
    
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

   
  
/*
vector<string> v {"1,01-11-2011,Kelly,Cunningham,Irving,Texas,\"United States\",\"I have friends whose eyes have been permanently disfigured and lenses marred by this surgery - resulting in chronic dry-eye and irreparable poor vision.\"",
"2,01-11-2011,Paula,Cofer,Mango,Florida,\"United States\",\"I suffered permanent, life-altering complications from LASIK.  I know of thousands of people who also had a bad outcome from LASIK.  Medical studies demonstrate that LASIK 'side effects' are common, and that adverse effects are universal.  LASIK surgeons do not fully inform potential patients, and are engaged in a cover-up. Clinical trials that the FDA relied upon were tainted by dishonest investigators.\"",
"3,01-11-2011,carmen,Fogliano,\"West Chester\",Pennsylvania,\"United States\",\"I had LASIK on 10-23-10. Since then ( and prior to! ) had dry eyes. Burning in my one eye. Starbursts and halos too... It's important to stop this cause of present problems and future unknown problems! My doctor said I was a good candidate.  Well I was not and he doesn't wanna hear about my ' problems'.\"",
"4,01-11-2011,Brent,Russo,Alhambra,California,\"United States\",",
"5,01-11-2011,belinda,brown,knoxville,Tennessee,\"United States\",\"My eyes were ruined from lasik\"",
"6,01-11-2011,James,Shuttleworth,Poughkeepsie,\"New York\",\"United States\",\"Lasik took away my night vision & left me scarred for life with unbearable starbursting.\"",
"7,01-11-2011,lisa,alagha,blauvelt,\"New York\",\"United States\",\"my brother's vision was severely and permanently damaged by lasik\"",
"8,01-11-2011,Lynn,Hamilton,Ashland,Virginia,\"United States\",\"I am permanently disabled as a result of Lasik.  My vision is 20/20 according to the ophthalmologist who mutilated my corneas.  He tells me the procedure was successful; however, while viewing an object I see six (6) ghost images, starbursts and halos around EVERY light source and the severe dryness negates the 20/20 correction.  My quality of my life has been RUINED, thanks to LASIK.\"",
"9,01-11-2011,Ewa,Gerszak,Edmonton,,Canada,\"Almost 2 years ago my son had Lasik for hyperopia.The surgery left him with irreparable damage, double vision, that can not be corrected even by custom gas permeable lenses\"",
"10,01-11-2011,Dale,Johnson,Woodridge,Illinois,\"United States\",\"Lasik nearly ruined my life.  Only got it back after finding a great set of expensive, custom contact lenses.\"",
"11,01-11-2011,Aytac,Yolas,istanbul,,Turkey,\"Many complications appeared a few years later after having lasik on both eyes. Good result at first doesn't mean it will continue for life. I hope lasik ops can be stopped and a cure will be developed for lasik victims.\"",
"12,01-11-2011,arturo,matta,Weston,Florida,\"United States\",",
"13,01-11-2011,gina,kronstadt,\"sherman oaks\",California,\"United States\",\"because my life has changed in a negative way since i got a botched EPI surgery.  the dr. took NO responsibility for what happened...AND did surgery without a signed consent form. pure arrogance.\"",
"14,01-11-2011,Michael,Michael,Palmer,Alaska,\"United States\",\"Now you know why lasik doctors dont give FDA lasik booklet patient information to patients.\"",
"15,01-11-2011,Suzanne,Buie,Knoxville,Tennessee,\"United States\",\"I underwent LASIK in 1999 and suffered many negative results to include:  neuropathic pain, halos, diminished vision and a sensation of severe dry eyes.  Currently, I am going through a period of severe photophobia and cannot drive or perform any activity in lighted conditions.  I would also like to make the point that it is not only LASIK that needs to be re-evaluated but the physicians' themselves that perform LASIK and provide no follow up care or responsibility to their patients that have negative and debilitating results.\"",
"16,01-11-2011,Cristina,Daniilidi,Piraeus,,Greece,\"Feel deceived because of lack of proper information regarding a permanent, irreversible elective procedure with all kinds of unnecessary side effects. It has been a financial and psychological burden that I carry ever since.\"",
"17,01-11-2011,Craig,Davies,\"Merthyr Tydfil\",,\"United Kingdom\",\"Too many people's health is being irreparably damaged by this procedure. Complications are extremely common (albeit the true rate is often covered up.) Patients with bad outcomes are ignored. This mass mutilation must stop.\"",
"18,01-11-2011,Joseph,Schnell,Philadelphia,Pennsylvania,\"United States\",\"I am fully aware of the harm Lasik causes to all eyes it is performed on - there simply is a mountain of science that proves so. I had Lasik performed on both of my eyes and despite having been told I had a fairly good result, even by optometrists who are against Lasik, I know the quality of my vision and health of my eyes have suffered as a result of Lasik.\"",
"19,01-11-2011,Jo,Wills,Burlington,\"New Jersey\",\"United States\",\"My husband was injured by Dr. Herbert Nevyas when he performed unauthorized especially when my husband was not a candidate.  My husband was butchered by this doctor, who also threatened to sue me for telling about  my husband's experience on my web site.\"",
"21,01-11-2011,Michael,Kasper,\"Farmington Hills\",Michigan,\"United States\",\"Need to stop damaging perfectly healthy eyes. People are not informed of the true risk and side effects.\"",
"22,01-11-2011,Carol,Moore,\"East Norriton\",Pennsylvania,\"United States\",\"my cousin was harmed permanently by this surgery\"",
"23,01-11-2011,Dominic,Morgan,Marlton,\"New Jersey\",\"United States\",\"As a LASIK casualty I experience the inadequecies of the FDA's lack of protection on a daily basis. With my websites (lasikdecision.com), I see a tremendous amount of traffic by those seeking help to corrrect the problems by doctors who don't abide by established rules and procedures. Too many people are needlessly damaged.\"",
"24,01-11-2011,Bill,Mauck,Willowbrook,Illinois,\"United States\",\"Electing to have Lasik was absolutely the worst decision of my life.  I went from crystal clear vision with glasses to chronic dry eye, redness, inability to focus and vision that is uncorrectable with glasses.\"",
"25,01-11-2011,James,Burke,Temecula,California,\"United States\",\"I've had my life ruined by lasik on 5-6-2009 by the latest lasik available.I was completely lied to about the safety of Lasik and destroyed.I'm now on Disability.Please stop destroying lives and warn the public of this horrible lasik procedure. PLEASE STOP LASIK AND HELP LASIK CASUALTIES.I need your help I've been injured so badly.\"",
"26,01-11-2011,carole,parkerson,southampton,\"New Jersey\",\"United States\",",
"27,01-11-2011,Patricia,Rudd,\"Amelia Court House\",Virginia,\"United States\",\"I had LASIK performed in 1999. Had good vision for about a year then it started to decline to bad night vision, double vision, ect. Virginia Eye Institute, who did the procedure, had me returning every 3 months for 8 years for checkups and i was told that nothing was wrong. I finally went to a different vision specialist who says he cannot correct the damage done by LASIK but fitted glasses to help some. My prescription has to be changed every 6 months to try to gradualy get my vision back the best it can be. I will always have vision problems since I had LASIK.\"",
"28,01-11-2011,Laura,Lelievre,\"Fall City\",Washington,\"United States\",\"Because of my unfortunate knowledge of doing anything to the eyes permanently which result in pain and less visible spectrum.\"",
"29,01-11-2011,Natalie,Messier,Brunswick,Maine,\"United States\",",
"30,01-11-2011,Michael,Mullery,Englewood,Florida,\"United States\",\"Like the previous posters Lynn Hamilton and James  Burke,  I am disabled from my chosen profession by the 'temporary side effects'of this surgery which have lasted for years.  As a direct result of this surgery,  I no longer can see to drive at night and my night vision is obscured by huge starbursts and haloes.  I also have permanent double vision in one eye due to a decentered ablation.   This surgery also induced very painful dry eyes as well as a loss of multiple lines of best correctable vision.due to induced irregular astigmatism.  Despite all these permanent unfixable complications,  I am still considered a success by industry standards.\"",
"31,01-11-2011,Joe,Darling,LORTON,Virginia,\"United States\",",
"32,01-11-2011,Charles,Jones,Fordyce,Arkansas,\"United States\",\"I am a physician who had LASEK done about 4 years ago.  It has ruined my life.  I cannot do what I studied my whole life for because of it.  I am limited to certain services that I can provide because of my eyesight behind LASEK.  People don't realize how long the rest of your life is if you have a bad outcome from this surgery.  Above and beyond that, it is the most unethical procedure in the world.\"",
"33,01-11-2011,Taylor,King,Kennesaw,Georgia,\"United States\",\"I had LASIK in September, 2010.  Prior to the surgery, I was a happy, healthy (in every way) young professional.  I will never be that person again.  Due to unbearable side effects - I have suffered from all the typical side effects (halos, starbursts, night vision problems) - plus severe depression, and even thoughts of suicide - something I never even thought myself capable of thinking of.  I hope to God that this tragedy can be prevented for others.\"",
"34,01-11-2011,Craig,Litman,Cedarhurst,\"New York\",\"United States\",",
"35,01-11-2011,Scott,Schulz,Kennesaw,Georgia,\"United States\",\"My girlfriend of 3 years has had her life turned upside down by this awful surgery.  She scouted one of the top locations in the region and paid top dollar only to be left with seemingly permanent after effects.  Down with LASIK and my support to your petition.\"",
"36,01-11-2011,Timothy,Russo,Colleyville,Texas,\"United States\",",
"37,01-11-2011,christopher,alexander,\"Palm Beach\",Florida,\"United States\",\"People are unnecessarily being harmed by Lasik. Anyone who makes their living caring for others vision knows this.\"",
"38,01-11-2011,Roger,Davis,\"Poplar Bluff\",Missouri,\"United States\",\"I've communicated with over 300 people who've expressed a desire to end their life because of LASIK. Much of this is related to dry eye and night vision complaints. Victims all say the same thing: That their surgeon lied to them about the severity of complications, and continued to lie when they experienced a bad outcome. Time for this to stop.\"",
"39,01-11-2011,Brook,Vanderford,Oakland,California,\"United States\",\"I had Lasik 2 1/2 years ago, and I am now visually disabled and cannot work or live my life free from pain. My eyes are so light sensitive that I can barely go outside, let alone use a computer or watch tv or be under non-natural lighting. No one seems to be able to help me in my condition either. I just keep getting told that this condition shouldn't have lasted this long (TLSS), as if that somehow addresses the issue. We need more research so this and other side effects don't keep happening.\"",
"40,01-11-2011,Jacques,Oyharcabal,Burlingame,California,\"United States\",\"I am having many complications as a result of LASIK\"",
"41,01-11-2011,Benjamin,Vanderford,OAKLAND,California,\"United States\",",
"42,01-11-2011,Mathilde,Oyharcabal,\"San Francisco\",California,\"United States\",\"My son had LASIK twice in the last year and is suffering from daily discomfort and horrible night vision and starbursts\"",
"43,01-11-2011,monica,short,\"las vegas\",Nevada,\"United States\",\"I had lasik done on my left eye and it is permanently damaged and no vision left in it. There are too many unscrupulous doctors lying to people about the lazy LASIK and they should all be in prison because they are criminals !  They don't give a hoot about their patients , they only care about making huge profits and they know they are ruining their patient's life for EVER but keep on convincing people the LASIK is safe ....  The media is just as corrupted as these so-called doctors because they advertise LASIK on TV  and promoting it for these low life doctors .  I have no respect for these bastards nor do I trust any of these money hungry charlatans and the same goes for the FDA  who approved such dangerous surgery .\"",
"44,01-11-2011,Sheralyn,Guilleminot,Winnipeg,,Canada,",
"45,01-11-2011,Vlad,Botezatu,MUNDELEIN,Illinois,\"United States\",",
"46,01-12-2011,patrick,schuhmacher,hoogland,,Netherlands,\"haven't had lasik,but had lasek. supposed to be the ''safer'' way to go. still suffer chronic dry eye for 5 years already.\"",
"47,01-12-2011,John,LaRocca,\"West Henrietta\",\"New York\",\"United States\",\"I had Lasik done in 1999 and it was the worst decision of my life. To say I have dry eye would be an understatement. I live on eye drops. I also see halos and star bursts at night. If I could go back to the way I was before Lasik I would do it.\"",
"48,01-12-2011,Blair,Brawner,\"Fort Myers Beach\",Florida,\"United States\",\"This petition is important to me because I have watched the pain and suffering of a dear friend who received lasik surgery.\"",
"49,01-12-2011,frederick,ayres,bristol,,\"United Kingdom\",",
"50,01-12-2011,\"Dean Andrew\",Kantis,\"Fort Lauderdale\",Florida,\"United States\",\"Because the world has been duped, the LASIK industry used falsified studies using only the good outcomes, and throwing away the bad outcomes, in order to get FDA approval...they cited lies that 'there were no known long-term damages from LASIK' when they knew every flap never heals, kills vital corneal nerves needed to generate tears, further thins out corneas which progressivly ages the eye causing/inducing irregular higher order aberrations then needing corneal transplants, all while causing it's victims escalated depression and some suicidal tendencies because there is no cure.\"",
"51,01-12-2011,Jean,Dorrian,Avondale,Pennsylvania,\"United States\",",
"52,01-12-2011,Jason,Jirovsky,\"Grundy Center\",Iowa,\"United States\",\"LASIK surgery was supposed to improve my quality of life.  Instead, it has deteriorated the quality of life for not only me, but my family as well.  I would give almost anything to go back.  That in itself should say enough.  Please discontinue this dangerous procedure until the long term side effects and additional corrective technologies can be developed.  Thank you.\"",
"53,01-12-2011,Catherine,Stone,Summerton,\"South Carolina\",\"United States\",\"I, like so many others, is a victim of LASIK surgery. I am now legally blind in both eyes and need a cornea transplant. PLEASE stop the butchering of healthy eyes.\"",
"54,01-12-2011,Richard,McQueen,\"Cape Town\",,\"South Africa\",\"How can patients sign an Informed Consent document if the side effects are not honestly shared?\"",
"55,01-12-2011,Katie,Enders,Novelty,Ohio,\"United States\",\"I got LASIK in 2006 (at age 23) and it has ruined my life. I suffer from disabling pain that will most likely last forever. With no end in sight, I am becoming more and more suicidal with each day that passes. I don't truly want to die, but I do not want to 'live' like this anymore. I can't.\"",
"56,01-12-2011,Thurlough,Smyth,Douglaston,\"New York\",\"United States\",\"My friend, Colin Dorrian, took his own life after years of suffering negative outcomes of a LASIK procedure.\"",
"57,01-12-2011,Gail,Brion,Lexington,Kentucky,\"United States\",\"I have been left with compromised vision after LASIK.  I have multiple images, halos, glare, loss of contrast sensitivity, and can no longer use a microscope.  The side-effects of this surgery were downplayed and my negative results were not reported as part of the study that was ongoing at the time of my surgery.  My university faculty surgeon calls me 'functional' and considers my outcome acceptable.  My worst decision was to have trusted him and the FDA with my vision.  The FDA needs to admit and rectify its mistakes.\"",
"58,01-12-2011,Kiran,Shah,coimbatore,,India,\"I had lasil 6 months back and frankly speaking, my lasik doctor conned me giving all the false promises, if he wanted money so badly i would have donated money, atleast my pricelss eyes would not have been compromised for ever, how can FDA approve an irreversible procedure?now i am suffering from pooer quality vision,loss of contrast, ghosting, haloes and starbursts, people who are promoting and helping to promote lasik are worst than devils.\"",
"59,01-12-2011,Susan,Amtsfield,Mohnton,Pennsylvania,\"United States\",",
"60,01-12-2011,katherine,falkenstern,\"ft wayne\",Indiana,\"United States\",\"my brother had severe eye damage after having lasik surgery and was not a good candidate for the surgery in the first place.\"",
"61,01-12-2011,Laura,Napier,Bronx,\"New York\",\"United States\",",
"62,01-12-2011,Kenneth,Minarik,Rockford,Illinois,\"United States\",\"I have dedicated 20 years of my professional life as an optometrist to solving the problems of botched refractive surgery.\"",
"63,01-12-2011,Donna,Russo,Irving,Texas,\"United States\",\"Lasik surgery has been devastating to my son!\"",
"64,01-12-2011,Nitin,Mitra,\"New Delhi\",,India,\"Laser kills Cornea!!\"",
"65,01-12-2011,Mary,Kurtz,Philadelphia,Pennsylvania,\"United States\",\"This issue is important to me because my nephew took his life when he was unable to live with the outcome to his eyes of lasik surgery.\"",
"66,01-12-2011,James,Singletary,Fayetteville,\"North Carolina\",\"United States\",\"We have to ask ourselves 'do we really need LASIK now that we have a new and improved non-surgical vision correction procedure called OrthoKeratology (Ortho-K).'  Thousands of people in this country and around the world are choosing Ortho-K over Lasik; and still it is not being heavily advertised here in the U.S.   My guess is that 98% of the people who are having problems with Lasik were not given the option of Ortho-K.   The public must know they have options.  Doctors, start offering this procedure to your patients.  To get updated/educated/training on the modern advancements of Ortho-K, visit online the OrthoKeratology Academy of America.\"",
"67,01-12-2011,Nadia,Salom,MEMPHIS,Tennessee,\"United States\",",
"68,01-12-2011,Cissy,Coon,FAYETTEVILLE,\"North Carolina\",\"United States\",\"have been in optical field past ten years and our eye sight and eye health is of the most importance. Who wants to loose their vision or even risk the possibility.This is something you can't buy if its not good.!! Please Agree and sign if you care.\"",
"69,01-12-2011,Dave,Johnson,Plano,Texas,\"United States\",",
"70,01-12-2011,David,Doyle,Skippack,Pennsylvania,\"United States\",",
"71,01-12-2011,Brittney,Jaynes,Atlanta,Georgia,\"United States\",\"One of my closest friends had this surgery and she was so excited....until it completely changed her life and now she suffers everyday.  She talked me out of doing LASIK and now I want everyone else to know that it is unnecessary and dangerous!  Say yes to glasses and contacts and no to lasik!!!\"",
"72,01-12-2011,Andrei,Andreev,pernik,,Bulgaria,",
"73,01-12-2011,Lloyd,Sokol,Coquitlam,,Canada,",
"74,01-12-2011,\"Kathleen Dorrian\",Leonardo,Cooperstown,\"New York\",\"United States\",\"My nephew took his own life, tortured by the unbearable after-effects of LASIK surgery.\"",
"75,01-12-2011,Katie,\"Van Sloten\",Macomb,Illinois,\"United States\",\"My friend has daily pain thanks to Lasik as well as other challenges.  When will the well being of people trump corporate greed? Enough is enough!\"",
"76,01-12-2011,Samer,Morcos,Danville,California,\"United States\",\"I developed corneal ectasia in the left eye post Lasik plus have severe image distortion at night with halos, double vision and depth misperception. Now I wear RGP contact in the left\"",
"77,01-12-2011,\"Rose An n\",Coville,Cortland,\"New York\",\"United States\",\"I am left permanently disable due to PRK surgery triggering the late Zoster Virus in my body.  This has the potential to cause damage to a great many people.  The doctors don't even speak poorly about each other, buiy222, Tid\""};
*/

while (moreLines(input)) {  

//smatch matches { reader.test(str) };
    
 smatch matches;

 string line, prior_line;

 while (1) {

     getline(input, line);
     cout << "Line:\n" << line << endl;
     
     string transformed_line = regex_replace(line, regex {"(\"\")"}, string{"'"}); 
   
     line = prior_line + transformed_line;

     bool hits = regex_search(line, matches, csv_regex);
         
     if (hits) { 
              
        break;    
  
     } else {
          
         prior_line = line;
     }

 } // end while
  
try {

  cout << " Regex match count is " << matches.size() << endl;
      
  for(size_t i = 1; i < matches.size(); ++i) {
      
          ssub_match submatch = matches[i];
          string str = submatch;
          
          //TODO: Test length of string within submatch
          // TODO: str = ? 
          //--cout << str << endl;
          
         
      /*
       * Remove any enclosing double quotes
       */
      cout << "Before:\n" << submatch << endl;
      
      
      if (str.front() == '"' && str.back() == '"') {
        
        str = str.substr(1, str.end() - str.begin() - 2);
             
      } 
      
      cout << "After:\n" << str << endl;     
      
      continue; // DEBUG skip switch
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
         
    auto rc1 = signer_info_stmt->execute(); 
    auto rc2 = signer_comments_stmt->execute(); 
      
    cout << "Result of signer_info_stmt->execute() = " << rc1 << endl;
    cout << "Result of signer_comments_stmt->execute() = " << rc2 << endl;
    */ 
  } // end for
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
