#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "menuView.h"
#include "menuControler.h"

	/*Affiche le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à afficher*/
void displayMenu(GtkWidget *menu_box)
{	
	gtk_widget_show_all(menu_box);
}

	/*Cache le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à cacher*/
void hideMenu(GtkWidget *menu_box)
{
	gtk_widget_hide(menu_box);
}

	/*Détruit le menu qui est entré en paramètres.
	menu_box = GtkWidget, menu à détruire*/
void destroyMenu(GtkWidget *menu_box)
{
	gtk_widget_destroy(menu_box);
}

	/*Permet de garder le menu affiché tant que l'utiisateur n'a pas appuyé sur un bouton du menu.*/
void waitInputMenu()
{ 	
 	//Permet de garder le menu affiché tant que l'utiisateur n'a pas appuyé sur un bouton du menu.
 	while (!__struct_global.b_isSelected)
 		gtk_main_iteration();
 	
 	__struct_global.b_isSelected=FALSE;	
}


	/*Permet à l'utilisateur d'entrer le nom du nouveau Visual Novel qu'il souhaite créer.
	new_vn_name_directory = char* ou string, emplacement du Visual Novel que l'utilisateur souhaite créer.*/
void enterNewVNname(char* new_vn_name_directory)
{
	const gchar* new_vn_name=NULL;
	GtkWidget *create_vn_dialog=NULL, *content_area_dialog=NULL, *entry_widget=NULL;
	
	//Crée une boîte de dialogue pour permettre à l'utiisateur d'entrer le nom du Visual qu'il veut créer
	create_vn_dialog=gtk_dialog_new_with_buttons("Entrez le nom du Visual Novel", GTK_WINDOW(__struct_global.main_window), GTK_DIALOG_MODAL, "Return", GTK_RESPONSE_CANCEL, "Create", GTK_RESPONSE_ACCEPT, NULL);
	entry_widget=gtk_entry_new();
	content_area_dialog=gtk_dialog_get_content_area(GTK_DIALOG(create_vn_dialog));
	gtk_container_add(GTK_CONTAINER(content_area_dialog), entry_widget);
	
	//Affiche cette boîte de dialogue
	gtk_widget_show_all(create_vn_dialog);
	
	//Si l'utiisateur a appuyé sur le bouton "Create"
	if (gtk_dialog_run(GTK_DIALOG(create_vn_dialog))==GTK_RESPONSE_ACCEPT)
	{
		new_vn_name=gtk_entry_get_text(GTK_ENTRY(entry_widget));
		
		//Si l'utiisateur a écrit quelque chose
		if(g_strcmp0(new_vn_name, "")!=0)
		{
			__struct_global.b_isSelected=TRUE;
			gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(__struct_global.list_vn_menu->combo_box_text), new_vn_name);
			sprintf(new_vn_name_directory, "VN/%s", new_vn_name);
			
		}
	}
	
	gtk_widget_destroy(create_vn_dialog);
}

	/*Initialise diverses éléments d'une structure global dont on aura besoin pour manipuler l'interface.*/
void initStructGlobal()
{	
	__struct_global.format_menu_label=(char*)malloc(255);
	__struct_global.format_text_color=(char*)malloc(255);
	__struct_global.format_character_name=(char*)malloc(255);
	__struct_global.format_dia_text=(char*) malloc(255);
	
	strcpy(__struct_global.format_menu_label, "<span foreground=\"black\" size=\"xx-large\" weight=\"ultrabold\">%s</span>");
	strcpy(__struct_global.format_text_color, "<span foreground=\"%s\">%s</span>");
	strcpy(__struct_global.format_character_name, "<span foreground=\"white\">%s</span>");
	strcpy(__struct_global.format_dia_text, "<span foreground=\"%s\">%c</span>");
}

	/*Initialise la Vue autrement dit l'interface.*/
