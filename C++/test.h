#ifndef DEF_TEST
#define DEF_TEST

#define POIDS_VOITURE 100
#define VITESSE_VOITURE 100
#define POIDS_CAMION 500
#define VITESSE_CAMION 80
#define POIDS_MOTO 50
#define VITESSE_MOTO 120

#include <iostream>
#include <string>

typedef enum
{
	Normal, Slow, Rapid
}VehiculeTrait;

typedef enum
{
	Car, Truck, Motorcycle
}VehiculeType;

class Vehicule
{
	protected:
		//Attributs
		int poids;
		int vitesse;
		VehiculeTrait type;
		int nb_place;
		
	public:
		//Constructeurs
		Vehicule(const int& poids, const int& vitesse, const VehiculeTrait& type, const int& nb_place)
		:	poids(poids),
			vitesse(vitesse),
			type(type),
			nb_place(nb_place)			
		{}
		
		//Fonctions membres	
		
		virtual void showStats()
		{
			std::cout << "=== Stats ===" << std::endl;
			std::cout << "=> Poids= " << poids << std::endl;
			std::cout << "=>Vitesse= " << vitesse << std::endl;
			std::cout << "=>Nombre de places= " << nb_place << std::endl;
			std::cout << "=>Type de vehicule= ";
			
			switch(type)
			{
				case Normal:
					std::cout << "Normal" << std::endl;
					break;
				
				case Slow:
					std::cout << "Lent" << std::endl;
					break;
				
				case Rapid:
					std::cout << "Rapide" << std::endl;
					break;
			}
		}
		
		void applyEffectOfType()
		{
			switch(type)
			{
				case Normal:
					poids *= 1;
					vitesse *= 1;
					break;
				
				case Slow:
					poids *= 1.5;
					vitesse *= 0.5;
					break;
				
				case Rapid:
					poids *= 0.5;
					vitesse *= 1.5;
					break;
			}	
		}
		
		virtual ~Vehicule()
		{}
};

class Voiture : public Vehicule 
{
	protected:
		//Attributs
		
		
	public:
		//Constructeurs
		Voiture(const int& poids, const int& vitesse, const VehiculeTrait& type)
		:	Vehicule(poids, vitesse, type, 4)
		{
			applyEffectOfType();		
		}
		
		//Fonctions membres	
		
};

class Camion : public Vehicule
{
	protected:
		//Attributs
	
	public:
		//Constructeurs
		Camion(const int& poids, const int& vitesse, const VehiculeTrait& type)
		:	Vehicule(poids, vitesse, type, 2)
		{	
			applyEffectOfType();
		}
		
		//Fonctions membres	
		
};

class Moto : public Vehicule
{
	protected:
		//Attributs
			
	
	public:
		//Constructeurs
		Moto(const int& poids, const int& vitesse, const VehiculeTrait& type)
		:	Vehicule(poids, vitesse, type, 1)
		{
			applyEffectOfType();
		}
		
		//Fonctions membres	
		
};

class TraitVehiculeFactory
{
	public:
		
		//Fonctions membres	
		
	virtual Voiture * createVoiture() const = 0;
	virtual Vehicule * createCamion() const = 0;
	virtual Vehicule * createMoto() const = 0;
};

class NormalFactory : public TraitVehiculeFactory
{
	public:		
		//Fonctions membres	
		Voiture * createVoiture() const
		{
			Voiture *voiture=new Voiture(POIDS_VOITURE, VITESSE_VOITURE, Normal);
			
			return voiture;
		}
		
		Vehicule * createCamion() const
		{
			Camion *camion=new Camion(POIDS_CAMION, VITESSE_CAMION, Normal);
			
			return camion;
		}
		
		Vehicule * createMoto() const
		{
			Moto *moto=new Moto(POIDS_MOTO, VITESSE_MOTO, Normal);
			
			return moto;
		}
};

class SlowFactory : public TraitVehiculeFactory
{
	public:		
		//Fonctions membres	
		Voiture * createVoiture() const
		{
			Voiture *voiture=new Voiture(POIDS_VOITURE, VITESSE_VOITURE, Slow);
			
			return voiture;
		}
		
		Vehicule * createCamion() const
		{
			Camion *camion=new Camion(POIDS_CAMION, VITESSE_CAMION, Slow);
			
			return camion;
		}
		
		Vehicule * createMoto() const
		{
			Moto *moto=new Moto(POIDS_MOTO, VITESSE_MOTO, Slow);
			
			return moto;
		}
};

class RapidFactory : public TraitVehiculeFactory
{
	public:		
		//Fonctions membres	
		Voiture * createVoiture() const
		{
			Voiture *voiture=new Voiture(POIDS_VOITURE, VITESSE_VOITURE, Rapid);
			
			return voiture;
		}
		
		Vehicule * createCamion() const
		{
			Camion *camion=new Camion(POIDS_CAMION, VITESSE_CAMION, Rapid);
			
			return camion;
		}
		
		Vehicule * createMoto() const
		{
			Moto *moto=new Moto(POIDS_MOTO, VITESSE_MOTO, Rapid);
			
			return moto;
		}
};

Vehicule * createVehicule(const TraitVehiculeFactory * factory, const VehiculeType& type)
{
	Vehicule *vehicule=NULL;
	
	switch(type)
	{
		case Car:
			vehicule= factory->createVoiture();
			break;
		
		case Truck:
			vehicule= factory->createCamion();
			break;
		
		case Motorcycle:
			vehicule= factory->createMoto();
			break;
	}
	
	return vehicule;
}

#endif /*TEST*/

