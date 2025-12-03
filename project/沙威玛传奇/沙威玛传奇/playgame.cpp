#include"gamestate.h"
#include"customers.h"
#include"playgame.h"
#include <algorithm>
#include <ctime>
extern void menu_restock(GameState& state);

void generateRandomBools(bool& bool1, bool& bool2, bool& bool3) {
	static bool seeded = false;
	if (!seeded) {
		srand(static_cast<unsigned int>(time(nullptr)));
		seeded = true;
	}
	bool1 = rand() % 2 == 0;
	bool2 = rand() % 2 == 0;
	bool3 = rand() % 2 == 0;
	if (!bool1 && !bool2 && !bool3) {
		int choice = rand() % 3;
		if (choice == 0) bool1 = true;
		else if (choice == 1) bool2 = true;
		else bool3 = true;
	}
}

Customer generate_customer()
{
	string names[] = { "杨飞扬","？？？","神秘助教","正常人","正常人" ,"大学生" };
	bool bool1, bool2, bool3;
	static bool seeded = false;
	if (!seeded) {
		srand(static_cast<unsigned int>(time(nullptr)));
		seeded = true;
	}
	bool1 = rand() % 2 == 0; bool2 = rand() % 2 == 0; bool3 = rand() % 2 == 0;
	if (!bool1 && !bool2 && !bool3) {
		int choice = rand() % 3;
		if (choice == 0) bool1 = true;
		else if (choice == 1) bool2 = true;
		else bool3 = true;
	}
	int x = rand() % 6; int a[] = { 0,0,0,0,0 }, l = 0;
	if (bool1) {
		l = rand() % 5 + 1;
		for (int i = 0; i < l; i++)a[i] = rand() % 5 + 1;
	}
	Customer yfy(a, l, bool1, bool2, bool3, names[x]);
	return yfy;
}

void put_pancake(GameState& state)
{
	if (state.has_pancake)cout << "已经有饼了" << endl;
	else {
		int temp = state.getMaterial(0);
		if (temp > 0) {
			state.has_pancake = true;
			state.reduceMaterial(0, 1);
			cout << "饼放好了" << endl;
		}
		else
			cout << "没有饼了" << endl;
	}
}

void add_sth(int n, GameState& state)
{
	bool flag = false;
	if (!state.has_pancake)cout << "还没放饼呢" << endl;
	else {
		int temp = state.getMaterial(n);
		if (temp > 0) {
			for (int i = 0; i < 5; i++){
				if(state.pancake[i]==0)
				{
					state.pancake[i]=n;
					state.reduceMaterial(n, 1);
					sort(state.pancake, state.pancake + 5);
					cout << "配料添加好了" << endl;
					flag = true;
					return;
				}
			}
			cout << "饼已经装不下了" << endl;
		}
		else cout << "该配料不足" << endl;
	}
}

void roll_pancake(GameState& state)
{
	if (!state.has_pancake)cout << "还没放饼呢" << endl;
	else {
		state.cake_roll = true;
		cout << "饼卷好了" << endl;
	}
}

void wrap_pancake(GameState& state)
{
	if (!state.has_pancake)cout << "还没放饼呢" << endl;
	else if (!state.cake_roll)cout << "还没卷饼呢" << endl;
	else if (state.getMaterial(9) == 0)cout << "没有包装纸了" << endl;
	else {
		state.cake_wrap = true;
		state.reduceMaterial(9, 1);
		cout << "包装好了" << endl;
	}
}

void give_customer_pancake(GameState& state, Customer& cus)
{
	if (!state.has_pancake)cout << "还没放饼呢" << endl;
	else if (!state.cake_roll)cout << "还没卷饼呢" << endl;
	else if (!state.cake_wrap)cout << "还没包装呢" << endl;
	else if (!cus.want_pancake) { 
		cout << cus.name << "不想要卷饼" << endl;
		state.clear_state();
		state.next_day = true; 
	}
	else {
		for (int i = 0; i < 5; i++)
			if (state.pancake[i] != cus.pancake[i]){
				cout << cus.name << "觉得你的卷饼糟透了" << endl;
				state.clear_state();
				state.next_day = true;
				return;
			}
		if (state.gold_plate)state.addGold(60);
		else state.addGold(40);
		cout << cus.name << "喜欢你的卷饼" << endl;
		state.has_pancake = false;
		state.cake_roll = false;
		state.cake_wrap = false;
		cus.want_pancake = false;
		for (int i = 0; i < 5; i++)state.pancake[i] = 0;
		if (!(cus.check_state())) {
			state.clear_state();
			state.next_day = true;
		}
	}
}

void takebox(GameState& state)
{
	if (state.take_box)cout << "已经拿了盒子" << endl;
	else {
		int temp = state.getMaterial(10);
		if (temp > 0) {
			state.take_box = true;
			state.reduceMaterial(10, 1);
			cout << "拿到盒子了" << endl;
		}
		else
			cout << "没有盒子了" << endl;
	}
}

