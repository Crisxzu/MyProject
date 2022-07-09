#ifndef DEF_PENDUMODEL
#define DEF_PENDUMODEL

#include "struct.h"
#include <time.h>

void intwords(Secretwords *secretwords);
int selectword(Secretwords *secretwords);
void check(char *entry, Secretwords *secretwords, const int wordchoosen);

#endif

