#include <iostream>
#include <string>
#include "test.h"


using	namespace std;

bool operator==(const Duree& a, const Duree& b)
{
	return a.isEqual(b);
}

bool operator>(const Duree& a, const Duree& b)
{
	return a.isUpper(b);
}

int main ()
{
	Duree A(1, 31, 9);
	Duree B(1, 30, 9);
	
	if (A==B)
	{
		A.showTime();
		B.showTime();	
	}
	else if (A>B)
	{
		A.showTime();
	}
	
	return 0;
}
