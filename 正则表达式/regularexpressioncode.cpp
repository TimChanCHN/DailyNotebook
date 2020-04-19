#include <iostream>
#include <regex>
using namespace std;

int main() 
{
    regex r("\\d{3}");
    string str;
    while(true)
    {
		cout << "pls enter:";
        if(!getline(cin,str) || str == "q")
        {
            break;
        } else
        {
            smatch match;
            if(regex_match(str, match, r))
            {
                cout << "vaild argument" << endl;
                cout << match[0] << endl;
                cout << match[1] << endl;
                cout << match[2] << endl;
            }else
            {
                cout << "invaild argument" << endl;
            }

        }
    }
    return 0;
}
