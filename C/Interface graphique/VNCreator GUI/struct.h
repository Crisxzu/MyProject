#ifndef DEF_STRUCT
#define DEF_STRUCT

#include <gtk/gtk.h>
#define WINDOW_WIDTH 786
#define WINDOW_HEIGHT 533
#define PROFILE_PIC_WIDTH 70
#define PROFILE_PIC_HEIGHT 70
#define TEXT_SPEED_MAX 10
#define TEXT_SPEED_MIN 1
#define TEXT_COLOR_MAX 5
#define TEXT_COLOR_MIN 0
#define TEXT_SPEED_DEFAULT_VALUE 5
#define TEXT_COLOR_DEFAULT_VALUE 0
#define NB_CHAMP_LOADGAME_MENU 6
typedef enum myColor MyColor;
enum MyColor
{
	White, Blue, Cyan, Red, Magenta, Yellow
};
typedef struct Settings Settings;
struct Settings
{
  float text_speed;
  enum MyColor text_color;
  char* vn_folder_name;
  int flag_is_allocated; // int qui permet de savoir si la variable vn_folder_name a reçu un malloc
};
typedef struct Dialogue Dialogue;
struct Dialogue
{
	int length_currentRoute; //taille de la route suivie par l'utiisateur. Route = Tableau ordonné de tous les noms des fichiers dia
	int i_currentBranch; //index du dialogue dans une branche. Branche = Nombre de fichiers dia parcouru depuis le dernier embranchement
	char* dia_text;
	GdkPixbuf *background_pixbuf;
	GdkPixbuf *profile_picture_pixbuf;
	char* character_name;
};

typedef struct
{
	/* Interface*/
	GtkWidget *overlay_container_for_background; //Placé en fond, contenant le background
	GtkWidget *background;
	GtkWidget *paned; //Placé au dessus l'overlay contenant le background afin de permettre de bien positionner d'un côté la box qui afficher la profile_pic et le character_name et de l'autre le text_view
	
	/*Elements de la première partie du paned*/
	GtkWidget *overlay_container_for_box; //Placé en haut
	GtkWidget *box; //Placé au dessus pour contenir la profile_pic et le character_name
	GtkWidget *profile_pic;
	GtkWidget *character_name;
	GtkWidget *character_name_label;
	
	/*Elements de la deuxième partie du paned*/
	GtkWidget *text_view; //Placé en bas
	GtkTextBuffer *text_buffer;
	GtkWidget *button_box; //Placé au dessus du text_view
	
	/*Elements de la button_box*/
	GtkWidget *edit_button, *add_image_button, *save_button;
	
	/*Pour assurer la liaison avec les touches du clavier*/
	GtkAccelGroup *accel_group;
}Vn_view;

typedef struct
{
	/* Menu de chargement de partie */
	GtkWidget *dialog;
	
	/*Elements du menu*/
	GtkWidget *content_area, *button[NB_CHAMP_LOADGAME_MENU];
}Dialog_menu;

typedef struct
{
	/*Menu In Game*/
	GtkWidget *box;
	
	/*Elements du menu*/
	GtkWidget *label;  
	GtkWidget *button_box;
	
	/*Elements de la button_box du menu*/ 
	GtkWidget *newgame_button, *loadgame_button, *return_button;
}Menu_ingame;

typedef struct
{
	/*Menu de choix de Visual Novel à jouer*/
	GtkWidget *box;
	
	/*Elements du menu*/
	GtkWidget *label; 
	GtkWidget *button_box;
	
	/*Elements de la button_box du menu*/
	GtkWidget *combo_box_text, *play_button, *create_vn_button, *return_button;
}List_vn_menu;

typedef struct
{
	/*Menu des paramètres*/
	GtkWidget *box;
	
	/*Elements du menu*/
	GtkWidget *label; 
	GtkWidget *button_box;
	
	/*Elements de la button_box du menu*/ 
	GtkWidget *text_speed_box, *text_color_box;
	GtkWidget *return_button;
	
	/*Elements de la text_speed_box*/ 
	GtkWidget *text_speed_label, *text_speed_value_label;
	GtkWidget *text_speed_inc_button, *text_speed_dec_button;
	
	/*Elements de la text_color_box*/
	GtkWidget *text_color_label, *text_color_value_label;
	GtkWidget *text_color_dec_button, *text_color_inc_button;

}Settings_menu;

typedef struct
{
	/*Menu principal*/
	GtkWidget *box;
	
	/*Elements du menu*/
	GtkWidget *label;  
	GtkWidget *button_box;
	
	/*Elements de la button_box du menu*/ 
	GtkWidget *play_button, *options_button, *quit_button;
}Main_menu;


typedef struct
{
	gboolean f_window_is_already_created;
	gboolean f_image_is_loaded;
	char *format_menu_label;
	gboolean b_isSelected;
	gboolean vn_isSelected;
	gboolean slot_isSelected;
	gboolean f_choice_is_made;
	char *format_text_color;
	char *format_character_name;
	char *format_dia_text;
	
	/*Fenêtre principale*/
	GtkWidget *main_window;
	GtkWidget *main_box;
	
	/*Menu Principal*/
	Main_menu *main_menu;
	
	/*Menu des paramètres*/
	Settings_menu *settings_menu;
	
	/*Menu de choix de Visual Novel à jouer*/
	List_vn_menu *list_vn_menu;
	
	/*Menu In Game*/
	Menu_ingame *menu_ingame;
	
	/*Boite de dialogue*/
	Dialog_menu *dialog_menu;
	
	/*Interface qui va afficher les dialogues*/
	Vn_view *vn_view;
}struct_global;

extern struct_global __struct_global;

#endif

