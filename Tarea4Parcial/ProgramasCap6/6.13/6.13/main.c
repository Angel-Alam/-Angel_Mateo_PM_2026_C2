#include <stdio.h>

const int MES = 12;
const int DEP = 3;
const int ANO = 8;

void Lectura(float [][DEP][ANO], int, int, int);
void Funcion1(float [][DEP][ANO], int, int, int);
void Funcion2(float [][DEP][ANO], int, int, int);
void Funcion3(float [][DEP][ANO], int, int, int);

int main(void)
{
    float PRO[MES][DEP][ANO];

    Lectura(PRO, MES, DEP, ANO);
    Funcion1(PRO, MES, DEP, 2);
    Funcion2(PRO, MES, DEP, ANO);
    Funcion3(PRO, MES, DEP, ANO);

    return 0;
}

void Lectura(float A[][DEP][ANO], int F, int C, int P)
{
    int K, I, J;

    for (K = 0; K < P; K++)
    {
        for (I = 0; I < F; I++)
        {
            for (J = 0; J < C; J++)
            {
                printf("Ingrese las ventas del mes %d, departamento %d, ano %d: ", I + 1, J + 1, K + 1);
                scanf("%f", &A[I][J][K]);
            }
        }
    }
}

void Funcion1(float A[][DEP][ANO], int F, int C, int P)
{
    int I, J;
    float SUM = 0.0;

    for (I = 0; I < F; I++)
    {
        for (J = 0; J < C; J++)
        {
            SUM += A[I][J][P - 1];
        }
    }

    printf("\n\nVentas totales de la empresa en el ano %d: %.2f", P, SUM);
}

void Funcion2(float A[][DEP][ANO], int F, int C, int P)
{
    int I;
    float SUM1 = 0.0, SUM2 = 0.0, SUM3 = 0.0;

    for (I = 0; I < F; I++)
    {
        SUM1 += A[I][0][P - 1];
        SUM2 += A[I][1][P - 1];
        SUM3 += A[I][2][P - 1];
    }

    if (SUM1 > SUM2)
    {
        if (SUM1 > SUM3)
        {
            printf("\n\nDepartamento con mayores ventas en el ultimo ano: Hilos");
            printf("  Ventas: %.2f", SUM1);
        }
        else
        {
            printf("\n\nDepartamento con mayores ventas en el ultimo ano: Licra");
            printf("  Ventas: %.2f", SUM3);
        }
    }
    else
    {
        if (SUM2 > SUM3)
        {
            printf("\n\nDepartamento con mayores ventas en el ultimo ano: Lanas");
            printf("  Ventas: %.2f", SUM2);
        }
        else
        {
            printf("\n\nDepartamento con mayores ventas en el ultimo ano: Licra");
            printf("  Ventas: %.2f", SUM3);
        }
    }
}

void Funcion3(float A[][DEP][ANO], int F, int C, int P)
{
    int K, I, J, DE = -1, ME = -1, AN = -1;
    float VEN = -1.0;

    for (K = 0; K < P; K++)
    {
        for (I = 0; I < F; I++)
        {
            for (J = 0; J < C; J++)
            {
                if (A[I][J][K] > VEN)
                {
                    VEN = A[I][J][K];
                    DE = J;
                    ME = I;
                    AN = K;
                }
            }
        }
    }

    printf("\n\nDepartamento: %d\tMes: %d\tAno: %d", DE + 1, ME + 1, AN + 1);
    printf("\tVentas: %.2f\n", VEN);
}
