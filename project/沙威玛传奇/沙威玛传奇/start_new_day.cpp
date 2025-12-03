#include"gamestate.h"
#include"customers.h"
#include"playgame.h"
extern void menu_start_day(GameState& state, Customer& cus);
void start_new_day(GameState& state)
{
	Customer cus = generate_customer();
	state.start_new_day_timer();
	state.current_patience = cus.patience;
	state.nextDay();
	menu_start_day(state, cus);
	char n;
	cin >> n;
	while (n)
	{
		if (state.check_time_up(cus)) return;
		switch (n)
		{
		case '1':
			put_pancake(state);
			break;
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
			add_sth(int(n-'1'), state);
			break;
		case '7':
			roll_pancake(state);
			break;
		case '8':
			wrap_pancake(state);
			break;
		case '9':
			give_customer_pancake(state,cus);
			break;
		case 'q':
			takebox(state);
			break;
		case 'w':
			putinfries(state);
			break;
		case 'e':
			give_customer_fries(state, cus);
			break;
		case 'a':
			takecup(state);
			break;
		case 's':
			putincoke(state);
			break;
		case 'd':
			give_customer_coke(state,cus);
			break;
		case 'z':
			cut_meat(state);
			break;
		case 'x':
			cut_potato(state);
			break;
		case 'm':
			fry_fries(state);
			break;
		case 'c':
			buy_materials(state, cus);
			break;
		case '#':
			return;
		default:
			cout << "Input error!" << endl;
			break;
		}
		state.update_timers();
		if (state.check_time_up(cus)) return;
		if (state.next_day) { state.next_day = false; return; }
		menu_start_day(state, cus);
		cin >> n;
	}
	return;
}