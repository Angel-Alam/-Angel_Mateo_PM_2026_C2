#include <stdio.h>

int cuenta(char *, char);

int main(void)
{
    char car, cad[50];
    int res;

    printf("Ingrese la cadena de caracteres: ");
    gets(cad);

    fflush(stdin);

    printf("Ingrese el caracter a buscar: ");
    car = getchar();

    res = cuenta(cad, car);

    printf("\n\nEl caracter '%c' se encuentra %d veces en la cadena \"%s\"\n", car, res, cad);

    return 0;
}

int cuenta(char *cad, char car)
{
    int i = 0, r = 0;

    while (cad[i] != '\0')
    {
        if (cad[i] == car)
        {
            r++;
        }
        i++;
    }

    return r;
}
