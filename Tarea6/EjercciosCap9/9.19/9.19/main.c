#include <stdio.h>

typedef struct
{
    char materia[20];
    int calificacion;
} matcal;

typedef struct
{
    int matricula;
    char nombre[20];
    matcal cal[5];
} alumno;

void F1(FILE *);
void F2(FILE *);
float F3(FILE *);

int main(void)
{
    float pro;
    FILE *ap;

    if ((ap = fopen("esc.dat", "rb")) != NULL)
    {
        F1(ap);
        F2(ap);
        pro = F3(ap);
        printf("\n\nPROMEDIO GENERAL MATERIA 4: %.2f\n", pro);

        fclose(ap);
    }
    else
    {
        printf("\nEl archivo no se puede abrir\n");
    }

    return 0;
}

void F1(FILE *ap)
{
    alumno alu;
    int j;
    float sum, pro;

    printf("\nMATRICULA y PROMEDIOS");

    rewind(ap);
    fread(&alu, sizeof(alumno), 1, ap);

    while (!feof(ap))
    {
        printf("\nMatricula: %d", alu.matricula);
        sum = 0.0;

        for (j = 0; j < 5; j++)
        {
            sum += alu.cal[j].calificacion;
        }

        pro = sum / 5.0;
        printf("\tPromedio: %.2f", pro);

        fread(&alu, sizeof(alumno), 1, ap);
    }
}

void F2(FILE *ap)
{
    alumno alu;

    rewind(ap);
    printf("\n\nALUMNOS CON CALIFICACION > 9 EN MATERIA 3");

    fread(&alu, sizeof(alumno), 1, ap);

    while (!feof(ap))
    {
        if (alu.cal[2].calificacion > 9)
        {
            printf("\nMatricula del alumno: %d", alu.matricula);
        }

        fread(&alu, sizeof(alumno), 1, ap);
    }
}

float F3(FILE *ap)
{
    alumno alu;
    int i = 0;
    float sum = 0.0, pro;

    rewind(ap);
    fread(&alu, sizeof(alumno), 1, ap);

    while (!feof(ap))
    {
        i++;
        sum += alu.cal[3].calificacion;

        fread(&alu, sizeof(alumno), 1, ap);
    }

    if (i > 0)
    {
        pro = sum / i;
    }
    else
    {
        pro = 0.0;
    }

    return pro;
}
