#include <stdio.h>
#include <string.h>

typedef struct
{
    char mat[20];
    int pro;
} matpro;

typedef struct
{
    int matri;
    char nom[20];
    matpro cal[5];
} alumno;

void Lectura(alumno *, int);
void F1(alumno *, int);
void F2(alumno *, int);
void F3(alumno *, int);

int main(void)
{
    alumno ALU[50];
    int TAM;

    do
    {
        printf("Ingrese el tamano del arreglo: ");
        scanf("%d", &TAM);
    }
    while (TAM > 50 || TAM < 1);

    Lectura(ALU, TAM);
    F1(ALU, TAM);
    F2(ALU, TAM);
    F3(ALU, TAM);

    return 0;
}

void Lectura(alumno A[], int T)
{
    int I, J;

    for (I = 0; I < T; I++)
    {
        printf("\nIngrese la matricula del alumno %d: ", I + 1);
        scanf("%d", &A[I].matri);
        fflush(stdin);

        printf("Ingrese el nombre del alumno %d: ", I + 1);
        gets(A[I].nom);

        for (J = 0; J < 5; J++)
        {
            printf("\tIngrese el nombre de la materia %d: ", J + 1);
            fflush(stdin);
            gets(A[I].cal[J].mat);

            printf("\tIngrese el promedio de %s: ", A[I].cal[J].mat);
            scanf("%d", &A[I].cal[J].pro);
        }
    }
}

void F1(alumno A[], int T)
{
    int I, J;
    float SUM;

    for (I = 0; I < T; I++)
    {
        SUM = 0.0;

        for (J = 0; J < 5; J++)
        {
            SUM += A[I].cal[J].pro;
        }

        printf("\nPromedio general del alumno %d (%s): %.2f", A[I].matri, A[I].nom, SUM / 5.0);
    }
    printf("\n");
}

void F2(alumno A[], int T)
{
    int I;

    printf("\nAlumnos con calificacion en la tercera materia > 9");

    for (I = 0; I < T; I++)
    {
        if (A[I].cal[2].pro > 9)
        {
            printf("\nMatricula del alumno : %d", A[I].matri);
        }
    }
    printf("\n");
}

void F3(alumno A[], int T)
{
    int I;
    float SUM = 0.0;

    for (I = 0; I < T; I++)
    {
        SUM += A[I].cal[3].pro;
    }

    printf("\nPromedio general de la cuarta materia: %.2f\n", SUM / T);
}
