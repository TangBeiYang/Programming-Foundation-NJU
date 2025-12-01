#include"head.h"
int main()
{
	GameState game(0, 1);
	menu_main(game);
	int n, flag = 0;
	cin >> n;
	while (n)
	{
		switch (n)
		{
		case 1:
			start_new_day(game);
			break;
		case 2:
			upgrade_store(game);
			break;
		case 3:
			flag = 1;
			break;
		default:
			cout << "You should input 1,2 or 3" << endl;
			break;
		}
		if (flag)break;
		menu_main(game);
		cin >> n;
	}
	return 0;
}