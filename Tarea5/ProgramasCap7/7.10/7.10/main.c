#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char c, cad[10];
    int i = 0;
    float sum = 0.0;

    printf("\nDesea ingresar una cadena de caracteres (S/N)? ");
    c = getchar();

    while (c == 'S' || c == 's')
    {
        printf("\nIngrese la cadena de caracteres: ");
        fflush(stdin);
        gets(cad);

        i++;
        sum += atof(cad);

        printf("\nDesea ingresar otra cadena de caracteres (S/N)? ");
        c = getchar();
    }

    printf("\nSuma: %.2f", sum);

    if (i > 0)
    {
        printf("\nPromedio: %.2f\n", sum / i);
    }
    else
    {
        printf("\nPromedio: 0.00\n");
    }

    return 0;
}
