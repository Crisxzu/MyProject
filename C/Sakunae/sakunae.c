#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Base Base;typedef struct List List; typedef struct CaseList CaseList;
struct Base
{
    char mots[200][30];
    double win[200], try[200], winratetab[200];
    int numword, l, m;
};

struct List
{
    int length_list;
    CaseList *first;
};

struct CaseList
{
   char trad[30];
   CaseList *next;
};

void getwords(Base *a, List *list);
void add(List *list, int k); 
void addcase(List *list, int p, Base *a, int m);
int verify(Base *b, List *list, int p);
void reversequiz(Base *a, List *list);
void quizv1(Base *a, int *m, List *list);
void checknorepeatword(Base *a);
void deletewordrepeat(Base * a, int p); 
void inittrywin(Base * a);
int findquestion(Base * a);
void quizv2(Base *a, int *m, List *list);
int findword(Base * a);
void afficheresultv2(Base *a, int * m);
void afficheresult(Base *a);
void updateDico(Base *a, char * buffer, List *list);
void displaywords(Base *a);
void displaytrad(List *list, int p);
void exchange(double *table, int i);
void tribulle(double *tab, int length);
void initmin(Base *a, double * list, double *listmin, int length);
void initmax(Base *a, double * list, double *listmax, int length);
void initlist(Base *a, double * list);
int findwin(Base *a);
int findmin(Base *a, double * listmin, int length);
int findmax(Base *a, double * listmax, int length);
void check(Base *a, int i, double *listmin, int length_min, double *listmax, int length_max);
void quizv3(Base *a, List *list);
void initwinratetab(Base * a);
void deleteword(Base * a, int p, List *list);
void deletetrad(Base *a, int p, char *buffer, List *list);
void delete(Base * a, char * buffer, List *list);
void deleteall(Base *a, List *list);
void addword(Base *a, List *list);
void addtrad(int p, List *list);
void newentry(Base *a, char * buffer, List *list);
void alterword(Base *a, int  p, List *list);
void altertrad(Base *a, int p, List *list, char *buffer);
void alter(Base *a, char *buffer, List *list);
void result(Base *a);
void quiz(Base *a, char *buffer, List *list);
void display(Base *a, char *buffer, List *list);
void entrydico(Base *a, List *list, FILE * f);
void usedico(Base *a, List *list, FILE * f);

void inittrywin(Base * a)
{
  int i=0;
  while(i<200)
  {
    a->try[i]=0; a->win[i]=0;
    i++;
  }
}

void add(List *list, int k)
{
   int i=0, j=0; CaseList *tmp;(list[k]).first=malloc(sizeof(CaseList));tmp=(list[k]).first; (list[k]).length_list=0;
   do
   {
     tmp->trad[i]=fgetc(stdin);
     while(tmp->trad[i]!='\n')
     {
       i++;
       tmp->trad[i]=fgetc(stdin);
     }
     tmp->trad[i]='\0';(list[k]).length_list++;
     if(tmp->trad[i-1]!='%')
     {
       i=0;
       tmp->next=malloc(sizeof(CaseList));
       tmp=tmp->next;
     }
     else
     {
       tmp->trad[i-1]='\0';
       tmp->next=NULL;
       j++;
     }
   }while(j==0);
}

void deletewordrepeat(Base * a, int p)
{
  int i=p, j=0;
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
   a->mots[i][j]='\0';
   i++;
   }while(i!=a->numword-1);
   a->numword--; 
  }
}

void checknorepeatword(Base *a)
{
  int i=0,j=0, k=0, l=0;
  for (i = 0; i < a->numword; i++)
  {
  	 for (k = 0; k < a->numword; k++)
  	 {
  	 	do
       {
         if(a->mots[i][j]!=a->mots[k][j])
         {
           l++;
         }
         j++;
       }while(l==0 && a->mots[i][j]!='\0');
       if (l==0 && k!=i)
       {
       	 deletewordrepeat(&*a, k);
       }
       l=0; j=0;
  	 }
  }
}

