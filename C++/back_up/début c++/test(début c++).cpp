#include <iostream>
#include <string>
#include "test.h"


using	namespace std;

int main ()
{
	int k=0;
	
	k=giveValue(k);
	
	
	cout << k << endl;
	return 0;
}

int giveValue(int& k)
{
	if (k==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