void initView(int argc, char** argv)
{
	gtk_init(&argc, &argv);
}

	/*Initialise la fenêtre principale du programme.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initMainWindow(int *highlight_index)
{
	
	//Crée la fenêtre principale
	__struct_global.main_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(__struct_global.main_window), WINDOW_WIDTH, WINDOW_HEIGHT);
	gtk_window_set_title(GTK_WINDOW(__struct_global.main_window), "VNCreator");
	gtk_window_set_resizable (GTK_WINDOW(__struct_global.main_window), FALSE);
	
	//Crée la box qui va contenir les différents interfaces et l'insère dans la fenêtre
	__struct_global.main_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(__struct_global.main_window), __struct_global.main_box);
	
	//Connecte au bouton de fermeture une fonction
	g_signal_connect(G_OBJECT(__struct_global.main_window), "destroy", G_CALLBACK(quitIsSelected), highlight_index);
	
	gtk_widget_show_all(__struct_global.main_window);
}

	/*Initialise les différents champs du menu principal(un champ "Play", un champ "Options" et un champ "Quit").
	main_menu = tableau de string ou char*, champs du menu principal.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initMainMenu(char** main_menu, int *highlight_index)
{
	gchar *main_menu_label_str=NULL;
	__struct_global.main_menu=malloc(sizeof(Main_menu));
	
	main_menu[0]=(char*) malloc(255);
	main_menu[1]=(char*) malloc(255);
	main_menu[2]=(char*) malloc(255);
	
	//On initialise les champs du menu
	strcpy(main_menu[0], "_Play");
	strcpy(main_menu[1], "_Options");
	strcpy(main_menu[2], "_Quit");
	
	//Crée le label "Menu principal" du menu
	__struct_global.main_menu->label=gtk_label_new(NULL);
	main_menu_label_str=g_markup_printf_escaped(__struct_global.format_menu_label, "Menu Principal");
	gtk_label_set_markup(GTK_LABEL(__struct_global.main_menu->label), main_menu_label_str);
	g_free(main_menu_label_str), main_menu_label_str=NULL;
	
	//Crée la box qui va contenir les différents éléments du menu
	__struct_global.main_menu->box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_set_homogeneous(GTK_BOX(__struct_global.main_menu->box), FALSE);
	
	//Crée la box qui va contenir les boutons du menu
	__struct_global.main_menu->button_box=gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_box_set_spacing(GTK_BOX(__struct_global.main_menu->button_box), 10);
	
	//Crée les boutons du menu
	__struct_global.main_menu->play_button=gtk_button_new_with_mnemonic(main_menu[0]);
	__struct_global.main_menu->options_button=gtk_button_new_with_mnemonic(main_menu[1]);
	__struct_global.main_menu->quit_button=gtk_button_new_with_mnemonic(main_menu[2]);
	
	//Insère la box qui contenir les éléments du menu dans celle de la fenêtre principal
	gtk_box_pack_start(GTK_BOX(__struct_global.main_box), __struct_global.main_menu->box, TRUE, TRUE, 0);
	
	//Insère dans la box du menu le label et la box des boutons
	gtk_box_pack_start(GTK_BOX(__struct_global.main_menu->box), __struct_global.main_menu->label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.main_menu->box), __struct_global.main_menu->button_box, TRUE, FALSE, 0);
	
	//Insère dans la box des boutons les différents boutons du menu
	gtk_box_pack_start(GTK_BOX(__struct_global.main_menu->button_box), __struct_global.main_menu->play_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.main_menu->button_box), __struct_global.main_menu->options_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.main_menu->button_box), __struct_global.main_menu->quit_button, FALSE, FALSE, 0);
	
	//Connecte à chaque bouton du menu une fonction spécifique
	g_signal_connect(G_OBJECT(__struct_global.main_menu->play_button), "clicked", G_CALLBACK(playIsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.main_menu->options_button), "clicked", G_CALLBACK(optionsIsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.main_menu->quit_button), "clicked", G_CALLBACK(quitIsSelected), highlight_index);
	
}	

	/*Signale que l'utiisateur a appuyé sur le bouton "Play"*/
void playIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=0;
	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur le bouton "Options"*/
void optionsIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=1;
	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur le bouton "Quit"*/
void quitIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=2;
	
	(void)widget;
}

		/*Initialise les différents champs du menu des paramètres(un champ pour text_speed, un pour text_color et pour "Return").
	settings_menu = tableau de char* ou string, champs du menu des paramètres.
	text_speed = int, vitesse de défilement du texte des différents dialogues des Visual Novel, valeur modifiée en fonction des choix de l'utiisateur.
	text_color = int, couleur du texte des différents dialogues, valeur modifiée en fonction des choix de l'utiisateur.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initSettingsMenu(char** settings_menu, float *text_speed, int *text_color, int *highlight_index)
{
	char* color_name[6]={"white", "blue", "cyan", "red", "magenta", "yellow"};
	char text_speed_str[10];
	gchar *settings_menu_label_str=NULL, *text_color_value_str=NULL;
	__struct_global.settings_menu=malloc(sizeof(Settings_menu));
	
	settings_menu[0]=(char*) malloc(255);
	settings_menu[1]=(char*) malloc(255);
	settings_menu[2]=(char*) malloc(255);
	
	//Initialise les champs du menu
	strcpy(settings_menu[0], "Textspeed");
	strcpy(settings_menu[1], "Textcolor");
	strcpy(settings_menu[2], "_Return");
	
	//Crée le label "Paramètres" du menu
	__struct_global.settings_menu->label=gtk_label_new(NULL);
	settings_menu_label_str=g_markup_printf_escaped(__struct_global.format_menu_label, "Paramètres");
	gtk_label_set_markup(GTK_LABEL(__struct_global.settings_menu->label), settings_menu_label_str);
	g_free(settings_menu_label_str), settings_menu_label_str=NULL;
	
	//Crée le label "Textspeed" ainsi que celui qui affiche la valeur de text_speed choisie
	__struct_global.settings_menu->text_speed_label=gtk_label_new(settings_menu[0]);
	sprintf(text_speed_str, "%d", (int)*text_speed);
	__struct_global.settings_menu->text_speed_value_label=gtk_label_new(text_speed_str);
	
	//Crée le label "Textcolor" ainsi que celui qui va afficher le nom de couleur du texte choisie
	__struct_global.settings_menu->text_color_label=gtk_label_new(settings_menu[1]);
	text_color_value_str=g_markup_printf_escaped(__struct_global.format_text_color, color_name[*text_color], color_name[*text_color]);
	__struct_global.settings_menu->text_color_value_label=gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(__struct_global.settings_menu->text_color_value_label), text_color_value_str);
	g_free(text_color_value_str), text_color_value_str=NULL;
	
	//Crée la box qui va contenir les différents éléments du menu et la box qui va contenir les boutons
	__struct_global.settings_menu->box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_set_homogeneous(GTK_BOX(__struct_global.settings_menu->box), FALSE);
	__struct_global.settings_menu->button_box=gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_box_set_spacing(GTK_BOX(__struct_global.settings_menu->button_box), 10);
	
	//Crée la box qui va contenir les différents label concernant text_speed et les boutons
	__struct_global.settings_menu->text_speed_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_set_homogeneous(GTK_BOX(__struct_global.settings_menu->text_speed_box), TRUE);
	
	//Crée la box qui va contenir les différents label concernant text_color et les boutons
	__struct_global.settings_menu->text_color_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_set_homogeneous(GTK_BOX(__struct_global.settings_menu->text_color_box), TRUE);
	
	//Crée les boutons qui vont permettre de modifier la valeur de text_speed, de text_color et de revenir au menu principal
	__struct_global.settings_menu->text_speed_inc_button=gtk_button_new_with_label("+");
	__struct_global.settings_menu->text_color_inc_button=gtk_button_new_with_label("+");
	__struct_global.settings_menu->text_speed_dec_button=gtk_button_new_with_label("-");
	__struct_global.settings_menu->text_color_dec_button=gtk_button_new_with_label("-");
	__struct_global.settings_menu->return_button=gtk_button_new_with_mnemonic(settings_menu[2]);
	
	//Insère la box qui va contenir les éléments du menu dans celle de la fenêtre principale
	gtk_box_pack_start(GTK_BOX(__struct_global.main_box), __struct_global.settings_menu->box, TRUE, TRUE, 0);
	
	//Insère dans la box du menu le label et la box des boutons
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->box), __struct_global.settings_menu->label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->box), __struct_global.settings_menu->button_box, TRUE, FALSE, 0);
	
	//Insère dans la box des boutons la box de text_speed et de text_color et le bouton "Return"
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->button_box), __struct_global.settings_menu->text_speed_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->button_box), __struct_global.settings_menu->text_color_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->button_box), __struct_global.settings_menu->return_button, FALSE, FALSE, 0);
	
	//Insère dans la box de text_speed les labels et les boutons le concernant 
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->text_speed_box), __struct_global.settings_menu->text_speed_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->text_speed_box), __struct_global.settings_menu->text_speed_dec_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->text_speed_box), __struct_global.settings_menu->text_speed_value_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->text_speed_box), __struct_global.settings_menu->text_speed_inc_button, FALSE, FALSE, 0);
	
	//Insère dans la box de text_color les labels et les boutons le concernant
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->text_color_box), __struct_global.settings_menu->text_color_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->text_color_box), __struct_global.settings_menu->text_color_dec_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->text_color_box), __struct_global.settings_menu->text_color_value_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.settings_menu->text_color_box), __struct_global.settings_menu->text_color_inc_button, FALSE, FALSE, 0);
	
	//Connecte à chaque bouton du menu une fonction spécifique
	g_signal_connect(G_OBJECT(__struct_global.settings_menu->text_speed_inc_button), "clicked", G_CALLBACK(incTextSpeed), text_speed);
	g_signal_connect(G_OBJECT(__struct_global.settings_menu->text_speed_dec_button), "clicked", G_CALLBACK(decTextSpeed), text_speed);
	g_signal_connect(G_OBJECT(__struct_global.settings_menu->text_color_inc_button), "clicked", G_CALLBACK(incTextColor), text_color);
	g_signal_connect(G_OBJECT(__struct_global.settings_menu->text_color_dec_button), "clicked", G_CALLBACK(decTextColor), text_color);
	g_signal_connect(G_OBJECT(__struct_global.settings_menu->return_button), "clicked", G_CALLBACK(returnIsSelected), highlight_index);

}

	/*Augmente la valeur de text_speed*/
