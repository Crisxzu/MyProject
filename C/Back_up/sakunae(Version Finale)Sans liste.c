#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Base Base;
struct Base
{
    char mots[200][30], trad[200][30];
    double win[200], try[200], winratetab[200];
    int numword, l, m;
};

void getwords(Base *a);  
void inittrywin(Base * a);
int findquestion(Base * a);
void quizv2(Base *a, int *m);
int findword(Base * a);
void afficheresultv2(Base *a, int * m);
void afficheresult(Base *a, int *choix);
void exchange(double *table, int i);
void tribulle(double *tab, int length);
void initmin(Base *a, double * list, double *listmin, int length);
void initmax(Base *a, double * list, double *listmax, int length);
void initlist(Base *a, double * list);
int findwin(Base *a);
int findmin(Base *a, double * listmin, int length);
int findmax(Base *a, double * listmax, int length);
void check(Base *a, int i, double *listmin, int length_min, double *listmax, int length_max);
void quizv3(Base *a, int * choix);
void initwinratetab(Base * a);
void deleteword(Base * a, int * p);
void delete(Base * a, int * choix);
void deleteall(Base *a, int * choix);
void newentry(Base *a, int * choix);
void alterentry(Base *a, int * p);
void alter(Base *a, int * choix);
void result(Base *a, int * choix);
void preview(Base * a, int * choix);
void entrydico(Base *a, FILE * f);
void usedico(Base *a, FILE * f);

void inittrywin(Base * a)
{
  int i=0;
  while(i<200)
  {
    a->try[i]=0; a->win[i]=0;
    i++;
  }
}
void getwords(Base *a)
{
  int i=0, j=0, k=0; a->numword=0;
  printf("Entrez les mots que vous souhaitez apprendre.Veillez bien faire attention à faire 'entrée' une fois que vous avez fini d'écrire un mot. Une fois que vous avez entré autant de mots que vous voulez, faites'%%' puis 'entrée'. Merci\n=============\n");
  do
  {  a->mots[i][j]=fgetc(stdin);
     while(a->mots[i][j]!='\n')
     {
       j++;
       a->mots[i][j]=fgetc(stdin);
     }
     a->mots[i][j]='\0'; 
     a->numword=a->numword+1;
     if(a->mots[i][j-1]!='%')
     {
     j=0;
     i++;
     }
     else
     {
       a->mots[i][j-1]='\0';
       k++;
     }
  }while(k!=1);
  printf("Entrez la traduction de chaque mots que vous souhaitez apprendre.Veillez bien faire attention à faire 'entrée' une fois que vous avez fini d'écrire une traduction. Une fois cela fait, faites'%%' puis 'entrée'. Merci\n=============\n");
     i=0, j=0, k=0;
     do
     {  a->trad[i][j]=fgetc(stdin);
        while(a->trad[i][j]!='\n')
        {
         j++;
         a->trad[i][j]=fgetc(stdin);
        }
        if(a->trad[i][j-1]!='%')
        {
         a->trad[i][j]='\0';
         j=0;
         i++;
        }
     else
     {
       a->trad[i][j-1]='\0';
       k++;
     }
  }while(k!=1 && i<a->numword);
}

int findquestion(Base * a)
{
  srand(time(NULL)); 
  int j=0, i=0, max=a->numword-1, min=0; initwinratetab(&*a);
  while(j==0)
  {
    i=rand()%(max+1-min)+min;
    if(a->winratetab[i]==-1)
    {
      j++;
    }
  }
  return i;
}

