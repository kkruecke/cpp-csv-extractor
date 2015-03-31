<?php
   
// See Maude source code.

  $this->LogFile = new \SplFileObject("error-log.txt", "w");
      
  $this->LogFile->setFlags(\SplFileObject::READ_AHEAD | \SplFileObject::SKIP_EMPTY);

  $matches = array();

  while ($file as $line_no => $text) {

      $regex = '/^(\d+),(\d\d-\d\d-\d\d\d\d),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*)$/m'; 

      $hit_count = preg_match_all($regex, $text, $matches);

      if ($hit_count != 8) {

      }

      if (count($matches[1]) < 8)  {
   
         echo "matches[1] count is " . count($matches[1]) . " on line $line_count \n";
   
         echo "$line_count : match count less than 8 (8th column is data_received). Match count equals " . count($matches[1]) . "\n");
      }
  }
