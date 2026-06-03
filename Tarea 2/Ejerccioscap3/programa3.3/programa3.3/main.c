#include <stdio.h>
#include <stdlib.h>


int main()
{
    float PAG, SPA;
    SPA = 0;
    printf("Ingrese el primer pago:\t");
    scanf("%f", &PAG);

    while (PAG != 0)
    {
        SPA = SPA + PAG;
        printf("Ingrese el siguiente pago:\t ");
        scanf("%f", &PAG);
    }

    printf("\nEl total de pagos del mes es: %.2f\n", SPA);

    return 0;
}
