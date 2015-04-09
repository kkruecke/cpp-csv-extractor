int comman_cnt = 0;
int substr_length = 0;

int seq_no;

string line;

string s {line};

int index = 0;

while (1) {

  switch (comma_cnt) {

    case 0:
            for(; s[index] !=','; index++);
            ++comma_cnt; 
            string seq_no_str = s.substr(0, index);              
            seq_no = atoi(seq_no_str);
            break;  
   
    case 1:  
        break;
   
    case 2:  
        break;
   
    case 3:  
        break;
   
    case 4:  
        break;
   
    case 5:  
        break;

    case 6:  
        break;




     default:
        break;
  }
while(*s++ != ','); // advance to next comma or end of string

