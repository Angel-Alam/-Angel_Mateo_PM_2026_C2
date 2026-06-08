#include <stdio.h>

void LecturaM(float [][12], int, int);
void LecturaV(float *, int);
void F1(float [][12], int, int, float *, float *);
void F2(float [][12], int, int);
void F3(float *, int);

int main(void)
{
    float FON[5][12], PRE[5], REN[5];

    LecturaM(FON, 5, 12);
    LecturaV(PRE, 5);
    F1(FON, 5, 12, PRE, REN);
    F2(FON, 5, 12);
    F3(REN, 5);

    return 0;
}

void LecturaM(float A[][12], int F, int C)
{
    int I, J;

    printf("\n--- Lectura de precios mensuales ---\n");
    for (I = 0; I < F; I++)
    {
        for (J = 0; J < C; J++)
        {
            printf("Fondo %d, Mes %d: ", I + 1, J + 1);
            scanf("%f", &A[I][J]);
        }
    }
}

void LecturaV(float A[], int N)
{
    int I;

    printf("\n--- Lectura de precios al 31 de diciembre ---\n");
    for (I = 0; I < N; I++)
    {
        printf("Precio base del fondo %d: ", I + 1);
        scanf("%f", &A[I]);
    }
}

void F1(float A[][12], int F, int C, float B[], float V[])
{
    int I;

    for (I = 0; I < F; I++)
    {
        V[I] = ((A[I][C - 1] - B[I]) / B[I]) * 100.0;
    }
}

void F2(float A[][12], int F, int C)
{
    int I, J;
    float SUM, PRO;

    printf("\n\nPROMEDIOS MENSUALES POR FONDO");
    for (I = 0; I < F; I++)
    {
        SUM = 0.0;
        for (J = 0; J < C; J++)
        {
            SUM += A[I][J];
        }
        PRO = SUM / C;
        printf("\nFondo %d: %6.2f", I + 1, PRO);
    }
}

void F3(float A[], int N)
{
    int I, M = 0, P = 0;
    float ME = A[0], PE = A[0];

    for (I = 1; I < N; I++)
    {
        if (A[I] > ME)
        {
            ME = A[I];
            M = I;
        }

        if (A[I] < PE)
        {
            PE = A[I];
            P = I;
        }
    }

    printf("\n\nMEJOR Y PEOR FONDO DE INVERSION");
    printf("\nMejor fondo: %d\tRendimiento: %6.2f%%", M + 1, ME);
    printf("\nPeor fondo: %d\tRendimiento: %6.2f%%\n", P + 1, PE);
}
