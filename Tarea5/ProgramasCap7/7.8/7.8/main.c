#include <stdio.h>
#include <ctype.h>

void minymay(char *cad);

int main(void)
{
    int i, n;
    char FRA[20][50];

    printf("Ingrese el numero de filas del arreglo: ");
    scanf("%d", &n);
    fflush(stdin);

    for (i = 0; i < n; i++)
    {
        printf("Ingrese la cadena %d: ", i + 1);
        gets(FRA[i]);
    }

    printf("\n--- RESULTADOS ---");
    for (i = 0; i < n; i++)
    {
        printf("\nCadena %d: %s", i + 1, FRA[i]);
        minymay(FRA[i]);
    }

    printf("\n");
    return 0;
}

void minymay(char *cad)
{
    int i = 0, mi = 0, ma = 0;

    while (cad[i] != '\0')
    {
        if (islower(cad[i]))
        {
            mi++;
        }
        else if (isupper(cad[i]))
        {
            ma++;
        }
        i++;
    }

    printf("\nMinusculas: %d \t Mayusculas: %d\n", mi, ma);
}
