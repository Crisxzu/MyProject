#ifndef DEF_HELW
#define DEF_HELW

typedef struct Dialogue Dialogue;
struct Dialogue
{
	int index_dia;
	char* diatext;
	char* background;
	char* profilepicture;
	char* charactername;
};

#define ENTER 10
#define TRUE 1
#define FALSE 0

#endif

