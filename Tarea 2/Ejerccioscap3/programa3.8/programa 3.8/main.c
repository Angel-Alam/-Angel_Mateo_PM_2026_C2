#include <stdio.h>

int main(void)
{
    int I, NUM;
    long FAC;
    printf("\nIngrese el numero: ");
    scanf("%d", &NUM);
    if (NUM >= 0)
    {
        FAC = 1;

        for (I = 1; I <= NUM; I++)
        {
            FAC *= I;
        }

        printf("\nEl factorial de %d es: %ld\n", NUM, FAC);
    }
    else
    {
        printf("\nError: No se puede calcular el factorial de un numero negativo.\n");
    }

    return 0;
}
