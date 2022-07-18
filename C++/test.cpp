#include <iostream>
#include <string>
#include "test.h"


using	namespace std;

int main ()
{
	SlowFactory A;
	Vehicule *vehicule=NULL;
	
	vehicule=createVehicule(&A, Car);
	
	vehicule->showStats();
	
	delete vehicule;
	return 0;
}
