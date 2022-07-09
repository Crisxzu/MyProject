#include <stdlib.h>
#include <stdio.h>

int main ()
{
	FILE *file=NULL;
	
	file=fopen("text.txt", "w");
	
	fclose(file);
	return 0;
}
