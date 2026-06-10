#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// puse libreria de time para la logica final de numeros aleatorios
//y calcular lo premio
const int MAX = 100;

int main(void)
{
    int OPCION, CANTIDAD = 0, I, GANADOR; // validacion yconf cantidad de jugadas
    int JUGADAS[MAX];
    float MONTOS[MAX], PREMIO_TOTAL;

    srand(time(NULL));
// creando menu interactivo de mi loreria
    do
    {
        printf("\n--- MENU DE LOTERIA ---\n");
        printf("1. Jugar\n");
        printf("2. Elegir cantidad de jugadas\n");
        printf("3. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &OPCION);

        switch (OPCION)
        {
            case 1:
                if (CANTIDAD == 0)
                {
                    printf("\nPrimero debe elegir la cantidad de jugadas en la opcion 2.\n");
                }
                else
                {
                    for (I = 0; I < CANTIDAD; I++)
                    {
                        do
                        {
                            printf("\nJugada %d - Ingrese el numero a jugar (1 a 40): ", I + 1);
                            scanf("%d", &JUGADAS[I]);
                        }
                        while (JUGADAS[I] < 1 || JUGADAS[I] > 40);

                        do
                        {
                            printf("Ingrese la cantidad de dinero a jugar: ");
                            scanf("%f", &MONTOS[I]);
                        }
                        while (MONTOS[I] <= 0);
                    }

                    GANADOR = (rand() % 40) + 1;
                    printf("\n*** SORTEO ***\n");
                    printf("El numero ganador de la loteria es: %d\n", GANADOR);

                    PREMIO_TOTAL = 0.0;

                    for (I = 0; I < CANTIDAD; I++)
                    {
                        if (JUGADAS[I] == GANADOR)
                        {
                            printf("\n¡Felicidades! Acertaste en la jugada %d.", I + 1);
                            PREMIO_TOTAL += (MONTOS[I] * 1000.0);
                        }
                    }

                    if (PREMIO_TOTAL > 0)
                    {
                        printf("\nEl premio total ganado es: %.2f\n", PREMIO_TOTAL);
                    }
                    else
                    {
                        printf("\nNo hubo suerte esta vez. Sigue intentando.\n");
                    }

                    CANTIDAD = 0;
                }
                break;

            case 2:
                do
                {
                    printf("\nIngrese la cantidad de jugadas que desea realizar: ");
                    scanf("%d", &CANTIDAD);
                }
                while (CANTIDAD < 1 || CANTIDAD > MAX);

                printf("Cantidad de jugadas configurada a %d.\n", CANTIDAD);
                break;

            case 3:
                printf("\nSaliendo del programa...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                break;
        }
    }
    while (OPCION != 3);

    return 0;
}
