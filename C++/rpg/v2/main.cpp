#include <iostream>
#include "rpgclass.h"

using namespace std;

int main ()
{
	Perso *team1[NB_MAX_PERSO_PER_GROUP], *team2[NB_MAX_PERSO_PER_GROUP], *team3[NB_MAX_PERSO_PER_GROUP], *team4[NB_MAX_PERSO_PER_GROUP], *team5[NB_MAX_PERSO_PER_GROUP], *team6[NB_MAX_PERSO_PER_GROUP], *team7[NB_MAX_PERSO_PER_GROUP], *team8[NB_MAX_PERSO_PER_GROUP];
	
	team1[0]=insertChevalier();
	team1[1]=insertChevalier();
	team1[2]=insertVoleur();
	team1[3]=insertPretre();
	team1[4]=insertMage();
	
	team2[0]=insertChevalier();
	team2[1]=insertChevalier();
	team2[2]=insertChevalier();
	team2[3]=insertChevalier();
	team2[4]=insertChevalier();
	
	team3[0]=insertMage();
	team3[1]=insertMage();
	team3[3]=insertMage();
	team3[2]=insertMage();
	team3[4]=insertMage();
	
	team4[0]=insertVoleur();
	team4[1]=insertVoleur();
	team4[2]=insertPretre();
	team4[3]=insertPretre();
	team4[4]=insertChevalier();
	
	team5[0]=insertMage();
	team5[1]=insertMage();
	team5[2]=insertChevalier();
	team5[3]=insertChevalier();
	team5[4]=insertPretre();
	
	team6[0]=insertVoleur();
	team6[1]=insertVoleur();
	team6[2]=insertVoleur();
	team6[3]=insertVoleur();
	team6[4]=insertVoleur();
	
	team7[0]=insertPretre();
	team7[1]=insertPretre();
	team7[2]=insertPretre();
	team7[3]=insertPretre();
	team7[4]=insertPretre();
	
	team8[0]=insertChevalier();
	team8[1]=insertMage();
	team8[2]=insertChevalier();
	team8[3]=insertMage();
	team8[4]=insertPretre();
	
	Tournoi tournoi(team1, team2, team3, team4, team5, team6, team7, team8);
	
	tournoi.launchTournament();
	
	deleteTeam(team1, NB_MAX_PERSO_PER_GROUP);
	deleteTeam(team2, NB_MAX_PERSO_PER_GROUP);
	deleteTeam(team3, NB_MAX_PERSO_PER_GROUP);
	deleteTeam(team4, NB_MAX_PERSO_PER_GROUP);
	deleteTeam(team5, NB_MAX_PERSO_PER_GROUP);
	deleteTeam(team6, NB_MAX_PERSO_PER_GROUP);
	deleteTeam(team7, NB_MAX_PERSO_PER_GROUP);
	deleteTeam(team8, NB_MAX_PERSO_PER_GROUP);
	
	return 0;
}
