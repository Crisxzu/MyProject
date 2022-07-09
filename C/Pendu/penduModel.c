#include <stdio.h>
#include <stdlib.h>
#include "penduModel.h"


void intwords(Secretwords *secretwords)
{
	FILE *f;
	int index_word=0, i=0;
	
	f=fopen("secretwords.txt", "r");
	for (index_word = 0; index_word < 10; index_word++, i=0)
	{
		(secretwords[index_word]).word[i]=fgetc(f);
		while ((secretwords[index_word]).word[i]!='\n')
		{
			i++;
			(secretwords[index_word]).word[i]=fgetc(f);
		}
		(secretwords[index_word]).word[i]='\0';
		(secretwords[index_word]).length_word=i;
		(secretwords[index_word]).success=FALSE;
		i=0;
		while (i<(secretwords[index_word]).length_word)
		{
			(secretwords[index_word]).win[i]=FALSE;
			i++;
		}
	}
	fclose(f);
}

void check(char *entry, Secretwords *secretwords, const int wordchoosen)
{
	int i=0, j=0;
	
	while ((secretwords[wordchoosen]).word[i]!='\0')
	{
		if (*entry==((secretwords[wordchoosen]).word[i]))
		{
			(secretwords[wordchoosen]).win[i]=TRUE;
		}
		i++;
	}
	i=0;
	while (i<(secretwords[wordchoosen]).length_word)
	{
		if ((secretwords[wordchoosen]).win[i]==TRUE)
		{
			j++;
		}
		i++;
	}
	if (j==(secretwords[wordchoosen]).length_word)
	{
		(secretwords[wordchoosen]).success=TRUE;
	}
}

int selectword(Secretwords *secretwords)
{
	int i=0, j=0, max=9, min=0; srand(time(NULL)); 
  while(j==0)
  {
   i=rand()%(max+1-min)+min;
   if((secretwords[i]).success!=TRUE)
   {
     j++;
   }
  }
  return i;
}