void quizv2(Base *a, int *m)
{
   int i=0, j=0, k=0, l=0; char entry[30];
   if(a->numword!=0)
   {
     printf("Vous aurez maintenant un quiz sur les mots que vous avez entrés(Max=10 questions).\n");
     do
     {
       i=findquestion(&*a);
       printf("Quelle est la traduction du mot ");
       while(a->mots[i][j]!='\0')
       {
        printf("%c", a->mots[i][j]);
        j++;
       }
       printf(" ?\n=============\n"); j=0;
       entry[j]=fgetc(stdin);
       while(entry[j]!='\n')
       {
        j++;
        entry[j]=fgetc(stdin);
       }
       j=0;
       do
       {
         if(entry[j]!=a->trad[i][j])
         {
           k++;
         }
         j++;
       }while(k==0 && entry[j]!='\n');
       if(k==0)
       {
         a->win[i]=a->win[i]+1; a->try[i]++;
         printf("Bien.\n");
       }
       else
       {
         printf("Faux.\n"); a->try[i]++;
       }
       j=0; k=0; l++; *m=*m+1;
     }while(l<10 && *m<a->numword); FILE * f;remove("dico.txt");
     f=fopen("dico.txt", "a");
     entrydico(&*a, f);
     fclose(f);
     if(*m!=a->numword)
     {
       afficheresultv2(&*a, &*m);
     }
     }
}

int findword(Base * a)
{
  srand(time(NULL)); 
  int j=0, i=0, max=a->numword-1, min=0;
  while(j==0)
  {
    i=rand()%(max+1-min)+min;
    if(a->winratetab[i]!=-1 && a->winratetab[i]!=900)
    {
      j++;
    }
  }
  return i;
}

void afficheresultv2(Base *a, int * m)
{
    int i=0, j=0, k=0, choix=0, rest=a->numword-*m;char * buffer = (char *) malloc( 255 ); initwinratetab(&*a);
     printf("== Résultats ==\n");
     if(a->numword!=0)
     {
     do
     {
          i=findword(&*a);
           while(a->mots[i][j]!='\0')
           {
             printf("%c", a->mots[i][j]);
             j++;
           }
           printf(" Taux de réussite=%f%%\n", a->winratetab[i]);
           k++;a->winratetab[i]=900;
          j=0;
     }while(k<10);
     }
     printf("Bien, voici les résultats de 10 mots que vous avez entrés. Il reste encore %d. Souhaitez vous continuer le quiz et être interrogé sur le reste des mots ?(Si oui, tapez 1 si non tapez 0 pour retourner à l'affichage des données puis faites 'entrée')\n=============\n", rest);
      do{
      j=0;
      fgets(buffer, sizeof(buffer) * 255, stdin);
      sscanf(buffer, "%d", &choix);
      switch(choix)
         {
           case 0:
           preview(&*a, &choix);
           break;
           case 1:
           quizv2(&*a, &*m);
           break;
           default:
           printf("Erreur, nous ne reconnaissons pas ce que vous avez choisi. Veuillez entrer le numéro correspondant à l'option que vous désirez ou à faire 0 pour retourner à l'affichage des données.\n=============\n");j++;
           break;
         }}while(j!=0);
}

void exchange(double *table, int i)
{
  double x, y;
  x=table[i+1]; y=table[i];
  table[i]=x; table[i+1]=y;
}

void tribulle(double *tab, int length)
{
   int i=0, borne=length-1;
   int tri=0; 
   while(tri==0)
   {
      tri=1;
      while(i<=borne-1)
      {
        if(tab[i]>tab[i+1])
        {
          exchange(&*tab, i);
          tri=0;
        }
        i++;
      }
      borne=borne-1;i=0;
   }
}

void initmin(Base *a, double * list, double *listmin, int length)
{
  int i=0;
  for(i=0; i<length; i++)
  {
    listmin[i]=list[i];
  }
}

void initmax(Base *a, double * list, double *listmax, int length)
{
  int i=0, j=0;
  for(i=a->numword-length; i<a->numword; i++)
  {
    listmax[j]=list[i];
    j++;
  }
}

void initlist(Base *a, double * list)
{
  int i=0;
  while(i<a->numword)
  {
    list[i]=a->winratetab[i];
    i++;
  }
}

int findwin(Base *a)
{
  int i=0, j=0, max=a->numword-1, min=0;srand(time(NULL)); 
  while(j==0)
  {
    i=rand()%(max+1-min)+min;
    if(a->winratetab[i]!=900)
    {
     j++;
    }
  }
  return i;
}

