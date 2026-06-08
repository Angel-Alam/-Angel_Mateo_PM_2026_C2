#include <stdio.h>
// creando menu interactivo de mi loreria
int main()
{
    int OPCION;

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
                printf("\n(Logica de juego pendiente)\n");
                break;
            case 2:
                printf("\n(Logica de cantidad pendiente)\n");
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
