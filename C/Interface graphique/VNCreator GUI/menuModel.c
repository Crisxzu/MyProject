#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "menuModel.h"

	/*Modifie les valeurs par défaut qui se trouve en paramètres en fonction du choix de l'utilisateur.
	s = variable de la structure "Settings", données des paramètres.
	text_speed = int, vitesse de défilement du texte choisie par l'utiisateur.
	text_color = int, couleur de texte choisie par l'utiisateur.*/
void setSettings(Settings *s, const int text_speed, const int text_color)
{
	s->text_speed=text_speed;
	s->text_color=text_color;
}

	/*Initialise les paramètres(text_speed, text_color, flag_is_allocated et vn_folder_name) avec des valeurs par défaut.
	s = variable de la structure "Settings", données des paramètres.*/ 
void intSettings(Settings *s)
{
	s->text_speed=TEXT_SPEED_DEFAULT_VALUE;
	s->text_color=TEXT_COLOR_DEFAULT_VALUE;
	s->flag_is_allocated=FALSE;
	s->vn_folder_name=NULL;
}

	/*Initialise les différents du champ du menu list_vn. Il y aura des champs qui vont former une liste des différents Visual Novel présents dans le dossier "VN", un champ "Play", un champ "NewNV" et un champ "Retour".
	list_vn_menu = tableau de string ou char*, champs du menu list_vn.
	nb_champ_menu = nombre total de champ que le menu list_vn aura.*/
void initListVNMenu(char** list_vn_menu, int* nb_champ_menu)
{
	DIR* all_vn_directory=NULL; dirent* vn_folder=NULL;
	int i_box=0;
	
	all_vn_directory=opendir("VN/");
	
	//Repère dans le dossier "VN", un à un les différents dossiers présents(Les Visual Novel) et on note leur nom dans une case du tableau et cela tant qu'on a pas fini de lister tous les dossiers. Limite maximale de 100 Visual Novel.
	while ((vn_folder=readdir(all_vn_directory))!=NULL && i_box<NBMAX_VN-3)
	{
		//On ne note le nom du dossier que si celui-ci n'a pas pour nom "." et ".."
		if (strcmp (vn_folder->d_name,"..") != 0 && strcmp (vn_folder->d_name,".") != 0)
		{	
			list_vn_menu[i_box]=(char*) malloc(255);
			strcpy(list_vn_menu[i_box], vn_folder->d_name);
			i_box++;
		}
	}
	
	list_vn_menu[i_box]=(char*) malloc(255);
	strcpy(list_vn_menu[i_box], "_Play");
	i_box++;
	
	list_vn_menu[i_box]=(char*) malloc(255);
	strcpy(list_vn_menu[i_box], "_New VN");
	i_box++;
	
	list_vn_menu[i_box]=(char*) malloc(255);
	strcpy(list_vn_menu[i_box], "_Return");
	*nb_champ_menu=i_box+1;
	
	closedir(all_vn_directory), all_vn_directory=NULL, vn_folder=NULL;
}

	/*Crée un nouveau Visual Novel(concrètement un dossier qui va contenir les différentes éléments qui vont composer le Visual Novel). Au sein de celui-ci, un premier fichier texte nommé "0000.dia" sera créé, il represente le premier dialogue du Visual Novel qui sera créé où il y aura le nom du fichier qui va servir de décor, celui de la photo de profil du perso, le nom du perso et un dialogue test, un dossier "img" où seront entreposés les différents images dont on va se servir pour le décor(dossier background) et la photo du perso(dossier profilepic) des différents dialogues et un dossier "save" qui va contenir les sauvegardes des parties de l'utilisateur.
	new_vn_name_directory = char* ou string, emplacement du Visual Novel que l'utilisateur souhaite créer.*/
void createVN(const char* new_vn_name_directory)
{
	FILE *dia_file=NULL;
	char* directory_dia_file=(char*) malloc(255); char* directory_img_folder=(char*) malloc(255); char* directory_save_folder=(char*) malloc(255);
	
	mkdir( new_vn_name_directory, 0777 );
	
	sprintf(directory_img_folder, "%s/img", new_vn_name_directory);
	mkdir( directory_img_folder, 0777 );
	sprintf(directory_img_folder, "%s/img/background", new_vn_name_directory);
	mkdir( directory_img_folder, 0777 );
	sprintf(directory_img_folder, "%s/img/profilepic", new_vn_name_directory);
	mkdir( directory_img_folder, 0777 );
	
	sprintf(directory_save_folder, "%s/save", new_vn_name_directory);
	mkdir( directory_save_folder, 0777 );
	
	sprintf(directory_dia_file, "%s/0000.dia", new_vn_name_directory);
	dia_file=fopen(directory_dia_file, "w");
	fprintf(dia_file, "choice= 0 (goto) 0001\nbackground= Insérer le nom d'un fichier bac\nprofilepicture= Insérer le nom d'un fichier pp\ncharactername= Insérer le nom du personnage\ndialogue= Ecrire le dialogue ici\n\nFormat par défaut, veuillez modifier en fonction de vos besoins.(ce texte est à effacer)\nP.S = Le texte du dialogue ne doit pas avoir plus de 415 caractères");
	
	fclose(dia_file), dia_file=NULL;
	free(directory_dia_file), directory_dia_file=NULL;
	free(directory_img_folder), directory_img_folder=NULL;
	free(directory_save_folder), directory_save_folder=NULL;
}

void freeMenu(char** Menu, const int nb_champ_menu)
{
	int index=0;
	
	//Libère la mémoire RAM de chaque case une par une, pour chaque champ jusqu'à ce soit fait pour toutes les cases du tableau
	while (index<nb_champ_menu)
	{
		free(Menu[index]);
		Menu[index]=NULL;
		index++;
	}
}
