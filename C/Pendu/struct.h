#ifndef DEF_STRUCT
#define DEF_STRUCT

typedef struct Secretwords Secretwords;
struct Secretwords
{
	int length_word;
	int success;
	int win[30];
	char word[30];
};
#define TRUE 1
#define FALSE 0
#endif

