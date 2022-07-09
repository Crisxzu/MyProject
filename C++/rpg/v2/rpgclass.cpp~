#include <iostream>
#include <ctime>
#include <string>
#include "rpgclass.h"



using	namespace std;

	/*Permet de construire notre personnage en initialisant chaque attributs.*/
Perso::Perso(const string& name, const string& attack_name, const int& life_point, const int& melee_attack_point) 
:	name(name),
	attack_name(attack_name),
	max_life_point(life_point),
	actual_life_point(life_point),
	melee_attack_point(melee_attack_point),
	pm_gain_per_turn(4)
{}

	/*Permet d'obtenir le nombre maximal de points de vie*/
int Perso::getMaxLifePoint() const
{
	return max_life_point;
}

	/*Permet d'obtenir le nombre actuel de points de vie*/
int Perso::getActualLifePoint() const
{
	return actual_life_point;
}

	/*Permet d'obtenir le nom du personnage*/
string Perso::getPersoName() const
{
	return name;
}

	/*Permet d'obtenir le nom de l'attaque du personnage*/
string Perso::getPersoAttackName() const
{
	return attack_name;
}

	/*Permet à notre personnage de recevoir un sort de soin*/
void Perso::takeHeal(const int& heal_magic_point)
{
	actual_life_point += heal_magic_point;

	//Si après soin, ses points de vie sont supérieurs au maximum fixé alors leur valeur sera égale à max_life_point
	if(actual_life_point>max_life_point)
	{
		actual_life_point=heal_magic_point;
	}
	
	cout << name << ": " << "gagne " << heal_magic_point << "points de vie !" << endl;
	cout << name << ": " << "PV: " << actual_life_point << "/" << max_life_point << endl;
}

	/*Permet de construire notre chevalier en initialisant ses attributs en tant que personnage et chevalier*/
Chevalier::Chevalier(const string& name, const string& attack_name, const int& life_point, const int& melee_attack_point, const int& defense_point)
:	
	Perso(name, attack_name, life_point, melee_attack_point),
	defense_point(defense_point)
{}

	/*Permet à notre chevalier d'effectuer une action.
	opponent_group = groupe adverse
	i_player = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void Chevalier::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
{
	//Le perso n'attaque son adversaire que si celui-ci est encore vivant
	if (opponent_group[i_player]->getActualLifePoint()>0)
	{
		cout << name << ": " << attack_name << " !" << endl;
		opponent_group[i_player]->takeDamage(melee_attack_point);	
	}	
}

	/*Permet à notre chevalier de subir des dégats*/
void Chevalier::takeDamage(const int& damage_point)
{
	//Le perso ne prend des dégats que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		//Si les points de dommages infligés sont supérieurs aux points de défense du chevalier alors 			celui-ci subit des dommages
		if(defense_point<damage_point)
		{
			actual_life_point = actual_life_point - (damage_point - defense_point);
			
			//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
			if(actual_life_point<0)
			{
				actual_life_point=0;
			}
			cout << name << " a perdu " << (damage_point - defense_point) << " points de vie !" << endl;
		}
		
		//Sinon, alors celui-ci ne subit aucun dommage
		else
		{
			cout << name << " n'a subi aucun point de dommages !" << endl;
		}	
	}
	
}

	/*Permet de construire notre mage en initialisant ses attributs en tant que personnage et mage*/
Mage::Mage(const string& name, const string& attack_name, const int& life_point, const int& magic_attack_point, const int& pm_point)
:	Perso(name, attack_name, life_point, magic_attack_point/10),
	max_pm(pm_point),
	actual_pm(pm_point),
	magic_attack_point(magic_attack_point),
	magic_attack_pm_cost(0.7*pm_point)		
{}

	/*Permet de regenerer les pm de notre mage*/
