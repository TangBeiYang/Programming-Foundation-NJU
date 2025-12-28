//核心:共享存储空间，memory
//目的:节省空间
//创建一个各元素可能互斥的结构体
// ============================================
// 联合体(union)的定义与应用
// ============================================

// 1 联合体的定义
union myType {
    int i;                     // 整型成员
    char c;                    // 字符型成员
    double d;                  // 双精度浮点型成员
};

/*联合体特点：
1. 所有成员共享同一块内存空间
2. 内存大小由最大成员决定
3. 同一时间只能使用一个成员
4. 为其中一个成员赋值会影响其他成员的值  */

// 2 联合体的使用示例
void unionExample() {
    myType v;                  // 定义联合体变量
  
    v.i = 12;                  // 使用整型成员
    cout << v.i << endl;       // 输出12
    
    v.c = 'X';                 // 使用字符型成员
    cout << v.c << endl;       // 输出'X'
    cout << v.i << endl;       // 此时输出的是'X'的ASCII码
    
    v.d = 12.95;               // 使用双精度浮点型成员
    cout << v.d << endl;       // 输出12.95
}

// 3 联合体数组的应用示例
enum Grade {UNDERGRAD, MASTER, PHD, FACULTY};  // 职级枚举

union Performance {
    int nPaper;               // 已发表论文篇数（用于硕士、博士、教师）
    double gpa;               // GPA（用于本科生）
};

struct Person {
    char id[20];              // 编号
    char name[20];            // 姓名
    Grade grd;                // 职级
    Performance pfmc;         // 业绩（根据职级选择不同成员）
};
