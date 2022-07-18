#include <iostream>
#include <ctime>
#include <string>
#include "rpgclass.h"



using	namespace std;

	/*Permet de construire notre personnage en initialisant chaque attributs.*/
Perso::Perso(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const PersoTrait& trait) 
:	name(name),
	attack_name(attack_name),
	max_life_point(life_point),
	actual_life_point(life_point),
	melee_attack_point(melee_attack_point),
	pm_gain_per_turn(2),
	trait(trait)
{
	applyEffectOfTrait();
}

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
		actual_life_point=max_life_point;
	}
	
	cout << name << ": " << "gagne " << heal_magic_point << "points de vie !" << endl;
	cout << name << ": " << "PV: " << actual_life_point << "/" << max_life_point << endl;
}

	/*Permet d'appliquer les effets du trait d'un personnage*/
void Perso::applyEffectOfTrait()
{
	switch(trait)
	{
		case Normal:
			max_life_point *=1;
			actual_life_point *=1;
			melee_attack_point *=1;
			pm_gain_per_turn *=1;
			break;
			
		case Badass:
			max_life_point *=1.25;
			actual_life_point *=1.25;
			break;
			
		case Weak:
			max_life_point *=0.75;
			actual_life_point *=0.75;
			break;
			
		case Muscly:
			melee_attack_point *=1.25;
			break;
			
		case Thin:
			melee_attack_point *=0.75;
			break;
		
		case Blessed:
			pm_gain_per_turn *=2;
			break;
	}
}
	/*Permet de construire notre chevalier en initialisant ses attributs en tant que personnage et chevalier*/
