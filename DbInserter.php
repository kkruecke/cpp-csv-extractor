<?php
/*
 * Purpose: To save petition signatures and associated information into the petition database
 */ 

class DbInserter { 
   
   private $FileIter;

// private $file_name;

// private $LogFile;

   private $signee_no;
   private $date;
   private $city;
   private $state;
   private $country;
   private $comments;

   private $insert_stmt;
   private $pdo;

   private $insert_count = 0;
   private $txt_line_count = 0;
       
   public function __construct($file_name, $db_cred) 
   {
       parent::__construct($file_name, $pdo);
           
       $this->LogFile = new \SplFileObject("text-log.txt", "w");
       $this->LogFile->setFlags(\SplFileObject::READ_AHEAD | \SplFileObject::SKIP_EMPTY);
         
       $this->signee = (int) 0;
       $this->date = (string) "";
       $this->city = (string) "";
       $this->state = (string) "";
       $this->country = (string) "";
       $this->comments = (string) "";

       $this->pdo = new \PDO()

       // SQL statements with named placeholders 
       $this->insert_stmt = $pdo->prepare("INSERT INTO petition(signee_no, date, city, state, country, comments)
                                                 VALUES(:signee_no, :date, :city, :state, :country, :comments)"); 

       // bind the parameters in each statement
       $this->insert_stmt->bindParam(':signee_no', $this->signee_no, \PDO::PARAM_INT);
  
       $this->insert_stmt->bindParam(':date',  $this->date,  \PDO::PARAM_STR);
       $this->insert_stmt->bindParam(':city',  $this->city,  \PDO::PARAM_STR);
       $this->insert_stmt->bindParam(':state',  $this->state,  \PDO::PARAM_STR);
       $this->insert_stmt->bindParam(':country',  $this->country,  \PDO::PARAM_STR);
       $this->insert_stmt->bindParam(':comments',  $this->comments,  \PDO::PARAM_STR);

       $this->insert_count = 0;
       $this->txt_line_count = 0;
   }

   public function processLine($text, $line_number)
   {
                         
       $matches = array();
            
       $this->line_count++;
               
       //  $arr = explode("|", $text); failed because there was one line with | in the narrative text. So a regular expression is preferred
      
       $hit_count = preg_match($this->regex, $text, $matches);
          
       if (count($matches) != 7) {
      
               echo "Hit count is $hit_count rather than 7 on line number $this->line_count of file $filename\n";
      
               return;
       }

       $pcre_regex = '/^(\d+)Ž(\d\d-\d\d-\d\d\d\d)Ž("[^"]*"|[^,]*)Ž("[^"]*"|[^,]*)Ž("[^"]*"|[^,]*)Ž("[^"]*"|[^,]*)Ž("[^"]*"|[^,]*)Ž("[^"]*"|[^,]*)/m' 
                
       $matches = array();

       $hits = preg_match($text, $pcre_regex, $matches); 
       var_dump($matches);
       return; 
       $signee_no = (int) $matches[1];
       
      /*
          Description of fields in foitextXXX.txt file:
          1. MDR Report Key
          2. MDR Text Key 
          3. Text Type Code (D=B5, E=H3, N=H10 from mdr_text table) 
          4. Patient Sequence Number (from mdr_text table) 
          5. Date Report (from mdr_text table) 
          6. Text (B5, or H3 or H10 from mdr_text table) 
       */
          
       $date_parts = explode("/", $matches[5]); // date is in format of MM/DD/YYYY      
       
       // Change format from   MM/DD/YYYY to  YYYY-MM-DD    
           
       $this->date = sprintf("%d-%02d-%02d", $date_parts[2], $date_parts[0], $date_parts[1]);
           
       $this->comments = trim($matches[6]);
      
       $this->comments = $this->fixText($text_report);

       echo "Inserting key {$this->signee_no}. With text starting with " . substr($this->text_report, 0, 30) , "\n";
       
       $bRc = $this->insert_stmt->execute();
      
       $this->insert_count++; 
      
       if ($this->line_count % 10000 == 0) {
       
            $inserted = number_format($insert_count); 
       
            $lines_read = number_format($this->line_count);
       
            echo "$inserted number of records inserted out of $lines_read lines read ...\n";
       }
      
   }

   protected function fixText($text)
   {
      $str = strtolower($text);
      
      $str = trim($str);
        
      // Next, capitalize first word of each sentence. 
      $str = preg_replace_callback(
          '/\.\s+([a-z])/',
          function($matches) { return strtoupper($matches[0]); },
          $str
          );
      
       // Also capitalize the first character of the text.       
       $str = preg_replace_callback(
          '/^([a-z])/',
          function($matches) { return strtoupper($matches[0]); },
          $str
          );
  
        //  Capitalize the pronoun ' i '
        $str = preg_replace_callback(
          '/(\s[i]\s)/',
          function($matches) { return strtoupper($matches[0]); },
          $str
          );
      
       return $str; 
    }
}
?>