void incTextSpeed(GtkWidget *widget, gpointer user_data)
{
	float *text_speed=(float*)user_data;
	gchar text_speed_str[5];
	
	*text_speed=*text_speed+1;
	if (*text_speed>TEXT_SPEED_MAX)
	{
		*text_speed=TEXT_SPEED_MAX;
	}
	sprintf(text_speed_str, "%d", (int)*text_speed);
	gtk_label_set_text(GTK_LABEL(__struct_global.settings_menu->text_speed_value_label), text_speed_str);	
	(void)widget;
}

	/*Diminue la valeur de text_speed*/
void decTextSpeed(GtkWidget *widget, gpointer user_data)
{
	float *text_speed=(float*)user_data;
	gchar text_speed_str[5];
	
	*text_speed=*text_speed-1;
	if (*text_speed<TEXT_SPEED_MIN)
	{
		*text_speed=TEXT_SPEED_MIN;
	}
	sprintf(text_speed_str, "%d", (int)*text_speed);
	gtk_label_set_text(GTK_LABEL(__struct_global.settings_menu->text_speed_value_label), text_speed_str);	
	(void)widget;
}

	/*Augmente la valeur de text_color*/
void incTextColor(GtkWidget *widget, gpointer user_data)
{
	char* color_name[6]={"white", "blue", "cyan", "red", "magenta", "yellow"};
	int *text_color=(int*)user_data;
	gchar *text_color_value_str=NULL;
	
	*text_color=*text_color+1;
	if (*text_color>TEXT_COLOR_MAX)
	{
		*text_color=TEXT_COLOR_MAX;
	}
	text_color_value_str=g_markup_printf_escaped(__struct_global.format_text_color, color_name[*text_color], color_name[*text_color]);
	gtk_label_set_markup(GTK_LABEL(__struct_global.settings_menu->text_color_value_label), text_color_value_str);
	
	g_free(text_color_value_str), text_color_value_str=NULL;	
	(void)widget;
}

	/*Diminue la valeur de text_color*/
void decTextColor(GtkWidget *widget, gpointer user_data)
{
	char* color_name[6]={"white", "blue", "cyan", "red", "magenta", "yellow"};
	int *text_color=(int*)user_data;
	gchar *text_color_value_str=NULL;
	
	*text_color=*text_color-1;
	if (*text_color<TEXT_COLOR_MIN)
	{
		*text_color=TEXT_COLOR_MIN;
	}
	text_color_value_str=g_markup_printf_escaped(__struct_global.format_text_color, color_name[*text_color], color_name[*text_color]);
	gtk_label_set_markup(GTK_LABEL(__struct_global.settings_menu->text_color_value_label), text_color_value_str);
	
	g_free(text_color_value_str), text_color_value_str=NULL;	
	(void)widget;
}

	/*Signale que l'utiisateur a appuyé sur le bouton "Return"*/
