#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int T, P, N;

    printf("\nINGRESE LOS VALORES DE T, P y N (separados por espacios): ");
    scanf("%d %d %d", &T, &P, &N);


    if (P != 0)
    {

        if (pow((double)T / P, N) == (pow(T, N) / pow(P, N)))
        {
            printf("\nSe comprueba la igualdad\n");
        }
        else
        {
            printf("\nNo se comprueba la igualdad\n");
        }
    }
    else
    {

        printf("\nP tiene que ser diferente de cero\n");
    }

    return 0;
}
