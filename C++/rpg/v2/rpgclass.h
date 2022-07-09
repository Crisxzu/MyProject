#ifndef DEF_RPGCLASS
#define DEF_RPGCLASS

#include <string>

#define NB_MAX_TEAM 8
#define NB_MAX_PERSO_PER_GROUP 5

class Perso
{
	protected:
		//Attributs
		const std::string name;
		const std::string attack_name;
		const int max_life_point;
		int actual_life_point;
		const int melee_attack_point;
		const int pm_gain_per_turn;
		
	public:
		//Constructeurs
		
			/*Permet de construire notre personnage en initialisant chaque attributs.*/
		Perso(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point);
			
		//Fonctions membres
		
			/*Permet d'obtenir le nombre maximal de points de vie*/
		int getMaxLifePoint() const;
		
			/*Permet d'obtenir le nombre actuel de points de vie*/
		int getActualLifePoint() const;
		
			/*Permet d'obtenir le nom du personnage*/
		std::string getPersoName() const;
		
			/*Permet d'obtenir le nom de l'attaque du personnage*/
		std::string getPersoAttackName() const;
		
			/*Permet à notre personnage de recevoir un sort de soin*/
		void takeHeal(const int& heal_magic_point);
		
		virtual void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group)
		{}
		
		virtual void takeDamage(const int& damage_point)
		{}
		
		virtual void pmRegeneration()
		{}
};

class Chevalier : public Perso
{
	protected:
		//Attributs du chevalier
		const int defense_point;
	
	public:
		//Constructeurs
		
			/*Permet de construire notre chevalier en initialisant ses attributs en tant que personnage et chevalier*/
		Chevalier(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& defense_point);
		
			/*Permet à notre chevalier d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre chevalier de subir des dégats*/
		void takeDamage(const int& damage_point);	
	
};

class Mage : public Perso
{
	protected:
		//Attributs
		const int max_pm;
		int actual_pm;
		const int magic_attack_point;
		const int magic_attack_pm_cost;
	
	public:
		//Constructeurs
		
			/*Permet de construire notre mage en initialisant ses attributs en tant que personnage et mage*/
		Mage(const std::string& name, const std::string& attack_name, const int& life_point, const int& magic_attack_point, const int& pm_point);

		//Fonctions membres	
		
			/*Permet de regenerer les pm de notre mage*/
		void pmRegeneration();
				
			/*Permet à notre mage d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre mage de subir des dégats*/
		void takeDamage(const int& damage_point);
};

class Voleur : public Perso
{
	protected:
		//Attributs
		float coef_dodge;
		
	public:
		//Constructeurs
		
			/*Permet de construire notre voleur en initialisant ses attributs en tant que personnage et voleur*/
		Voleur(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point);
		
		//Fonctions membres	
		
			/*Permet à notre voleur d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre voleur de subir des dégats*/
		void takeDamage(const int& damage_point);
};


class Pretre : public Perso
{
	protected:
		//Attributs
		float coef_pray;
		int max_pm;
		int actual_pm;
		int heal_magic_point;
		int heal_magic_pm_cost;
	
	public:
		//Constructeurs
		
			/*Permet de construire notre prêtre en initialisant ses attributs en tant que personnage et prêtre*/
		Pretre(const std::string& name, const std::string& attack_name, const int& life_point, const int& heal_magic_point, const int& pm_point);
		
		//Fonctions membres	
		
			/*Permet de regenerer les pm de notre prêtre*/
		void pmRegeneration();
		
			/*Permet à notre prêtre d'effectuer une action.
			ally_group = groupe allié
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_perso, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre prêtre de subir des dégats*/
		void takeDamage(const int& damage_point);
		
};

class Combat
{
	protected:
		//Attributs
		unsigned int round;
		unsigned int turn;
		const unsigned int nb_max_perso_per_group;
		unsigned int i_perso;
		Perso **group_winner;
		Perso **groupe1;
		Perso **groupe2;
	
	public:
		//Constructeurs
		
			/*Permet de construire un combat en initialisant ses attributs*/
		Combat();
		
			/*Permet de construire un combat en initialisant ses attributs*/
		Combat(Perso **groupe1, Perso **groupe2);
	
	private:
		//Sous-méthodes
		
			/*Permet de savoir si tous les persos d'un des deux groupe sont morts*/
		bool isOver();
		
			/*Permet de lancer le prochain round dans lequel un perso d'un groupe va effectuer une action*/
		void nextRound();
		
	public:	
		//Fonctions membres	
		
			/*Permet d'obtenir le groupe gagnant du combat*/
		Perso ** getGroupWinnner() const;
		
			/*Permet d'obtenir le nombre max de persos par groupe*/
		unsigned int getNbMaxPersoPerGroup() const;
		
			/*Permet d'enclencher un combat entre deux groupes*/
		void fight();
			
			/*Permet de changer les groupes qui doivent combattre
			groupe 1 = Permier groupe de persos.
			groupe 2 = Deuxième groupe de persos.*/
		void updateGroup(Perso **groupe1, Perso **groupe2);
};

class Tournoi
{
	protected:
		//Attributs
		const unsigned int nb_fight_for_quarter_final;
		const unsigned int nb_fight_for_semifinal;
		const unsigned int nb_fight_for_final;
		Perso ** teams[NB_MAX_TEAM];
		Combat combat;
		int i_team[NB_MAX_TEAM];
		
	public:
		//Constructeurs
	
			/*Permet de construire un tournoi*/
		Tournoi(Perso **team1, Perso **team2, Perso **team3, Perso **team4, Perso **team5, Perso **team6, Perso **team7, Perso **team8);
		
	private:
		//Sous-méthodes	
		
			/*Permet de lancer les quarts de final*/
		void quarterFinal();
		
			/*Permet de lancer les demi-final*/
		void semiFinal();
		
			/*Permet de lancer la finale*/
		void finalMatch();
	
	public:
		//Fonctions membres
		
			/*Permet de lancer le tournoi*/
		void launchTournament();
};

//////////PUBLIC//////////

	/*Permet d'insérer un chevalier dans un groupe*/
Chevalier * insertChevalier();

	/*Permet d'insérer un mage dans un groupe*/
Mage * insertMage();

	/*Permet d'insérer un voleur dans un groupe*/
Voleur *insertVoleur();

	/*Permet d'insérer un prêtre dans un groupe*/
Pretre *insertPretre();

	/*Permet de supprimer une équipe de persos.
	team = équipe de perso à supprimer.
	nb_max_perso_per_group = nombre max de persos par groupe*/
void deleteTeam(Perso ** team, const unsigned int& nb_max_perso_per_group);

#endif /*RPGCLASS*/

