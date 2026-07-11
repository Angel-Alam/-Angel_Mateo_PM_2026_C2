#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(void)
{
    DIR *dir;
    struct dirent *ent;
    char archivos[50][100];
    int totalArchivos = 0;
    int seleccion;

    dir = opendir(".");
    if (dir == NULL) return 1;
//interfaz
    printf("=========================================\n");
    printf("        EXPLORADOR DE IMAGENES          \n");
    printf("=========================================\n\n");

    while ((ent = readdir(dir)) != NULL)
    {
        char *ext = strrchr(ent->d_name, '.');
        if (ext != NULL && (strcasecmp(ext, ".bmp") == 0 || strcasecmp(ext, ".png") == 0 || strcasecmp(ext, ".jpg") == 0))//listado de archivos
        {
            strncpy(archivos[totalArchivos], ent->d_name, 100);
            printf("[%d] %s\n", totalArchivos + 1, archivos[totalArchivos]);
            totalArchivos++;
        }
    }
    closedir(dir);
//menu interactivo
    if (totalArchivos == 0) return 0;

    printf("\nSeleccione el numero del archivo que desea procesar: ");
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > totalArchivos)
    {
        printf("Seleccion no valida.\n");
        return 1;
    }

    char *archivoSeleccionado = archivos[seleccion - 1];
    printf("\nArchivo seleccionado: %s\n", archivoSeleccionado);
    printf("Preparando modulo de conversion...\n");

    return 0;
}
