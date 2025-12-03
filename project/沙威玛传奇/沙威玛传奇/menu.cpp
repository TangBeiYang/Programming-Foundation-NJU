#include<iostream>
#include"customers.h"
#include"gamestate.h"
#include<thread>
#include<chrono>
using namespace std;

void menu_main(GameState& state)
{
	printf("\n\n");
	cout << "================================" << endl;
	cout << "\t   沙威玛传奇" << endl;
	cout << "================================" << endl;
	cout << "你需要在10天内赚取超过200金币，成为卷饼大王！" << endl;
	cout << "累计金币：" << state.getGold() << endl;
	cout << "进行天数：" << state.getDay() << endl;
	cout << state.upgrade_state() << endl;
	cout << "--------------------------------" << endl;
	cout << "1.开始新的一天" << endl;
	cout << "2.升级店铺" << endl;
	cout << "3.设置" << endl;
	cout << "4.退出游戏" << endl;
	cout << "--------------------------------" << endl;
	cout << "请输入数字（1-4）";
}

void menu_upgrade(GameState& state)
{
	cout << "\n\n";
	cout << "================================" << endl;
	cout << "\t   升级店铺" << endl;
	cout << "================================" << endl;
	cout << "累计金币：" << state.getGold() << endl;
	cout << "进行天数：" << state.getDay() << endl;
	cout << state.upgrade_state() << endl;
	cout << "--------------------------------" << endl;
	cout << "1.[40金币]自动产肉机(肉的库存不会再降至0)" << endl;
	cout << "2.[70金币]金盘子(提升卷饼价值到60金币)" << endl;
	cout << "3.[1000金币]扩展区域(敬请期待)" << endl;
	cout << "0.返回主菜单" << endl;
	cout << "--------------------------------" << endl;
	cout << "请输入数字（0-3）";
}

void displayMaterials(GameState& state) {
	string materialNames[] = { "饼","肉","黄瓜","沙司","薯条","番","土豆块","土豆条","肉块","纸","盒","杯","可乐" };
	cout << "[主料] " << materialNames[0] << ": " << state.getMaterial(0) << endl;
	cout << "[配料] ";
	for (int i = 1; i <= 5; i++) {
		cout << materialNames[i] << ": " << state.getMaterial(i);
		if (i < 5) cout << " ";
	}
	cout << endl;
	cout << "[辅料] ";
	for (int i = 6; i <= 8; i++) {
		cout << materialNames[i] << ": " << state.getMaterial(i);
		if (i < 8) cout << " ";
	}
	cout << endl;
	cout << "[耗材] ";
	for (int i = 9; i <= 11; i++) {
		cout << materialNames[i] << ": " << state.getMaterial(i);
		if (i < 11) cout << " ";
	}
	cout << endl;
	cout << "[饮料] " << materialNames[12] << "液: " << state.getMaterial(12) << endl;
}

void menu_start_day(GameState& state, Customer& cus)
{
	state.update_timers();
	printf("\n\n");
	cout << "[第 " << state.getDay() << " 天] | 时间: " << state.total_time << "s | 金币: " << state.getGold() << endl;
	cout << "卷饼40金币/个  可乐20金币/杯  薯条15金币/份" << endl;
	cout << "--------------------------------" << endl;
	cout << "提示: " << cus.name << "来了！" << endl;
	cout << "--------------------------------" << endl;
	cout << "顾客订单 (耐心: " << state.current_patience << "s):" << endl;
	cout << cus.want_pancake_print() << endl;
	cout << "- 小吃: " << cus.want_snack_print() << endl;
	cout << "--------------------------------" << endl;
	cout << "【卷饼台】 " << state.state1_pancake_print() << " | 配料: " << state.state4_pancake_print() << " | " << state.state2_pancake_print() << " | " << state.state3_pancake_print() << endl;
	cout << "【小吃台】 薯条: " << state.state_fries_print() << " | 可乐: " << state.state_coke_print() << endl;
	cout << "--------------------------------" << endl;
	displayMaterials(state);
	cout << "--------------------------------" << endl;
	cout << "指令帮助:" << endl;
	cout << "卷饼制作: [1] 放饼 [2] 加肉 [3] 加黄瓜 [4] 加沙司 [5] 加薯条 [6] 加番茄酱" << endl;
	cout << "          [7] 卷起 [8] 包装 [9] 给顾客卷饼" << endl;
	cout << "小吃制作: [q] 拿盒 [w] 装薯条 [e] 给顾客薯条" << endl;
	cout << "          [a] 拿杯 [s] 接可乐 [d] 给顾客可乐" << endl;
	cout << "库存管理: [z] 切肉 [x] 切土豆 [m] 炸薯条" << endl;
	cout << "          [c] 补充原料" << endl;
	cout << "          [#] 回到主界面" << endl;
	cout << "--------------------------------" << endl;
	if (state.check_time_up(cus)) return;
	cout << "请输入指令: ";
}

void menu_restock(GameState& state)
{
	state.update_timers();
	state.is_restock_menu_open = true;
	printf("\n\n\n");
	cout << "================================" << endl;
	cout << "    补充原料    剩余时间: " << state.total_time << "s" << endl;
	cout << "================================" << endl;
	cout << "\t 当前金币：" << state.getGold() << endl;
	cout << "--------------------------------" << endl;
	cout << "1.饼 (2金币)" << endl;
	cout << "2.肉块 (6金币)" << endl;
	cout << "3.黄瓜 (4金币)" << endl;
	cout << "4.沙司 (4金币)" << endl;
	cout << "5.番茄酱 (4金币)" << endl;
	cout << "6.土豆块 (3金币)" << endl;
	cout << "7.纸 (2金币)" << endl;
	cout << "8.盒 (2金币)" << endl;
	cout << "9.杯 (2金币)" << endl;
	cout << "10.可乐液 (5金币)" << endl;
	cout << "0.返回上一菜单" << endl;
	cout << "--------------------------------" << endl;
	cout << "请输入数字(0-10):";
}

void menu_settings(GameState& state)
{
	printf("\n\n\n");
	cout << "================================" << endl;
	cout << "\t   设置菜单" << endl;
	cout << "================================" << endl;
	cout << "金币: " << state.getGold() << endl;
	cout << "总时间: " << state.max_time << "s  最大库存: " << state.maxstorage << endl;
	cout << "1.每天总时间" << endl;
	cout << "2.最大库存" << endl;
	cout << "3.作弊(获得100金币)" << endl;
	cout << "0.返回主菜单" << endl;
	cout << "--------------------------------" << endl;
	cout << "请输入数字（0-3）";
}