void returnIsSelected(GtkWidget *widget, gpointer user_data)
{
	int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=2;
	
	(void)widget;
}

	/*Initialise la box du menu list_vn.
	list_vn_menu = tableau de string ou char*, champs du menu list_vn.
	nb_champ_menu = nombre total de champ que le menu list_vn aura.
	highlight_index = int, valeur modifiée en fonction du champ qui sera sélectionné par l'utilisateur pendant ses déplacements dans le menu.*/
void initListVNMenuBox(char **list_vn_menu, const int nb_champ_menu, int *highlight_index)
{
	__struct_global.list_vn_menu=malloc(sizeof(List_vn_menu));
	gchar *list_vn_menu_label_str=NULL;
	int i=0;
	
	//Crée le label "Choix de Visual Novel" du menu
	__struct_global.list_vn_menu->label=gtk_label_new(NULL);
	list_vn_menu_label_str=g_markup_printf_escaped(__struct_global.format_menu_label, "Choix de Visual Novel");
	gtk_label_set_markup(GTK_LABEL(__struct_global.list_vn_menu->label), list_vn_menu_label_str);
	g_free(list_vn_menu_label_str), list_vn_menu_label_str=NULL;
	
	//Crée la box qui va contenir les différents éléments du menu et la box qui va contenir les boutons
	__struct_global.list_vn_menu->box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	__struct_global.list_vn_menu->button_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_set_spacing(GTK_BOX(__struct_global.list_vn_menu->button_box), 10);
	
	//Crée la combo box qui va contenir la liste des différents visual novel présents
	__struct_global.list_vn_menu->combo_box_text=gtk_combo_box_text_new();
	
	//Insère dans la combo_box_text tous les champs de list_vn_menu hormis "Play", "New VN" et "Return"
	while (i<nb_champ_menu-3)
	{
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(__struct_global.list_vn_menu->combo_box_text), list_vn_menu[i]);
		i++;
	}
	
	//Crée les boutons du menu
	__struct_global.list_vn_menu->play_button=gtk_button_new_with_mnemonic(list_vn_menu[i]);
	__struct_global.list_vn_menu->create_vn_button=gtk_button_new_with_mnemonic(list_vn_menu[i+1]);
	__struct_global.list_vn_menu->return_button=gtk_button_new_with_mnemonic(list_vn_menu[i+2]);
	
	//Insère la box qui va contenir les éléments du menu dans celle de la fenêtre principale
	gtk_box_pack_start(GTK_BOX(__struct_global.main_box), __struct_global.list_vn_menu->box, TRUE, TRUE, 0);
	
	//Insère dans la box du menu le label et la box des boutons
	gtk_box_pack_start(GTK_BOX(__struct_global.list_vn_menu->box), __struct_global.list_vn_menu->label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.list_vn_menu->box), __struct_global.list_vn_menu->button_box, TRUE, FALSE, 0);
	
	//Insère dans la box des boutons les boutons du menu
	gtk_box_pack_start(GTK_BOX(__struct_global.list_vn_menu->button_box), __struct_global.list_vn_menu->combo_box_text, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.list_vn_menu->button_box), __struct_global.list_vn_menu->play_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.list_vn_menu->button_box), __struct_global.list_vn_menu->create_vn_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(__struct_global.list_vn_menu->button_box), __struct_global.list_vn_menu->return_button, FALSE, FALSE, 0);
	
	//Connecte à chaque bouton du menu une fonction spécifique
	g_signal_connect(G_OBJECT(__struct_global.list_vn_menu->combo_box_text), "changed", G_CALLBACK(vnIsSelected), NULL);
	g_signal_connect(G_OBJECT(__struct_global.list_vn_menu->play_button), "clicked", G_CALLBACK(playIsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.list_vn_menu->create_vn_button), "clicked", G_CALLBACK(createVNIsSelected), highlight_index);
	g_signal_connect(G_OBJECT(__struct_global.list_vn_menu->return_button), "clicked", G_CALLBACK(returnIsSelected), highlight_index);
}

	/*Signale que l'utiisateur a choisi un Visual Novel*/
void vnIsSelected(GtkWidget *widget, gpointer user_data)
{
	__struct_global.vn_isSelected=TRUE;
	
	(void)widget;
	(void)user_data;
}

	/*Signale que l'utiisateur a appuyé sur le bouton "create_vn"*/
void createVNIsSelected(GtkWidget *widget, gpointer user_data)
{
		int *highlight_index=(int*)user_data;
	
	__struct_global.b_isSelected=TRUE;
	*highlight_index=1;
	
	(void)widget;
}
