#include <stdio.h>


void moverTorre(int n, char origen, char destino, char auxiliar, FILE *archivo, int *movimiento)
{
    //  si solo hay 1 disco
    if (n == 1)
    {
        (*movimiento)++;

        fprintf(archivo, "Movimiento %d: Mover disco de la torre %c a la torre %c\n", *movimiento, origen, destino);

        printf("Movimiento %d: Mover disco de la torre %c a la torre %c\n", *movimiento, origen, destino);
        return;
    }


    moverTorre(n - 1, origen, auxiliar, destino, archivo, movimiento);


    (*movimiento)++;
    fprintf(archivo, "Movimiento %d: Mover disco de la torre %c a la torre %c\n", *movimiento, origen, destino);
    printf("Movimiento %d: Mover disco de la torre %c a la torre %c\n", *movimiento, origen, destino);


    moverTorre(n - 1, auxiliar, destino, origen, archivo, movimiento);
}

int main(void)
{
    int numDiscos;
    int contador = 0;
    FILE *archivo;

    printf("=================================\n");
    printf("        TORRES DE HANOI          \n");
    printf("=================================\n\n");

    printf("Ingresa la cantidad de discos: ");
    scanf("%d", &numDiscos);


    archivo = fopen("solucion_hanoi.txt", "w");

    if (archivo == NULL)
    {
        printf("Error: No se pudo crear el archivo de texto.\n");
        return 1;
    }

    printf("\nCalculando movimientos...\n\n");


    moverTorre(numDiscos, 'A', 'C', 'B', archivo, &contador);

    printf("\n¡Rompecabezas resuelto!\n");
    printf("Los %d movimientos exactos han sido guardados en el archivo 'solucion_hanoi.txt'\n", contador);

    fclose(archivo);

    return 0;
}
