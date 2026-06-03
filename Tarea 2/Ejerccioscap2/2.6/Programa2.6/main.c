#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float SAL;
    int NIV;
    printf("ingrese el nivel academico del profesor:");
    scanf("%d", &NIV);
    printf("Ingrese salario:");
    scanf("%f", &SAL);
    switch(NIV)
    {
        case 1: SAL = SAL * 1.0035; break;
        case 2: SAL = SAL * 1.0035; break;
        case 3: SAL = SAL * 1.0035; break;
        case 4: SAL = SAL * 1.0035; break;
    }
    printf("\nNivel: %d \tNuevo salario: %8.2f",NIV, SAL);
    return 0;
}
