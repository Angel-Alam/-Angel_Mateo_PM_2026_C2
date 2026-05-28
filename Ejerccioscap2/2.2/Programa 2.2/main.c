#include <stdio.h>
#include <stdlib.h>
/* Incremento de precio
El programa al recibir como dato el precio de un producto importado,
 11% el mismo si éste es inferior a $1,500.
PRE y NPR: variable de tipo real. */

void main(void)
{
    float PRE, NPR;

    printf("\ningrese el precio del producto:");
    scanf("%f",&PRE);
    /*me di cuenta que dice que suma un 11% si el producto es inferior pero
    en el codigo esta puesto como > mayor a 1500 se puede corregir cambiando
      a < menor que* pa cumplir con la logica que dice*/
    if (PRE < 1500)
    {
        NPR = PRE * 1.11;
        printf("\nNuevo precio: %7.2f",NPR);
    }

}
