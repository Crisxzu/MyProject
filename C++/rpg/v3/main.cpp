#include <iostream>
#include "rpgclass.h"

using namespace std;

int main ()
{
	Perso *team1[NB_MAX_PERSO_PER_GROUP], *team2[NB_MAX_PERSO_PER_GROUP], *team3[NB_MAX_PERSO_PER_GROUP], *team4[NB_MAX_PERSO_PER_GROUP], *team5[NB_MAX_PERSO_PER_GROUP], *team6[NB_MAX_PERSO_PER_GROUP], *team7[NB_MAX_PERSO_PER_GROUP], *team8[NB_MAX_PERSO_PER_GROUP];
	
	team1[0]=createChevalierPretre();
	team1[1]=createChevalierPretre();
	team1[2]=createMagePretre();
	team1[3]=createChevalierVoleur();
	team1[4]=createChevalierPretre();
	
	team2[0]=createMage();
	team2[1]=createChevalier();
	team2[2]=createChevalier();
	team2[3]=createChevalier();
	team2[4]=createChevalier();
	
	team3[0]=createMage();
	team3[1]=createMage();
	team3[3]=createMage();
	team3[2]=createMage();
	team3[4]=createMage();
	
	team4[0]=createVoleur();
	team4[1]=createVoleur();
	team4[2]=createPretre();
	team4[3]=createPretre();
	team4[4]=createChevalier();
	
	team5[0]=createMage();
	team5[1]=createMage();
	team5[2]=createChevalier();
	team5[3]=createChevalier();
	team5[4]=createPretre();
	
	team6[0]=createVoleur();
	team6[1]=createVoleur();
	team6[2]=createVoleur();
	team6[3]=createVoleur();
	team6[4]=createVoleur();
	
	team7[0]=createPretre();
	team7[1]=createPretre();
	team7[2]=createPretre();
	team7[3]=createPretre();
	team7[4]=createPretre();
	
	team8[0]=createChevalier();
	team8[1]=createMage();
	team8[2]=createChevalier();
	team8[3]=createMage();
	team8[4]=createPretre();
	
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
