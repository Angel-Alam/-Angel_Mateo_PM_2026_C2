#include <stdio.h>

void f1(void);
int K = 5;

int main(void)
{
    int I;
    for (I = 1; I <= 3; I++)
    {
        f1();
    }
    return 0;
}

void f1(void)
{
    int K = 2;
    K += K;

    printf("\n\nEl valor de la variable local es: %d", K);

    ::K = ::K + K;

    printf("\nEl valor de la variable global es: %d", ::K);
}
