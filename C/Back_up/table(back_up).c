#include <stdio.h>
#include <stdlib.h>

/*void affichetableaunum(int* tab, int length_tab)
{
     int i=0;
     printf("== Tableau ==\n");
     for(i=0; i<lenght_tab; i++)
     {
     printf("Valeur de %d= %d\n", i, tab[i]);
     }
}

void affichetableaureversenum(int* tab, int length_tab)
{
     int i=0;
     printf("== Tableau Reverse ==\n");
     for(i=lenght_tab-1; i>-1; i--)
     {
     printf("Valeur de %d= %d\n", i, tab[i]);
     }
}*/
void affichetableaumot(char *mot)
{
     int i=0;
     printf("== Mot ==\n");
     while(mot[i]!='\0')
     {
     printf("%c", mot[i]);
     i++;
     }
     printf("\n");
}
void affichetableaumot2(char (*mot)[30], int *numword)
{
     int i=0, j=0, k=0;
     printf("== Mots ==\n");
     printf("Vous avez entré %d\n", *numword);
     if(*numword!=0)
     {
     do
     {
        while(mot[j][i]!='\0')
        {
          printf("%c", mot[j][i]);
          i++;
        }
        printf("\n");
        if(mot[j][i-1]!=32)
        {
          i=0;
          j++;
        }
        else
        {
          k++;
        }
     }while(k!=1);
     }
}
/*
void strcpy2(char* source, char* dest)
{
   int i=0;
   while(source[i]!='\0')
   {
      dest[i]=source[i];
      i++;
   }
}
int length(char* source)
{
   int i=0;
   while(source[i]!='\0')
   {
     i++;
   }
   return i;
} */

void getWordFromUser(char* mot)
{
  int i=0;
  mot[i]=fgetc(stdin);
  while(mot[i]!='\n')
  {
    i++;
    mot[i]=fgetc(stdin);
  }
  mot[i]='\0';
}
void getWordFromUser2(char *word, int* numword)
{
  int i=0;
  printf("Entrez autant de mots que vous le désirez. Une fois que vous avez fini de taper un mot, faites 'entrée' pour taper un autre mot. Une fois que vous avez tapé autant de mots que vous le désirez, faites '%%' puis 'entrée'. Merci\n");
     word[i]=fgetc(stdin);
     while(word[i]!='\n')
     {
       i++;
       word[i]=fgetc(stdin);
     }
     word[i]='\0'; 
     *numword=*numword+1; 
}
void wordequal(char *mot, char *trad)
{
   int i=0, j=0;
   do{
   if(mot[i]==trad[i])
   {
     i++;
   }
   else
   {
     j++;
   }
   }while(j==0 && mot[i]!='\0' && trad[i]!='\0');
   if(j==0)

   {
     printf("Vrai");
   }
   else
   {
     printf("Faux");
   }
}
/*double calculatrice(double number1, double number2, int choix)
{
    double resultat;
    int i=0; char * buffer = (char *) malloc( 255 );
 for(i=0; i!=2; i++)
 {
    switch(i)
    {
      case 0:
      printf("Entrez le 1er nombre\n");
      fgets(buffer, sizeof(buffer) * 255, stdin);
      sscanf(buffer, "%lf", &number1);
      break;
      case 1:
      printf("Entrez le 2ème nombre\n");
      fgets(buffer, sizeof(buffer) * 255, stdin);
      sscanf(buffer, "%lf", &number2);
      default:
      break;
    }
    }
    switch(choix)
    {
      case 1:
      printf("Vous avez choisi de faire une addition ^^\n");
      resultat=number1+number2;
      break;
      case 2:
      printf("Vous avez choisi de faire une soustraction ^^\n");
      resultat=number1-number2;
      break;
      case 3:
      printf("Vous avez choisi de faire une multiplication ^^\n");
      resultat=number1*number2;
      break;
      case 4:
      printf("Vous avez choisi de faire une division ^^\n");
      resultat=number1/number2;
      break;
    }
    return resultat;
}*/ 
int main()
{
    /*int length_tab1=10,  length_tab2=30, a1, b1;
    int tab1[length_tab1], tab2[length_tab2];
    for(a1=0; a1<length_tab1; a1++)
    {
    tab1[a1]=68*a1;
    }
    for(b1=0; b1<length_tab2; b1++)
    {
    tab2[b1]=69*b1;
    }
    affichetableaureverse(tab1, length_tab1);
    affichetableaureverse(tab2, length_tab2);*/
    /*char mot[30]={'C','o','n','a','s','s','e','\0'};char mot1[30];
    int taille=length(mot);
    printf("Ce mot contient %d lettre(s)\n", taille);
    affichetableaumot(mot);
    strcpy2(mot, mot1);
    affichetableaumot(mot1);*/
    /*double number1=0, number2=0; int choix; char * buffer = (char *) malloc( 255 );
    printf("== Calculatrice ==\n1. Addition\n2.Soustraction\n3.Multiplication\n4.Division\n");
    fgets(buffer, sizeof(buffer) * 255, stdin);
    sscanf(buffer, "%d", &choix);
    double resultat=calculatrice(number1, number2, choix);
    printf("Le résultat est %lf\n", resultat);*/
    char mot[30], trad[30]; int numword=0;
    /*printf("=== Menu ===\n1.Entrez des mots\n2.Voir les mots entrés\n");
    fgets(buffer, sizeof(buffer) * 255, stdin);
    sscanf(buffer, "%d", &choix);
    do
    {
    switch(choix)
    {
      case 1:
      getWordFromUser2(mot, &numword);
      choix++;
      break;
      case 2:
      affichetableaumot2(mot, &numword);
      i++;
      break;
      default:
      printf("Recommencez");
      i++;
    }
    }while(i!=1);*/
    getWordFromUser2(mot, &numword);
    getWordFromUser2(trad, &numword);
    wordequal(mot, trad);
    return 0;
}
