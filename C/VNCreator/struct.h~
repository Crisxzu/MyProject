#ifndef DEF_STRUCT
#define DEF_STRUCT

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
	char* background;
	char* profile_picture;
	char* character_name;
};
#define TRUE 1
#define FALSE 0

#endif

