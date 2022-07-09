#include <stdio.h>

int main()
{
    FILE * f;
    f=fopen("hello.txt", "wb");
    if(f !=NULL)
    {
       fprintf(f, "Hello, world\n");
       fclose(f);
    }
    else
    {
       perror("hello.txt");
    }
    return 0;
}
