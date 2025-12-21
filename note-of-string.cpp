#include<iostream>
using namespace std;
int test_cin()
{
	char a[100],c;
	while (cin >> a) {          //当我输入回车时程序会结束
		c = getchar();            //用来接受缓冲区
		cout << c << "yfy   ";    //查看接受的内容
		cout << a << endl;        //查看stringa的值
	}
	return 0;
}
/*
输入:
hello␣world␣␣this[tap]is␣[tap]a[tap]␣test↵
输出:
 yfy   hello
 yfy   world
        yfy   this
 yfy   is
        yfy   a

yfy   test                     //c接受的是缓冲区第一个字符
*/
int test_getline()
{
	char a[100],c;
	cin.getline(a, 100);         //接受包括tap,空格等字符，且缓冲区无内容
	cout << a << endl;           //输出a
	return 0;
}
/*
输入:
hello␣world␣␣this[tap]is␣[tap]a[tap]␣test↵
输出:
hello world  this       is      a        test
*/
