#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <curses.h>


#include "helw.h"


int giveValue(const int k)
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

int main()
{
	int k=0;
	
	k=giveValue(k);

	printf("%d", k);
	
  return 0;
}
