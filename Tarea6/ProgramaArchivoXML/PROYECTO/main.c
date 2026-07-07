
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[30];
    char apellido[30];
    float promedio;
    char materia[40];
} Alumno;

void procesarCSV(void);
void procesarXML(void);
void procesarJSON(void);

int main(void)
{
    printf("======================================\n");
    printf("        PROCESADOR DE ALUMNOS         \n");
    printf("======================================\n");

    printf("\n>>> LEYENDO ARCHIVO CSV <<<\n");
    procesarCSV();

    printf("\n>>> LEYENDO ARCHIVO XML <<<\n");
    procesarXML();

    printf("\n>>> LEYENDO ARCHIVO JSON <<<\n");
    procesarJSON();

    return 0;
}

void procesarCSV(void)
{
    FILE *ar = fopen("alumnos.csv", "r");
    if (ar == NULL) {
        printf("No se pudo abrir alumnos.csv\n");
        return;
    }

    int count = 0;
    char buffer[150];

    // Paso 1: Contar lineas para saber la cantidad 'n'
    while (fgets(buffer, 150, ar) != NULL) {
        if (strlen(buffer) > 5) {
            count++;
        }
    }

    // Paso 2: Crear memoria dinamica
    Alumno *arreglo = (Alumno *)malloc(count * sizeof(Alumno));

    // Paso 3: Regresar al inicio y cargar datos
    rewind(ar);
    for (int i = 0; i < count; i++) {
        fgets(buffer, 150, ar);
        // Separamos por comas usando sscanf
        sscanf(buffer, "%[^,],%[^,],%f,%[^\n]", arreglo[i].nombre, arreglo[i].apellido, &arreglo[i].promedio, arreglo[i].materia);
    }

    // Paso 4: Imprimir array y liberar memoria
    printf("Se encontraron %d alumnos:\n", count);
    for (int i = 0; i < count; i++) {
        printf("- %s %s | Promedio: %.2f | Materia: %s\n", arreglo[i].nombre, arreglo[i].apellido, arreglo[i].promedio, arreglo[i].materia);
    }

    free(arreglo);
    fclose(ar);
}

void procesarXML(void)
{
    FILE *ar = fopen("alumnos.xml", "r");
    if (ar == NULL) {
        printf("No se pudo abrir alumnos.xml\n");
        return;
    }

    int count = 0;
    char buffer[150];

    // Paso 1: Contar cuantas veces aparece la etiqueta <Alumno>
    while (fgets(buffer, 150, ar) != NULL) {
        if (strstr(buffer, "<Alumno>") != NULL) {
            count++;
        }
    }

    // Paso 2: Memoria dinamica
    Alumno *arreglo = (Alumno *)malloc(count * sizeof(Alumno));
    rewind(ar);

    // Paso 3: Buscar las sub-etiquetas y llenar el arreglo
    int i = 0;
    while (fgets(buffer, 150, ar) != NULL && i < count) {
        if (strstr(buffer, "<Nombre>")) {
            sscanf(buffer, "%*[^>]>%[^<]", arreglo[i].nombre);
        }
        else if (strstr(buffer, "<Apellido>")) {
            sscanf(buffer, "%*[^>]>%[^<]", arreglo[i].apellido);
        }
        else if (strstr(buffer, "<Promedio>")) {
            sscanf(buffer, "%*[^>]>%f", &arreglo[i].promedio);
        }
        else if (strstr(buffer, "<Materia>")) {
            sscanf(buffer, "%*[^>]>%[^<]", arreglo[i].materia);
        }
        else if (strstr(buffer, "</Alumno>")) {
            i++; // Cuando cerramos el bloque, pasamos al siguiente alumno
        }
    }

    printf("Se encontraron %d alumnos:\n", count);
    for (int j = 0; j < count; j++) {
        printf("- %s %s | Promedio: %.2f | Materia: %s\n", arreglo[j].nombre, arreglo[j].apellido, arreglo[j].promedio, arreglo[j].materia);
    }

    free(arreglo);
    fclose(ar);
}

void procesarJSON(void)
{
    FILE *ar = fopen("alumnos.json", "r");
    if (ar == NULL) {
        printf("No se pudo abrir alumnos.json\n");
        return;
    }

    int count = 0;
    char buffer[150];

    // Paso 1: Contar las ocurrencias de "Nombre" para saber cuantos objetos hay
    while (fgets(buffer, 150, ar) != NULL) {
        if (strstr(buffer, "\"Nombre\"") != NULL) {
            count++;
        }
    }

    // Paso 2: Memoria dinamica
    Alumno *arreglo = (Alumno *)malloc(count * sizeof(Alumno));
    rewind(ar);

    // Paso 3: Buscar las claves y extraer el valor despues de los dos puntos
    int i = 0;
    while (fgets(buffer, 150, ar) != NULL && i < count) {
        if (strstr(buffer, "\"Nombre\"")) {
            sscanf(buffer, "%*[^:]: \"%[^\"]\"", arreglo[i].nombre);
        }
        else if (strstr(buffer, "\"Apellido\"")) {
            sscanf(buffer, "%*[^:]: \"%[^\"]\"", arreglo[i].apellido);
        }
        else if (strstr(buffer, "\"Promedio\"")) {
            sscanf(buffer, "%*[^:]: %f", &arreglo[i].promedio);
        }
        else if (strstr(buffer, "\"Materia\"")) {
            sscanf(buffer, "%*[^:]: \"%[^\"]\"", arreglo[i].materia);
        }
        else if (strstr(buffer, "}")) {
            i++; // Fin del objeto JSON
        }
    }

    printf("Se encontraron %d alumnos:\n", count);
    for (int j = 0; j < count; j++) {
        printf("- %s %s | Promedio: %.2f | Materia: %s\n", arreglo[j].nombre, arreglo[j].apellido, arreglo[j].promedio, arreglo[j].materia);
    }

    free(arreglo);
    fclose(ar);
}
