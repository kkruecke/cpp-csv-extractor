<?php
require_once("loader/SplClassLoader.php");
use Csv\CsvReader as CsvReader;

 $spl_loader = new SplClassLoader('Csv', 'src');

 $spl_loader->register();
   
 $regex = '/^(\d+),(\d\d-\d\d-\d\d\d\d),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*),("[^"]*"|[^,"]*)$/m'; 
  
 $reader = new CsvReader("/home/kurt/public_html/petition/petition.csv", $regex); 

 while (!$reader->moreLines()) {

     $matches = $reader->getMatches();

     echo "=======================\n";

     for ($i = 1; $i < count($matches) - 1; ++$i) {

         echo "  " . $matches[$i]  . "\n";          

     }

     echo "\n=======================\n";
 }