void putinfries(GameState& state)
{
	if (!state.take_box)cout << "还没拿盒子呢" << endl;
	else if (state.putin_fries)cout << "已经放薯条了" << endl;
	else {
		int temp = state.getMaterial(4);
		if (temp > 0) {
			state.putin_fries = true;
			state.reduceMaterial(4, 1);
			cout << "薯条放好了" << endl;
		}
		else
			cout << "没有薯条了" << endl;
	}
}

void takecup(GameState& state)
{
	if (state.take_cup)cout << "已经拿了杯子" << endl;
	else {
		int temp = state.getMaterial(11);
		if (temp > 0) {
			state.take_cup = true;
			state.reduceMaterial(11, 1);
			cout << "拿到杯子了" << endl;
		}
		else
			cout << "没有杯子了" << endl;
	}
}

void putincoke(GameState& state)
{
	if (!state.take_cup)cout << "还没拿杯子呢" << endl;
	else if (state.putin_coke)cout << "已经接可乐了" << endl;
	else {
		int temp = state.getMaterial(12);
		if (temp > 0) {
			state.putin_coke = true;
			state.reduceMaterial(12, 1);
			cout << "可乐接好了" << endl;
		}
		else
			cout << "没有可乐了" << endl;
	}
}

void give_customer_fries(GameState& state, Customer& cus)
{
	if (!state.take_box)cout << "还没拿盒子呢" << endl;
	else if (!state.putin_fries)cout << "还没放薯条呢" << endl;
	else if (!cus.want_fries) { 
		cout << cus.name << "不想要薯条" << endl; 
		state.clear_state();
		state.next_day = true; 
	}
	else {
		cout << cus.name << "拿到了薯条" << endl;
		state.addGold(15);
		state.take_box = false;
		state.putin_fries = false;
		cus.want_fries = false;
		if (!(cus.check_state())) {
			state.clear_state();
			state.next_day = true;
		}
	}
}

void give_customer_coke(GameState& state, Customer& cus)
{
	if (!state.take_cup)cout << "还没拿杯子呢" << endl;
	else if (!state.putin_coke)cout << "还没接可乐呢" << endl;
	else if (!cus.want_coke) { cout << cus.name << "不想要可乐" << endl; state.next_day = true; }
	else {
		cout << cus.name << "拿到了可乐" << endl;
		cout << cus.name << "给了你一些金币" << endl;
		state.addGold(20);
		state.take_cup = false;
		state.putin_coke = false;
		cus.want_coke = false;
		if (!(cus.check_state())) {
			state.clear_state();
			state.next_day = true;
		}
	}
}

void cut_meat(GameState& state)
{
	int temp = state.getMaterial(8);
	if (temp > 0 && state.getMaterial(1) < state.maxstorage)
	{
		state.reduceMaterial(8, 1);
		state.addMaterial(1, 1);
		cout << "肉切好了" << endl;
	}
	else if (temp == 0)cout << "没有肉块了" << endl;
	else cout << "肉已经满了" << endl;
}

void cut_potato(GameState& state)
{
	int temp = state.getMaterial(6);
	if (temp > 0 && state.getMaterial(7) < state.maxstorage)
	{
		state.reduceMaterial(6, 1);
		state.addMaterial(7, 1);
		cout << "土豆条切好了" << endl;
	}
	else if (temp == 0)cout << "没有土豆块了" << endl;
	else cout << "土豆条已经满了" << endl;
}

void fry_fries(GameState& state)
{
	int temp = state.getMaterial(7);
	if (temp > 0 && state.getMaterial(4) < state.maxstorage)
	{
		state.reduceMaterial(7, 1);
		state.addMaterial(4, 1);
		cout << "薯条炸好了" << endl;
	}
	else if (temp == 0)cout << "没有土豆条了" << endl;
	else cout << "薯条已经满了" << endl;
}

void buysth(GameState& state, int index, int cost)
{
	if (state.getGold() >= cost)
	{
		if (state.getMaterial(index) >= state.maxstorage)
		{
			cout << "该物品已满" << endl;
			return;
		}
		state.spendGold(cost);
		state.addMaterial(index, 1);
		cout << "购买成功" << endl;
	}
	else cout << "金币不足" << endl;
}

void buy_materials(GameState& state, Customer& cus)
{
	state.is_restock_menu_open = true;
	int n;
	menu_restock(state);
	cin >> n;
	while (n)
	{
		switch (n)
		{
		case 1:
			buysth(state, 0, 2);
			break;
		case 2:
			buysth(state, 8, 6);
			break;
		case 3:
			buysth(state, 2, 4);
			break;
		case 4:
			buysth(state, 3, 4);
			break;
		case 5:
			buysth(state, 5, 4);
			break;
		case 6:
			buysth(state, 6, 3);
			break;
		case 7:
		case 8:
		case 9:
			buysth(state, n - 2, 2);
			break;
		case 10:
			buysth(state, 12, 5);
			break;
		case 0:
			state.is_restock_menu_open = false;
			return;
		default:
			cout << "Input error!" << endl;
			break;
		}
		menu_restock(state);
		if (state.check_time_up(cus)) return;
		cin >> n;
	}
	state.is_restock_menu_open = false;
}