void Mage::pmRegeneration()
{
	//Les pm du perso ne se regenere que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		//Les pm d'un perso ne sont regénérés que si celui-ci a des pm inférieurs à son maximum de pm
		if (actual_pm<max_pm)
		{
			actual_pm += pm_gain_per_turn; 
		
			//Si après regeneration de pm, ceux-ci sont supérieurs au maximum de pm alors leur valeur sera égale à max_pm 
			if(actual_pm>max_pm)
			{
				actual_pm=max_pm;
			}

			cout << name << ": " << "gagne des pm !" << endl;
			cout << name << ": " << "PM: " << actual_pm << "/" << max_pm << endl;
		}	
	}	
}

	/*Permet à notre mage d'effectuer une action.
	opponent_group = groupe adverse
	i_player = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void Mage::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
{
	//Si les pm du mage sont suffisants pour effectuer une attaque magique, alors il l'a fait
	if(actual_pm>=magic_attack_pm_cost)
	{
		cout << name << ":" << attack_name << " !" << endl;
		actual_pm -= magic_attack_pm_cost;
		
		//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
		if(actual_pm<0)
		{
			actual_pm=0;
		}
		
		//L'attaque du mage atteint un à un chacun des persos du groupe adverse jusqu'à les avoir tous toucher
		for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
		{
			//Le perso n'attaque son adversaire que si celui-ci est encore vivant
			if (opponent_group[i]->getActualLifePoint()>0)
			{
				opponent_group[i]->takeDamage(magic_attack_point);	
			}
		}
			
	}
	
	//Sinon, alors il fait une attaque baton
	else
	{
		//Le perso n'attaque son adversaire que si celui-ci est encore vivant
		if (opponent_group[i_player]->getActualLifePoint()>0)
		{
			cout << name << ":" << "Attaque baton" << "!" << endl;
			opponent_group[i_player]->takeDamage(melee_attack_point);	
		}
	}
}

	/*Permet à notre mage de subir des dégats*/
void Mage::takeDamage(const int& damage_point)
{
	//Le perso ne prend des dégats que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		actual_life_point -= damage_point;
			
		//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
		if(actual_life_point<0)
		{
			actual_life_point=0;
		}
		cout << name << " a perdu " << damage_point << " points de vie !" << endl;
	}
}

	/*Permet de construire notre voleur en initialisant ses attributs en tant que personnage et voleur*/
Voleur::Voleur(const string& name, const string& attack_name, const int& life_point, const int& melee_attack_point)
:	Perso(name, attack_name, life_point, melee_attack_point),
	coef_dodge(0.2)
{}

	/*Permet à notre voleur d'effectuer une action.
	opponent_group = groupe adverse
	i_player = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void Voleur::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
{
	
	int val_min=999;
	int i_most_weak_perso=999;
	
	//Permet d'examiner les pv des persos du groupe adverse un à un jusqu'à les avoir tous examiner et de noter l'index de celui dont les pv sont les plus faibles
	for (unsigned int i_perso = 0; i_perso < nb_max_perso_per_group; i_perso += 1)
	{
		//Si les pv du perso sont inférieurs à la valeur minimale enregistré actuellement et supérieures à 0, on note son index et la valeur de ses pv en tant que nouvelle valeur minimale
		if (opponent_group[i_perso]->getActualLifePoint()<val_min and opponent_group[i_perso]->getActualLifePoint()>0)
		{
			val_min=opponent_group[i_perso]->getActualLifePoint();
			i_most_weak_perso=i_perso;
		}
	} 

	cout << name << ": " << attack_name << " !" << endl;
	cout << name << ": " << attack_name << " !" << endl;
	
	opponent_group[i_most_weak_perso]->takeDamage(melee_attack_point*2);
}

	/*Permet à notre voleur de subir des dégats*/
void Voleur::takeDamage(const int& damage_point)
{
	int max=100, min=0, random_nb=0;
	srand(time(NULL));
	
	//Le perso ne prend des dégats que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		random_nb=rand()%(max+1-min)+min;
		
		//Si le nombre aléatoire généré est supérieure au taux d'esquive, alors le voleur prend des 			dommages
		if(random_nb>coef_dodge*10)
		{
			actual_life_point -= damage_point;
			
			//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
			if(actual_life_point<0)
			{
				actual_life_point=0;
			}
			cout << name << " a perdu " << damage_point << " points de vie !" << endl;
		}
		
		//Sinon, le voleur ne prend aucun dommage
		else
		{
			cout << name << " a esquivé l'attaque !" << endl;
		}
	}
}

	/*Permet de construire notre prêtre en initialisant ses attributs en tant que personnage et prêtre*/
Pretre::Pretre(const string& name, const string& attack_name, const int& life_point, const int& heal_magic_point, const int& pm_point)
:	Perso(name, attack_name, life_point, 0),
	coef_pray(2),
	max_pm(pm_point),
	actual_pm(pm_point),
	heal_magic_point(heal_magic_point),
	heal_magic_pm_cost(0.5*pm_point)
{}

	/*Permet de regenerer les pm de notre prêtre*/
