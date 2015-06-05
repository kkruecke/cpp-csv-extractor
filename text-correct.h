  
/* 
  Next, capitalize first word of each sentence. Look for dot/period followed by whitespace, followed by a lowercase letter.
 */ 

 $str = preg_replace_callback(
        '/\.\s+([a-z])/',
        function($matches) { return strtoupper($matches[0]); },
        $str
        );
  
/* Capitalize for character in comments */