Chevalier::Chevalier(const string& name, const string& attack_name, const int& life_point, const int& melee_attack_point, const int& defense_point, const PersoTrait& trait)
:	
	Perso(name, attack_name, life_point, melee_attack_point, trait),
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
Mage::Mage(const string& name, const string& attack_name, const int& life_point, const int& magic_attack_point, const int& pm_point, const PersoTrait& trait)
:	Perso(name, attack_name, life_point, magic_attack_point/4, trait),
	max_pm(pm_point),
	actual_pm(pm_point),
	magic_attack_point(magic_attack_point),
	magic_attack_pm_cost(0.35*pm_point)		
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
Voleur::Voleur(const string& name, const string& attack_name, const int& life_point, const int& melee_attack_point, const PersoTrait& trait)
:	Perso(name, attack_name, life_point, melee_attack_point, trait),
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
Pretre::Pretre(const string& name, const string& attack_name, const int& life_point, const int& heal_magic_point, const int& pm_point, const PersoTrait& trait)
:	Perso(name, attack_name, life_point, 0, trait),
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
		//Les pm d'un perso ne sont regénérés que si celui-ci a des pm inférieurs à son maximum de pm
		if (actual_pm<max_pm)
		{
			cout << name << ": " << "prie !" << endl;
			cout << name << ": " << "reçoit " << coef_pray << "plus de pm ce tour ci !" << endl;
		
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

	/*Permet de construire notre chevalier mage en initialisant ses attributs en tant que chevalier et mage*/
ChevalierMage::ChevalierMage(const string& name, const std::string& attack_name, const int& life_point, const int& magic_attack_point, const int& pm_point, const int& defense_point, const PersoTrait& trait)
:	Perso(name, attack_name, life_point, magic_attack_point/2, trait),
	Chevalier(name, attack_name, life_point, magic_attack_point/2, defense_point, trait),
	Mage(name, attack_name, life_point, magic_attack_point, pm_point, trait)
{}

	/*Permet de regenerer les pm de notre chevalier mage*/
void ChevalierMage::pmRegeneration()
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

	/*Permet à notre chevalier mage d'effectuer une action.
	opponent_group = groupe adverse
	i_perso = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void ChevalierMage::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
{
	//Si les pm du chevalier mage sont suffisants pour effectuer une attaque magique, alors il l'a fait
	if(actual_pm>=magic_attack_pm_cost*2)
	{
		cout << name << ":" << attack_name << " !" << endl;
		actual_pm -= (magic_attack_pm_cost*2);
		
		//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
		if(actual_pm<0)
		{
			actual_pm=0;
		}
		
		//L'attaque du chevalier mage atteint un à un chacun des persos du groupe adverse jusqu'à les avoir tous toucher
		for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
		{
			//Le perso n'attaque son adversaire que si celui-ci est encore vivant
			if (opponent_group[i]->getActualLifePoint()>0)
			{
				opponent_group[i]->takeDamage(magic_attack_point);	
			}
		}
			
	}
	
	//Sinon, alors il fait une attaque avec son épée
	else
	{
		//Le perso n'attaque son adversaire que si celui-ci est encore vivant
		if (opponent_group[i_player]->getActualLifePoint()>0)
		{
			cout << name << ":" << "Coup d'épée" << "!" << endl;
			opponent_group[i_player]->takeDamage(melee_attack_point);	
		}
	}
}

	/*Permet à notre chevalier mage de subir des dégats*/
void ChevalierMage::takeDamage(const int& damage_point)
{
	//Le perso ne prend des dégats que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		//Si les points de dommages infligés sont supérieurs aux points de défense du chevalier mage alors celui-ci subit des dommages
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

	/*Permet de construire notre mage voleur en initialisant ses attributs en tant que mage et voleur*/
MageVoleur::MageVoleur(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& magic_attack_point, const int& pm_point, const PersoTrait& trait)
:	Perso(name, attack_name, life_point, melee_attack_point, trait),
	Mage(name, attack_name, life_point, magic_attack_point, pm_point, trait),
	Voleur(name, attack_name, life_point, melee_attack_point, trait)
{}

	/*Permet de regenerer les pm de notre mage voleur*/
void MageVoleur::pmRegeneration()
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

	/*Permet à notre mage voleur d'effectuer une action.
	opponent_group = groupe adverse
	i_perso = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void MageVoleur::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
{
	int val_min=999;
	int i_most_weak_perso=999;
	
	//Si les pm du mage voleur sont suffisants pour effectuer une attaque magique, alors il l'a fait
	if(actual_pm>=magic_attack_pm_cost)
	{
		cout << name << ":" << attack_name << " !" << endl;
		actual_pm -= magic_attack_pm_cost;
		
		//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
		if(actual_pm<0)
		{
			actual_pm=0;
		}
		
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
		
		opponent_group[i_most_weak_perso]->takeDamage(magic_attack_point*2);
	}
	
	//Sinon, alors il fait une attaque rapide
	else
	{
		//Le perso n'attaque son adversaire que si celui-ci est encore vivant
		if (opponent_group[i_player]->getActualLifePoint()>0)
		{
			cout << name << ": " << "Coup rapide " << "!" << endl;
			opponent_group[i_player]->takeDamage(melee_attack_point);	
		}
	}
}

	/*Permet à notre mage voleur de subir des dégats*/
void MageVoleur::takeDamage(const int& damage_point)
{
	int max=100, min=0, random_nb=0;
	srand(time(NULL));
	
	//Le perso ne prend des dégats que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		random_nb=rand()%(max+1-min)+min;
		
		//Si le nombre aléatoire généré est supérieure au taux d'esquive, alors le voleur prend des dommages
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
		
		//Sinon, le mage voleur ne prend aucun dommage
		else
		{
			cout << name << " a esquivé l'attaque !" << endl;
		}
	}
}

	/*Permet de construire notre mage pretre en initialisant ses attributs en tant que mage et pretre.*/
MagePretre::MagePretre(const std::string& name, const std::string& attack_name, const int& life_point, const int& magic_attack_point, const int& pm_point, const PersoTrait& trait)
:	Perso(name, attack_name, life_point, 0, trait),
	Mage(name, attack_name, life_point, magic_attack_point, pm_point, trait),
	Pretre(name, attack_name, life_point, 0, pm_point, trait),
	max_pm(pm_point),
	actual_pm(pm_point)
{}

	/*Permet de regenerer les pm de notre mage voleur*/
void MagePretre::pmRegeneration()
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

	/*Permet à notre mage pretre d'effectuer une action.
	opponent_group = groupe adverse
	i_perso = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void MagePretre::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
{
	//Si les pm du mage pretre sont suffisants pour effectuer une attaque magique, alors il l'a fait
	if(actual_pm>=magic_attack_pm_cost)
	{
		cout << name << ":" << attack_name << " !" << endl;
		actual_pm -= magic_attack_pm_cost;
		
		//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
		if(actual_pm<0)
		{
			actual_pm=0;
		}
		
		//L'attaque du mage pretre atteint un à un chacun des persos du groupe adverse jusqu'à les avoir tous toucher
		for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
		{
			//Le perso n'attaque son adversaire que si celui-ci est encore vivant
			if (opponent_group[i]->getActualLifePoint()>0)
			{
				opponent_group[i]->takeDamage(magic_attack_point*0.8);	
			}
		}
			
	}
	
	//Sinon, alors il prie
	else
	{		
		//Les pm d'un perso ne sont regénérés que si celui-ci a des pm inférieurs à son maximum de pm
		if (actual_pm<max_pm)
		{
			cout << name << ": " << "prie !" << endl;
			cout << name << ": " << "reçoit " << coef_pray << "plus de pm ce tour ci !" << endl;
			
			actual_pm += ((coef_pray-1) * pm_gain_per_turn); 

			//Si après regeneration de pm, ceux-ci sont supérieurs au maximum de pm alors leur valeur sera égale à max_pm 
			if(actual_pm>max_pm)
			{
				actual_pm=max_pm;
			}
		
		}

	}
}

	/*Permet à notre mage pretre de subir des dégats*/
void MagePretre::takeDamage(const int& damage_point)
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

	/*Permet de construire notre chevalier voleur en initialisant ses attributs en tant que chevalier et voleur*/
ChevalierVoleur::ChevalierVoleur(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& defense_point, const PersoTrait& trait)
:	Perso(name, attack_name, life_point, melee_attack_point, trait),
	Chevalier(name, attack_name, life_point, melee_attack_point, defense_point*0.5, trait),
	Voleur(name, attack_name, life_point, melee_attack_point, trait)
{}

	/*Permet à notre chevalier voleur d'effectuer une action.
	opponent_group = groupe adverse
	i_perso = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void ChevalierVoleur::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
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
	
	opponent_group[i_most_weak_perso]->takeDamage(melee_attack_point);
}

	/*Permet à notre chevalier voleur de subir des dégats*/
void ChevalierVoleur::takeDamage(const int& damage_point)
{
	int max=100, min=0, random_nb=0;
	srand(time(NULL));
	
	//Le perso ne prend des dégats que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		random_nb=rand()%(max+1-min)+min;
		
		//Si le nombre aléatoire généré est supérieure au taux d'esquive, alors le chevalier voleur subit l'attaque
		if(random_nb>(coef_dodge*0.5)*10)
		{
			//Si les points de dommages infligés sont supérieurs aux points de défense du chevalier voleur alors celui-ci subit des dommages
			if(defense_point<damage_point)
			{
				actual_life_point = actual_life_point - (damage_point - (defense_point));
				
				//Si les points restants sont inférieurs à 0, alors ceux-ci seront remis à 0
				if(actual_life_point<0)
				{
					actual_life_point=0;
				}
				cout << name << " a perdu " << (damage_point - (defense_point)) << " points de vie !" << endl;
			}
			
			//Sinon, alors celui-ci ne subit aucun dommage
			else
			{
				cout << name << " n'a subi aucun point de dommages !" << endl;
			}
		}
		
		//Sinon, alors celui-ci l'esquive
		else
		{
			cout << name << " a esquivé l'attaque !" << endl;
		}
	}
}

	/*Permet de construire notre voleur pretre en initialisant ses attributs en tant que voleur et pretre*/
