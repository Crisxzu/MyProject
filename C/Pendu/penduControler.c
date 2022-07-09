#include <stdio.h>
#include <stdlib.h>
#include "penduControler.h"
#include "penduModel.h"
#include "penduView.h"
#include "struct.h"


void play()
{
	int wordchoosen=0, try=0, i=0;
	Secretwords secretwords[10];
	
	intwords(secretwords);
	wordchoosen=selectword(secretwords);
	while (try!=10 && (secretwords[wordchoosen]).success!=TRUE)
	{
		char entry;
		
		display(secretwords, wordchoosen);
		userentry(&entry);
		check(&entry, secretwords, wordchoosen);
		if ((secretwords[wordchoosen]).success==TRUE)
		{
			while ((secretwords[wordchoosen]).word[i]!='\0')
			{
				printf("%c", (secretwords[wordchoosen]).word[i]);
				i++;
			}
			printf("\n");
			printf("VICTORY\n");
			i=0;
		}
		else
		{
			printf("CONTINUE!\n");
			try++;
			if (try==10)
			{
				printf("YOU LOSE\n");
			}
		}
	}
	
}