/*void deletetradrepeat(List *list, int m, int p)
{
  int i=m, j=p, k=0; CaseList *tmp, *tmpl; tmp=(list[i]).first;
      if(j==0)
      {
        (list[i]).first=(list[i]).first->next;
        free(tmp);
      }
      else
      {
       while(k!=j-1)
       {
         tmp=tmp->next; k++;
       }
       if(k+1==(list[i]).length_list-1)
       {
         free(tmp->next);
         tmp->next=NULL;
       }
       else
       {
         tmpl=tmp->next;
         tmp->next=tmp->next->next;
         free(tmpl);
       }
      }
      (list[i]).length_list--;
}


void checknorepeattrad(List *list, int p)
{
  int i=p,j=0, k=0, l=0; CaseList *tmp, *tmpl; tmp=(list[i]).first;
  do{
    tmpl=(list[i]).first; k=0;
  	do{
  	 do
       {
         if(tmp->trad[j]!=tmpl->trad[j])
         {
           l++;
         }
         j++;
       }while(l==0 && tmp->trad[j]!='\0');
       if (l==0)
       {
       	 deletetradrepeat(list, i, k);
       }
       tmpl=tmpl->next;
       l=0; j=0;k++;
  	 }while(tmpl!=NULL);
  	 tmp=tmp->next;
  }while(tmp!=NULL);
}*/


void getwords(Base *a, List *list)
{
  int i=0, j=0, k=0; a->numword=0;
  printf("Entrez les mots que vous souhaitez apprendre. Veillez bien faire attention à faire 'entrée' une fois que vous avez fini d'écrire un mot. Une fois que vous avez entré autant de mots que vous voulez, faites'%%' puis 'entrée'. Merci.\nP.S: Les mots répétés seront supprimés.\n=============\n");
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
  }while(k!=1); i=0, j=0, k=0; checknorepeatword(&*a);
  do{
  printf("Quelle(s) est(sont) la(les) traduction(s) que vous souhaitez attribuer à ");
  while(a->mots[i][j]!='\0')
  {
    printf("%c", a->mots[i][j]);
    j++;
  }
  printf(" ?\nP.S:Une fois que vous avez fini d'écrire une traduction, faites 'entrée'. Une fois que vous avez terminé d'entrer toutes les traductions que vous voulez? faites '%%' puis 'entrée'.\nP.S: Les traductions répétés seront supprimés.\n");
  add(list, i);
    i++; j=0;
    }while(i<a->numword);
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

void addcase(List *list, int p, Base *a, int m)
{
  int i=p, j=0;CaseList *tmp; 
  if((list[i]).length_list>0)
  {
   tmp=(list[i]).first;
   while(j!=(list[i]).length_list-1)
   {
     tmp=tmp->next;j++;
   } 
   j=0;
   tmp->next=malloc(sizeof(CaseList)); tmp=tmp->next;
   while(a->mots[m][j]!='\0')
   {
     tmp->trad[j]=a->mots[m][j];
     j++;
   }
   tmp->trad[j]='\0';
   tmp->next=NULL;
  }
  else
  {
   (list[i]).first=malloc(sizeof(CaseList)); tmp=(list[i]).first;
   while(a->mots[m][j]!='\0')
   {
     tmp->trad[j]=a->mots[m][j];
     j++;
   }
   tmp->trad[j]='\0';
   tmp->next=NULL;
  }
  (list[i]).length_list++;
}

int verify(Base *b, List *list, int p)
{
  int i=p, j=0, k=0, l=0, m=0; CaseList *tmp; tmp=(list[i]).first;
  while (k!=b->l)
  {
    tmp=tmp->next;k++;
  }
  k=0;
  while(j==0)
  {
  do
  {
    if(tmp->trad[j]!=b->mots[m][j])
    {
      k++;
    }
    else
    {
      j++;
    }
  }while(k==0 && tmp->trad[j]!='\0');
  if(k==1 && m<=b->numword-1)
  {
    m++;j=0;k=0;
  }
  else
  {
    j++;
  }
  }
  if(k==1)
  {
    l++;
  }
  return l;
}


