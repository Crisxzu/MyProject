#ifndef DEF_TEST
#define DEF_TEST

#include <iostream>
#include <string>

class M
{
	protected:
		//Attributs
		int a;
		int b;
	
	public:
		//Constructeurs
		M()
		:	a(0),
			b(0)			
		{}
		
		//Fonctions membres	
		
		virtual void test()
		{
		
		}
		
		
		virtual ~M()
		{
			std::cout << "Destructeur Classe M" << std::endl;
		}
};

class A : virtual public M
{
	protected:
		//Attributs
		int *tab;
	
	public:
		//Constructeurs
		A()
		:	tab(NULL)
		{
			tab=new int[4];
		}
		
		void test()
		{
			
		}
		
		~A()
		{
			std::cout << "Destructeur Classe A" << std::endl;
			delete[] tab;
		}
		//Fonctions membres	
		
};


#endif /*TEST*/

