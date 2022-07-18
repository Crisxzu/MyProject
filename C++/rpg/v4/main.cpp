#include <iostream>
#include "rpgclass.h"

using namespace std;

int main ()
{
	Perso *team1[NB_MAX_PERSO_PER_GROUP], *team2[NB_MAX_PERSO_PER_GROUP], *team3[NB_MAX_PERSO_PER_GROUP], *team4[NB_MAX_PERSO_PER_GROUP], *team5[NB_MAX_PERSO_PER_GROUP], *team6[NB_MAX_PERSO_PER_GROUP], *team7[NB_MAX_PERSO_PER_GROUP], *team8[NB_MAX_PERSO_PER_GROUP];
	NormalFactory normal_factory;
	BadassFactory badass_factory;
	WeakFactory weak_factory;
	MusclyFactory muscly_factory;
	ThinFactory thin_factory;
	BlessedFactory blessed_factory;
	
	team1[0]=createPerso(&badass_factory, Knight);
	team1[1]=createPerso(&weak_factory, Knight);
	team1[2]=createPerso(&muscly_factory, Knight);
	team1[3]=createPerso(&thin_factory, Knight);
	team1[4]=createPerso(&blessed_factory, Magus);
	
	team2[0]=createPerso(&normal_factory, Knight);
	team2[1]=createPerso(&normal_factory, Knight);
	team2[2]=createPerso(&normal_factory, Knight);
	team2[3]=createPerso(&normal_factory, Knight);
	team2[4]=createPerso(&normal_factory, Knight);
	
	team3[0]=createPerso(&normal_factory, Knight);
	team3[1]=createPerso(&normal_factory, Knight);
	team3[3]=createPerso(&normal_factory, Knight);
	team3[2]=createPerso(&normal_factory, Knight);
	team3[4]=createPerso(&normal_factory, Knight);
	
	team4[0]=createPerso(&normal_factory, Knight);
	team4[1]=createPerso(&normal_factory, Knight);
	team4[2]=createPerso(&normal_factory, Knight);
	team4[3]=createPerso(&normal_factory, Knight);
	team4[4]=createPerso(&normal_factory, Knight);
	
	team5[0]=createPerso(&normal_factory, Knight);
	team5[1]=createPerso(&normal_factory, Knight);
	team5[2]=createPerso(&normal_factory, Knight);
	team5[3]=createPerso(&normal_factory, Knight);
	team5[4]=createPerso(&normal_factory, Knight);
	
	team6[0]=createPerso(&normal_factory, Knight);
	team6[1]=createPerso(&normal_factory, Knight);
	team6[2]=createPerso(&normal_factory, Knight);
	team6[3]=createPerso(&normal_factory, Knight);
	team6[4]=createPerso(&normal_factory, Knight);
	
	team7[0]=createPerso(&normal_factory, Knight);
	team7[1]=createPerso(&normal_factory, Knight);
	team7[2]=createPerso(&normal_factory, Knight);
	team7[3]=createPerso(&normal_factory, Knight);
	team7[4]=createPerso(&normal_factory, Knight);
	
	team8[0]=createPerso(&normal_factory, Knight);
	team8[1]=createPerso(&normal_factory, Knight);
	team8[2]=createPerso(&normal_factory, Knight);
	team8[3]=createPerso(&normal_factory, Knight);
	team8[4]=createPerso(&normal_factory, Knight);
	
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
