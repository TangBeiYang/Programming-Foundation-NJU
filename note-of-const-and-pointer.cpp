#include<iostream>
using namespace std;
int n = 0;
const int M = 0; // m为整型常量，其值不可以改变
const int *p1;
//p1 = &M; // p1为指向常量的指针变量，其值可以改变
                     // *p1的值不可以改变
//p1 = &n; // 允许，只不过不能通过p1修改n的值
int * const p2 = &n; // p2为指向变量的指针常量，其值不可以改变
                     // *p2的值可以改变
//(int * const p2 = &M; // 不允许，以防止通过p2修改m的值)
const int * const p3 = &M; // p3为指向常量的指针常量
// 其值与*p3的值都不可以改变
//(const int * const p3 = &n; // 允许，只不过不能通过p3修改n的值)
//n++; // 允许
//m++; // 不允许
//p1++; // 允许
//p2++; // 不允许
//p3++; // 不允许
//int *q; // 可以进行“*q = 1”、“q++”操作，当然需初始化
//q = &n; // 允许
//q = &M; // 不允许，以防止通过q修改M的值

//引用类型：相当于给一个变量取一个别名
void yinyong(){
    int x = 0;
    int &y = x; //y为引用类型的变量
    cout << x << ',' << y << endl; //结果为：0,0
    y = 1;
    cout << x << ',' << y << endl; //结果为：1,1
    x = 2;
    cout << x << ',' << y << endl; //结果为：2,2
}
//利用引用类型交换变量值
void swap(int& a,int& b){
    int temp=a;
    a=b;
    b=temp;
}
//将const int 型地址转换成 int 型地址
int *Max(const int ac[ ], int num)
{
    int max_index = 0;
    for(int i = 1; i < num; i++)
        if(ac[i] > ac[max_index])
            max_index = i;
    return (int *)&ac[max_index];
}
//写一个类似python里map函数功能的函数
typedef double(*yfy)(double);
void map(double a[],int l,yfy f)
{
    for(int i=0;i<l;i++)a[i]=f(a[i]);
}
//或直接这样写
void map2(double a[],int l,double(*yfy)(double))
{
    for(int i=0;i<l;i++)a[i]=yfy(a[i]);
}
double f(double a){ return a*2; }
//也可以直接写一个函数list
