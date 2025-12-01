#pragma once
#include<iostream>
#include <algorithm>
#include <string>
using namespace std;
class Customer {
public:
	string name;
	int pancake[5];
	int patience;
	bool want_pancake;
	bool want_fries;
	bool want_coke;
	Customer(int a[], int l, bool pan, bool fry, bool coke, string name);
	bool check_state();
	string want_pancake_print();
	string want_snack_print();
};