#include<iostream>
using namespace std;
struct ListNode {
    int val;                // 节点值
    ListNode* next;         // 指向下一个节点的指针
    // 构造方法
    ListNode() : val(0), next(nullptr) {}                    // 默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}               // 带值构造函数
    ListNode(int x, ListNode* next) : val(x), next(next) {}  // 全参构造函数
};
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
//创建链表
//1.直接输入：
ListNode* Input(ListNode* head){
	  int n;
	  while (cin >> n)
	  {
		    ListNode* newNode = new ListNode(n);
		    ListNode* p = head;
		    while (p->next)
			      p = p->next;
		    p->next = newNode;
		    if (char ch = cin.get() == '\n')
			      break;
  	}
	  return head;
}
//2.创建：
ListNode* creat() {
	  ListNode* phead = new ListNode();
	  ListNode* cur = phead;
	  int n = 0;
	  while (1) {
		    if (cin.peek() == '\n') {
			      cin.get();
			      break;
		    }
		    cin >> n;
		    ListNode* yfy = new ListNode(n);
		    cur->next = yfy;
		    cur = yfy;
	  }
	  return phead;
}
