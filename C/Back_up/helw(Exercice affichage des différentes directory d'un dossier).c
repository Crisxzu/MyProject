#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <curses.h>


#include "helw.h"

void addcase(List *ListVNMenu, char* VNFoldername)
{
  /*Elle va permettre d'initialiser chaque case de la liste chainée au nom de chaque dossier contenant un Visual Novel.
  ListVNMenu désigne la liste chaînée qui va contenir les différents noms des champs du menu de "Play". Ce sont les cases de cette liste qui vont être initialisés au nom des dossiers(qui contiennent les différentes données qui vont composer un Visual Novel) présents dans le dossier "VN" et du dernier champ du menu "New".
  VNFoldername désigne le nom du dossier du Visual Novel qui va être ajouter à la liste.*/
  int i=0;
  CaseList *actualcase; 
  
  if(ListVNMenu->length_list>0)//S'il y a déjà un(ou des) nom(s) présent(s) sur la liste
  {
		actualcase=ListVNMenu->firstcase;
		while(i!=ListVNMenu->length_list-1)//On se dirige à la fin de la liste, pour ajouter un nouveau nom
		{
			actualcase=actualcase->nextcase;i++;
		} 
		i=0;
		
		actualcase->nextcase=malloc(sizeof(CaseList)); actualcase=actualcase->nextcase;
		actualcase->vn_name= VNFoldername;
		actualcase->nextcase=NULL;
  }
  else//S'il n'y a rien sur la liste, on ajoute le nom au début de celle-ci
  {
		ListVNMenu->firstcase=malloc(sizeof(CaseList)); actualcase=ListVNMenu->firstcase;
		actualcase->vn_name= VNFoldername;
		actualcase->nextcase=NULL;
  }
  ListVNMenu->length_list++;
}

void intListVNMenu(List *ListVNMenu)
{
	/*Elle va permettre d'initialiser les différents du champ du menu de "Play". Il y aura des champs qui vont former une liste des différents Visual Novel présents dans le dossier "VN" et un champ "New". Ainsi l'utilisateur pourra choisir le Visual Novel qu'il veut jouer ou choisir d'en créer un en accédant au champ "New".
	ListVNMenu désigne la liste chaînée qui va contenir les différents noms des champs du menu de "Play". Ce sont les cases de cette liste qui vont être initialisés au nom des dossiers(qui contiennent les différentes données qui vont composer un Visual Novel) présents dans le dossier "VN" et du dernier champ du menu "New".*/
	DIR* VNDirectory=NULL; dirent* VNFolder=NULL;
	
	VNDirectory=opendir("VN/");
	while ((VNFolder=readdir(VNDirectory))!=NULL)//On repère dans le dossier "VN", un à un les différents dossiers présents(Les Visual Novel) et on note leur nom dans la liste et cela tant qu'on a pas fini de lister tous les dossiers
	{
		if (strcmp (VNFolder->d_name,"..") != 0 && strcmp (VNFolder->d_name,".") != 0)//On omet les "directory" "." qui réprésente le dossier dans lequel on se trouve c'est-à-dire le dossier "VN" et ".." le dossier dans lequel le dossier "VN" est contenu
		{	
			addcase(&*ListVNMenu, VNFolder->d_name);
		}
	}
	ListVNMenu->newvn="New";
}

void addcase(List *list, char* directory_name)
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
   tmp->option_name= directory_name;
   tmp->next=NULL;
  }
  else
  {
   list->first=malloc(sizeof(CaseList)); tmp=list->first;
   tmp->option_name= directory_name;
   tmp->next=NULL;
  }
  list->length_list++;
}

void initoption(List *list)
{
	DIR* rep=NULL; dirent* file=NULL;
	char *delete;
	
	rep=opendir("VNCreator/");
	while ((file=readdir(rep))!=NULL)
	{
		delete = (char*) memchr (file->d_name, '~', strlen(file->d_name));
		if (strcmp (file->d_name,"..") != 0 && strcmp (file->d_name,".") != 0 && delete==NULL)
		{	
			addcase(&*list, file->d_name);
		}
	}
	directory_name="New";
	addcase(&*list, directory_name);
}

void options(List *list, int highlight_index)
{
   int i=0; CaseList *tmp; tmp=list->first;
   printw("== Options ==\n");
   for (i = 0; tmp!=NULL ; i++)
   {
   	if (i==highlight_index)
   	{
   		attron(COLOR_PAIR(1));
			printw("%s\n", tmp->option_name);
			attroff(COLOR_PAIR(1));
   	}
   	else
   	{
   		printw("%s\n", tmp->option_name);
   	}
   	tmp=tmp->next;
   }
}

void waitchoice(List *list)
{
	int key, highlight_index=0;
	initscr();
	start_color();
	init_pair(1,COLOR_GREEN,COLOR_WHITE);
	init_pair(2,COLOR_BLUE,COLOR_WHITE);
	init_pair(3,COLOR_RED,COLOR_WHITE);
	curs_set(0);
	noecho(); 
	keypad(stdscr, TRUE);
	options(list, highlight_index);  
	while (1)
	{
		key=getch();
		if (key==KEY_UP)
		{
			highlight_index--;
			if (highlight_index<0)
			{
				highlight_index=list->length_list-1;
			}
			clear();
			refresh();
			options(list, highlight_index);
		}	
		else if (key==KEY_DOWN)
		{
			highlight_index++;
			if (highlight_index>list->length_list-1)
			{
				highlight_index=0;
			}
			clear();
			refresh();
			options(list, highlight_index);
		}		
		else if (key==KEY_BACKSPACE)
		{
			keypad(stdscr, FALSE); 
			break;
		}
	}
	endwin();
}

int main()
{
	List list; list.length_list=0;
	DIR* rep=NULL; dirent* file=NULL;
	char *delete;
	
	rep=opendir(".");
	while ((file=readdir(rep))!=NULL)
	{
		delete = (char*) memchr (file->d_name, '~', strlen(file->d_name));
		if (strcmp (file->d_name,"..") != 0 && strcmp (file->d_name,".") != 0 && delete==NULL)
		{
			printf("%s", file->d_name);
		}
	}
	
  initoption(&list);
  waitchoice(&list);
  
  

  return 0;
}