void reversequiz(Base *a, List *list)
{
  int i=0, j=0, k=0, m=0, n=0; CaseList *tmp;
  Base b; List list2[200]; b.numword=0;
  for (m = 0; m < a->numword; m++)
  {
    b.l=0;
  	while (b.l!=(list[m]).length_list)
  	{
      tmp=(list[m]).first;(list2[i]).length_list=0;
      if (verify(&b, list, m)==1)
      {
      	k=0; j=0;
      	while (k!=b.l)
      	{
      		tmp=tmp->next;k++;
      	}
      	while(tmp->trad[j]!='\0')
      	{
      	  b.mots[i][j]=tmp->trad[j];
      	  j++;
      	}
      	b.mots[i][j]='\0'; b.numword++; b.l++;
      	addcase(list2, i, &*a, m);
      	i++; 	
      }
      else
      {
        k=0; j=0;n=0;
        while (k!=b.l)
      	{
      		tmp=tmp->next;k++;
      	}
      	  do
      	  {
      	  	if (tmp->trad[j]!=b.mots[n][j])
      	  	{
      	  		n++; j=0;
      	  	}
      	  	else
      	  	{
      	  		j++;
      	  	}
      	  } while (tmp->trad[j]!='\0');
      	  addcase(list2, n, &*a, m);b.l++;
      	}
      }
  	}
  	i=0;
   quizv1(&b,&i, list2);
}


void quizv1(Base *a, int *m, List *list)
{
   int i=0, j=0, k=0, l=0; char entry[30]; CaseList *tmp; initwinratetab(&*a);inittrywin(&*a);
   if(a->numword!=0)
   {
     printf("Vous aurez maintenant un quiz sur les mots que vous avez entrés(Max=20 questions).\n");
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
       j=0; tmp=(list[i]).first;
       do
       {
         if(entry[j]!=tmp->trad[j])
         {
           if(tmp->next!=NULL)
           {
              tmp=tmp->next; j=0;	
           }
           else
           {
              k++;
           }
         }
         else
         {
         j++;
         }
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
     }while(l<20 && *m<a->numword);
     if(*m!=a->numword)
     {
       afficheresultv2(&*a, &*m);
     }
     }
}


