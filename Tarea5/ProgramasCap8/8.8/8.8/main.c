#include <stdio.h>
#include <string.h>

typedef struct
{
    char cal[20];
    int num;
    char col[20];
    char cp[5];
    char ciu[20];
} domicilio;

typedef struct
{
    char nom[20];
    int edad;
    char sexo;
    int con;
    domicilio dom;
    char tel[10];
} paciente;

void Lectura(paciente *, int);
void F1(paciente *, int);
void F2(paciente *, int);
void F3(paciente *, int);

int main(void)
{
    paciente HOSPITAL[100];
    int TAM;

    do
    {
        printf("Ingrese el numero de pacientes (1-50): ");
        scanf("%d", &TAM);
    }
    while (TAM > 50 || TAM < 1);

    Lectura(HOSPITAL, TAM);
    F1(HOSPITAL, TAM);
    F2(HOSPITAL, TAM);
    F3(HOSPITAL, TAM);

    return 0;
}

void Lectura(paciente A[], int T)
{
    int I;

    for (I = 0; I < T; I++)
    {
        printf("\n\t\tPaciente %d\n", I + 1);
        fflush(stdin);

        printf("Nombre: ");
        gets(A[I].nom);

        printf("Edad: ");
        scanf("%d", &A[I].edad);

        fflush(stdin);
        printf("Sexo (F-M): ");
        scanf("%c", &A[I].sexo);

        printf("Condicion (1..5): ");
        scanf("%d", &A[I].con);

        fflush(stdin);
        printf("\tCalle: ");
        gets(A[I].dom.cal);

        printf("\tNumero: ");
        scanf("%d", &A[I].dom.num);

        fflush(stdin);
        printf("\tColonia: ");
        gets(A[I].dom.col);

        printf("\tCodigo Postal: ");
        gets(A[I].dom.cp);

        printf("\tCiudad: ");
        gets(A[I].dom.ciu);

        printf("Telefono: ");
        gets(A[I].tel);
    }
}

void F1(paciente A[], int T)
{
    int I;

    printf("\n--- Pacientes en Condicion 5 (Grave) ---\n");

    for (I = 0; I < T; I++)
    {
        if (A[I].con == 5)
        {
            printf("Nombre: %s \t Tel: %s\n", A[I].nom, A[I].tel);
        }
    }
}

void F2(paciente A[], int T)
{
    int I;
    int sum_f = 0, sum_m = 0, count_f = 0, count_m = 0;

    for (I = 0; I < T; I++)
    {
        if (A[I].sexo == 'F' || A[I].sexo == 'f')
        {
            sum_f += A[I].edad;
            count_f++;
        }
        else if (A[I].sexo == 'M' || A[I].sexo == 'm')
        {
            sum_m += A[I].edad;
            count_m++;
        }
    }

    printf("\n--- Promedio de Edad por Sexo ---\n");

    if (count_f > 0)
    {
        printf("Femenino: %.2f anios\n", (float)sum_f / count_f);
    }
    else
    {
        printf("Femenino: 0 pacientes\n");
    }

    if (count_m > 0)
    {
        printf("Masculino: %.2f anios\n", (float)sum_m / count_m);
    }
    else
    {
        printf("Masculino: 0 pacientes\n");
    }
}

void F3(paciente A[], int T)
{
    int I;

    printf("\n--- Pacientes Menores de Edad ---\n");

    for (I = 0; I < T; I++)
    {
        if (A[I].edad < 18)
        {
            printf("Nombre: %s \t Edad: %d\n", A[I].nom, A[I].edad);
        }
    }
    printf("\n");
}
