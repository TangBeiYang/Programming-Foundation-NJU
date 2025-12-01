#pragma once
#include <iostream>
#include"customers.h"
#include <algorithm>
#include <thread>
#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;
class GameState {
private:
    int gold;
    int day;
    int materials[13];
    steady_clock::time_point day_start_time;
    steady_clock::time_point last_patience_update;
    steady_clock::time_point last_total_time_update;
public:
    int pancake[5];
    int maxstorage;
    int total_time;
    int current_patience;
    bool auto_cutter;
    bool gold_plate;
    bool area_expansion;
    bool has_pancake;
    bool has_fries;
    bool has_coke;
    bool cake_roll;
    bool cake_wrap;
    bool take_box;
	bool putin_fries;
	bool take_cup;
	bool putin_coke;
    bool next_day;
    bool is_restock_menu_open;
    GameState(int initialGold, int initialDay);
    void clear_state();
    int getGold();
    void addGold(int amount);
    void spendGold(int amount);
    int getDay();
    void nextDay();
    string upgrade_state();
    int getMaterial(int index);           
    void addMaterial(int index, int amoun); 
    void reduceMaterial(int index, int amount);
    string state1_pancake_print();
    string state2_pancake_print();
    string state3_pancake_print();
    string state4_pancake_print();
	string state_fries_print();
    string state_coke_print();
    void start_new_day_timer();
    void update_timers();
    bool check_time_up(Customer& cus);
};