#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int MAT, CAR, SEM;
    float PRO;
    printf("ingrse la matricula");
    scanf("%d", &MAT);
    printf("ingrse la carrera(1-industrial 2- telematrica 3-computacion 4-mecanica):");
    scanf("%d", &CAR);
    printf("Ingrese semestre:");
    scanf("%d", &SEM);
    printf("ingrese promedio:");
    scanf("%f", &PRO);
    switch(CAR)
    {
        case 1: if(SEM >= 6 && PRO >= 8.5)
        printf("\n%d %d %5.2f", MAT, CAR, PRO);
        break;
         case 2: if(SEM >= 5 && PRO >= 9.0)
        printf("\n%d %d %5.2f", MAT, CAR, PRO);
        break;
         case 3: if(SEM >= 6 && PRO >= 8.8)
        printf("\n%d %d %5.2f", MAT, CAR, PRO);
        break;
         case 4: if(SEM >= 7 && PRO >= 9.0)
        printf("\n%d %d %5.2f", MAT, CAR, PRO);
        break;
        default: printf("\n error en la carrera");
        break;
    }
    return 0;
}
