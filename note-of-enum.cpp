// C++ 枚举类型总结
// 根据《程序设计教程 用C++语言编程（第3版）》5.1节整理

// ===== 1. 枚举类型的定义 =====

// 基本定义格式：enum <枚举类型名> {<枚举值表>};
enum Day { SUN, MON, TUE, WED, THU, FRI, SAT };  // 默认从0开始：SUN=0, MON=1...
enum Color { RED, GREEN, BLUE };
enum Month { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

// 显式指定枚举值(先定义最大值，再定义最小值，之后依次补齐)
enum CustomDay { SUN = 7, MON = 1, TUE, WED, THU, FRI, SAT };  // SUN=7, MON=1, TUE=2...

// bool类型可视为预定义枚举
// enum bool { false, true };

// ===== 2. 枚举变量的定义 =====

// 方式1：先定义类型，再定义变量
Day work_day, rest_day;

// 方式2：同时定义类型和变量
enum Day { SUN, MON, TUE, WED, THU, FRI, SAT } d1, d2, d3;

// 方式3：匿名枚举（必须同时定义变量）
enum { V1, V2, V3 } v1, v2;

// 保留C语言的写法（也可用）
enum Day weekend_day;

// ===== 3. 枚举类型的操作 =====

void enum_operations() {
    // 3.1 赋值操作
    Day d1, d2;
    d1 = SUN;      // 正确
    d2 = d1;       // 正确
    
    // 3.2 类型安全限制
    Color c;
    // c = d1;        // 错误：不同类型枚举不能赋值
    // d1 = RED;      // 错误：RED属于Color类型
    
    // 3.3 枚举与整型的转换
    int i = SUN;    // 正确：枚举可转整型
    // d1 = 10;       // 错误：整型不能直接赋给枚举（类型不安全）
    d1 = (Day)3;    // 正确：强制类型转换（需确保值有效）
    
    // 3.4 比较运算
    bool b1 = (MON > TUE);   // 比较前转换为整型：1 > 2 → false
    // bool b2 = (MON > RED); // 语法允许但语义可能错误
    
    // 3.5 算术运算
    int j = d1 * 2;          // 正确：运算结果为int型
    // d1 = d1 * 2;          // 错误：不能将int结果赋给枚举
    
    // 3.6 自增运算（需强制转换）
    for (Day i = SUN; i <= SAT; i = (Day)(i + 1)) {
        // 处理每周各天
    }
}

// ===== 4. 枚举的输入输出 =====

#include <iostream>
using namespace std;

void enum_io_example() {
    Day d;
    int i;
    
    // 4.1 输入：不能直接输入枚举
    // cin >> d;  // 错误
    
    cin >> i;  // 先输入整型值
    // 方法1：switch转换
    switch (i) {
        case 0: d = SUN; break;
        case 1: d = MON; break;
        case 2: d = TUE; break;
        case 3: d = WED; break;
        case 4: d = THU; break;
        case 5: d = FRI; break;
        case 6: d = SAT; break;
        default: cout << "Input Error!" << endl; return;
    }
    
    // 方法2：强制转换（需先检查范围）
    if (i < 0 || i > 6) {
        cout << "Input Error!" << endl;
        return;
    } else {
        d = (Day)i;  // 安全转换
    }
    
    // 4.2 输出：直接输出为整型
    cout << d;  // 输出对应的整数值
    
    // 通常输出对应的字符串
    switch (d) {
        case SUN: cout << "SUN" << endl; break;
        case MON: cout << "MON" << endl; break;
        case TUE: cout << "TUE" << endl; break;
        case WED: cout << "WED" << endl; break;
        case THU: cout << "THU" << endl; break;
        case FRI: cout << "FRI" << endl; break;
        case SAT: cout << "SAT" << endl; break;
    }
}

// ===== 5. 枚举的优点总结 =====

// 5.1 提高程序可读性
// 使用枚举值名代替魔术数字
void process_week() {
    // 差：使用int
    for (int i = 0; i <= 6; i++) { /* 难以理解i的含义 */ }
    
    // 好：使用枚举
    for (Day d = SUN; d <= SAT; d = (Day)(d + 1)) { /* 明确处理每周各天 */ }
}

// 5.2 增强类型安全性
void type_safety() {
    Day d;
    // d = 10;  // 编译错误，防止非法赋值
    d = MON;    // 只能赋枚举值
}

// ===== 6. 注意事项 =====

// 1. 不同枚举类型不能混用
// 2. 整型转枚举需强制转换且确保值有效
// 3. 算术运算结果为整型
// 4. 输入需间接进行，输出为整型
// 5. 枚举值本质是整型常量
