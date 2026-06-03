#include <stdio.h>
#include <stdlib.h>

/*promedio curso
El programa al recibir como dato el promedio de un alumno en un curso
universitario, escribe aprobado si su promedio es mayor o igual a 6.*/

void main (void)
{
    float PRO;
    printf ("igrese el promedio del alumno:");
    scanf("%f", &PRO);
    if (PRO >= 6)
        printf("\nAprobado");
    /* le agregre esta parte luego de probar el ejerccio del libro, tambien podria hacerse asi*/
    else
    {

        if (PRO <= 6)
            printf("\nReprobado");

    }

}
