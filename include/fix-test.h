  
/* 
  Next, capitalize first word of each sentence. Look for dot/period followed by whitespace, followed by a lowercase letter.
 */ 

void fixText(std::string& str)
{
  std::size_t pos = 0;
 
  while (1) {

    std::size_t found = str.find('.', pos);

    if (found == std::string::npos) {

        break;
    }

    // Look for at least one whitespace character

  }
} 