void Pretre::pmRegeneration()
{
	//Les pm ne se regenere que si le perso est encore vivant
	if (getActualLifePoint()>0)
	{
		//Les pm d'un perso ne sont regénérés que si celui-ci a des pm inférieurs à son maximum de pm
		if (actual_pm<max_pm)
		{
			actual_pm += pm_gain_per_turn; 
		
			//Si après regeneration de pm, ceux-ci sont supérieurs au maximum de pm alors leur valeur sera égale à max_pm 
			if(actual_pm>max_pm)
			{
				actual_pm=max_pm;
			}

			cout << name << ": " << "gagne des pm !" << endl;
			cout << name << ": " << "PM: " << actual_pm << "/" << max_pm << endl;
		}		
	}
}

	/*Permet à notre prêtre d'effectuer une action.
	ally_group = groupe allié
	i_player = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void Pretre::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
{
	int val_min=999;
	int i_most_weak_perso=999; 
	
	//Si les pm du prêtre sont suffisants pour effectuer une sort de soin, alors il le fait
	if(actual_pm>=heal_magic_pm_cost)
	{
		cout << name << ": " << attack_name << " !" << endl;
		actual_pm -= heal_magic_pm_cost;
		
		//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
		if(actual_pm<0)
		{
			actual_pm=0;
		}
		
		//Permet d'examiner les pv des persos du groupe allié un à un jusqu'à les avoir tous examiner 		et de noter l'index de celui dont les pv sont les plus faibles
		for (unsigned int i_perso = 0; i_perso < nb_max_perso_per_group; i_perso += 1)
		{
			//Si les pv du perso sont inférieurs à la valeur minimale enregistré actuellement et supérieursà 0, on note son index et la valeur de ses pv en tant que nouvelle valeur minimale
			if (ally_group[i_perso]->getActualLifePoint()<val_min && ally_group[i_perso]->getActualLifePoint()>0)
			{
				val_min=ally_group[i_perso]->getActualLifePoint();
				i_most_weak_perso=i_perso;
			}
		}
		ally_group[i_most_weak_perso]->takeHeal(heal_magic_point);	
	}
	
	//Sinon, alors il prie
	else
	{
		cout << name << ": " << "prie !" << endl;
		cout << name << ": " << "reçoit " << coef_pray << "plus de pm ce tour ci !" << endl;
		
		//Les pm d'un perso ne sont regénérés que si celui-ci a des pm inférieurs à son maximum de pm
		if (actual_pm<max_pm)
		{
			actual_pm += ((coef_pray-1) * pm_gain_per_turn); 

			//Si après regeneration de pm, ceux-ci sont supérieurs au maximum de pm alors leur valeur sera égale à max_pm 
			if(actual_pm>max_pm)
			{
				actual_pm=max_pm;
			}
		}

	}
}

	/*Permet à notre prêtre de subir des dégats*/
void Pretre::takeDamage(const int& damage_point)
{
	//Le perso ne prend des dégats que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		actual_life_point -= damage_point;
			
		//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
		if(actual_life_point<0)
		{
			actual_life_point=0;
		}
		cout << name << " a perdu " << damage_point << " points de vie !" << endl;
	}
}

	/*Permet de construire un combat en initialisant ses attributs*/
Combat::Combat()
:	round(0),
	turn(1),
	nb_max_perso_per_group(NB_MAX_PERSO_PER_GROUP),
	i_perso(0),
	group_winner(NULL),
	groupe1(NULL),
	groupe2(NULL)	
{}

	/*Permet de construire un combat en initialisant ses attributs*/
Combat::Combat(Perso **groupe1, Perso **groupe2)
:	round(0),
	turn(1),
	nb_max_perso_per_group(NB_MAX_PERSO_PER_GROUP),
	i_perso(0),
	group_winner(NULL),
	groupe1(groupe1),
	groupe2(groupe2)
{}

	/*Permet de savoir si tous les persos d'un des deux groupe sont morts*/
