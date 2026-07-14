#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
// tuve que agregar estas librerias porq me di cuenta que no funcionaba sin ellas investigando para las imagenes png y jpg
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void convertirImagenReal(const char *nombreArchivo)
{
    int ancho, alto, canales;
    unsigned char *pixeles = stbi_load(nombreArchivo, &ancho, &alto, &canales, 3);

    if (pixeles == NULL)
    {
        printf("Error: No se pudo cargar o descomprimir la imagen.\n");
        return;
    }

    int totalBytes = ancho * alto * 3;
    for (int i = 0; i < totalBytes; i += 3)
    {
        unsigned char r = pixeles[i];
        unsigned char g = pixeles[i + 1];
        unsigned char b = pixeles[i + 2];

        unsigned char gris = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);

        pixeles[i] = gris;
        pixeles[i + 1] = gris;
        pixeles[i + 2] = gris;
    }
//proceso de conversion
    char nombreSalida[120];
    snprintf(nombreSalida, sizeof(nombreSalida), "gris_%s", nombreArchivo);

    char *ext = strrchr(nombreArchivo, '.');
    int resultadoGuardado = 0;

    if (ext != NULL && (strcasecmp(ext, ".jpg") == 0 || strcasecmp(ext, ".jpeg") == 0))
    {
        resultadoGuardado = stbi_write_jpg(nombreSalida, ancho, alto, 3, pixeles, 100);
    }
    else if (ext != NULL && strcasecmp(ext, ".png") == 0)
    {
        resultadoGuardado = stbi_write_png(nombreSalida, ancho, alto, 3, pixeles, ancho * 3);
    }
    else if (ext != NULL && strcasecmp(ext, ".bmp") == 0)
    {
        resultadoGuardado = stbi_write_bmp(nombreSalida, ancho, alto, 3, pixeles);
    }

    stbi_image_free(pixeles);

    if (resultadoGuardado)
    {
        printf("\n¡Imagen convertida con exito! Guardada como: %s\n", nombreSalida);
    }
    else
    {
        printf("\nError: No se pudo guardar la imagen procesada.\n");
    }
}

int main(void)
{
    DIR *dir;
    struct dirent *ent;
    char archivos[50][100];
    int totalArchivos = 0;
    int seleccion;

    dir = opendir(".");
    if (dir == NULL)
    {
        printf("No se pudo abrir la carpeta actual.\n");
        return 1;
    }
//interfaz
    printf("=========================================\n");
    printf("     CONVERTIDOR DE IMAGENES (STB)       \n");
    printf("=========================================\n\n");
    printf("Archivos de imagen detectados:\n");

    while ((ent = readdir(dir)) != NULL)
    {
        char *ext = strrchr(ent->d_name, '.');
        if (ext != NULL)
        {
            if (strcasecmp(ext, ".bmp") == 0 || strcasecmp(ext, ".png") == 0 || strcasecmp(ext, ".jpg") == 0 || strcasecmp(ext, ".jpeg") == 0)//lista de archivos
            {
                if (strncmp(ent->d_name, "gris_", 5) != 0)
                {
                    strncpy(archivos[totalArchivos], ent->d_name, 100);
                    printf("[%d] %s\n", totalArchivos + 1, archivos[totalArchivos]);
                    totalArchivos++;
                }
            }
        }
    }
    closedir(dir);

    if (totalArchivos == 0)
    {
        printf("No se encontraron imagenes para procesar.\n");
        return 0;
    }

    printf("\nSeleccione el numero de la foto a convertir: ");
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > totalArchivos)
    {
        printf("Seleccion invalida.\n");
        return 1;
    }

    printf("\nProcesando matriz de pixeles...\n");
    convertirImagenReal(archivos[seleccion - 1]);

    return 0;
}
