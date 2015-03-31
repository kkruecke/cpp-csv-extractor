<?php
   
class CsvReader {

  $file;     // \SplFileObject
  $line_no;
  $csv_regex;

  public function __constructor($file_name, $regex)s
  {
     $this->file = new \SplFileObject($file_name, "r");
         
     $this->file->setFlags(\SplFileObject::READ_AHEAD | \SplFileObject::SKIP_EMPTY);

     $this->csv_regex = $regex;
  }

  public function moreLines()
  {
    return $file->eof(); // TODO: check thi
  }

  public function getMatches()
  {
     $matches = array();
     $prior_line = "";

     while(1) {

        $text = $this->file->fgets(); 

        $transformed_line = preg_replace(line, '""', "'");
               
        $line = $prior_line + $transformed_line;

        $hit_count = preg_match_all($this->regex, $text, $matches);
   
        if ($hit_count === FALSE) {

            $prior_line = $line;

        } else {

            break;
        }
   
     }

     return $matches;
  }
}
