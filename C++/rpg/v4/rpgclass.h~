#ifndef DEF_RPGCLASS
#define DEF_RPGCLASS

#include <string>

#define NB_MAX_TEAM 8
#define NB_MAX_PERSO_PER_GROUP 5

typedef enum
{
	Knight, Magus, Robber, Priest, KnightMagus, MagusRobber, MagusPriest, KnightRobber, RobberPriest, KnightPriest
}PersoType;

typedef enum
{
	Normal, Badass, Weak, Muscly, Thin, Blessed
}PersoTrait;

class Perso
{
	protected:
		//Attributs
		const std::string name;
		const std::string attack_name;
		int max_life_point;
		int actual_life_point;
		int melee_attack_point;
		int pm_gain_per_turn;
		const PersoTrait trait;
		
	public:
		//Constructeurs
		
			/*Permet de construire notre personnage en initialisant chaque attributs.*/
		Perso(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const PersoTrait& trait);
		
		//Destructeur
		
			/*Permet de détruire notre personnage*/
		virtual ~Perso()
		{
			
		}
			
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
		
		virtual void resetPerCombatAbility()
		{}
		
			/*Permet d'appliquer les effets du trait d'un personnage*/
		void applyEffectOfTrait();
};

class Chevalier : virtual public Perso
{
	protected:
		//Attributs du chevalier
		const int defense_point;
	
	public:
		//Constructeurs
		
			/*Permet de construire notre chevalier en initialisant ses attributs en tant que personnage et chevalier*/
		Chevalier(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& defense_point, const PersoTrait& trait);
		
			/*Permet à notre chevalier d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre chevalier de subir des dégats*/
		void takeDamage(const int& damage_point);	
	
};

class Mage : virtual public Perso
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
		Mage(const std::string& name, const std::string& attack_name, const int& life_point, const int& magic_attack_point, const int& pm_point, const PersoTrait& trait);

		
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

class Voleur : virtual public Perso
{
	protected:
		//Attributs
		const float coef_dodge;
		
	public:
		//Constructeurs
		
			/*Permet de construire notre voleur en initialisant ses attributs en tant que personnage et voleur*/
		Voleur(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const PersoTrait& trait);
		
		//Fonctions membres	
		
			/*Permet à notre voleur d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre voleur de subir des dégats*/
		void takeDamage(const int& damage_point);
};


class Pretre : virtual public Perso
{
	protected:
		//Attributs
		const float coef_pray;
		const int max_pm;
		int actual_pm;
		const int heal_magic_point;
		const int heal_magic_pm_cost;
	
	public:
		//Constructeurs
		
			/*Permet de construire notre prêtre en initialisant ses attributs en tant que personnage et prêtre*/
		Pretre(const std::string& name, const std::string& attack_name, const int& life_point, const int& heal_magic_point, const int& pm_point, const PersoTrait& trait);
		
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

class ChevalierMage : virtual public Chevalier, virtual public Mage
{
	protected:
		//Attributs
		/* data */
	
	public:
		//Constructeurs
			
			/*Permet de construire notre chevalier mage en initialisant ses attributs en tant que chevalier et mage*/
		ChevalierMage(const std::string& name, const std::string& attack_name, const int& life_point, const int& magic_attack_point, const int& pm_point, const int& defense_point, const PersoTrait& trait);
		
		//Fonctions membres	
		
			/*Permet de regenerer les pm de notre chevalier mage*/
		void pmRegeneration();

			/*Permet à notre chevalier mage d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre chevalier mage de subir des dégats*/
		void takeDamage(const int& damage_point);
};

class MageVoleur : virtual public Mage, virtual public Voleur
{
	protected:
		//Attributs
		/* data */
	
	public:
		//Constructeurs
		
			/*Permet de construire notre mage voleur en initialisant ses attributs en tant que mage et voleur*/
		MageVoleur(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& magic_attack_point, const int& pm_point, const PersoTrait& trait);
		
		
		//Fonctions membres	
		
			/*Permet de regenerer les pm de notre mage voleur*/
		void pmRegeneration();

