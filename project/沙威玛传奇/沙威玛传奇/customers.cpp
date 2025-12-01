#include"customers.h"
#include <algorithm>

string helper_cus(int val) {
    switch (val) {
    case 1:
        return "肉 ";
    case 2:
        return "黄瓜 ";
    case 3:
        return "沙司 ";
    case 4:
        return "薯条 ";
    case 5:
        return "番茄酱 ";
    default:
        return "";
    }
}

Customer::Customer(int a[], int l, bool pan, bool fry, bool coke, string nam)
    :want_pancake(pan), want_fries(fry), want_coke(coke), patience(40), name(nam) {
    for (int i = 0; i < l; i++)pancake[i] = a[i];
    for (int j = l; j < 5; j++)pancake[j] = 0;
    sort(pancake, pancake + 5);
}

string Customer::want_snack_print(){
	if (!(want_fries || want_coke))
		return "无";
	string res = "";
	if (want_fries)res += "薯条 ";
	if (want_coke)res += "可乐";
	return res;
}

string Customer::want_pancake_print(){
    if (want_pancake) {
        string res = "卷饼需求: ";
        for (int i = 0; i < 5; i++) res += helper_cus(pancake[i]);
        return res;
    }
    return "不需要卷饼";
}

bool Customer::check_state(){
    bool temp = want_pancake || want_fries || want_coke;
    return temp;
}