bool Combat::isOver()
{
	int i_group=1;
	bool f_all_perso_are_dead=true, f_can_pass_to_another_group=false;
	
	//Permet de passer à la vérification des pv des persos d'un autre groupe si celui vérifié précédemment n'a pas tous ses persos déjà morts
	do{
		f_all_perso_are_dead=true, f_can_pass_to_another_group=false;
		
		switch(i_group)
		{
			//Vérification des pv des persos du groupe 1
			case 1:
				
				//Permet de vérifier si chaque perso du groupe est vivant et n'arrêter de vérifier que si un perso est toujours vivant ou si les pv tous les persos du groupe ont été vérifiés
				for (unsigned int i = 0; i < nb_max_perso_per_group and f_all_perso_are_dead!=false; i += 1)
				{
					//Si un perso du groupe est en encore vivant
					if(groupe1[i]->getActualLifePoint()>0)
					{
						f_all_perso_are_dead=false;
					}
				}
				
				//Si tous les persos du groupe sont morts
				if(f_all_perso_are_dead)
				{
					group_winner=groupe2;
					cout << "Tous les persos du groupe 1 sont morts! Victoire du groupe 2 !" << endl;
					return true;
				}
				
				//Sinon, on passe à la vérification du prochain groupe
				else
				{
					f_can_pass_to_another_group=true;
					i_group++;
				}
				
				break;
			
			//Vérification des pv des persos du groupe 2
			case 2:
				//Permet de vérifier si chaque perso du groupe est vivant et n'arrêter de vérifier que si un perso est toujours vivant ou si les pv tous les persos du groupe ont été vérifiés
				for (unsigned int i = 0; i < nb_max_perso_per_group and f_all_perso_are_dead!=false; i += 1)
				{
					//Si un perso du groupe est en encore vivant
					if(groupe2[i]->getActualLifePoint()>0)
					{
						f_all_perso_are_dead=false;
					}
				}
				
				//Si tous les persos du groupe sont morts
				if(f_all_perso_are_dead)
				{
					group_winner=groupe1;
					cout << "Tous les persos du groupe 2 sont morts! Victoire du groupe 1 !" << endl;
					return true;
				}
				
				//Sinon, on passe à la vérification du prochain groupe
				else
				{
					f_can_pass_to_another_group=true;
					i_group++;
				}
				break;
				
			//Une fois la vérification terminé et si aucun des groupes n'a tous ses persos morts
			default:
				return false;
				break;
		}
	}while(f_can_pass_to_another_group);
	
	return false;
}

	/*Permet de lancer le prochain round dans lequel un perso d'un groupe va effectuer une action*/
void Combat::nextRound()
{
	
	//Pour ramener l'index du perso qui doit effectuer une action à 0 si celui-ci dépasse le nombre max de persos
	if(i_perso>=nb_max_perso_per_group)
	{
		i_perso=0;
	}
	
	switch(turn)
	{
		//Tour d'un perso du premier groupe d'effectuer une action
		case 1:
			
			if (groupe1[i_perso]->getActualLifePoint()>0)
			{
				round++;
				cout << "Round" << round << endl;
				cout << groupe1[i_perso]->getPersoName() << ":" << groupe1[i_perso]->getActualLifePoint() << "/" << groupe1[i_perso]->getMaxLifePoint() << "pv" << endl;
				cout << "vs" << endl;
				cout << groupe2[i_perso]->getPersoName() << ":" << groupe2[i_perso]->getActualLifePoint() << "/" << groupe2[i_perso]->getMaxLifePoint() << "pv" << endl;
				
				groupe1[i_perso]->action(groupe2, groupe1, i_perso, nb_max_perso_per_group);	
			}
			
			turn=2;
			break;
		
		//Tour d'un perso du deuxième groupe d'effectuer une action
		case 2:
			if (groupe2[i_perso]->getActualLifePoint()>0)
			{
				round++;
				cout << "Round" << round << endl;
				cout << groupe1[i_perso]->getPersoName() << ":" << groupe1[i_perso]->getActualLifePoint() << "/" << groupe1[i_perso]->getMaxLifePoint() << "pv" << endl;
				cout << "vs" << endl;
				cout << groupe2[i_perso]->getPersoName() << ":" << groupe2[i_perso]->getActualLifePoint() << "/" << groupe2[i_perso]->getMaxLifePoint() << "pv" << endl;
				
				groupe2[i_perso]->action(groupe1, groupe2, i_perso, nb_max_perso_per_group);	
			}
		
			i_perso++;
			turn=1;
			break;
	} 
}

	/*Permet d'obtenir le groupe gagnant du combat*/
Perso ** Combat::getGroupWinnner() const
{
	return group_winner;
}

	/*Permet d'obtenir le nombre max de persos par groupe*/
unsigned int Combat::getNbMaxPersoPerGroup() const
{
	return nb_max_perso_per_group;
}

	/*Permet d'enclencher un combat entre deux groupes*/
