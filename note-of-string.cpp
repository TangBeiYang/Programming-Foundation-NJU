#include<iostream>
using namespace std;

//字符串与指针
// ===== 1. 指向字符数组（可修改） =====
char arr[] = "Program";
char *p = arr;                    // p指向arr[0]
p++;                              // 指向arr[1]
*p = 'R';                         // 合法：修改数组内容
// ===== 2. 指向字符串字面量（只读） =====
char *pstr = "Hello";             // pstr指向常量区
// *pstr = 'h';                   // 错误！试图修改常量内存
const char *pstr_const = "Hello"; // 正确：明确常量性
// ===== 3. 指针与数组关键区别 =====
char str[10] = "Hello";
char *ptr = "World";
// 初始化与赋值
str = "New";                      // 错误！数组名是常量
ptr = "New";                      // 正确！改变指针指向
// 输入输出
cin >> str;                       // 正确：输入到数组空间
// cin >> ptr;                    // 危险！ptr可能指向只读区
// 内存大小
sizeof(str);                      // = 10（数组总大小）
sizeof(ptr);                      // = 4/8（指针大小）
// ===== 4. 指针运算与访问 =====
char s[] = "ABCDE";
char *p = s;
cout << p[2];                     // 'C'：下标法
cout << *(p+2);                   // 'C'：指针算术
cout << p;                        // "ABCDE"：输出整个字符串
cout << (void*)p;                 // 输出地址值

//指针与二维字符数组
// ===== 1. 指针数组 vs 数组指针 =====
char *names[] = {"Zhao", "Qian", "Sun", "Li"};  // 指针数组：元素是指针
char (*pNames)[5];                              // 数组指针：指向数组的指针
// ===== 2. 二维字符数组的两种表示 =====
// 方法1：固定大小的二维数组
char names2D[4][5] = {"Zhao", "Qian", "Sun", "Li"};
// 方法2：指针数组（更灵活）
char *namesPtr[] = {"Zhao", "Qian", "Sun", "Li"};
// ===== 3. 二级指针与数组指针操作 =====
//you can read note of double pointer.

//字符串的输入函数
int test_cin()
{
	char a[100],c;
	while (cin >> a) {            //当我输入回车时程序会结束
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

//常见字符串处理库函数及其代码实现
// ===== 1. 字符串长度 =====
// 标准库：strlen(const char* s)
unsigned long strlen_impl(const char *str) {
    const char *cp = str;
    while (*cp++) ;               // 找到'\0'-------字符串处理经典方法，类似链表的找到null
    return (cp - str - 1);        // 计算长度
}
// ===== 2. 字符串复制 =====
// 标准库：strcpy(char* dst, const char* src)
void myStrcpy(char *dst, const char *src) {
    while ((*dst++ = *src++) != '\0');  // 精简实现
}
// 安全版本（VS）：strcpy_s(dst, dst_size, src);
// ===== 3. 字符串拼接 =====
char* strcat_impl(char *s1, char *s2) {
    if(!s1 || !s2) return NULL;
    char *pt = s1;
    while(*s1) s1++;              // 找到s1结尾
    while(*s2) *s1++ = *s2++;     // 复制s2
    *s1 = '\0';                   // 添加结束符
    return pt;
}
// ===== 4. 字符串比较 =====
// strcmp返回ASCII码差值：负数(s1<s2), 0(相等), 正数(s1>s2)
// strcmp("study", "student") = 20 ('y'-'e'的ASCII差)

//常见字符串函数
// ===== 1. 字符串反转 =====
void reverse_string(char *s) {
    char *start = s, *end = s;
    while (*end) end++;          // 找到字符串结尾
    end--;                       // 指向最后一个字符（跳过\0）
    
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}
// ===== 2. 字符串转整数 =====
int str_to_int(const char *s) {
    int result = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            result = result * 10 + (s[i] - '0');
        }
    }
    return result;
}

//main 函数的参数
int main(int argc, char *argv[]) {
    // argc: 参数个数（包括程序名）
    // argv: 参数数组（argv[0]是程序名）
    
    // 示例：运行 ./program file.txt -v
    // argc = 3
    // argv[0] = "./program"
    // argv[1] = "file.txt"
    // argv[2] = "-v"
    for (int i = 1; i < argc; i++) {
        cout << "参数 " << i << ": " << argv[i] << endl;
    }
    return 0;
}

//折半法（二分查找）信息检索
//===== 1. 迭代版本 =====
// 参数：x[]-有序字符数组, k-目标字符, ph-区间起点, pt-区间终点
int BiSearch(char x[], char k, int ph, int pt) {
    int pmid;
    while (ph <= pt) {
        pmid = (ph + pt) / 2;  // 计算中间位置
        
        if (k == x[pmid])       // 找到目标
            break;
        else if (k > x[pmid])   // 目标在右半区
            ph = pmid + 1;
        else                    // 目标在左半区
            pt = pmid - 1;
    }
    // 判断查找结果
    if (ph > pt)
        pmid = -1;  // 未找到
    return pmid;
}
//===== 2. 递归版本 =====
// 参数：x[]-有序字符数组, k-目标字符, ph-区间起点, pt-区间终点
int BiSearch_Recursive(char x[], char k, int ph, int pt) {
    if (ph <= pt) {
        int pmid = (ph + pt) / 2;
        
        if (k == x[pmid]) 
            return pmid;
        else if (k > x[pmid]) 
            return BiSearch_Recursive(x, k, pmid + 1, pt);
        else  // k < x[pmid]
            return BiSearch_Recursive(x, k, ph, pmid - 1);
    }
    else {
        return -1;  // 区间无效，未找到
    }
}
/*  算法复杂度分析
情况	比较次数	时间复杂度
最好情况	1次	O(1)
最坏情况	⌊log₂(n+1)⌋次	O(log n)
平均情况	≈ log₂(n+1)-1次	O(log n)
*/

//字符串数组排序
//===== 1. 比较方法:strcmp =====
// strcmp返回值含义：
int result = strcmp(s1, s2);
// result < 0: s1在字典序中小于s2
// result == 0: s1等于s2
// result > 0: s1大于s2
// 例如：
strcmp("study", "student") = 20;  // 'y'(121) - 'e'(101) = 20
strcmp("work", "worker") = -'e';   // 字符串结束符 < 'e'

//===== 2. 冒泡排序法 =====
void bubble_sort_strings(char* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                // 交换指针
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;  // 提前终止优化
    }
}

//=====3. 现有库中的方法=====               //更应掌握
#include <algorithm>
#include <string>
#include <vector>
// 现代C++推荐做法
vector<string> names = {"Zhao", "Qian", "Sun", "Li"};
// 使用标准库排序
sort(names.begin(), names.end());  // 默认字典序排序
// 自定义比较
sort(names.begin(), names.end(), [](const string& a, const string& b) {
    return a.length() < b.length();  // 按长度排序
});
