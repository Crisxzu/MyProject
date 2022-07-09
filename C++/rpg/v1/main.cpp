#include <iostream>
#include "perso.h"

using namespace std;

int main ()
{
	Perso Group1[2], Group2[2];
	int perso_group1_total_life_point[2], perso_group2_total_life_point[2];
	int i_round=0, turn=1, i_player=0;
	bool f_match_is_finished=false;
	
	Group1[0].create("Gon", "Janken", 500, 150);
	perso_group1_total_life_point[0]=Group1[0].life_point;
	Group1[1].create("Kirua", "Thunder", 400, 200);
	perso_group1_total_life_point[1]=Group1[1].life_point;
	
	Group2[0].create("Hisoka", "Gum-Gum", 1000, 250);
	perso_group2_total_life_point[0]=Group2[0].life_point;
	Group2[1].create("Irumi", "Regard de la mort", 800, 300);
	perso_group2_total_life_point[1]=Group2[1].life_point;
	
	do
	{
		i_round++;
		cout <<  "Round" << i_round << endl;
		switch(turn)
		{
			case 1:
				Group1[i_player].attack(Group2[i_player].life_point, Group2[i_player].name);
				cout << Group1[i_player].name << ":" << Group1[i_player].life_point << "/" << perso_group1_total_life_point[i_player] << "pv" << endl;
				cout << "vs" << endl;
				cout << Group2[i_player].name << ":" << Group2[i_player].life_point << "/" << perso_group2_total_life_point[i_player] << "pv" << endl;
				if (Group2[0].life_point<=0 and Group2[1].life_point<=0)
				{
					f_match_is_finished=true;
				}
				else if(Group2[i_player].life_point<=0)
				{
					if (i_player==0)
					{
						i_player=1;
					}
					else if (i_player==1)
					{
						i_player=0;
					}	
				}
				turn=2;
				break;
			
			case 2:
				Group2[i_player].attack(Group1[i_player].life_point, Group1[i_player].name);
				cout << Group1[i_player].name << ":" << Group1[i_player].life_point << "/" << perso_group1_total_life_point[i_player] << "pv" << endl;
				cout << "vs" << endl;
				cout << Group2[i_player].name << ":" << Group2[i_player].life_point << "/" << perso_group2_total_life_point[i_player] << "pv" << endl;
				if (Group1[0].life_point<=0 and Group1[1].life_point<=0)
				{
					f_match_is_finished=true;
				}
				else if(Group1[i_player].life_point<=0)
				{
					if (i_player==0)
					{
						i_player=1;
					}
					else if (i_player==1)
					{
						i_player=0;
					}	
				}
				turn=1;
				break;
		} 
				
	}while(!f_match_is_finished);
	
	cout << "Match terminé Victoire" << endl;
	return 0;
}