			/*Permet à notre mage voleur d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre mage voleur de subir des dégats*/
		void takeDamage(const int& damage_point);
};

class MagePretre : virtual public Mage, virtual public Pretre
{
	protected:
		//Attributs
		int max_pm;
		int actual_pm;		
	
	public:
		//Constructeurs
		
			/*Permet de construire notre mage pretre en initialisant ses attributs en tant que mage et pretre.*/
		MagePretre(const std::string& name, const std::string& attack_name, const int& life_point, const int& magic_attack_point, const int& pm_point, const PersoTrait& trait);
		
		//Fonctions membres	
		
			/*Permet de regenerer les pm de notre mage pretre*/
		void pmRegeneration();

			/*Permet à notre mage pretre d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre mage pretre de subir des dégats*/
		void takeDamage(const int& damage_point);		
};

class ChevalierVoleur : virtual public Chevalier, virtual public Voleur
{
	protected:
		//Attributs
		/* data */
	
	public:
		//Constructeurs
		
			/*Permet de construire notre chevalier voleur en initialisant ses attributs en tant que chevalier et voleur*/
		ChevalierVoleur(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& defense_point, const PersoTrait& trait);
		
		//Fonctions membres	

			/*Permet à notre chevalier voleur d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre chevalier voleur de subir des dégats*/
		void takeDamage(const int& damage_point);		
};

class VoleurPretre : virtual public Voleur, virtual public Pretre
{
	protected:
		//Attributs
		bool f_can_use_heal_ability;
		const int max_ability_use_per_combat;
		int actual_ability_use;
	
	public:
		//Constructeurs
		
			/*Permet de construire notre voleur pretre en initialisant ses attributs en tant que voleur et pretre*/
		VoleurPretre(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& heal_magic_point, const int& pm_point, const PersoTrait& trait);
		
		//Fonctions membres	
		
			/*Permet de reinitialiser la capacité à utiliser des abilités après chaque combat*/
		void resetPerCombatAbility();
		
			/*Permet à notre voleur pretre d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre voleur pretre de subir des dégats*/
		void takeDamage(const int& damage_point);		
};

class ChevalierPretre : virtual public Chevalier, virtual public Pretre
{
	protected:
		//Attributs
		bool f_can_use_heal_ability;
		const int max_ability_use_per_combat;
		int actual_ability_use;
	
	public:
		//Constructeurs
		
			/*Permet de construire notre chevalier pretre en initialisant en tant que chevalier et pretre*/
		ChevalierPretre(const std::string& name, const std::string& attack_name, const int& life_point, const int& melee_attack_point, const int& heal_magic_point, const int& pm_point, const int& defense_point, const PersoTrait& trait);
	
	private:
		//Sous-méthodes
		
			/*Permet de savoir si un perso allié est en danger en retournant true si oui ou false si non
			ally_group = groupe allié
			nb_max_perso_per_group = nombre max de persos par groupe
			i_player_in_danger = index du perso en danger*/
		bool isAllyPlayerInDanger(Perso **ally_group, const unsigned int& nb_max_perso_per_group, int& i_player_in_danger);
	
	public:
	
		//Fonctions membres	

			/*Permet de reinitialiser la capacité à utiliser des abilités après chaque combat*/
		void resetPerCombatAbility();
		
			/*Permet à notre chevalier pretre d'effectuer une action.
			opponent_group = groupe adverse
			i_perso = int, index du perso ciblé par l'action
			nb_max_perso_per_group= int, nombre max de persos par groupe*/
		void action(Perso **opponent_group, Perso **ally_group, const int& i_player, const unsigned int& nb_max_perso_per_group);
		
			/*Permet à notre chevalier pretre de subir des dégats*/
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
		unsigned int i_frontliner;
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
		
			/*Permet d'obtenir l'index du personnage qui est en avant*/
		int getFrontLiner(Perso **group);
		
			/*Permet de regenerer les pm de tous les persos de chaque groupe*/
		void allGroupPmRegeneration();
		
			/*Permet de reinitialiser la capacité à utiliser des abilités de tous les persos de chaque groupe*/
		void allGroupResetPerCombatAbility();
		
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

class TraitPersoFactory
{
	public:
		//Fonctions membres	
	
