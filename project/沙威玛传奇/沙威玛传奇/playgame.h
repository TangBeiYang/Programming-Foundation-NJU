#pragma once
#include"gamestate.h"
#include"customers.h"
#include <algorithm>
#include <ctime>
Customer generate_customer();
void put_pancake(GameState& state);
void add_sth(int n, GameState& state);
void roll_pancake(GameState& state);
void wrap_pancake(GameState& state);
void give_customer_pancake(GameState& state, Customer& cus);
void takebox(GameState& state);
void putinfries(GameState& state);
void takecup(GameState& state);
void putincoke(GameState& state);
void give_customer_fries(GameState& state, Customer& cus);
void give_customer_coke(GameState& state, Customer& cus);
void cut_meat(GameState& state);
void cut_potato(GameState& state);
void fry_fries(GameState& state);
void buysth(GameState& state, int index, int cost);
void buy_materials(GameState& state, Customer& cus);