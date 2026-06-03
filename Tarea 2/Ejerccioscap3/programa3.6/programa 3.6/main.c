#include <stdio.h>

int main()
{
    int I = 0;
    float SAL, PRO, NOM = 0;
    printf("Ingrese el salario del profesor:\t");
    scanf("%f", &SAL);
    do
    {
        NOM = NOM + SAL;
        I = I + 1;
        printf("Ingrese el salario del profesor -0 para terminar- :\t");
        scanf("%f", &SAL);
    }
    while (SAL != 0);
    PRO = NOM / I;
    printf("\nNomina: %.2f \t Promedio de salarios: %.2f\n", NOM, PRO);

    return 0;
}
