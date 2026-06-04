#include <stdio.h>

int cubo(void);
int I;

int main(void)
{
    int CUB;

    for (I = 1; I <= 10; I++)
    {
        CUB = cubo();
        printf("\nEl cubo de %d es: %d", I, CUB);
    }

    return 0;
}

int cubo(void)
{
    return (I * I * I);
}
