#include"gamestate.h"

GameState::GameState(int Gold, int Day)
    : gold(Gold), day(Day), auto_cutter(false), gold_plate(false), area_expansion(false),
    has_pancake(false), has_coke(false), has_fries(false), cake_roll(false), cake_wrap(false),
    take_box(false), putin_coke(false), putin_fries(false), take_cup(false),//到时候可以传参数修改
    maxstorage(10), next_day(false), is_restock_menu_open(false), total_time(120), current_patience(40) {
    //0-饼，1-肉，2-黄瓜，3-沙司，4-薯条，5-番，6-土豆块，7-土豆条，8-肉块，9-纸，10-盒，11-杯，12-可乐
    for (int i = 0; i < 13; i++) {
        materials[i] = 5;
    }
    for (int i = 0; i < 5; i++) {
        pancake[i] = 0;
    }
	max_time = 120;
}

int GameState::getGold() {
    return gold;
}

void GameState::addGold(int amount) {
    gold += amount;
}

void GameState::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
    }
    else
        cout << "使用失败，余额不足" << endl;
}

int GameState::getDay() {
    return day;
}

void GameState::nextDay() {
    day++;
}

string GameState::upgrade_state() {
    string a = "自动产肉机";
    string b = "金盘子";
    string c = "扩展区域";
    string res = "店铺升级：";
    res += auto_cutter ? (a + "; 已升级 ") : (a + "; 未升级 ");
    res += gold_plate ? (b + "; 已升级 ") : (b + "; 未升级 ");
    res += area_expansion ? (c + "; 已升级 ") : (c + "; 未升级 ");
    return res;
}

int GameState::getMaterial(int index) {
    if (index >= 0 && index < 13) {
        return materials[index];
    }
    return 0;
}

void GameState::addMaterial(int index, int amount) {
    if (index >= 0 && index < 13 && amount > 0) {
        materials[index] += amount;
    }
    else
        cout << "Index error!" << endl;
}

void GameState::reduceMaterial(int index, int amount) {
    if (index >= 0 && index < 13 && amount > 0) {
        if (materials[index]- amount < 0) {
            cout << "Materials has run out!" << endl;
        }
        else {
            materials[index] -= amount;
			if (index == 1 && auto_cutter && materials[1] < 1) {
                materials[1] = maxstorage;
            }
        }
    }
    else
        cout << "Index error!" << endl;
}

string GameState::state1_pancake_print(){
    if (has_pancake)return"满";
	else return"空";
}

string GameState::state2_pancake_print() {
    if (cake_roll)return"已卷";
    else return"未卷";
}

string GameState::state3_pancake_print() {
    if (cake_wrap)return"已包";
    else return"未包";
}

string helper(int val) {
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

string GameState::state4_pancake_print() {
    string res = "[ ";
    for (int i = 0; i < 5; i++) res += helper(pancake[i]);
    res += "]";
    return res;
}

string GameState::state_fries_print() {
    if (has_fries)return"有";
    else return"无";
}

string GameState::state_coke_print() {
    if (has_coke)return"有";
    else return"无";
}

void GameState::clear_state() {
	has_coke = false;
	has_fries = false;
	has_pancake = false;
	cake_roll = false;
	cake_wrap = false;
	take_box = false;
	putin_coke = false;
	putin_fries = false;
	take_cup = false;
    for (int i = 0; i < 5; i++) {
        pancake[i] = 0;
	}
}

void GameState::start_new_day_timer() {
    day_start_time = steady_clock::now();
    last_patience_update = day_start_time;
    last_total_time_update = day_start_time;
    total_time = max_time;
}

void GameState::update_timers() {
    auto now = steady_clock::now();
    auto total_elapsed = duration_cast<seconds>(now - last_total_time_update).count();
    if (total_elapsed >= 1) {
        total_time -= total_elapsed;
        last_total_time_update = now;
        if (total_time < 0) total_time = 0;
    }
    if (!is_restock_menu_open) {
        auto patience_elapsed = duration_cast<seconds>(now - last_patience_update).count();
        if (patience_elapsed >= 1) {
            current_patience -= patience_elapsed;
            last_patience_update = now;
            if (current_patience < 0) current_patience = 0;
        }
    }
    else last_patience_update = now;
}

bool GameState::check_time_up(Customer&cus) {
    if (total_time <= 0 || current_patience <= 0) {
        if (total_time <= 0) {
            cout << "时间到了，今天结束了！" << endl;
        }
        else {
            cout << cus.name << "失去了耐心，离开了！" << endl;
        }
        clear_state();
        next_day = true;
        nextDay();
        return true;
    }
    return false;
}

bool GameState::check_game_over() {
    if (gold > 200) {
        cout << "你成了卷饼大王！" << endl;
        return true;
    }
    if (getDay() > 10) {
        cout << "房租到期了，你灰溜溜的搬走了" << endl;
        return true;
    }
    return false;
}