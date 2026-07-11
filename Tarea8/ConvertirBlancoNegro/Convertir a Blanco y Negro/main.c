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

    dir = opendir(".");
    if (dir == NULL)
    {
        printf("No se pudo abrir la carpeta actual.\n");
        return 1;
    }

    printf("=========================================\n");
    printf("        EXPLORADOR DE IMAGENES          \n");
    printf("=========================================\n\n");
    printf("Archivos de imagen detectados:\n");

    while ((ent = readdir(dir)) != NULL)
    {
        char *ext = strrchr(ent->d_name, '.');
        if (ext != NULL)
        {
            if (strcasecmp(ext, ".bmp") == 0 || strcasecmp(ext, ".png") == 0 || strcasecmp(ext, ".jpg") == 0)
            {
                strncpy(archivos[totalArchivos], ent->d_name, 100);
                printf("[%d] %s\n", totalArchivos + 1, archivos[totalArchivos]);
                totalArchivos++;
            }
        }
    }
    closedir(dir);

    if (totalArchivos == 0)
    {
        printf("No se encontraron imagenes en esta carpeta.\n");
    }

    return 0;
}
