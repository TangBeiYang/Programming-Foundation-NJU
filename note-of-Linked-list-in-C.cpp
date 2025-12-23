#include<iostream>
using namespace std;
// ============================================
// 第8章 结构与联合 - 链表与联合体详解
// ============================================

/*本章重点掌握：
1. 链表节点的定义和基本操作（创建、插入、删除、遍历）
2. 链表排序和检索算法的实现
3. 结构体数组的定义和应用
4. 联合体的定义、特性和应用场景
5. 指针在链表操作中的正确使用
6. 内存管理的基本原则 */

// ============================================
// 1. 链表节点结构体定义
// ============================================

struct ListNode {
    int val;                // 节点值
    ListNode* next;         // 指向下一个节点的指针
    // 构造方法
    ListNode() : val(0), next(nullptr) {}                    // 默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}               // 带值构造函数
    ListNode(int x, ListNode* next) : val(x), next(next) {}  // 全参构造函数
};

/*注意：结构体成员不能是自身类型的变量，但可以是自身类型的指针变量
这是链表能够连接多个节点的关键*/

// ============================================
// 2. 链表的建立方式
// ============================================

// 2.1 头部插入法创建链表
Node* InsCreate() {
    Node* head = NULL;      // 链表头指针初始化为空
    for(int i = 0; i < 10; i++) {
        Node* p = new Node;    // 创建新节点
        p->data = i;           // 设置节点数据
        p->next = head;        // 新节点指向原头节点
        head = p;              // 更新头节点为新节点
    }
    return head;               // 返回链表头指针
}

// 2.2 尾部追加法创建链表
Node* AppCreate() {
    Node* head = NULL, *tail = NULL;  // 头指针和尾指针
    for(int i = 0; i < 10; i++) {
        Node* p = new Node;    // 创建新节点
        p->data = i;           // 设置节点数据
        p->next = NULL;        // 新节点指向空
        if(head == NULL) {     // 链表为空的情况
            head = p;
        } else {               // 链表不为空的情况
            tail->next = p;
        }
        tail = p;              // 更新尾指针
    }
    return head;               // 返回链表头指针
}

// ============================================
// 3. 链表节点的插入操作
// ============================================

// 3.1 在第i个节点后插入新节点
void InsertNode(Node* head, int i) {
    Node* current = head;      // current指向第一个节点
    int j = 1;
    // 查找第i个节点
    while(j < i && current->next != NULL) {
        current = current->next;
        j++;
    }
    if(j == i) {               // 找到第i个节点
        Node* p = new Node;    // 创建新节点
        cin >> p->data;        // 输入新节点数据
        p->next = current->next;  // 新节点指向第i+1个节点
        current->next = p;     // 第i个节点指向新节点
    } else {
        cout << "没有节点:" << i << endl;
    }
}

// 3.2 在指定值节点前插入新节点（使用引用传参）
void InsertBeforeKeyNode(Node*& h, int key) {
    Node* p = new Node;        // 创建新节点
    cin >> p->data;            // 输入新节点数据
    if(h != NULL) {            // 链表不为空
        Node* current = h;     // 当前节点
        Node* previous = NULL; // 前驱节点
        // 查找键值为key的节点
        while(current != NULL && current->data != key) {
            previous = current;
            current = current->next;
        }
        if(current != NULL && previous != NULL) {  
            // 在链表中间插入
            p->next = current;
            previous->next = p;
        } else if(current != NULL && previous == NULL) {  
            // 在链表头部插入
            p->next = current;
            h = p;            // 更新头指针
        }
        // 如果没找到key，则不插入
    } else {
        // 链表为空的情况
        p->next = NULL;
        h = p;
    }
}

// ============================================
// 4. 链表节点的删除操作
// ============================================

// 4.1 删除第i个节点
Node* DeleteNode(Node* head, int i) {
    if(i == 1) {                  // 删除头节点
        Node* current = head;     // current指向头节点
        head = head->next;        // head指向新的头节点
        delete current;           // 释放删除节点的空间
    } else {
        Node* previous = head;    // previous指向头节点
        int j = 1       // 查找第i-1个节点
        while(j < i-1 && previous->next != NULL) {
            previous = previous->next;
            j++;
        }
        if(previous->next != NULL) {  // 存在第i个节点
            Node* current = previous->next;  // current指向第i个节点
            previous->next = current->next;  // 连接前后节点
            delete current;          // 释放第i个节点的空间
        } else {
            cout << "没有节点:" << i << endl;
        }
    }
    return head;                  // 返回更新后的头指针
}

// 4.2 删除最后一个节点
Node* DeleteLastNode(Node* head) {
    Node* previous = NULL, *current = head;
    // 查找最后一个节点
    while(current->next != NULL) {
        previous = current;
        current = current->next;
    }
    if(previous != NULL) {       // 存在倒数第二个节点
        previous->next = NULL;   // 断开最后一个节点
    } else {                     // 链表中只有一个节点
        head = NULL;             // 链表置空
    }
    delete current;              // 释放删除节点的空间
    return head;                 // 返回更新后的头指针
}

