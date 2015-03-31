<?php
namespace Csv;
   
class CsvReader {

  private $file;     // \SplFileObject
  private $line_no;
  private $regex;

  public function __construct($file_name, $regex)
  {
     $this->file = new \SplFileObject($file_name, "r");
         
     $this->file->setFlags(\SplFileObject::READ_AHEAD | \SplFileObject::SKIP_EMPTY);

     $this->regex = "@$regex@m";
  }
  public function readLine()
  {
    $str = $this->file->fgets();
    return $str;
  }

  public function moreLines()
  {
    $bool = $this->file->eof(); // TODO: test this
    return $bool;
  }

  public function getMatches()
  {
     $matches = array();
     $prior_line = "";

     while(1) {

        $line = $this->file->fgets(); 

        // replace two double quotes with a single, single quote
        $transformed_line = \preg_replace('""', "'", $line);
               
        $line = $prior_line . $transformed_line;

        $hit_count = \preg_match($this->regex, $line, $matches);
        
        echo "var_dump(\$line):\n";
        
        echo var_dump($line);
        
        echo  "\n";
        
        echo "var_dump(\$matches):  \n";
        var_dump($matches);
        echo "\n";
   
        if ($hit_count === FALSE) {

            $prior_line = $line;

        } else {

            break;
        }
   
     }

     return $matches;
  }
}