VoleurPretre::VoleurPretre(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& heal_magic_point, const int& pm_point, const PersoTrait& trait)
:	Perso(name, attack_name, life_point, melee_attack_point, trait),
	Voleur(name, attack_name, life_point, melee_attack_point, trait),
	Pretre(name, attack_name, life_point, heal_magic_point, pm_point, trait),
	f_can_use_heal_ability(true),
	max_ability_use_per_combat(1),
	actual_ability_use(0)
{}

	/*Permet de reinitialiser la capacité à utiliser des abilités après chaque combat*/
void VoleurPretre::resetPerCombatAbility()
{
	actual_ability_use=0;
	f_can_use_heal_ability=true;
}

	/*Permet à notre voleur pretre d'effectuer une action.
	opponent_group = groupe adverse
	i_perso = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void VoleurPretre::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
{
	int val_min=999;
	int i_most_weak_perso=999;
	
	//Si le voleur pretre a été touché et qu'il peut utiliser son abilité à se soigner, il se soigne
	if (actual_life_point<max_life_point and f_can_use_heal_ability==true)
	{
		cout << name << ": " << "Soin du voleur " << "!" << endl;
		
		takeHeal(heal_magic_point);
		actual_ability_use++;
		
		//Si le perso a dépassé le nombre max d'usage de son abilité alors il ne peut plus l'utiliser
		if (actual_ability_use>=max_ability_use_per_combat)
		{
			f_can_use_heal_ability=false;
		}
	}
	
	//Sinon il attaque
	else
	{
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
}

	/*Permet à notre voleur pretre de subir des dégats*/
void VoleurPretre::takeDamage(const int& damage_point)
{
	int max=100, min=0, random_nb=0;
	srand(time(NULL));
	
	//Le perso ne prend des dégats que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		random_nb=rand()%(max+1-min)+min;
		
		//Si le nombre aléatoire généré est supérieure au taux d'esquive, alors le voleur pretre prend des dommages
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
		
		//Sinon, le voleur pretre ne prend aucun dommage
		else
		{
			cout << name << " a esquivé l'attaque !" << endl;
		}
	}
}

	/*Permet de construire notre chevalier pretre en initialisant en tant que chevalier et pretre*/
ChevalierPretre::ChevalierPretre(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& heal_magic_point, const int& pm_point, const int& defense_point, const PersoTrait& trait)
:	Perso(name, attack_name, life_point, melee_attack_point, trait),
	Chevalier(name, attack_name, life_point, melee_attack_point, defense_point, trait),
	Pretre(name, attack_name, life_point, heal_magic_point*2, pm_point, trait),
	f_can_use_heal_ability(true),
	max_ability_use_per_combat(1),
	actual_ability_use(0)
{}

	/*Permet de savoir si un perso allié est en danger en retournant true si oui ou false si non
	ally_group = groupe allié
	nb_max_perso_per_group = nombre max de persos par groupe
	i_player_in_danger = index du perso en danger*/
