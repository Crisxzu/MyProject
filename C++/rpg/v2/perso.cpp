include <iostream>
#include "perso.h"

using namespace std;

void Perso::attack(int& life_point_opponent, const string& opponent_name)
{
	life_point_opponent -= attack_point;
	cout << name << ":" << attack_name << "!" << endl;
	cout << opponent_name << "a perdu " << attack_point << " points de vie" << endl;
}
