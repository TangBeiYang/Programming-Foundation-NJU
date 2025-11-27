#include<iostream>
using namespace std;
//测试与二级指针有关表达式所占内存
void sizeof_test()
{
	double b[10][5];
	// sizeof里必须为纯地址表达式，不能有其他运算符
	cout << sizeof(b) << endl;            //10*5*sizeof(double)
	cout << sizeof(b + 0) << endl;        //4(32位) or 8
	cout << sizeof(b[0]) << endl;         //5*sizeof(double)
	cout << sizeof(b[0] + 0) << endl;     //4(32位) or 8 
	cout << sizeof(b[0][0]) << endl;      //sizeof(double)
	cout << sizeof(b[0][0] + 0) << endl;  //sizeof(double)
	cout << sizeof(*b) << endl;           //5*sizeof(double) 
	cout << sizeof(*b + 0) << endl;       //4(32位) or 8
	cout << sizeof(*b[0]) << endl;        //sizeof(double)
	cout << sizeof(*b[0] + 0) << endl;    //sizeof(double)
}
//交换两个指针变量值
void swap(int** p1, int** p2)
{
	int* temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
//数组的指针与指针数组
void array_pointer()
{
	typedef int A[10];
	A* p;                 //定义数组指针方法1
	int(*q)[3];           //定义数组指针方法2---是一个指针
	int* r[3];            //定义指针数组---是一个数组
	//使用
	int b[2][3] = { {1,2,3},{4,5,6} };
	q = &b[0];            //or q = p
	//q相当于一个二级指针变量
}