bool ChevalierPretre::isAllyPlayerInDanger(Perso **ally_group, const unsigned int& nb_max_perso_per_group, int& i_player_in_danger)
{
	//Permet de vérifier les pv de chaque perso allié un à un jusqu'à l'avoir fait pour tous les perso
	for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
	{
		//Si les pv d'un perso allié sont inférieurs ou égale à 50% de sa valeur max alors on note l'index de celui-ci
		if (ally_group[i]->getActualLifePoint()<=(0.5*ally_group[i]->getMaxLifePoint()))
		{
			i_player_in_danger=i;
			return true;
		}
	}
	
	return false;
}

	/*Permet de reinitialiser la capacité à utiliser des abilités après chaque combat*/
void ChevalierPretre::resetPerCombatAbility()
{
	actual_ability_use=0;
	f_can_use_heal_ability=true;	
}

	/*Permet à notre voleur pretre d'effectuer une action.
	opponent_group = groupe adverse
	i_perso = int, index du perso ciblé par l'action
	nb_max_perso_per_group= int, nombre max de persos par groupe*/
void ChevalierPretre::action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
{
	int i_player_in_danger=0;
	
	//Si un des persos alliés est en danger et que le chevalier prêtre peut utiliser son abilité à soigner, il se soigne
	if (isAllyPlayerInDanger(ally_group, nb_max_perso_per_group, i_player_in_danger)==true and f_can_use_heal_ability==true)
	{
		cout << name << ": " << "Soin du Chevalier Pretre " << "!" << endl;
		
		ally_group[i_player_in_danger]->takeHeal(heal_magic_point);
		actual_ability_use++;
		
		//Si le perso a dépassé le nombre max d'usage de son abilité alors il ne peut plus l'utiliser
		if (actual_ability_use>=max_ability_use_per_combat)
		{
			f_can_use_heal_ability=false;
		}
	}
	
	//Sinon, alors il attaque
	else
	{
		//Le perso n'attaque son adversaire que si celui-ci est encore vivant
		if (opponent_group[i_player]->getActualLifePoint()>0)
		{
			cout << name << ": " << attack_name << "!" << endl;
			opponent_group[i_player]->takeDamage(melee_attack_point);	
		}
	}
}

	/*Permet à notre chevalier pretre de subir des dégats*/
void ChevalierPretre::takeDamage(const int& damage_point)
{
	//Le perso ne prend des dégats que si celui-ci est encore vivant
	if (getActualLifePoint()>0)
	{
		//Si les points de dommages infligés sont supérieurs aux points de défense du chevalier pretre alors celui-ci subit des dommages
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
			
			//Le perso désigné ne fait une action que s'il est encore vivant
			if (groupe1[i_perso]->getActualLifePoint()>0)
			{
				round++;
				i_frontliner=getFrontLiner(groupe2);
				
				cout << "Round " << round << endl;
				allGroupPmRegeneration();
				
				cout << "(Groupe 1) " << groupe1[i_perso]->getPersoName() << ": " << groupe1[i_perso]->getActualLifePoint() << "/" << groupe1[i_perso]->getMaxLifePoint() << " pv" << endl;
				cout << "vs" << endl;
				cout << "(Groupe 2) " << groupe2[i_frontliner]->getPersoName() << ": " << groupe2[i_frontliner]->getActualLifePoint() << "/" << groupe2[i_frontliner]->getMaxLifePoint() << " pv" << endl;
				
				groupe1[i_perso]->action(groupe2, groupe1, i_frontliner, nb_max_perso_per_group);	
			}
			
			turn=2;
			break;
		
		//Tour d'un perso du deuxième groupe d'effectuer une action
		case 2:
			
			//Le perso désigné ne fait une action que s'il est encore vivant
			if (groupe2[i_perso]->getActualLifePoint()>0)
			{
				round++;
				i_frontliner=getFrontLiner(groupe1);
				
				cout << "Round " << round << endl;
				allGroupPmRegeneration();
				
				cout << "(Groupe 2) " << groupe2[i_perso]->getPersoName() << ": " << groupe2[i_perso]->getActualLifePoint() << "/" << groupe2[i_perso]->getMaxLifePoint() << " pv" << endl;
				cout << "vs" << endl;
				cout << "(Groupe 1) " << groupe1[i_frontliner]->getPersoName() << ": " << groupe1[i_frontliner]->getActualLifePoint() << "/" << groupe1[i_frontliner]->getMaxLifePoint() << " pv" << endl;
				
				groupe2[i_perso]->action(groupe1, groupe2, i_frontliner, nb_max_perso_per_group);	
			}
		
			i_perso++;
			turn=1;
			break;
	} 
}

	/*Permet d'obtenir l'index du personnage qui est en avant*/
int Combat::getFrontLiner(Perso **group)
{
	unsigned int i_frontliner=0;
	
	//Permet d'obtenir l'index du premier perso vivant du groupe et le boucle est gardé jusqu'à trouver le premier jouer vivant ou que le nombre max de perso soit dépassé
	for (;group[i_frontliner]->getActualLifePoint() == 0 && i_frontliner<nb_max_perso_per_group; i_frontliner += 1);
	
	return i_frontliner;
}

	/*Permet de regenerer les pm de tous les persos de chaque groupe*/
