#ifndef DEF_PERSO
#define DEF_PERSO

#include <string>

class Perso
{
	public:
		std::string name;
		std::string attack_name;
		int life_point;
		int attack_point;
		
		void create(const std::string& entry_name, const std::string& entry_attack_name, const int& entry_life_point, const int& entry_attack_point);
		
		void attack(int& life_point_opponent, const std::string& opponent_name);
};

#endif /*PERSO*/

