#include <stdio.h>

int main(void)
{
    char cad[50];
    FILE *ap;

    if ((ap = fopen("arc.txt", "r")) != NULL)
    {
        while (!feof(ap))
        {
            if (fgets(cad, 50, ap) != NULL)
            {
                puts(cad);
            }
        }

        fclose(ap);
    }
    else
    {
        printf("No se puede abrir el archivo\n");
    }

    return 0;
}