		virtual Chevalier *createChevalier() const =0;
		virtual Mage *createMage() const =0;
		virtual Voleur *createVoleur() const =0;
		virtual Pretre *createPretre() const =0;
		virtual ChevalierMage *createChevalierMage() const =0;
		virtual MageVoleur *createMageVoleur() const =0;
		virtual MagePretre *createMagePretre() const=0;
		virtual ChevalierVoleur *createChevalierVoleur() const=0;
		virtual VoleurPretre *createVoleurPretre() const=0;
		virtual ChevalierPretre *createChevalierPretre() const=0;
};

class NormalFactory : public TraitPersoFactory
{
	public:
		//Fonctions membres
		
			/*Permet de créer un chevalier et de le renvoyer*/
		Chevalier *createChevalier() const;
		
			/*Permet de créer un mage et de le renvoyer*/
		Mage *createMage() const;			

			/*Permet de créer un voleur et de le renvoyer*/
		Voleur *createVoleur() const;

			/*Permet de créer un prêtre et de le renvoyer*/
		Pretre *createPretre() const;

			/*Permet de créer un chevalier mage et de le renvoyer*/
		ChevalierMage *createChevalierMage() const;

			/*Permet de créer un mage voleur et de le renvoyer*/
		MageVoleur *createMageVoleur() const;

			/*Permet de créer un mage pretre et de le renvoyer*/
		MagePretre *createMagePretre() const;

			/*Permet de créer un chevalier voleur et de le renvoyer*/
		ChevalierVoleur *createChevalierVoleur() const;

			/*Permet de créer un voleur pretre et de le renvoyer*/
		VoleurPretre *createVoleurPretre() const;

			/*Permet de créer un chevalier pretre et de le renvoyer*/
		ChevalierPretre *createChevalierPretre() const;	
};

class BadassFactory : public TraitPersoFactory
{
	public:
		//Fonctions membres
		
			/*Permet de créer un chevalier et de le renvoyer*/
		Chevalier *createChevalier() const;
		
			/*Permet de créer un mage et de le renvoyer*/
		Mage *createMage() const;			

			/*Permet de créer un voleur et de le renvoyer*/
		Voleur *createVoleur() const;

			/*Permet de créer un prêtre et de le renvoyer*/
		Pretre *createPretre() const;

			/*Permet de créer un chevalier mage et de le renvoyer*/
		ChevalierMage *createChevalierMage() const;

			/*Permet de créer un mage voleur et de le renvoyer*/
		MageVoleur *createMageVoleur() const;

			/*Permet de créer un mage pretre et de le renvoyer*/
		MagePretre *createMagePretre() const;

			/*Permet de créer un chevalier voleur et de le renvoyer*/
		ChevalierVoleur *createChevalierVoleur() const;

			/*Permet de créer un voleur pretre et de le renvoyer*/
		VoleurPretre *createVoleurPretre() const;

			/*Permet de créer un chevalier pretre et de le renvoyer*/
		ChevalierPretre *createChevalierPretre() const;	
};

class WeakFactory : public TraitPersoFactory
{
	public:
		//Fonctions membres
		
			/*Permet de créer un chevalier et de le renvoyer*/
		Chevalier *createChevalier() const;
		
			/*Permet de créer un mage et de le renvoyer*/
		Mage *createMage() const;			

			/*Permet de créer un voleur et de le renvoyer*/
		Voleur *createVoleur() const;

			/*Permet de créer un prêtre et de le renvoyer*/
		Pretre *createPretre() const;

			/*Permet de créer un chevalier mage et de le renvoyer*/
		ChevalierMage *createChevalierMage() const;

			/*Permet de créer un mage voleur et de le renvoyer*/
		MageVoleur *createMageVoleur() const;

			/*Permet de créer un mage pretre et de le renvoyer*/
		MagePretre *createMagePretre() const;

			/*Permet de créer un chevalier voleur et de le renvoyer*/
		ChevalierVoleur *createChevalierVoleur() const;

			/*Permet de créer un voleur pretre et de le renvoyer*/
		VoleurPretre *createVoleurPretre() const;

