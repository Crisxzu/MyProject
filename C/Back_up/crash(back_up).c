#include <stdio.h>
#include <stdlib.h>

void exchange(int *table, int i); 
void tribulle(int *tab, int length); 
int findIndexToInsert(int *tab, int *tabx, int length);
void shiftRightAt(int index, int length, int *tab, int *tabx);

void exchange(int *table, int i)
{
  double x, y;
  x=table[i+1]; y=table[i];
  table[i]=x; table[i+1]=y;
}

/*int findmin(double *winrate, Base *a)
{
  double min; int i=0, index_min;
  min=winrate[i], index_min=0;
  for(i=1; i<a->numword; i++)
  {
    if((int)winrate[i]<(int)min)
    {
      min=winrate[i];
      index_min=i;
    }
  }
  winrate[index_min]=900;
  i=0;
  min=winrate[i], index_min=0;
  for(i=1; i<a->numword; i++)
  {
    if((int)winrate[i]<(int)min)
    {
      min=winrate[i];
      index_min=i;
    }
  }
  return index_min;
}
int lastword(double *winrate, Base *a)
{
  double min, index_min; int i=0;
   min=winrate[i]; index_min=0;
  for(i=1; i<a->numword; i++)
  {
    if((int)winrate[i]<(int)min)
    {
      min=winrate[i];
      index_min=i;
    }
  }
  return index_min;
}*/

void tribulle(int *tab, int length)
{
   int i=0, borne=length;
   int tri=0; 
   while(tri==0)
   {
      tri=1;
      while(i<=borne-1)
      {
        if(tab[i]>tab[i+1])
        {
          exchange(&*tab, i);
          tri=0;
        }
        i++;
      }
      borne=borne-1;i=0;
   }
}

int findIndexToInsert(int *tab, int *tabx, int length)
{
  int i=length-1, j=0;
  while(j==0)
  {
      if(tabx[0]<tab[i])
      {
        i--;
      }
      else
      {
        i++;
        j++;
      }
  }
  if(i<0)
  {
    i=0;
  }
  return i;
}

void shiftRightAt(int index, int length, int *tab, int *tabx)
{
  int j=length-1; 
  while(j!=index)
  {
    tab[j]=tab[j-1];
    j--;
  }
  tab[j]=tabx[0];
}
int main()
{
  int length=5, tab[length], tabx[5], i=0, index; tabx[0]=1;
  tab[0]=85; tab[1]=56; tab[2]=90; tab[3]=1; tab[4]=74;
  tribulle(tab, length);
  while(i<length)
  {
    printf("Index=%d, Valeur=%d\n", i, tab[i]);
    i++;
  }
  i=0;
  index=findIndexToInsert(tab, tabx, length);
  if(index<length)
  {
   shiftRightAt(index, length, tab, tabx );
  }
  while(i<length)
  {
    printf("Index=%d, Valeur=%d\n", i, tab[i]);
    i++;
  }
  return 0;
}
