#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ctoi(char number_);
int main()
{
    FILE *archivo;
    char linea[100];
    archivo = fopen("test.txt", "r");


    while (fgets(linea, 100, (FILE*) archivo))
    {
        printf("%s", linea);
    }
    

}

int ctoi(char n)
{
    return n;
}
