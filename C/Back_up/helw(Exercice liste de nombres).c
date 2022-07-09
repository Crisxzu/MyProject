#include <stdio.h>
#include <stdlib.h>

typedef struct List List; typedef struct CaseList CaseList;
struct List
{
   int length_list;
   CaseList *first;
};

struct CaseList
{
  int number;
  CaseList *next;
};

void add(List *list, char * buffer)
{
   int num=0; CaseList *tmp;list->first=malloc(sizeof(CaseList));tmp=list->first;
   do
   {
     fgets(buffer, sizeof(char)*255, stdin);
     sscanf(buffer, "%d", &num);
     if(num==0)    
     {
       if(list->length_list==0)
       {
         list->first=NULL;
       }
       else
       {
         tmp->next=NULL;
       }
     }
     else
     {
       if(list->length_list>=1)
       {
         tmp=tmp->next;
       }
       tmp->number=num;list->length_list++;
       tmp->next=malloc(sizeof(CaseList));
     }
   }while(num!=0);
}

void showlist(List *list)
{
  int i=0;CaseList *tmp; tmp=list->first;
  if(list->length_list==0)
  {
    printf("Vous n'avez pas entré de numéros ><\n");
  }
  else
  {
  while(tmp!=NULL)
   {
     printf("Nombre %d=%d\n", i, tmp->number);
     tmp=tmp->next;
     i++;
   }
  }
}

void deletecase(List * list, char * buffer)
{
  int i=0, j=0, k=0; CaseList  *tmp, *tmpl; tmp=list->first;
    printf("Quel élément voulez supprimer de la liste ?\nP.S= Le premier élement de la liste correspond à 0 et le dernier %d.\n", list->length_list-1);
    do{
    k=0;
    fgets(buffer, sizeof(char)*255, stdin);
    sscanf(buffer, "%d",&i);
    if(i>list->length_list-1 || i<0)
    {
      k++;
      printf("Erreur, vous avez entré un nombre qui ne se trouve dans l'intervalle 0 et %d. Veuillez entrer un nombre correspondant à un élément se trouvant dans la liste.\nP.S= Le premier élement de la liste correspond à 0 et le dernier %d.\n", list->length_list-1, list->length_list-1);
    }
    else
    {
      if(i==0)
      {
        list->first=list->first->next;
        free(tmp);
      }
      else
      {
       while(j!=i-1)
       {
         tmp=tmp->next; j++;
       }
       if(j+1==list->length_list-1)
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
      list->length_list--;
    }
  }while(k!=0);
}

void addcase(List *list, char * buffer)
{
  int i=0;CaseList *tmp; 
  if(list->length_list>0)
  {
   tmp=list->first;
   while(i!=list->length_list-1)
   {
     tmp=tmp->next;i++;
   } 
   tmp->next=malloc(sizeof(CaseList));
   printf("Veuillez un nouveau nombre.\n");
   fgets(buffer, sizeof(char)*255, stdin);
   sscanf(buffer, "%d",&i);
   tmp->next->number=i;
   tmp->next->next=NULL;
  }
  else
  {
   list->first=malloc(sizeof(CaseList)); tmp=list->first;
   printf("Veuillez un nouveau nombre.\n");
   fgets(buffer, sizeof(char)*255, stdin);
   sscanf(buffer, "%d",&i);
   tmp->number=i;
   tmp->next=NULL;
  }
  list->length_list++;
}
int main()
{
  List list; char * buffer=(char*) malloc(255);list.length_list=0;
  printf("Entrez tous les nombres que vous voulez. Faites '0' dés que vous voulez arrêter.\n");
  add(&list, buffer);
  printf("=== Résultats ===\n");
  showlist(&list);
  if(list.length_list>0)
  {
    deletecase(&list, buffer);
  }
  addcase(&list, buffer);
  showlist(&list);
  return 0;
}