void Combat::allGroupPmRegeneration()
{
	//Permet de régénerer les pm de chaque perso du groupe1 un à un jusqu'à l'avoir fait pour tous les perso
	for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
	{
		groupe1[i]->pmRegeneration();
	}
	
	//Permet de régénerer les pm de chaque perso du groupe2 un à un jusqu'à l'avoir fait pour tous les perso
	for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
	{
		groupe2[i]->pmRegeneration();
	}	
}

	/*Permet de reinitialiser la capacité à utiliser des abilités de tous les persos de chaque groupe*/
void Combat::allGroupResetPerCombatAbility()
{
	//Permet de réintialiser la capacité à utiliser des abilités de chaque perso du groupe1 un à un jusqu'à l'avoir fait pour tous les perso
	for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
	{
		groupe1[i]->resetPerCombatAbility();
	}
	
	//Permet de réintialiser la capacité à utiliser des abilités de chaque perso du groupe2 un à un jusqu'à l'avoir fait pour tous les perso
	for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
	{
		groupe2[i]->resetPerCombatAbility();
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
	
	allGroupResetPerCombatAbility();
	
	//Permet de continuer à lancer un round tant que tous les persos d'un groupe ne sont pas morts
	while (!isOver())
	{
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

	/*Permet de créer un chevalier et de le renvoyer*/
Chevalier *NormalFactory::createChevalier() const
{
	Chevalier *chevalier=new Chevalier("Lancelot", "Epee Sainte", 400, 100, 40, Normal);
	
	return chevalier;
}

	/*Permet de créer un mage et de le renvoyer*/
Mage *NormalFactory::createMage() const
{
	Mage *mage=new Mage("Merlin", "Feu tout puissant", 400, 80, 100, Normal);
	
	return mage;
}

	/*Permet de créer un voleur et de le renvoyer*/
Voleur *NormalFactory::createVoleur() const
{
	Voleur *voleur=new Voleur("Pack", "Coup rapide", 400, 40, Normal);
	
	return voleur;
}

	/*Permet de créer un prêtre et de le renvoyer*/
Pretre *NormalFactory::createPretre() const
{
	Pretre *pretre=new Pretre("Trust", "Soin", 400, 100, 100, Normal);
	
	return pretre;
}

	/*Permet de créer un chevalier mage et de le renvoyer*/
ChevalierMage *NormalFactory::createChevalierMage() const
{
	ChevalierMage *chevaliermage=new ChevalierMage("Lancelin", "Feu tout puissant du chevalier", 400, 80, 100, 40, Normal);
	
	return chevaliermage;
}

	/*Permet de créer un mage voleur et de le renvoyer*/
MageVoleur *NormalFactory::createMageVoleur() const
{
	MageVoleur *magevoleur=new MageVoleur("Merlack", "Feu tout puissant du voleur", 400, 40, 80, 100, Normal);
	
	return magevoleur;
}

	/*Permet de créer un mage pretre et de le renvoyer*/
MagePretre *NormalFactory::createMagePretre() const
{
	MagePretre *magepretre=new MagePretre("Merlust", "Feu tout puissant du pretre", 400, 80, 100, Normal);
	
	return magepretre;
}

	/*Permet de créer un chevalier voleur et de le renvoyer*/
ChevalierVoleur *NormalFactory::createChevalierVoleur() const
{
	ChevalierVoleur *chevaliervoleur=new ChevalierVoleur("Lancelack", "Coup d'épée", 400, 100, 40, Normal);
	
	return chevaliervoleur;
}

	/*Permet de créer un voleur pretre et de le renvoyer*/
VoleurPretre *NormalFactory::createVoleurPretre() const
{
	VoleurPretre *voleurpretre=new VoleurPretre("Pacrust", "Coup rapide", 400, 40, 100, 100, Normal);
	
	return voleurpretre;
}

	/*Permet de créer un chevalier pretre et de le renvoyer*/
ChevalierPretre *NormalFactory::createChevalierPretre() const
{
	ChevalierPretre *chevalierpretre= new ChevalierPretre("Lancelust", "Epee sainte", 400, 100, 100, 100, 40, Normal);
	
	return chevalierpretre;
}

	/*Permet de créer un chevalier et de le renvoyer*/
Chevalier *BadassFactory::createChevalier() const
{
	Chevalier *chevalier=new Chevalier("Lancelot", "Epee Sainte", 400, 100, 40, Badass);
	
	return chevalier;
}

	/*Permet de créer un mage et de le renvoyer*/
Mage *BadassFactory::createMage() const
{
	Mage *mage=new Mage("Merlin", "Feu tout puissant", 400, 80, 100, Badass);
	
	return mage;
}

	/*Permet de créer un voleur et de le renvoyer*/
Voleur *BadassFactory::createVoleur() const
{
	Voleur *voleur=new Voleur("Pack", "Coup rapide", 400, 40, Badass);
	
	return voleur;
}

	/*Permet de créer un prêtre et de le renvoyer*/
Pretre *BadassFactory::createPretre() const
{
	Pretre *pretre=new Pretre("Trust", "Soin", 400, 100, 100, Badass);
	
	return pretre;
}

	/*Permet de créer un chevalier mage et de le renvoyer*/
ChevalierMage *BadassFactory::createChevalierMage() const
{
	ChevalierMage *chevaliermage=new ChevalierMage("Lancelin", "Feu tout puissant du chevalier", 400, 80, 100, 40, Badass);
	
	return chevaliermage;
}

	/*Permet de créer un mage voleur et de le renvoyer*/
MageVoleur *BadassFactory::createMageVoleur() const
{
	MageVoleur *magevoleur=new MageVoleur("Merlack", "Feu tout puissant du voleur", 400, 40, 80, 100, Badass);
	
	return magevoleur;
}

	/*Permet de créer un mage pretre et de le renvoyer*/
MagePretre *BadassFactory::createMagePretre() const
{
	MagePretre *magepretre=new MagePretre("Merlust", "Feu tout puissant du pretre", 400, 80, 100, Badass);
	
	return magepretre;
}

	/*Permet de créer un chevalier voleur et de le renvoyer*/
ChevalierVoleur *BadassFactory::createChevalierVoleur() const
{
	ChevalierVoleur *chevaliervoleur=new ChevalierVoleur("Lancelack", "Coup d'épée", 400, 100, 40, Badass);
	
	return chevaliervoleur;
}

	/*Permet de créer un voleur pretre et de le renvoyer*/
VoleurPretre *BadassFactory::createVoleurPretre() const
{
	VoleurPretre *voleurpretre=new VoleurPretre("Pacrust", "Coup rapide", 400, 40, 100, 100, Badass);
	
	return voleurpretre;
}

	/*Permet de créer un chevalier pretre et de le renvoyer*/
ChevalierPretre *BadassFactory::createChevalierPretre() const
{
	ChevalierPretre *chevalierpretre= new ChevalierPretre("Lancelust", "Epee sainte", 400, 100, 100, 100, 40, Badass);
	
	return chevalierpretre;
}

	/*Permet de créer un chevalier et de le renvoyer*/
Chevalier *WeakFactory::createChevalier() const
{
	Chevalier *chevalier=new Chevalier("Lancelot", "Epee Sainte", 400, 100, 40, Weak);
	
	return chevalier;
}

	/*Permet de créer un mage et de le renvoyer*/
Mage *WeakFactory::createMage() const
{
	Mage *mage=new Mage("Merlin", "Feu tout puissant", 400, 80, 100, Weak);
	
	return mage;
}

	/*Permet de créer un voleur et de le renvoyer*/
Voleur *WeakFactory::createVoleur() const
{
	Voleur *voleur=new Voleur("Pack", "Coup rapide", 400, 40, Weak);
	
	return voleur;
}

	/*Permet de créer un prêtre et de le renvoyer*/
Pretre *WeakFactory::createPretre() const
{
	Pretre *pretre=new Pretre("Trust", "Soin", 400, 100, 100, Weak);
	
	return pretre;
}

	/*Permet de créer un chevalier mage et de le renvoyer*/
ChevalierMage *WeakFactory::createChevalierMage() const
{
	ChevalierMage *chevaliermage=new ChevalierMage("Lancelin", "Feu tout puissant du chevalier", 400, 80, 100, 40, Weak);
	
	return chevaliermage;
}

	/*Permet de créer un mage voleur et de le renvoyer*/
MageVoleur *WeakFactory::createMageVoleur() const
{
	MageVoleur *magevoleur=new MageVoleur("Merlack", "Feu tout puissant du voleur", 400, 40, 80, 100, Weak);
	
	return magevoleur;
}

	/*Permet de créer un mage pretre et de le renvoyer*/
MagePretre *WeakFactory::createMagePretre() const
{
	MagePretre *magepretre=new MagePretre("Merlust", "Feu tout puissant du pretre", 400, 80, 100, Weak);
	
	return magepretre;
}

	/*Permet de créer un chevalier voleur et de le renvoyer*/
ChevalierVoleur *WeakFactory::createChevalierVoleur() const
{
	ChevalierVoleur *chevaliervoleur=new ChevalierVoleur("Lancelack", "Coup d'épée", 400, 100, 40, Weak);
	
	return chevaliervoleur;
}

	/*Permet de créer un voleur pretre et de le renvoyer*/
VoleurPretre *WeakFactory::createVoleurPretre() const
{
	VoleurPretre *voleurpretre=new VoleurPretre("Pacrust", "Coup rapide", 400, 40, 100, 100, Weak);
	
	return voleurpretre;
}

	/*Permet de créer un chevalier pretre et de le renvoyer*/
ChevalierPretre *WeakFactory::createChevalierPretre() const
{
	ChevalierPretre *chevalierpretre= new ChevalierPretre("Lancelust", "Epee sainte", 400, 100, 100, 100, 40, Weak);
	
	return chevalierpretre;
}

	/*Permet de créer un chevalier et de le renvoyer*/
Chevalier *MusclyFactory::createChevalier() const
{
	Chevalier *chevalier=new Chevalier("Lancelot", "Epee Sainte", 400, 100, 40, Muscly);
	
	return chevalier;
}

	/*Permet de créer un mage et de le renvoyer*/
Mage *MusclyFactory::createMage() const
{
	Mage *mage=new Mage("Merlin", "Feu tout puissant", 400, 80, 100, Muscly);
	
	return mage;
}

	/*Permet de créer un voleur et de le renvoyer*/
Voleur *MusclyFactory::createVoleur() const
{
	Voleur *voleur=new Voleur("Pack", "Coup rapide", 400, 40, Muscly);
	
	return voleur;
}

	/*Permet de créer un prêtre et de le renvoyer*/
Pretre *MusclyFactory::createPretre() const
{
	Pretre *pretre=new Pretre("Trust", "Soin", 400, 100, 100, Muscly);
	
	return pretre;
}

	/*Permet de créer un chevalier mage et de le renvoyer*/
ChevalierMage *MusclyFactory::createChevalierMage() const
{
	ChevalierMage *chevaliermage=new ChevalierMage("Lancelin", "Feu tout puissant du chevalier", 400, 80, 100, 40, Muscly);
	
	return chevaliermage;
}

	/*Permet de créer un mage voleur et de le renvoyer*/
MageVoleur *MusclyFactory::createMageVoleur() const
{
	MageVoleur *magevoleur=new MageVoleur("Merlack", "Feu tout puissant du voleur", 400, 40, 80, 100, Muscly);
	
	return magevoleur;
}

	/*Permet de créer un mage pretre et de le renvoyer*/
MagePretre *MusclyFactory::createMagePretre() const
{
	MagePretre *magepretre=new MagePretre("Merlust", "Feu tout puissant du pretre", 400, 80, 100, Muscly);
	
	return magepretre;
}

	/*Permet de créer un chevalier voleur et de le renvoyer*/
ChevalierVoleur *MusclyFactory::createChevalierVoleur() const
{
	ChevalierVoleur *chevaliervoleur=new ChevalierVoleur("Lancelack", "Coup d'épée", 400, 100, 40, Muscly);
	
	return chevaliervoleur;
}

	/*Permet de créer un voleur pretre et de le renvoyer*/
VoleurPretre *MusclyFactory::createVoleurPretre() const
{
	VoleurPretre *voleurpretre=new VoleurPretre("Pacrust", "Coup rapide", 400, 40, 100, 100, Muscly);
	
	return voleurpretre;
}

	/*Permet de créer un chevalier pretre et de le renvoyer*/
ChevalierPretre *MusclyFactory::createChevalierPretre() const
{
	ChevalierPretre *chevalierpretre= new ChevalierPretre("Lancelust", "Epee sainte", 400, 100, 100, 100, 40, Muscly);
	
	return chevalierpretre;
}

	/*Permet de créer un chevalier et de le renvoyer*/
Chevalier *ThinFactory::createChevalier() const
{
	Chevalier *chevalier=new Chevalier("Lancelot", "Epee Sainte", 400, 100, 40, Thin);
	
	return chevalier;
}

	/*Permet de créer un mage et de le renvoyer*/
Mage *ThinFactory::createMage() const
{
	Mage *mage=new Mage("Merlin", "Feu tout puissant", 400, 80, 100, Thin);
	
	return mage;
}

	/*Permet de créer un voleur et de le renvoyer*/
Voleur *ThinFactory::createVoleur() const
{
	Voleur *voleur=new Voleur("Pack", "Coup rapide", 400, 40, Thin);
	
	return voleur;
}

	/*Permet de créer un prêtre et de le renvoyer*/
Pretre *ThinFactory::createPretre() const
{
	Pretre *pretre=new Pretre("Trust", "Soin", 400, 100, 100, Thin);
	
	return pretre;
}

	/*Permet de créer un chevalier mage et de le renvoyer*/
ChevalierMage *ThinFactory::createChevalierMage() const
{
	ChevalierMage *chevaliermage=new ChevalierMage("Lancelin", "Feu tout puissant du chevalier", 400, 80, 100, 40, Thin);
	
	return chevaliermage;
}

	/*Permet de créer un mage voleur et de le renvoyer*/
MageVoleur *ThinFactory::createMageVoleur() const
{
	MageVoleur *magevoleur=new MageVoleur("Merlack", "Feu tout puissant du voleur", 400, 40, 80, 100, Thin);
	
	return magevoleur;
}

	/*Permet de créer un mage pretre et de le renvoyer*/
MagePretre *ThinFactory::createMagePretre() const
{
	MagePretre *magepretre=new MagePretre("Merlust", "Feu tout puissant du pretre", 400, 80, 100, Thin);
	
	return magepretre;
}

	/*Permet de créer un chevalier voleur et de le renvoyer*/
ChevalierVoleur *ThinFactory::createChevalierVoleur() const
{
	ChevalierVoleur *chevaliervoleur=new ChevalierVoleur("Lancelack", "Coup d'épée", 400, 100, 40, Thin);
	
	return chevaliervoleur;
}

	/*Permet de créer un voleur pretre et de le renvoyer*/
VoleurPretre *ThinFactory::createVoleurPretre() const
{
	VoleurPretre *voleurpretre=new VoleurPretre("Pacrust", "Coup rapide", 400, 40, 100, 100, Thin);
	
	return voleurpretre;
}

	/*Permet de créer un chevalier pretre et de le renvoyer*/
ChevalierPretre *ThinFactory::createChevalierPretre() const
{
	ChevalierPretre *chevalierpretre= new ChevalierPretre("Lancelust", "Epee sainte", 400, 100, 100, 100, 40, Thin);
	
	return chevalierpretre;
}

	/*Permet de créer un chevalier et de le renvoyer*/
Chevalier *BlessedFactory::createChevalier() const
{
	Chevalier *chevalier=new Chevalier("Lancelot", "Epee Sainte", 400, 100, 40, Blessed);
	
	return chevalier;
}

	/*Permet de créer un mage et de le renvoyer*/
Mage *BlessedFactory::createMage() const
{
	Mage *mage=new Mage("Merlin", "Feu tout puissant", 400, 80, 100, Blessed);
	
	return mage;
}

	/*Permet de créer un voleur et de le renvoyer*/
Voleur *BlessedFactory::createVoleur() const
{
	Voleur *voleur=new Voleur("Pack", "Coup rapide", 400, 40, Blessed);
	
	return voleur;
}

	/*Permet de créer un prêtre et de le renvoyer*/
Pretre *BlessedFactory::createPretre() const
{
	Pretre *pretre=new Pretre("Trust", "Soin", 400, 100, 100, Blessed);
	
	return pretre;
}

	/*Permet de créer un chevalier mage et de le renvoyer*/
ChevalierMage *BlessedFactory::createChevalierMage() const
{
	ChevalierMage *chevaliermage=new ChevalierMage("Lancelin", "Feu tout puissant du chevalier", 400, 80, 100, 40, Blessed);
	
	return chevaliermage;
}

	/*Permet de créer un mage voleur et de le renvoyer*/
MageVoleur *BlessedFactory::createMageVoleur() const
{
	MageVoleur *magevoleur=new MageVoleur("Merlack", "Feu tout puissant du voleur", 400, 40, 80, 100, Blessed);
	
	return magevoleur;
}

	/*Permet de créer un mage pretre et de le renvoyer*/
MagePretre *BlessedFactory::createMagePretre() const
{
	MagePretre *magepretre=new MagePretre("Merlust", "Feu tout puissant du pretre", 400, 80, 100, Blessed);
	
	return magepretre;
}

	/*Permet de créer un chevalier voleur et de le renvoyer*/
ChevalierVoleur *BlessedFactory::createChevalierVoleur() const
{
	ChevalierVoleur *chevaliervoleur=new ChevalierVoleur("Lancelack", "Coup d'épée", 400, 100, 40, Blessed);
	
	return chevaliervoleur;
}

	/*Permet de créer un voleur pretre et de le renvoyer*/
VoleurPretre *BlessedFactory::createVoleurPretre() const
{
	VoleurPretre *voleurpretre=new VoleurPretre("Pacrust", "Coup rapide", 400, 40, 100, 100, Blessed);
	
	return voleurpretre;
}

	/*Permet de créer un chevalier pretre et de le renvoyer*/
ChevalierPretre *BlessedFactory::createChevalierPretre() const
{
	ChevalierPretre *chevalierpretre= new ChevalierPretre("Lancelust", "Epee sainte", 400, 100, 100, 100, 40, Blessed);
	
	return chevalierpretre;
}

	/*Permet de supprimer une équipe de persos.
	team = équipe de perso à supprimer.
	nb_max_perso_per_group = nombre max de persos par groupe*/
void deleteTeam(Perso ** team, const unsigned int& nb_max_perso_per_group)
{
	for (unsigned int i = 0; i < nb_max_perso_per_group; i += 1)
	{
		delete team[i]; 
		team[i]=NULL;
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

	/*Permet de créer un perso en fonction de son trait et de son type*/
Perso *createPerso(const TraitPersoFactory *factory, const PersoType& type)
{
	Perso *perso=NULL;
	
	switch(type)
	{
		case Knight:
			perso=factory->createChevalier();
			break;
			
		case Magus:
			perso=factory->createMage();
			break;
			
		case Robber:
			perso=factory->createVoleur();
			break;
			
		case Priest:
			perso=factory->createPretre();
			break;
			
		case KnightMagus:
			perso=factory->createChevalierMage();
			break;
			
		case MagusRobber:
			perso=factory->createMageVoleur();
			break;
			
		case MagusPriest:
			perso=factory->createMagePretre();
			break;
			
		case KnightRobber:
			perso=factory->createChevalierVoleur();
			break;
			
		case RobberPriest:
			perso=factory->createVoleurPretre();
			break;
			
		case KnightPriest:
			perso=factory->createChevalierPretre();
			break; 
	}
	
	return perso;
}
