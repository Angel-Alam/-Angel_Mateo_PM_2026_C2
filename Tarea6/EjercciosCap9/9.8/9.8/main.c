#include <stdio.h>

typedef struct
{
    int matricula;
    char nombre[20];
    int carrera;
    float promedio;
} alumno;

void escribe(FILE *);

int main(void)
{
    FILE *ar;

    if ((ar = fopen("ad1.dat", "wb")) != NULL)
    {
        escribe(ar);
        fclose(ar);
    }
    else
    {
        printf("\nEl archivo no se puede abrir\n");
    }

    return 0;
}

void escribe(FILE *ap)
{
    alumno alu;
    int i = 0, r;

    printf("\nDesea ingresar informacion sobre alumnos? (Si-1  No-0): ");
    scanf("%d", &r);

    while (r)
    {
        i++;
        printf("Matricula del alumno %d: ", i);
        scanf("%d", &alu.matricula);

        printf("Nombre del alumno %d: ", i);
        fflush(stdin);
        gets(alu.nombre);

        printf("Carrera del alumno %d: ", i);
        scanf("%d", &alu.carrera);

        printf("Promedio del alumno %d: ", i);
        scanf("%f", &alu.promedio);

        fwrite(&alu, sizeof(alumno), 1, ap);

        printf("\nDesea ingresar informacion sobre mas alumnos? (Si-1 No-0): ");
        scanf("%d", &r);
    }
}
