#include <iostream>
#include <string>
#include "test.h"


using	namespace std;

int main ()
{
	A *a=new A;
	
	M *m=a;
	
	delete m;
	return 0;
}
