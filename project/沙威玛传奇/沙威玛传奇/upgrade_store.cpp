#include"gamestate.h"
extern void menu_upgrade(GameState& state);
void buy_auto_cutter(GameState& state)
{
	const int cost = 40;
	if (state.getGold() >= cost)
	{
		state.spendGold(cost);
		state.auto_cutter = true;
		cout << "³É¹¦¹ºÂò×Ô¶¯ÇĞÈâ»ú£¡" << endl;
	}
	else
	{
		cout << "½ğ±Ò²»×ã£¬¹ºÂòÊ§°Ü£¡" << endl;
	}
}
void buy_gold_plate(GameState& state)
{
	const int cost = 70;
	if (state.getGold() >= cost)
	{
		state.spendGold(cost);
		state.gold_plate = true;
		cout << "³É¹¦¹ºÂò½ğÅÌ×Ó£¡" << endl;
	}
	else
	{
		cout << "½ğ±Ò²»×ã£¬¹ºÂòÊ§°Ü£¡" << endl;
	}
}
void buy_area_expansion(GameState& state)
{
	const int cost = 1000;
	if (state.getGold() >= cost)
	{
		state.spendGold(cost);
		state.area_expansion = true;
		cout << "³É¹¦¹ºÂòÀ©Õ¹ÇøÓò£¡" << endl;
	}
	else
	{
		cout << "½ğ±Ò²»×ã£¬¹ºÂòÊ§°Ü£¡" << endl;
	}
}
void upgrade_store(GameState& state)
{
	menu_upgrade(state);
	int n;
	cin >> n;
	while (n)
	{
		switch (n)
		{
		case 1:
			buy_auto_cutter(state);
			break;
		case 2:
			buy_gold_plate(state);
			break;
		case 3:
			buy_area_expansion(state);
			break;
		case 0:
			return;
			break;
		default:
			cout << "You should input 0,1,2 or 3" << endl;
			break;
		}
		menu_upgrade(state);
		cin >> n;
	}
}