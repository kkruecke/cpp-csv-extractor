#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
using namespace std;

int main()
{
    string utf8_str =  u8"z\u00df\u6c34\U0001d10b"; // or u8"zß水𝄋"
                        // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";

    cout << "original UTF-8 string size: " << utf8_str.size() << endl;
    cout << "original UTF-8 string : " << utf8_str << endl;
 
    // the UTF-8 - UTF-32 standard conversion facet
    wstring_convert<codecvt_utf8<char32_t>, char32_t> cvt; // wstring_convert not part of g++ 4.9
 
    // UTF-8 to UTF-32
    u32string utf32_str = cvt.from_bytes(utf8_str);

    cout << "UTF-32 string size: " << utf32_str.size() << endl;
//    cout << "UTF-32 string : " << utf32_str << endl;

    cout << "converted() == " << cvt.converted() << endl;
}
