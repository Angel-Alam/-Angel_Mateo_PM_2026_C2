#include <stdio.h>

const int MAX = 50;
const int EXA = 4;

void Lectura(float [][EXA], int);
void Funcion1(float [][EXA], int);
void Funcion2(float [][EXA], int);

int main(void)
{
    int NAL;
    float ALU[MAX][EXA];

    do
    {
        printf("Ingrese el numero de alumnos del grupo: ");
        scanf("%d", &NAL);
    }
    while (NAL > MAX || NAL < 1);

    Lectura(ALU, NAL);
    Funcion1(ALU, NAL);
    Funcion2(ALU, NAL);

    return 0;
}

void Lectura(float A[][EXA], int N)
{
    int I, J;

    for (I = 0; I < N; I++)
    {
        for (J = 0; J < EXA; J++)
        {
            printf("Ingrese la calificacion del alumno %d en el examen %d: ", I + 1, J + 1);
            scanf("%f", &A[I][J]);
        }
    }
}

void Funcion1(float A[][EXA], int N)
{
    int I, J;
    float SUM, PRO;

    for (I = 0; I < N; I++)
    {
        SUM = 0.0;
        for (J = 0; J < EXA; J++)
        {
            SUM += A[I][J];
        }
        PRO = SUM / EXA;
        printf("\nPromedio del alumno %d: %5.2f", I + 1, PRO);
    }
    printf("\n");
}

void Funcion2(float A[][EXA], int N)
{
    int I, J, MAY = 0;
    float SUM, PRO, MPRO = 0.0;

    for (J = 0; J < EXA; J++)
    {
        SUM = 0.0;
        for (I = 0; I < N; I++)
        {
            SUM += A[I][J];
        }
        PRO = SUM / N;

        if (PRO > MPRO)
        {
            MPRO = PRO;
            MAY = J;
        }
        printf("\nEl promedio del examen %d es: %f", J + 1, PRO);
    }

    printf("\n\nEl examen con mayor promedio es: %d \t Promedio: %5.2f\n", MAY + 1, MPRO);
}