int findmin(Base *a, double * listmin, int length)
{
  int i=0, j=0, max=length-1, min=0;srand(time(NULL)); 
  while(j==0)
  {
   i=rand()%(max+1-min)+min;
   if(listmin[i]!=900)
   {
     j++;
   }
  }
  return i;
}

int findmax(Base *a, double * listmax, int length)
{
  int i=0, j=0, max=length-1, min=0;srand(time(NULL)); 
  while(j==0)
  {
   i=rand()%(max+1-min)+min;
   if(listmax[i]!=900)
   {
     j++;
   }
  }
  return i;
}

void check(Base *a, int i, double *listmin, int length_min, double *listmax, int length_max)
{
  int j=0, k=0, n=0;
  if(a->l!=length_min)
  {
  j=findmin(&*a, listmin, length_min);
  } 
  if(a->m!=length_max)
  {
  k=findmax(&*a, listmax, length_max);
  }
  while(n==0)
  {
    if(a->winratetab[i]==listmin[j] && a->l!=length_min && a->l!=10)
    {
     listmin[j]=900; a->l++; n++;
    }
    else if(a->winratetab[i]==listmax[k] && a->m!=length_max && a->m!=10)  
    {
      listmax[k]=900; a->m++; n++;
    }
    else
    {
     if(a->l!=length_min)
     {
       j=findmin(&*a, listmin, length_min);
     } 
     if(a->m!=length_max)
     {
       k=findmax(&*a, listmax, length_max);
     }
    }
  }
 
}
void quizv3(Base *a, int * choix)
{
  int i=0, j=0, k=0, l=0, length=a->numword, length_min, length_max; double list[length], *listmin, *listmax; char entry[30]; a->l=0, a->m=0;
  initlist(&*a, list);
  tribulle(list, length); length_min=20*a->numword/100; length_max=a->numword-length_min;
  listmin= malloc( length_min*sizeof(double)); listmax= malloc( length_max*sizeof(double));
  initmin(&*a, list, &*listmin, length_min); initmax(&*a, list, &*listmax, length_max);
     printf("Bien. Vous allez donc être interoggé sur certains mots, un melange de mots qui n'ont pas été bien maîtrisés et bien maîtrisés.(Max=20)\n=============\n");
     do
     {
       i=findwin(&*a);
       check(&*a, i, &*listmin, length_min, &*listmax, length_max);
       printf("Quelle est la traduction du mot ");
       a->winratetab[i]=900;
       while(a->mots[i][j]!='\0')
       {
        printf("%c", a->mots[i][j]);
        j++;
       }
       printf(" ?\n=============\n"); j=0;
       entry[j]=fgetc(stdin);
       while(entry[j]!='\n')
       {
        j++;
        entry[j]=fgetc(stdin);
       }
       j=0;
       do
       {
         if(entry[j]!=a->trad[i][j])
         {
           k++;
         }
         j++;
       }while(k==0 && entry[j]!='\n');
       if(k==0)
       {
         a->win[i]=a->win[i]+1; a->try[i]++;
         printf("Bien.\n");
       }
       else
       {
         printf("Faux.\n"); a->try[i]++;
       }
       j=0; k=0;l++;
       if(a->l==10 && a->m==length_max)
       {
         l=20;
       }
       if(a->m==10 && a->l==length_min)
       {
         l=20;
       }
     }while(l<20 && l<a->numword);
     remove("dico.txt");FILE *f;
     f=fopen("dico.txt", "a");
     entrydico(&*a, f);
     fclose(f);  
afficheresult(&*a, &*choix);
}

void initwinratetab(Base * a)
{
  int i=0;
  while(i<a->numword)
  {
    if(a->try[i]>0)
    {
      a->winratetab[i]=a->win[i]*100/a->try[i];
      i++;
    }
    else
    {
      a->winratetab[i]=-1;
      i++;
    }
  }
}

