#include <stdio.h>
#include <stdlib.h>
#include "penduView.h"

void display(Secretwords *secretwords, const int wordchoosen)
{
	int i=0;
	
	printf("MOT SECRET: ");
	for (i = 0; (secretwords[wordchoosen]).word[i]!='\0'; i++)
	{
		if ((secretwords[wordchoosen]).win[i]==TRUE)
		{
			printf("%c", (secretwords[wordchoosen]).word[i]);
		}
		else
		{
			printf("*");
		}
	}
	printf("\n");
}

void userentry(char *entry)
{
	char* delete=(char*) malloc(5);
	printf("ENTREZ UN CARATERE: ");
	*entry=fgetc(stdin);
	*delete=fgetc(stdin);
	free(delete);
	printf("\n");
}
