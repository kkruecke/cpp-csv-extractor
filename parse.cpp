int comman_cnt = 0;
int substr_length = 0;

int seq_no;

string line;

string s {line};

int start = index = 0;

while (1) {

  switch (comma_cnt) {

    case 0:
            for(; s[index] !=','; index++);
            ++comma_cnt; 
            string str = s.substr(start, index);              
            seq_no = atoi(seq_no_str);
            break;  
   
    case 1:  
    case 2:  
    case 3:  
    case 4:  
    case 5:  // Skip comma, if starting double quote.
         for (*++s == '"') {

            while(*s++ != '"'); // go to enclosing double quote.

            if (*s++ != ',') {

                 throw badly_formed;
            }  

         } else {

            while(*s++ != ',');
         } 

        string str = s.substr(start, index);  
        break;
   
        string str = s.substring str(start, index);  
        break;
   
        string str = s.substring str(start, index);  
        break;
   
        string str = s.substring str(start, index);  
        break;
   
        s = s.substring str(start, index);  
        break;

    case 6:  
        break;




     default:
        break;
  }
while(*s++ != ','); // advance to next comma or end of string

