#ifndef DEF_TEST
#define DEF_TEST

#include <iostream>
#include <string>

class Perso
{
	protected:
		//Attributs
		/* data */
	
	public:
		//Constructeurs
		Perso()
		{
			std::cout << "Appel du constructeur de Perso" << std::endl;
		}
		
		//Fonctions membres	
		
};

class Mage : virtual public Perso
{
	protected:
		//Attributs
		int max_pm;
		int actual_pm;
	
	public:
		//Constructeurs
		Mage(const int& max_pm, const int& actual_pm)
		:	Perso(),
			max_pm(max_pm),
			actual_pm(actual_pm)
		{
			std::cout << "Appel du constructeur de Mage" << std::endl;
		}
		
		//Fonctions membres	
		
};

class Chevalier : virtual public Perso
{
	protected:
		//Attributs
		int max_pm;
		int actual_pm;
	
	public:
		//Constructeurs
		Chevalier(const int& max_pm, const int& actual_pm)
		:	Perso(),
			max_pm(max_pm),
			actual_pm(actual_pm)
		{
			std::cout << "Appel du constructeur de Chevalier" << std::endl;
		}
		
		//Fonctions membres	
		
};

class MageChevalier : virtual public Chevalier, virtual public Mage
{
	protected:
		//Attributs
		int max_pm;
		int actual_pm;
		
	public:
		//Constructeurs
		MageChevalier(const int& max_pm, const int& actual_pm)
		:	Perso(),
			Chevalier(max_pm, actual_pm),
			Mage(max_pm, actual_pm),
			max_pm(max_pm),
			actual_pm(actual_pm)
		{
			std::cout << "Appel du constructeur de MageChevalier" << std::endl;
		}
		
		//Fonctions membres	
		
		void show() const
		{
			std::cout << max_pm << "/" << actual_pm << std::endl;
		}		
};

#endif /*TEST*/

