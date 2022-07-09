#include <stdio.h>
#include <stdlib.h>

/*int menu = 0;
   int err = 0;
   int maxerr=0;
   do
   {
   if (err == 0)
   {
   printf("=== Menu ===\n1. Garba Normal\n2. Garba Royal\n3. Garba Deluxe\nVotre choix ?\n"); //Liste du menu
   }
   else
   {
   err = 0;
   printf("Apparement, tu n'as pas bien compris alors je vais te remettre le menu\n");
   printf("=== Menu ===\n1. Garba Normal\n2. Garba Royal\n3. Garba Deluxe\nChoisis bien cette fois!\n");
   }
   do
   {
   fgets(buffer, sizeof(buffer) * 255, stdin);
   sscanf(buffer, "%d", &menu);
     switch (menu)
     {
     case 1:
     printf("Vous avez choisi le Garba Normal, option %d. Bon appétit !\n", menu);
     break;
     case 2:
     printf("Vous avez choisi le Garba Royal, option %d. Bon appétit !\n", menu);
     break;
     case 3:
     printf("Vous avez choisi le Garba Deluxe, option %d. Bon appétit !\n", menu);
     break;
     default:
     err++;
     maxerr++;
     if(maxerr <5)
     {
     printf("Vous n'avez pas choisi de valeur dans le lot, vous avez tapé %d. Recommencez en choisissant ce qui se trouve dans le menu.\n", menu);
     }
     break;
     }
   }while ( err < 3 && err!=0 && maxerr <5);
   }while (err >= 3 && maxerr <5);
   if (maxerr ==5)
   {
   printf("He bien, he bien, tu as l'air finalement trop idiot pour choisir même avec un menu. Sors d'ici !\n");
   }*/
   /*while (compteur<10)
   {
   printf("La variable compteur vaut %d\n", compteur);
   compteur = 9;
   compteur=compteur+1;
   } */
   /*printf("Entrez un nombre\n");
   fgets(buffer, sizeof(buffer) * 255, stdin);
   if(sscanf(buffer, "%d", &nb) != 1)
  {
         printf("Verror\n");
  }
   else{
         printf("Vous avez entré %d\n", nb);
  }
  printf("%d\n", sizeof (buffer));*/
int compteurOccurrence (int *tableau){
     int nb_occurence = 0;
     
     return nb_occurence;
}
void entry(int* tab, int length_tab)
{
    int i=0; char * buffer = (char *) malloc( 255 );
    for(i=0; i<length_tab; i++)
    {
           printf("Entrez un nombre\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
    }
}
void affichetab(int* tab, int length_tab)
{
   int i=0;
   printf("Voici votre tableau\n");
   for(i=0; i<length_tab; i++)
   {
      printf("Valeur %d= %d\n", i, tab[i]);
   }
   printf("Merci pour votre patience\n");
}
void compteurocc1(int* tab, int length_tab)
{
   int i=0; int num=0, occ=0; char * buffer = (char *) malloc( 255 );
   printf("Entrez le nombre dont vous souhaitez vérifier l'occurence\n");
   fgets(buffer, sizeof(buffer) * 255, stdin);
   sscanf(buffer, "%d", &num);
   for(i=0; i<length_tab; i++)
   {
       if(num==tab[i])
       {
         occ++;
       }
   }
   printf("%d apparait %d fois dans le tableau\n", num, occ);
}
void compteurocc2(int* tab, int length_tab)
{
   int i=0, j=0, occ[length_tab];
   printf("Voici votre tableau et l'occurence\n");
   while(i<length_tab)
   {
     occ[i]=0;
     for(j=0; j<length_tab; j++)
     {
       if(tab[i]==tab[j])
       {
          occ[i]=occ[i]+1;
       }
     }
     printf("Valeur %d= %d(%d)\n", i, tab[i], occ[i]);
     i++;
   }
   printf("Merci pour votre patience\n");
}
void entrytest(int* tab, int length_tab)
{
    int i=0, win=0; char * buffer = (char *) malloc( 255 ); 
    for(i=0; i<length_tab; i++)
    {
       switch(i)
       {
           case 0:
           printf("Combien vaut 1+1 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==2)
           {
              win++;
           }
           break;
           case 1:
           printf("Combien vaut 9*9 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==81)
           {
             win++;
           }
           break;
           case 2:
           printf("Combien vaut 1/1 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==1)
           {
             win++;
           }
           break;
           case 3:
           printf("Combien vaut 89-45 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==44)
           {
             win++;
           }
           break;
           case 4:
           printf("Combien vaut 50+50 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==100)
           {
             win++;
           }
           break;
           case 5:
           printf("Combien vaut 10/5 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==2)
           {
             win++;
           }
           break;
           case 6:
           printf("Combien vaut (9*9)-10 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==71)
           {
             win++;
           }
           break;
           case 7:
           printf("Combien vaut 8*8 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==64)
           {
             win++;
           }
           break;
           case 8:
           printf("Combien vaut 7*7 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==49)
           {
             win++;
           }
           break;
           case 9:
           printf("Combien vaut 5-5 ?\n");
           fgets(buffer, sizeof(buffer) * 255, stdin);
           sscanf(buffer, "%d", &tab[i]);
           if(tab[i]==0)
           {
             win++;
           }
           break;
           default:
           break;
       }
    } 
    int result=win*100/length_tab;
    printf("Taux de réussite=%d%% \n", result); 
}
int main()
{
   /*int length_tab=10; int tab[length_tab];
   entry(tab, length_tab);
   compteurocc2(tab, length_tab);*/
   int length_tab=10, tab[length_tab];
   entrytest(tab, length_tab);
   return 0;  
}
