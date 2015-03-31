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

  }