void quizv2(Base *a, int *m, List *list)
{
   int i=0, j=0, k=0, l=0; char entry[30]; CaseList *tmp;
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
       j=0; tmp=(list[i]).first;
       do
       {
         if(entry[j]!=tmp->trad[j])
         {
           if(tmp->next!=NULL)
           {
              tmp=tmp->next; j=0;	
           }
           else
           {
              k++;
           }
         }
         else
         {
         j++;
         }
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
     entrydico(&*a, list, f);
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

void afficheresultv2(Base *a, int *m)
{
    int i=0, j=0, k=0, rest=a->numword-*m; initwinratetab(&*a);
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
     printf("Bien, voici les résultats de 10 mots que vous avez entrés. Il reste encore %d. Nous vous redirigeons vers le menu précédent.\n=============\n", rest);
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
void quizv3(Base *a, List *list)
{
  int i=0, j=0, k=0, l=0, length=a->numword, length_min, length_max; double liste[length], *listmin, *listmax; char entry[30]; a->l=0, a->m=0;
  initlist(&*a, liste); CaseList *tmp;
  tribulle(liste, length); length_min=20*a->numword/100; length_max=a->numword-length_min;
  listmin= malloc( length_min*sizeof(double)); listmax= malloc( length_max*sizeof(double));
  initmin(&*a, liste, &*listmin, length_min); initmax(&*a, liste, &*listmax, length_max);
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
       j=0;tmp=(list[i]).first;
       do
       {
         if(entry[j]!=tmp->trad[j])
         {
           if(tmp->next!=NULL)
           {
              tmp=tmp->next; j=0;	
           }
           else
           {
              k++;
           }
         }
         else
         {
         j++;
         }
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
     entrydico(&*a, list, f);
     fclose(f);  
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

void afficheresult(Base *a)
{
     int i=0, j=0, k=0;double fac=50;
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
         printf("Vous n'avez pas complètement réussi le quiz malheuresement. Veuillez maintenant faire le quiz avancé.\n");
       }
       else
       {
         i++;
       }  
     }
     if(k==0)
     {
      printf("Bien, vous avez maîtrisé chacun des mots. Nous allons vous rediriger vers le menu précédent.\n");
      k++;
     }
}

void updateDico(Base *a, char * buffer, List *list)
{
   int choix=0, i=0;
   printf("Vous avez choisi de modifier les données. Bien, veuillez choisir parmi les options suivantes.\n");
   do{
   printf("=== Options ===\n1.Supprimer une donnée\n2.Supprimer toutes les données et en entrer de nouvelles\n3.Ajouter une entrée\n4.Modifier une entrée\n5. Retour au Menu\n=============\n");
   fgets(buffer, sizeof(char)*5, stdin);
   sscanf(buffer, "%d", &choix);
   switch(choix)
   {
     case 1:
     delete(&*a, buffer, list);
     break;
     case 2:
     deleteall(&*a, list);
     break;
     case 3:
     newentry(&*a, buffer, list);
     break;
     case 4:
     alter(&*a, buffer, list);
     break;
     case 5:
     i++;
     break;
     default:
     printf("Erreur, vous avez entré un nombre qui ne correspond à aucune option. Veuillez choisir une option qui se trouve dans cette liste ou tout simplement retourner sur le menu en faisant 5.\n");
     break;
   }}while(i==0);
}          

void displaywords(Base *a)
{
  int i=0, j=0;
  printf("=== Liste de mots ===\n");
  do{
  while(a->mots[i][j]!='\0')
  {
    printf("%c", a->mots[i][j]);
    j++;
  }
  printf("\n");i++; j=0;
  }while(i!=a->numword);
}

void displaytrad(List *list, int p)
{
  int i=p, j=0, k=0; CaseList *tmp; tmp=(list[i]).first;
  printf("=== Liste de traductions ===\n");
  if((list[i]).length_list==0)
  {
    printf("Rien n'a été entré Oo.\n");
  }
  else
  {
   while(tmp!=NULL)
   {
     printf("%d.", k);
     while(tmp->trad[j]!='\0')
     {
       printf("%c", tmp->trad[j]);
       j++;
     }
     printf("\n");
     j=0; k++; tmp=tmp->next;
   }
  }
   printf("=============\n");
}

void deleteword(Base * a, int p, List *list)
{
  int i=p, j=0; CaseList *tmp; 
  if(i==a->numword-1)
  {
    a->numword--; 
    do{
    tmp=(list[i]).first;
    if((list[i]).length_list>1)
    {
    while(j<(list[i]).length_list-2)
    {
      tmp=tmp->next; j++;
    }
    free(tmp->next); tmp->next=NULL;
    } 
    else
    {
      free((list[i]).first); (list[i]).first=NULL;
    }
    j=0; (list[i]).length_list--;
    }while((list[i]).length_list!=0);
  }
  else
  {
   do{
    tmp=(list[i]).first;
    if((list[i]).length_list>1)
    {
    while(j<(list[i]).length_list-2)
    {
      tmp=tmp->next; j++;
    }
    free(tmp->next); tmp->next=NULL;
    } 
    else
    {
      free((list[i]).first); (list[i]).first=NULL;
    }
    j=0; (list[i]).length_list--;
    }while((list[i]).length_list!=0);
   do{
   j=0;
   while(a->mots[i+1][j]!='\0')
   {
     a->mots[i][j]=a->mots[i+1][j];
     j++;
   }
   a->mots[i][j]='\0';
   list[i]=list[i+1];
   i++;
   }while(i!=a->numword-1);
   a->numword--; 
  }
}

void deletetrad(Base *a, int p, char *buffer, List *list)
{
  int i=p, j=0, k=0, l=0; CaseList *tmp, *tmpl; tmp=(list[i]).first;
  printf("Bien, vous avez choisi de supprimer une des traductions du mot ");
  while(a->mots[i][j]!='\0')
  {
    printf("%c", a->mots[i][j]);
    j++;
  }
  printf(".\n"); j=0;
  displaytrad(list, p);
  if((list[i]).length_list!=0)
  {
  printf("Quel élément voulez supprimer de la liste ?\nP.S= Le premier élement de la liste correspond à 0 et le dernier %d.\n", (list[i]).length_list-1);
    do{
    l=0;
    fgets(buffer, sizeof(char)*255, stdin);
    sscanf(buffer, "%d",&j);
    if(j>(list[i]).length_list-1 || j<0)
    {
      l++;
      printf("Erreur, vous avez entré un nombre qui ne se trouve dans l'intervalle 0 et %d. Veuillez entrer un nombre correspondant à un élément se trouvant dans la liste.\nP.S= Le premier élement de la liste correspond à 0 et le dernier %d.\n", (list[i]).length_list-1, (list[i]).length_list-1);
    }
    else
    {
      if(j==0)
      {
        (list[i]).first=(list[i]).first->next;
        free(tmp);
      }
      else
      {
       while(k!=j-1)
       {
         tmp=tmp->next; k++;
       }
       if(k+1==(list[i]).length_list-1)
       {
         free(tmp->next);
         tmp->next=NULL;
       }
       else
       {
         tmpl=tmp->next;
         tmp->next=tmp->next->next;
         free(tmpl);
       }
      }
      (list[i]).length_list--;
    }
  }while(l!=0);
  }
  else
  {
    printf("Il n'est pas possible de supprimer un élément de la liste puisqu'il n'y en a aucun\n");
  }
}


void delete(Base * a, char * buffer, List *list)
{
  int i=0, choix=0, reste=a->numword-1, j=0; FILE * f;
  printf("Bien vous avez choisi de supprimer une entrée. Veuillez choisir parmi les options suivantes.\n");
  printf("=== Options ===\n1. Supprimer un mot\n2. Supprimer une traduction d'un mot\n3.Retour\n=============\n");
  do{
  fgets(buffer, sizeof(char) * 5, stdin);
  sscanf(buffer, "%d", &choix);
  switch(choix)
  {
     case 1:
     displaywords(&*a);
     printf("=============\n");
     printf("Quel mot en particulier souhaitez-vous supprimer ?\nP.S: Vous avez entré %d mots. Veuillez choisir un mot, en entrant un nombre entre 0 et %d, 0 répresentant le premier mot vous avez entré et %d le dernier mot.\n=============\n", a->numword, reste, reste);
     fgets(buffer, sizeof(char) * 255, stdin);
     sscanf(buffer, "%d", &i);
     deleteword(&*a, i, list);j++;
     break;
     case 2:
     displaywords(&*a);
     printf("=============\n");
     printf("De quel mot vous voulez vous supprimer une des traductions ?\nP.S: Vous avez entré %d mots. Veuillez choisir un mot, en entrant un nombre entre 0 et %d, 0 répresentant le premier mot vous avez entré et %d le dernier mot\n=============\n",a->numword, reste, reste);
     fgets(buffer, sizeof(char) * 255, stdin);
     sscanf(buffer, "%d", &i);
     deletetrad(&*a, i, buffer, list); j++;
     break;
     case 3:
     j++;
     break;
     default:
     printf("Erreur, vous avez entré un nombre qui ne correspond à aucune option. Veuillez choisir une option qui se trouve dans cette liste ou tout simplement faire retour en faisant 3.\n");
     break;
   }}while(j==0);
    printf("Bien, nous allons maintenant vous rediriger vers le menu précédent.\n");
    remove("dico.txt");f=fopen("dico.txt", "a");
    entrydico(&*a, list, f);
    fclose(f);
}

void deleteall(Base *a, List *list)
{
  int i=0;
  for(i=0; i<a->numword; i++)
  {
    deleteword(&*a, i, list);
  }
  a->numword=0; remove("dico.txt"); FILE * f;
  printf("Bien, vous avez choisi de supprimer toutes les entrées. La tâche a été effectuée avec succès. Veuillez bien maintenant entrer les nouveaux mots et traductions que vous souhaitez\n=============\n");
  getwords(&*a, list); f=fopen("dico.txt", "a");
  entrydico(&*a, list, f);
  fclose(f);
  printf("Bien, nous allons maintenant vous rediriger vers le menu précédent.\n");
}

void addword(Base *a, List *list)
{
  int i=a->numword, j=0;
  printf("Bien, veuillez maintenant le mot que vous souhaitez ajouter. Veillez bien faire attention à faire 'entrée' une fois que vous avez fini d'écrire le mot.\n");
  a->mots[i][j]=fgetc(stdin);
  while(a->mots[i][j]!='\n')
  {
    j++;
    a->mots[i][j]=fgetc(stdin);
  }
  a->mots[i][j]='\0'; j=0; a->numword++;
  printf("Quelle(s) est(sont) la(les) traduction(s) que vous souhaitez attribuer à ");
  while(a->mots[i][j]!='\0')
  {
    printf("%c", a->mots[i][j]);
    j++;
  }
  printf(" ?\nP.S:Une fois que vous avez fini d'écrire une traduction, faites 'entrée'. Une fois que vous avez terminé d'entrer toutes les traductions que vous voulez? faites '%%' puis 'entrée'.\n");
  add(list, i);
}

void addtrad(int p, List *list)
{
  int i=p, j=0;CaseList *tmp; 
  if((list[i]).length_list>0)
  {
   tmp=(list[i]).first;
   while(j!=(list[i]).length_list-1)
   {
     tmp=tmp->next;j++;
   } 
   j=0;
   tmp->next=malloc(sizeof(CaseList)); tmp=tmp->next;
   printf("Veuillez entrer la nouvelle traduction.\n");
   tmp->trad[j]=fgetc(stdin);
   while(tmp->trad[j]!='\n')
   {
     j++;
     tmp->trad[j]=fgetc(stdin);
   }
   tmp->trad[j]='\0';
   tmp->next=NULL;
  }
  else
  {
   (list[i]).first=malloc(sizeof(CaseList)); tmp=(list[i]).first;
   printf("Veuillez entrer la nouvelle traduction.\n");
   tmp->trad[j]=fgetc(stdin);
   while(tmp->trad[j]!='\n')
   {
     j++;
     tmp->trad[j]=fgetc(stdin);
   }
   tmp->trad[j]='\0';
   tmp->next=NULL;
  }
  (list[i]).length_list++;
}

void newentry(Base *a, char * buffer, List *list)
{
  int reste=a->numword-1, i=0, j=0, choix=0; FILE * f;
  printf("Bien, vous avez choisi d'ajouter une nouvelle entrée.\nVeuillez choisir une option parmi celles suivantes.\n"); 
  printf("=== Options ===\n1. Nouveau mot\n2. Nouvelle traduction d'un mot\n3. Retour\n=============\n");
  do{
  fgets(buffer, sizeof(char) * 5, stdin);
  sscanf(buffer, "%d", &choix);
  switch(choix)
  {
    case 1:
    addword(&*a, list);j++;
    break;
    case 2:
    displaywords(&*a);
    printf("=============\n");
    printf("A quel mot voulez-vous ajouter une traduction ?\nP.S: Vous avez entré %d mots. Veuillez choisir un mot, en entrant un nombre entre 0 et %d, 0 répresentant le premier mot vous avez entré et %d le dernier mot\n=============\n",a->numword, reste, reste);
    fgets(buffer, sizeof(char) * 255, stdin);
    sscanf(buffer, "%d", &i);
    addtrad(i, list);j++;
    break;
    case 3:
    j++;
    break;
    default:
    printf("Erreur, vous avez entré un nombre qui ne correspond à aucune option. Veuillez choisir une option qui se trouve dans cette liste ou tout simplement faire retour en faisant 3.\n");
    break;
  }}while(j==0);
  printf("Bien, nous allons maintenant vous rediriger vers le menu précédent.\n");
  remove("dico.txt");f=fopen("dico.txt", "a");
  entrydico(&*a, list, f);
  fclose(f);
}

void alterword(Base *a, int  p, List *list)
{
  int i=p, j=0;
  printf("Veuillez entrer la nouvelle forme du mot.\n");
  a->mots[i][j]=fgetc(stdin);
  while(a->mots[i][j]!='\n')
  {
    j++;
    a->mots[i][j]=fgetc(stdin);
  }
  a->mots[i][j]='\0'; j=0;
}

void altertrad(Base *a, int p, List *list, char *buffer)
{
  int i=p, choix=0, j=0; CaseList *tmp; tmp=(list[i]).first;
  displaytrad(list, p);
  printf("Choisissez la traduction que vous souhaitez modifier.\n");
  fgets(buffer, sizeof(char)*5, stdin);
  sscanf(buffer, "%d", &choix);
  while (j!=choix)
  {
  	tmp=tmp->next;j++;
  }
  j=0;
  printf("Entrez maintenant la nouvelle traduction.\n");
  tmp->trad[j]=fgetc(stdin);
  while(tmp->trad[j]!='\n')
  {
    j++; tmp->trad[j]=fgetc(stdin);
  }
  tmp->trad[j]='\0';
}

void alter(Base *a, char *buffer, List *list)
{
  int i=0, choix=0, j=0, reste=a->numword-1; FILE * f;
  printf("Bien, vous avez choisi de modifier une entrée. Veuillez choisir parmi les options suivantes.\n");
  printf("=== Options ===\n1. Modifier un mot\n2. Modifier une traduction d'un mot\n3. Retour\n=============\n");
  do{
  fgets(buffer, sizeof(char)*5, stdin);
  sscanf(buffer, "%d", &choix);
  switch(choix)
  {
    case 1:
    displaywords(&*a);
    printf("=============\n");
    printf("Quel mot en particulier souhaitez-vous modifier ?\nP.S: Vous avez entré %d mots. Veuillez choisir un mot, en entrant un nombre entre 0 et %d, 0 répresentant le premier mot vous avez entré et %d le dernier mot\n=============\n",a->numword, reste, reste);
    fgets(buffer, sizeof(char) * 255, stdin);
    sscanf(buffer, "%d", &i);
    alterword(&*a, i, list); j++;
    break;
    case 2:
    displaywords(&*a);
    printf("=============\n");
    printf("De quel mot en particulier souhaitez-vous modifier une des traductions ?\nP.S: Vous avez entré %d mots. Veuillez choisir un mot, en entrant un nombre entre 0 et %d, 0 répresentant le premier mot vous avez entré et %d le dernier mot\n=============\n",a->numword, reste, reste);
    fgets(buffer, sizeof(char) * 255, stdin);
    sscanf(buffer, "%d", &i);
    altertrad(&*a, i, list, buffer); j++;
    break;
    case 3:
    j++;
    break;
    default:
    printf("Erreur, vous avez entré un nombre qui ne correspond à aucune option. Veuillez choisir une option qui se trouve dans cette liste ou tout simplement faire retour en faisant 3.\n");
    break;  
  }}while(j==0);
  remove("dico.txt");f=fopen("dico.txt", "a");
  entrydico(&*a, list, f);
  fclose(f);
  printf("Bien, nous allons maintenant vous rediriger vers le menu précédent.\n");
}

void quiz(Base *a, char *buffer, List *list)
{
  int choix=0, i=0, j=0, k=0; initwinratetab(&*a);
  printf("Bien, vous avez décidé de tenter le quiz. Veuillez maintenant choisir parmi les options suivantes.\n");
  do{
  printf("=== Options ===\n1. Quiz simple(Recommandé si c'est la première fois que vous utilisez Sakunae)\n2. Quiz avancé(Uniquement si vous avez déjà été interrogé sur chacun des mots)\n3. Quiz inversé\n4. Retour au menu\n");
  fgets(buffer, sizeof(char)*5, stdin);
  sscanf(buffer, "%d", &choix);
  switch(choix)
  {
  	case 1:
  	quizv2(&*a, &k, list);
    if(k==a->numword)
    {
     afficheresult(&*a);
    }
  	break;
  	case 2:
  	while(i<a->numword && j!=1)
  	{
  		if (a->winratetab[i]==-1)
  		{
  			j++;
  		}
  	    i++;
  	}
  	if(j==1)
  	{
  		printf("Erreur, il semblerait qu'il reste encore des mots sur lesquelles vous n'avez pas été interrogé. Veuillez choisir plutôt le quiz simple.\n"); j=0;
  	}
    else
    {
    	quizv3(&*a, list); afficheresult(&*a);
    } 
    break;
    case 3:
    reversequiz(&*a, list);
    case 4:
    j++;
    break;
    default:
    printf("Erreur, veuillez choisir une option parmi celle de la liste.\n");
    break;
  }}while(j==0);


}

void display(Base *a, char *buffer, List *list)
{
  int choix=0, i=0, j=0, reste=a->numword-1; 
  printf("Bien, choisissez quel genre de données vous voulez voir.\n");
  do{
  printf("=== Options ===\n1. Mots\n2. Traductions d'un mot\n3. Taux de réussite\n4. Retour au menu\n");
  fgets(buffer, sizeof(char)*5, stdin);
  sscanf(buffer, "%d", &choix);
  switch(choix)
  {
    case 1:
    displaywords(&*a);
    printf("=============\n");
    break;
    case 2:
    printf("De quel mot en particulier souhaitez-vous voir les traductions ?\nP.S: Vous avez entré %d mots. Veuillez choisir un mot, en entrant un nombre entre 0 et %d, 0 répresentant le premier mot vous avez entré et %d le dernier mot\n=============\n",a->numword, reste, reste);
    fgets(buffer, sizeof(char) * 255, stdin);
    sscanf(buffer, "%d", &i);
    displaytrad(list, i);
    break;
    case 3:
    result(&*a);
    break;
    case 4:
    j++;
    default:
    printf("Erreur, veuillez choisir une option parmi celle de la liste.\n");
    break;
  }}while(j==0);


}
void result(Base *a)
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
}

void entrydico(Base *a, List *list, FILE * f)
{
  int i=0, j=0; CaseList *tmp;
  while(i<a->numword)
  { 
   tmp=(list[i]).first;
   for(j=0; a->mots[i][j]!='\0'; j++)
   {
   fprintf(f, "%c", a->mots[i][j]);
   }
   fprintf(f, "\n");
   do{
   for(j=0; tmp->trad[j]!='\0'; j++)
   {
   fprintf(f, "%c", tmp->trad[j]);
   }
   fprintf(f, "\n");
   tmp=tmp->next;
   }while(tmp!=NULL);
   fprintf(f, "%%\n");
   fprintf(f,"%lf\n", a->try[i]);
   fprintf(f,"%lf\n", a->win[i]);
   i++;
  }

}


void usedico(Base *a, List *list, FILE * f)
{
  int i=0, j=0, k=0; a->numword=0; double t[200], u[200];CaseList *tmp;
  for(i=0;fgetc(f)!=EOF; i++, j=0, k=0)
  {
  fseek(f, -1L,SEEK_CUR);
  a->mots[i][j]=fgetc(f);
  while(a->mots[i][j]!='\n')
  {
    j++;
    a->mots[i][j]=fgetc(f);
  }
  a->mots[i][j]='\0';a->numword++;
  (list[i]).first=malloc(sizeof(CaseList));tmp=(list[i]).first;(list[i]).length_list=0;
  do{
  j=0; tmp->trad[j]=fgetc(f);
  while(tmp->trad[j]!='\n')
  {
    j++;
    tmp->trad[j]=fgetc(f);
  }
  tmp->trad[j]='\0';(list[i]).length_list++;
  if(fgetc(f)=='%')
  {
    tmp->next=NULL; k++;
  }
  else
  {
   fseek(f, -1L, SEEK_CUR);
   tmp->next=malloc(sizeof(CaseList));
   tmp=tmp->next;
  }
  }while(k==0);
  fseek(f, 1L,SEEK_CUR);
  fscanf(f,"%lf", &t[i]);a->try[i]=t[i];
  fseek(f, 1L,SEEK_CUR);
  fscanf(f, "%lf", &u[i]);a->win[i]=u[i];
  fseek(f, 1L,SEEK_CUR);
  }
}
int main(int argc, char *argv[])
{
   int choix=0, k=0; FILE * f; f=fopen("dico.txt", "r"); char * buffer=(char*) malloc( 255 ); List list[200];
   Base a; inittrywin(&a); //Iniatialisation du programme et du fichier où les données entrées par l'utilisateur seront stockés.
   if(f!=NULL) 
   {
    printf("Bienvenue. Il semblerait que ça ne soit pas la première fois que vous utilisez Sakunae. Nous allons donc nous servir des différentes données entrées précédemment.\n");
    usedico(&a, list, f);
    fclose(f);
   }
   else
   {
    f=fopen("dico.txt", "a");
    printf("Bienvenue. Ce programme Sakunae est là pour vous aider dans votre apprentissage.\n");
    getwords(&a, list);
    entrydico(&a, list, f);
    fclose(f);
   }
   printf("Vos données ont été bien initialisées. Veuillez maintenant choisir une option, parmi celles présentes.\n");
   //Menu de Sakunae
   do{
   printf("=== Options ===\n1.Modification des données\n2.Quiz\n3.Affichage des données\n4.Quittez le programme\n=============\n");
   fgets(buffer, sizeof(char)*5, stdin);
   sscanf(buffer, "%d", &choix);
   switch(choix)
   {
     case 1:
     updateDico(&a, buffer, list); //Suppression, Ajout, Modification d'entrée
     break;
     case 2:
     quiz(&a, buffer, list); //Tester les connaissances de l'utilisateur
     break;
     case 3:
     display(&a, buffer, list); //Pour consulter les différentes données
     break;
     case 4:
     k++; printf("Au revoir, à bientôt.\n"); //Quitter Sakunae
     break;
     default:
     printf("Erreur, vous avez entré un nombre qui ne correspond à aucune option. Veuillez choisir une option qui se trouve dans cette liste ou tout simplement quittez Sakunae en faisant 4.\n");
     break;
   }}while(k==0);
   return 0;
}
