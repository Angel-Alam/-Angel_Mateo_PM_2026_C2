#include <stdio.h>

int cubo(int);

int main(void)
{
    int I;

    for (I = 1; I <= 10; I++)
    {
        printf("\nEl cubo de %d es: %d", I, cubo(I));
    }

    return 0;
}

int cubo(int K)
{
    return (K * K * K);
}
