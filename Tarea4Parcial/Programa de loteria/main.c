#include <stdio.h>
// creando menu interactivo de mi loreria

const int MAX = 100;
int main()
{
    int OPCION, CANTIDAD = 0;// validacion yconf cantidad de jugadas

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
                    printf("\n(Captura de jugadas pendiente)\n");
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