void afficheresult(Base *a, int *choix)
{
     int i=0, j=0, k=0;double fac=50;char * buffer = (char *) malloc( 255 );
     printf("Vous avez entré un total de %d mots. Vous avez été interrogé sur chacun d'eux. Voici maintenant le résultat pour chaque mots.\n", a->numword);
     printf("== Résultats ==\n"); initwinratetab(&*a);
     if(a->numword!=0)
     {
     do
     {
        while(a->mots[i][j]!='\0')
        {
          printf("%c", a->mots[i][j]);
          j++;
        }
        printf(" Taux de réussite=%f%%\n", a->winratetab[i]);
       j=0; i++;
     }while(i<a->numword); 
     }
     i=0;
     while(k!=1 && i<a->numword)
       {
       if(a->winratetab[i]<fac)
       {
         k++;
         printf("Vous n'avez pas complètement réussi le quiz. Souhaitez-vous le reprendre en étant interrogé sur certains mots dans un quiz special ? Si oui, tapez 1 sinon, tapez 0 pour revenir à l'affichage des données\n=============\n");
         do{
         j=0;
         fgets(buffer, sizeof(buffer) * 255, stdin);
         sscanf(buffer, "%d", &*choix);
         switch(*choix)
         {
           case 0:
           preview(&*a, &*choix);
           break;
           case 1:
           quizv3(&*a, &*choix);
           break;
           default:
           printf("Erreur, nous ne reconnaissons pas ce que vous avez choisi. Veuillez entrer le numéro correspondant à l'option que vous désirez ou à faire 0 pour revenir à l'affichage des données.\n=============\n");j++;
           break;
         }}while(j!=0);
       }
       else
       {
         i++;
       }  
     }
     if(k==0)
     {
      printf("Bien, vous avez maîtrisé chacun des mots. Au revoir.\n");
      k++;
     }
}          

void deleteword(Base * a, int * p)
{
  int i=*p, j=0;
  if(i==a->numword-1)
  {
    a->numword--;
  }
  else
  {
   do{
   j=0;
   while(a->mots[i+1][j]!='\0')
   {
     a->mots[i][j]=a->mots[i+1][j];
     j++;
   }
   a->mots[i][j]='\0'; j=0;
   while(a->trad[i+1][j]!='\0')
   {
     a->trad[i][j]=a->trad[i+1][j];
     j++;
   }
   a->trad[i][j]='\0'; i++;
   }while(i!=a->numword-1);
   a->numword--; 
  }
}

void delete(Base * a, int * choix)
{
  int i=0, reste=a->numword-1; char * buffer = (char *) malloc( 255 ); FILE * f;
  printf("Bien vous avez choisi de supprimer une entrée. Quel mot en particulier souhaitez-vous supprimer ?\nP.S: Vous avez entré %d mots. Veuillez choisir un mot, en entrant un nombre entre 0 et %d, 0 répresentant le premier mot vous avez entré et %d le dernier mot.\n=============\n", a->numword, reste, reste);
  fgets(buffer, sizeof(buffer) * 255, stdin);
  sscanf(buffer, "%d", &i);
    deleteword(&*a, &i);
    printf("Bien, le mot a bien été supprimé. Nous allons maintenant vous rediriger vers l'affichage des données.\n");
    remove("dico.txt");f=fopen("dico.txt", "a");
    entrydico(&*a, f);
    fclose(f);
    preview(&*a, &*choix);
}

void deleteall(Base *a, int * choix)
{
  a->numword=0; remove("dico.txt"); FILE * f;
  printf("Bien, vous avez choisi de supprimer toutes les entrées. La tâche a été effectuée avec succès. Veuillez bien maintenant entrer les nouveaux mots et traductions que vous souhaitez\n=============\n");
  getwords(&*a); f=fopen("dico.txt", "a");
  entrydico(&*a, f);
  fclose(f);
  printf("Bien, nous allons maintenant vous rediriger vers l'affichage des données.\n");
  preview(&*a, &*choix);
}

