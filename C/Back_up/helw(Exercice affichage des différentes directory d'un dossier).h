#ifndef DEF_HELW
#define DEF_HELW

typedef struct dirent dirent;
typedef struct List List;
typedef struct CaseList CaseList;
struct List
{
	int length_list;
	CaseList *first;
};
struct CaseList
{
	char* option_name;
	CaseList *next;
};
typedef struct List List;
struct List
{
	int length_list;
	char* newvn; 
	CaseList *firstcase;
};
typedef struct CaseList CaseList;
struct CaseList
{
	char* vn_name;
	CaseList *nextcase;
};
#define ENTER 10

#endif

