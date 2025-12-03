#include"gamestate.h"
#include"customers.h"
#include"playgame.h"
extern void menu_settings(GameState& state);
void settings(GameState& state)
{
	menu_settings(state);
	int n;
	cin >> n;
	while (1) {
		switch (n){
		case 1:
			cout << "总时间更新为: ";
			cin >> state.max_time;
			break;
		case 2:
			cout << "最大库存更新为: ";
			cin >> state.maxstorage;
			break;
		case 3:
			state.addGold(100);
			break;
		case 0:
			return;
			break;
		default:
			cout << "请输入正确的数字（0-3）" << endl;
			break;
		}
		menu_settings(state);
		cin >> n;
	}
	return;
}