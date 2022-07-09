#include <iostream>
#include "perso.h"

using namespace std;

 void Perso::create(const string& entry_name, const string& entry_attack_name, const int& entry_life_point, const int& entry_attack_point)
{
	name=entry_name;
	attack_name=entry_attack_name;
	life_point=entry_life_point;
	attack_point=entry_attack_point;
}

void Perso::attack(int& life_point_opponent, const string& opponent_name)
{
	life_point_opponent -= attack_point;
	cout << name << ":" << attack_name << "!" << endl;
	cout << opponent_name << "a perdu " << attack_point << " points de vie" << endl;
}