// ============================================
// 5. 链表的遍历与撤销
// ============================================

// 5.1 遍历输出链表
void PrintList(Node* head) {
    if(!head) {                   // 空链表判断
        cout << "List is empty." << endl;
        return;
    }
    Node* p = head;
    while(p != NULL) {           // 遍历所有节点
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// 5.2 撤销整个链表（释放内存）
void DeleteList(Node* head) {
    while(head != NULL) {        // 遍历所有节点
        Node* current = head;
        head = head->next;
        delete current;          // 释放每个节点
    }
}

// ============================================
// 6. 基于链表的排序算法
// ============================================

// 6.1 链表插入排序主函数
Node* ListSort(Node* head) {
    if(head == NULL || head->next == NULL) {
        return head;            // 空链表或只有一个节点直接返回
    }
    Node* cur = head->next;     // 从第二个节点开始
    head->next = NULL;          // 将头节点脱离，作为已排序队列
    while(cur != NULL) {        // 将后面的节点依次插入已排序队列
        Node* prev = cur;
        cur = cur->next;
        head = ListSortInsert(head, prev);  // 插入到合适位置
    }
    return head;
}

// 6.2 链表插入排序辅助函数
Node* ListSortInsert(Node* head, Node* p) {
    if(p->data < head->data) {  // 插入到头部的情况
        p->next = head;
        return p;               // 返回新的头节点
    }
    Node* cur = head;
    Node* prev = NULL;
    // 查找合适的插入位置
    while(cur != NULL && p->data >= cur->data) {
        prev = cur;
        cur = cur->next;
    }
    // 插入到prev和cur之间
    p->next = prev->next;
    prev->next = p;
    return head;
}

// ============================================
// 7. 基于链表的信息检索
// ============================================

// 7.1 学生节点结构体
struct NodeStu {
    int id;                     // 学号
    float score;                // 成绩
    NodeStu* next;              // 指向下一个节点的指针
};

// 7.2 顺序查找指定学号的学生成绩
float ListSearch(NodeStu* head, int x) {
    NodeStu* p = head;
    // 遍历链表查找指定学号
    while(p != NULL && p->id != x) {
        p = p->next;
    }
    if(p != NULL) {            // 找到该节点
        return p->score;
    } else {                   // 未找到
        return -1.0;
    }
}

// ============================================
// 8. 结构体数组的应用
// ============================================

// 8.1 学生结构体定义
enum FeMale {F, M};            // 枚举类型，表示性别

struct Stu {
    int id;                    // 学号
    char name;                 // 姓名（简化为一个字符）
    FeMale s;                  // 性别
    int age;                   // 年龄
    float score;               // 成绩
};

// 8.2 基于结构体数组的顺序查找
float Search(Stu stu_array[], int count, int id) {
    for(int i = 0; i < count; i++) {
        if(id == stu_array[i].id) {
            return stu_array[i].score;  // 找到则返回成绩
        }
    }
    return -1.0;               // 未找到返回-1.0
}

// 8.3 基于结构体数组的折半查找（需先排序）
float BiSearchR(Stu stu_array[], int first, int last, int id) {
    if(first > last) {
        return -1.0;           // 查找区间无效
    }
    
    int mid = (first + last) / 2;  // 计算中间位置
    
    if(id == stu_array[mid].id) {
        return stu_array[mid].score;  // 找到目标
    } else if(id > stu_array[mid].id) {
        return BiSearchR(stu_array, mid + 1, last, id);  // 右半区查找
    } else {
        return BiSearchR(stu_array, first, mid - 1, id);  // 左半区查找
    }
}

// ============================================
// 10. 重要注意事项
// ============================================

/*链表操作注意事项：
1. 空链表情况处理 (head == NULL)
2. 单节点链表处理
3. 头节点和尾节点的特殊处理
4. 指针操作前确保不为NULL
5. 及时释放删除的节点内存

传参方式选择：
1. 值传递：函数内修改不影响外部
2. 引用传递：函数内修改影响外部
3. 指针传递：可通过返回值或二级指针修改外部指针

内存管理：
1. 使用new创建节点，使用delete释放节点
2. 链表使用完毕后应撤销整个链表
3. 避免内存泄漏和野指针*/

// ============================================
//     其他链表相关函数
// ============================================

//反转链表
ListNode* reverse(ListNode* cur){
    ListNode* pre = ListNode();
    ListNode* curr = cur;
    while (curr){
        ListNode* pnext = curr->next;
        curr->next = pre;
        pre = curr;
        curr = pnext;
    }
    return pre;
}
