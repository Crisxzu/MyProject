#ifndef DEF_GRILLE
#define DEF_GRILLE

#define NBMAX_LIGNE 15
#define NBMAX_CASE 15
#define ENTER 10
void initInterface();
void waitinputgrille(int *highlight_x, int *highlight_y, int *input, char (*grille)[NBMAX_CASE]);
void intgrille(char (*grille)[NBMAX_CASE]);
void display(char (*grille)[NBMAX_CASE], const int highlight_x, const int highlight_y);

#endif