void newentry(Base *a, int * choix)
{
  int i=a->numword, j=0; a->numword++; FILE * f;
  printf("Bien, vous avez choisi d'ajouter une nouvelle entrée.\nVeuillez entrer le nouveau mot que vous souhaitez ajouter puis faites 'entrée'\n=============\n");
  a->mots[i][j]=fgetc(stdin);
  while(a->mots[i][j]!='\n')
  {
    j++;
    a->mots[i][j]=fgetc(stdin);
  }
  a->mots[i][j]='\0';j=0;
  printf("Veuillez maintenant entrer la traduction de ce nouveau mot.\n");
  a->trad[i][j]=fgetc(stdin);
  while(a->trad[i][j]!='\n')
  {
    j++;
    a->trad[i][j]=fgetc(stdin);
  }
  a->trad[i][j]='\0';
  f=fopen("dico.txt", "a");
   for(j=0; a->mots[i][j]!='\0'; j++)
   {
   fprintf(f, "%c", a->mots[i][j]);
   }
   fprintf(f, "\n");
   for(j=0; a->trad[i][j]!='\0'; j++)
   {
   fprintf(f, "%c", a->trad[i][j]);
   }
   fprintf(f, "\n");
  fclose(f);
  printf("La tâche a bien été effectué. Nous allons maintenant vous rediriger vers l'affichage des données.\n");
  preview(&*a, &*choix);
}

void alterentry(Base *a, int * p)
{
  int i=*p, j=0;
  printf("Veuillez entrer la nouvelle forme du mot.\n");
  a->mots[i][j]=fgetc(stdin);
  while(a->mots[i][j]!='\n')
  {
    j++;
    a->mots[i][j]=fgetc(stdin);
  }
  a->mots[i][j]='\0'; j=0;
  printf("Veuillez entrer la nouvelle traduction du mot.\n");
  a->trad[i][j]=fgetc(stdin);
  while(a->trad[i][j]!='\n')
  {
    j++;
    a->trad[i][j]=fgetc(stdin);
  }
  a->trad[i][j]='\0';
}

void alter(Base *a, int * choix)
{
  int i=0, reste=a->numword-1; char * buffer = (char *) malloc( 255 ); FILE * f;
  printf("Bien, vous avez choisi de modifier une entrée. Quel mot souhaitez-vous modifier ?\nP.S: Vous avez entré %d mots. Veuillez choisir un mot, en entrant un nombre entre 0 et %d, 0 répresentant le premier mot vous avez entré et %d le dernier mot.\n=============\n", a->numword, reste, reste); 
  fgets(buffer, sizeof(buffer) * 255, stdin);
  sscanf(buffer, "%d", &i);
  alterentry(&*a, &i);
  remove("dico.txt");f=fopen("dico.txt", "a");
  entrydico(&*a, f);
  fclose(f);
  printf("La tâche a bien été effectué. Nous allons maintenant vous rediriger vers l'affichage des données.\n");
  preview(&*a, &*choix);
}

void result(Base *a, int * choix)
{
  int i=0, j=0;
  initwinratetab(&*a);
  printf("=== WINRATE ===\n");
     do
     {
        while(a->mots[i][j]!='\0')
        {
          printf("%c", a->mots[i][j]);
          j++;
        }
        printf(" Taux de réussite=%f%%\n", a->winratetab[i]);
       i++;j=0;
     }while(i<a->numword); 
   printf("P.S: Si le taux de réussite affiche -1, cela signifie que vous n'avez pas encore été interrogé sur le mot en question.\nLa tâche a bien été effectué. Nous allons maintenant vous rediriger vers l'affichage des données.\n");
   preview(&*a, &*choix);
}

