
#include <stdio.h>
// comense  a agrgar Arreglos para almacenar numeros y montos de apuestas
const int MAX = 100;

int main(void)
{
    int OPCION, CANTIDAD = 0, I;
    int JUGADAS[MAX];
    float MONTOS[MAX];

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
                    printf("\n(Sorteo pendiente)\n");
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
