#include <stdio.h>
#include <string.h>

typedef struct
{
    int clave;
    char nombre[15];
    float precio;
    int existencia;
} producto;

void Lectura(producto *, int);
void Ventas(producto *, int);
void Reabastecimiento(producto *, int);
void Nuevos_Productos(producto *, int *);
void Inventario(producto *, int);

int main(void)
{
    producto INV[100];
    int TAM, OPE;

    do
    {
        printf("Ingrese el numero de productos: ");
        scanf("%d", &TAM);
    }
    while (TAM > 100 || TAM < 1);

    Lectura(INV, TAM);

    printf("\nIngrese operacion a realizar.\n\t\t1 - Ventas\n\t\t2 - Reabastecimiento\n\t\t3 - Nuevos Productos\n\t\t4 - Inventario\n\t\t0 - Salir: ");
    scanf("%d", &OPE);

    while (OPE)
    {
        switch (OPE)
        {
            case 1:
                Ventas(INV, TAM);
                break;
            case 2:
                Reabastecimiento(INV, TAM);
                break;
