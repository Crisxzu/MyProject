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
  char animename[100];
  CaseList *next;
};

void add(List *list)
{
   int i=0, j=0; CaseList *tmp;list->first=malloc(sizeof(CaseList));tmp=list->first;
   do
   {
     tmp->animename[i]=fgetc(stdin);
     while(tmp->animename[i]!='\n')
     {
       i++;
       tmp->animename[i]=fgetc(stdin);
     }
     tmp->animename[i]='\0';list->length_list++;
     if(tmp->animename[i-1]!='%')
     {
       i=0;
       tmp->next=malloc(sizeof(CaseList));
       tmp=tmp->next;
     }
     else
     {
       tmp->animename[i-1]='\0';
       tmp->next=NULL;
       j++;
     }
   }while(j==0);
}

void showlist(List *list)
{
  int i=0, j=1;CaseList *tmp; tmp=list->first;
  printf("=== Liste d'animés préférés ===\n");
  if(list->length_list==0)
  {
    printf("Rien n'a été entré Oo.\n");
  }
  else
  {
  while(tmp!=NULL)
   {
     printf("%d.", j);
     while(tmp->animename[i]!='\0')
     {
       printf("%c", tmp->animename[i]);
       i++;
     }
     printf("\n");
     i=0; j++; tmp=tmp->next;
   }
   printf("Il y a en tout %d animés. Quel otaku ><.\n", list->length_list);
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
   i=0;
   tmp->next=malloc(sizeof(CaseList)); tmp=tmp->next;
   printf("Veuillez un nouveau nom d'anime.\n");
   tmp->animename[i]=fgetc(stdin);
   while(tmp->animename[i]!='\n')
   {
     i++;
     tmp->animename[i]=fgetc(stdin);
   }
   tmp->animename[i]='\0';
   tmp->next=NULL;
  }
  else
  {
   list->first=malloc(sizeof(CaseList)); tmp=list->first;
   printf("Veuillez un nouveau nom d'anime.\n");
   tmp->animename[i]=fgetc(stdin);
   while(tmp->animename[i]!='\n')
   {
     i++;
     tmp->animename[i]=fgetc(stdin);
   }
   tmp->animename[i]='\0';
   tmp->next=NULL;
  }
  list->length_list++;
}
int main()
{
  List list; char * buffer=(char*) malloc(255); char name[30];int i=0;list.length_list=0; 
  printf("Entrez votre nom\n");
  name[i]=fgetc(stdin);
  while(name[i]!='\n' && i<30)
  {
    i++;
    name[i]=fgetc(stdin);
  }
  name[i]='\0';i=0;
  printf("Okay, vous vous appelez ");
  while(name[i]!='\0')
  {
    printf("%c", name[i]);
    i++;
  }
  printf(".Enchanté de vous rencontré. Quelles sont vos animés préférés ?\nP.S= Entrez autant de noms que vous voulez, à chaque nouvelle entrée faites 'entrée'. Une fois que vous avez terminé, faites '%%' puis 'entrée'.\n");
  add(&list);
  showlist(&list);
  if(list.length_list>0)
  {
    deletecase(&list, buffer);
  }
  addcase(&list, buffer);
  showlist(&list);
  return 0;
}