void Combat::fight()
{
	round=0, i_perso=0, turn=1;
	
	//Permet de continuer à lancer un round tant que tous les persos d'un groupe ne sont pas morts
	while (!isOver())
	{
		//Permet de régénerer les pm de chaque perso du groupe1 un à un jusqu'à l'avoir pour tous les perso
		for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
		{
			groupe1[i]->pmRegeneration();
		}
		
		//Permet de régénerer les pm de chaque perso du groupe2 un à un jusqu'à l'avoir pour tous les perso
		for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
		{
			groupe2[i]->pmRegeneration();
		}
		nextRound();
	}
}

	/*Permet de changer les groupes qui doivent combattre
	groupe 1 = Permier groupe de persos.
	groupe 2 = Deuxième groupe de persos.*/
void Combat::updateGroup(Perso **groupe1, Perso **groupe2)
{
	this->groupe1=groupe1;
	this->groupe2=groupe2;
}

	/*Permet d'insérer un chevalier dans un groupe*/
Chevalier * insertChevalier()
{
	Chevalier *chevalier=new Chevalier("Lancelot", "Epee Sainte", 400, 100, 40);
	
	return chevalier;
}

	/*Permet d'insérer un mage dans un groupe*/
Mage * insertMage()
{
	Mage *mage=new Mage("Merlin", "Feu tout puissant", 400, 200, 100);
	
	return mage;
}

	/*Permet d'insérer un voleur dans un groupe*/
Voleur *insertVoleur()
{
	Voleur *voleur=new Voleur("Pack", "Coup rapide", 400, 40);
	
	return voleur;
}

	/*Permet d'insérer un prêtre dans un groupe*/
Pretre *insertPretre()
{
	Pretre *pretre=new Pretre("Trust", "Soin", 400, 100, 100);
	
	return pretre;
}

	/*Permet de supprimer une équipe de persos.
	team = équipe de perso à supprimer.
	nb_max_perso_per_group = nombre max de persos par groupe*/
void deleteTeam(Perso ** team, const unsigned int& nb_max_perso_per_group)
{
	for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
	{
		free(team[i]), team[i]=NULL;
	}	
}

	/*Permet de construire un tournoi*/
Tournoi::Tournoi(Perso **team1, Perso **team2, Perso **team3, Perso **team4, Perso **team5, Perso **team6, Perso **team7, Perso **team8)
:	nb_fight_for_quarter_final(4),
	nb_fight_for_semifinal(2),
	nb_fight_for_final(1),
	combat()
{
	teams[0]=team1;
	teams[1]=team2;
	teams[2]=team3;
	teams[3]=team4;
	teams[4]=team5;
	teams[5]=team6;
	teams[6]=team7;
	teams[7]=team8;
}

	/*Permet de lancer les quarts de final*/
void Tournoi::quarterFinal()
{
	int i_winner_team=0;
	
	cout << "Quart de Finale" << endl;
	
	for (unsigned int i = 0; i < nb_fight_for_quarter_final*2; i += 2)
	{
		cout << "Match "<< i_winner_team << endl;
		combat.updateGroup(teams[i], teams[i+1]);
		
		combat.fight();
		
		teams[i_winner_team]=combat.getGroupWinnner();
		cout << "Fin du Match " << i_winner_team << endl;
		
		i_winner_team++;
	}
}

	/*Permet de lancer les demi-final*/
void Tournoi::semiFinal()
{
	int i_winner_team=0;
	
	cout << "Demi-Finale" << endl;
	
	for (unsigned int i = 0; i < nb_fight_for_semifinal*2; i += 2)
	{
		cout << "Match "<< i_winner_team << endl;
		combat.updateGroup(teams[i], teams[i+1]);
		
		combat.fight();
		
		teams[i_winner_team]=combat.getGroupWinnner();
		cout << "Fin du Match " << i_winner_team << endl;
		
		i_winner_team++;
	}
}
	
	/*Permet de lancer la finale*/
void Tournoi::finalMatch()
{
	
	cout << "Finale" << endl;
	
	for (unsigned int i = 0; i < nb_fight_for_final*2; i += 2)
	{
		cout << "Dernier Match" << endl;
		combat.updateGroup(teams[i], teams[i+1]);
		
		combat.fight();
		
		cout << "Fin du Match. Tournoi terminé !" << endl;
	}
}

	/*Permet de lancer le tournoi*/	
void Tournoi::launchTournament()
{
	quarterFinal();
	
	semiFinal();
	
	finalMatch();
}