void preview(Base * a, int * choix)
{
   int i=0, j=0, k=0; char * buffer = (char *) malloc( 255 );
   printf("== Données ==\n");
   for(i=0; i<a->numword; i++, j=0) 
   {  
     while(a->mots[i][j]!='\0')
     {
       printf("%c", a->mots[i][j]);
       j++;
     }
     printf(" "); j=0;
     while(a->trad[i][j]!='\0')
     {
       printf("%c", a->trad[i][j]);
       j++;
     }
     printf("\n");
   }
   printf("Bien vous avez entré ces mots et leurs traductions. Ils sont au nombre de %d. Veuillez choisir ce que vous souhaitez faire.\n== Options ==\n1.Supprimer une entrée\n2.Supprimer toutes les données et en entrer de nouvelles\n3.Ajouter une entrée\n4.Modifier une entrée\n5.Lancer le quiz\n6.Visualiser les différents winrates\n7.Quittez le programme\n=============\n", a->numword);
   do{
   k=0;
   fgets(buffer, sizeof(buffer) * 255, stdin);
   sscanf(buffer, "%d", &*choix);
   switch(*choix)
   {
    case 1:
    delete(&*a, &*choix);
    break;
    case 2:
    deleteall(&*a, &*choix);
    break;
    case 3:
    newentry(&*a, &*choix);
    break;
    case 4:
    alter(&*a, &*choix);
    break;
    case 5:
    break;
    case 7:
    printf("Bien, merci et au revoir.\n");
    break;
    case 6:
    result(&*a, &*choix);
    break;
    default:
    printf("Erreur, nous ne reconnaissons pas ce que vous avez choisi. Veuillez entrer le numéro correspondant à l'option que vous désirez ou à faire 7 pour quitter le programme.\n=============\n"); k++;
    break;
   }}while(k!=0);
}

void entrydico(Base *a, FILE * f)
{
  int i=0, j=0;
  while(i<a->numword)
  { 
   for(j=0; a->mots[i][j]!='\0'; j++)
   {
   fprintf(f, "%c", a->mots[i][j]);
   }
   fprintf(f, "\n");
   for(j=0; a->trad[i][j]!='\0'; j++)
   {
   fprintf(f, "%c", a->trad[i][j]);
   }
   fprintf(f, "\n");
   fprintf(f,"%lf\n", a->try[i]);
   fprintf(f,"%lf\n", a->win[i]);
   i++;
  }
}


void usedico(Base *a, FILE * f)
{
  int i=0, j=0; a->numword=0; double t[200], u[200];
  for(i=0;fgetc(f)!=EOF; i++, j=0)
  {
  fseek(f, -1L,SEEK_CUR);
  a->mots[i][j]=fgetc(f);
  while(a->mots[i][j]!='\n')
  {
    j++;
    a->mots[i][j]=fgetc(f);
  }
  a->mots[i][j]='\0';a->numword++;
  j=0;
  a->trad[i][j]=fgetc(f);
  while(a->trad[i][j]!='\n')
  {
    j++;
    a->trad[i][j]=fgetc(f);
  }
  a->trad[i][j]='\0';
  fscanf(f,"%lf", &t[i]);a->try[i]=t[i];
  fseek(f, 1L,SEEK_CUR);
  fscanf(f, "%lf", &u[i]);a->win[i]=u[i];
  fseek(f, 1L,SEEK_CUR);
  }
}
int main(int argc, char *argv[])
{
   int i=0, j=0; FILE * f; f=fopen("dico.txt", "r");
   Base a; inittrywin(&a);
   if(f!=NULL)
   {
    printf("Il semblerait que ça ne soit pas la première fois que vous utilisez notre programme. Nous allons donc nous servir des différentes données entrées précédemment.\n");
    usedico(&a, f);
    fclose(f);
   }
   else
   {
    f=fopen("dico.txt", "a");
    getwords(&a);
    entrydico(&a, f);
    fclose(f);
   }
   preview(&a, &j);
   /*quiz(&a);*/
   if(j==5)
   {
   quizv2(&a, &i);
   }
   if(i==a.numword)
   {
   afficheresult(&a, &i);
   }
   return 0;
}
