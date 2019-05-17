#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ctoi(char number_);
int main()
{
    char posicion[3];
    int j, i;

    int orden = scanf("%s", &posicion);

    while (orden == 0)
    {
        printf("La posicion debe ser del tipo LETRA-NUMERO (Ejemplo: A2, F5): ");
        fflush(stdin);
        orden = scanf("%s", &posicion);
    }
    j = ctoi(posicion[0]) - 97;
    i = atoi(&posicion[1])-1;
    printf("%d", j);
    return j;
}

int ctoi(char n)
{

    return tolower(n);
}
