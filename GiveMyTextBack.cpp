///*
//*/
//
//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//
//string givebacktext(string str, int& periodspos)
//{
//	while((str[0]>'Z'||str[0]<'A')&&(str[0]>'z'||str[0]<'a'))
//		str=str.substr(1);
////	if(str[0]<='z'&&str[0]>='a')
////		str[0]-=32;
////	int periodspos=-1;
//	int s=0, e=0;
//	for(int i=0; i<str.size(); i++)
//	{
//		if(periodspos==-1&&(str[i]>='A'&&str[i]<='Z'))
//			str[i]+=32;
//		if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
//		{
//			if(periodspos==1)
//			{
//				if(str[i]>='a'&&str[i]<='z')
//					str[i]-=32;
//				periodspos=-1;
//			}
//			if(e>s+1)
//			{
//				str=str.substr(0,s+1)+str.substr(e);
//				i=s+1;
//			}
//			s=e=i;
//		}
//		else if(str[i]==' ')
//		{
//			e++;
//		}
//		else if(str[i]==','||str[i]=='.')
//		{
//			str=str.substr(0,s+1)+str.substr(i);
//			if(str[i]=='.') periodspos=1;
//			s++;
//			e=s;
//			i=s;
//			str=str.substr(0,s+1)+" "+str.substr(s+1);
//		}
//	}
//	if(e>s)
//		str=str.substr(0,s+1);
//	
//	return str;
//}
//
//int main()
//{
//	char c;
//	vector<string> str;
//	string temp="";
//	//c=getchar();
//	while(cin >> noskipws >> c)
//	{
//		if(c!='\n')
//			temp+=c;
//		else
//		{
//			str.push_back(temp);
//			temp="";
//		}
//	}
////	str.push_back(temp);
//	int periodspos=1;
//	for(int i=0; i<str.size(); i++)
//	{
//		
//		if(i==str.size()-1)
//		{
//			if(str[i].back()!='.')
//			{
//
//				if(str[i].back()==',')
//					str[i].back()='.';
//				else
//					str[i]+='.';
//			} 
//		}
//		string s=givebacktext(str[i], periodspos);
//		cout << s << endl;
//	}
//	system("pause");
//	return 0;
//}

#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    vector<string> input;
    string word = "";
    char c;
    while (cin >> noskipws >> c)
    {
        if (isalpha(c))
        {
            if (c >= 'A'&&c <= 'Z')
                c += 32;
            word += c;
        }
        else
        {
            if (word != "")
            {
                input.push_back(word);
                word = "";
            }
            if (c != ' ')
                input.push_back(to_string(c));
        }
    }

    int n = input.size();
    bool isFirst = true;
    for (int i = 0; i < n; i++)
    {
        if (input[i] == "44")
            cout << ',';
        else if (input[i] == "46")
        {
            cout << '.';
            isFirst = true;
        }
        else if (input[i] == "10")
            cout << endl;
        else
        {
            if (i>0 && input[i - 1] != "10")
                cout << " ";

            if (isFirst)
            {
                input[i][0] -= 32;
                isFirst = false;
            }
            cout << input[i];
        }
    }
	system("pause");
    return 0;
}