			/*Permet de créer un chevalier pretre et de le renvoyer*/
		ChevalierPretre *createChevalierPretre() const;	
};

class MusclyFactory : public TraitPersoFactory
{
	public:
		//Fonctions membres
		
			/*Permet de créer un chevalier et de le renvoyer*/
		Chevalier *createChevalier() const;
		
			/*Permet de créer un mage et de le renvoyer*/
		Mage *createMage() const;			

			/*Permet de créer un voleur et de le renvoyer*/
		Voleur *createVoleur() const;

			/*Permet de créer un prêtre et de le renvoyer*/
		Pretre *createPretre() const;

			/*Permet de créer un chevalier mage et de le renvoyer*/
		ChevalierMage *createChevalierMage() const;

			/*Permet de créer un mage voleur et de le renvoyer*/
		MageVoleur *createMageVoleur() const;

			/*Permet de créer un mage pretre et de le renvoyer*/
		MagePretre *createMagePretre() const;

			/*Permet de créer un chevalier voleur et de le renvoyer*/
		ChevalierVoleur *createChevalierVoleur() const;

			/*Permet de créer un voleur pretre et de le renvoyer*/
		VoleurPretre *createVoleurPretre() const;

			/*Permet de créer un chevalier pretre et de le renvoyer*/
		ChevalierPretre *createChevalierPretre() const;	
};

class ThinFactory : public TraitPersoFactory
{
	public:
		//Fonctions membres
		
			/*Permet de créer un chevalier et de le renvoyer*/
		Chevalier *createChevalier() const;
		
			/*Permet de créer un mage et de le renvoyer*/
		Mage *createMage() const;			

			/*Permet de créer un voleur et de le renvoyer*/
		Voleur *createVoleur() const;

			/*Permet de créer un prêtre et de le renvoyer*/
		Pretre *createPretre() const;

			/*Permet de créer un chevalier mage et de le renvoyer*/
		ChevalierMage *createChevalierMage() const;

			/*Permet de créer un mage voleur et de le renvoyer*/
		MageVoleur *createMageVoleur() const;

			/*Permet de créer un mage pretre et de le renvoyer*/
		MagePretre *createMagePretre() const;

			/*Permet de créer un chevalier voleur et de le renvoyer*/
		ChevalierVoleur *createChevalierVoleur() const;

			/*Permet de créer un voleur pretre et de le renvoyer*/
		VoleurPretre *createVoleurPretre() const;

			/*Permet de créer un chevalier pretre et de le renvoyer*/
		ChevalierPretre *createChevalierPretre() const;	
};

class BlessedFactory : public TraitPersoFactory
{
	public:
		//Fonctions membres
		
			/*Permet de créer un chevalier et de le renvoyer*/
		Chevalier *createChevalier() const;
		
			/*Permet de créer un mage et de le renvoyer*/
		Mage *createMage() const;			

			/*Permet de créer un voleur et de le renvoyer*/
		Voleur *createVoleur() const;

			/*Permet de créer un prêtre et de le renvoyer*/
		Pretre *createPretre() const;

			/*Permet de créer un chevalier mage et de le renvoyer*/
		ChevalierMage *createChevalierMage() const;

			/*Permet de créer un mage voleur et de le renvoyer*/
		MageVoleur *createMageVoleur() const;

			/*Permet de créer un mage pretre et de le renvoyer*/
		MagePretre *createMagePretre() const;

			/*Permet de créer un chevalier voleur et de le renvoyer*/
		ChevalierVoleur *createChevalierVoleur() const;

			/*Permet de créer un voleur pretre et de le renvoyer*/
		VoleurPretre *createVoleurPretre() const;

			/*Permet de créer un chevalier pretre et de le renvoyer*/
		ChevalierPretre *createChevalierPretre() const;	
};

//////////PUBLIC//////////

	/*Permet de créer un perso en fonction de son trait et de son type*/
Perso *createPerso(const TraitPersoFactory *factory, const PersoType& type);

	/*Permet de supprimer une équipe de persos.
	team = équipe de perso à supprimer.
	nb_max_perso_per_group = nombre max de persos par groupe*/
void deleteTeam(Perso ** team, const unsigned int& nb_max_perso_per_group);

#endif /*RPGCLASS*/

