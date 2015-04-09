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
        string str = s.substr(start, index);  
        break;
   
    case 2:  
        string str = s.substring str(start, index);  
        break;
   
    case 3:  
        string str = s.substring str(start, index);  
        break;
   
    case 4:  
        string str = s.substring str(start, index);  
        break;
   
    case 5:  
        s = s.substring str(start, index);  
        break;

    case 6:  
        break;




     default:
        break;
  }
while(*s++ != ','); // advance to next comma or end of string

