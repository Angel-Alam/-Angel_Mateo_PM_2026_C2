#include <stdio.h>

int main(void)
{
    char *cad0;
    char cad1[50];
    char cad2[20] = "Mexico";

    cad0 = "Argentina";
    puts(cad0);

    cad0 = "Brasil";
    puts(cad0);

    printf("Ingrese una cadena para cad1: ");
    gets(cad1);
    puts(cad1);

    printf("cad2 inicial es: ");
    puts(cad2);

    printf("Ingrese otra cadena para cad2: ");
    gets(cad2);
    puts(cad2);

    return 0;
}
