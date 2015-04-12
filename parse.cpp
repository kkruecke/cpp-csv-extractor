
vector<<pair<int>> indecies(8);

int comma_cnt = 0;
int substr_length = 0;

const int date_length = 10;

string line;

int start = current_index = 0;

while (1) {

  switch (comma_cnt) {

    case 0:
            for(; s[index] !=','; current_index++);

            ++comma_cnt; 

            indecies[0] = make_pair(start, current_index);              

            break;  
   
    case 1: // date is a fixed length and can therefore be calculated 
                          
            indecies[1] = make_pair(indecies[1].last + 1, date_length);              

            break;

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

