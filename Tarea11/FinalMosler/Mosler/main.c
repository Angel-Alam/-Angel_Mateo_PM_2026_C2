#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parámetros y Estructura del Método Mosler
typedef struct {
    int id;
    char bien[50];
    char dano[50];
    int F, S, P, E, A, V;
    int ER;
    char clase[20];
} Riesgo;

// Nodo para Memoria Dinámica
typedef struct Nodo {
    Riesgo dato;
    struct Nodo* sig;
} Nodo;

Nodo* cabeza = NULL;
char archivo_actual[50] = "riesgos_mecatronica.csv";
int contador_id = 1;

// --- Prototipos ---
void menu();
void crear_riesgo();
void modificar_riesgo();
void calcular_riesgos();
void imprimir_riesgos();
void borrar_riesgo();
void manejar_archivos();
void guardar_csv();
void cargar_csv();
void asistente_ia(Riesgo r);

// --- Funciones Principales ---
int main() {
    cargar_csv();
    menu();
    return 0;
}

void menu() {
    int opcion;
    do {
        printf("\n=== GESTION DE RIESGOS MOSLER ===\n");
        printf("Archivo actual: %s\n", archivo_actual);
        printf("1. Crear nuevo riesgo\n");
        printf("2. Modificar parametros de un riesgo\n");
        printf("3. Calcular riesgos\n");
        printf("4. Imprimir los riesgos (y Recomendacion IA)\n");
        printf("5. Borrar riesgo\n");
        printf("6. Seleccionar / Crear Archivo Especifico\n");
        printf("7. Guardar en disco (CSV)\n");
        printf("8. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer

        switch(opcion) {
            case 1: crear_riesgo(); break;
            case 2: modificar_riesgo(); break;
            case 3: calcular_riesgos(); break;
            case 4: imprimir_riesgos(); break;
            case 5: borrar_riesgo(); break;
            case 6: manejar_archivos(); break;
            case 7: guardar_csv(); break;
            case 8: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while(opcion != 8);
}

void crear_riesgo() {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato.id = contador_id++;

    printf("Bien / Activo: ");
    fgets(nuevo->dato.bien, 50, stdin);
    nuevo->dato.bien[strcspn(nuevo->dato.bien, "\n")] = 0;

    printf("Dano posible: ");
    fgets(nuevo->dato.dano, 50, stdin);
    nuevo->dato.dano[strcspn(nuevo->dato.dano, "\n")] = 0;

    printf("Valores (1 a 5):\n");
    printf("F (Funcion): "); scanf("%d", &nuevo->dato.F);
    printf("S (Sustitucion): "); scanf("%d", &nuevo->dato.S);
    printf("P (Profundidad): "); scanf("%d", &nuevo->dato.P);
    printf("E (Extension): "); scanf("%d", &nuevo->dato.E);
    printf("A (Agresion): "); scanf("%d", &nuevo->dato.A);
    printf("V (Vulnerabilidad): "); scanf("%d", &nuevo->dato.V);

    nuevo->dato.ER = 0;
    strcpy(nuevo->dato.clase, "No calculado");
    nuevo->sig = cabeza;
    cabeza = nuevo;
    printf("Riesgo creado exitosamente.\n");
}

void calcular_riesgos() {
    Nodo* actual = cabeza;
    while(actual != NULL) {
        int I = actual->dato.F * actual->dato.S;
        int D = actual->dato.P * actual->dato.E;
        int C = I + D;
        int PB = actual->dato.A * actual->dato.V;
        actual->dato.ER = C * PB;

        if(actual->dato.ER <= 250) strcpy(actual->dato.clase, "Muy Pequeno");
        else if(actual->dato.ER <= 500) strcpy(actual->dato.clase, "Pequeno");
        else if(actual->dato.ER <= 750) strcpy(actual->dato.clase, "Normal");
        else if(actual->dato.ER <= 1000) strcpy(actual->dato.clase, "Grande");
        else strcpy(actual->dato.clase, "Elevado");

        actual = actual->sig;
    }
    printf("Calculos realizados correctamente.\n");
}

void imprimir_riesgos() {
    Nodo* actual = cabeza;
    printf("\n--- LISTA DE RIESGOS ---\n");
    while(actual != NULL) {
        printf("ID: %d | Bien: %s | Dano: %s\n", actual->dato.id, actual->dato.bien, actual->dato.dano);
        printf("Parametros: F:%d S:%d P:%d E:%d A:%d V:%d\n",
            actual->dato.F, actual->dato.S, actual->dato.P, actual->dato.E, actual->dato.A, actual->dato.V);
        printf("Clasificacion: %d (%s)\n", actual->dato.ER, actual->dato.clase);
        asistente_ia(actual->dato);
        printf("------------------------\n");
        actual = actual->sig;
    }
}

// Simulacion de IA (Sistema Experto basado en heuristica)
void asistente_ia(Riesgo r) {
    printf("🤖 [IA]: ");
    if(r.ER == 0) {
        printf("Calcula los riesgos primero.\n");
    } else if (r.ER > 750) {
        printf("ALERTA CRITICA. Requiere redisenar la arquitectura del sistema y agregar paros de emergencia fisicos.\n");
    } else if (r.F > 3 && r.S > 3) {
        printf("Alto impacto en hardware. Sugiero mantener refacciones del '%s' en inventario local.\n", r.bien);
    } else {
        printf("Riesgo aceptable. Mantener rutinas de mantenimiento preventivo.\n");
    }
}

void modificar_riesgo() {
    int id_mod;
    printf("Ingrese ID a modificar: ");
    scanf("%d", &id_mod);
    Nodo* actual = cabeza;
    while(actual != NULL) {
        if(actual->dato.id == id_mod) {
            printf("Nuevos valores (1 a 5) F S P E A V: ");
            scanf("%d %d %d %d %d %d", &actual->dato.F, &actual->dato.S, &actual->dato.P, &actual->dato.E, &actual->dato.A, &actual->dato.V);
            actual->dato.ER = 0; // Reiniciar calculo
            printf("Modificado.\n");
            return;
        }
        actual = actual->sig;
    }
    printf("ID no encontrado.\n");
}

void borrar_riesgo() {
    int id_borrar;
    printf("Ingrese ID a borrar: ");
    scanf("%d", &id_borrar);
    Nodo *actual = cabeza, *anterior = NULL;

    while(actual != NULL && actual->dato.id != id_borrar) {
        anterior = actual;
        actual = actual->sig;
    }
    if(actual == NULL) {
        printf("Riesgo no encontrado.\n");
        return;
    }
    if(anterior == NULL) cabeza = actual->sig;
    else anterior->sig = actual->sig;

    free(actual);
    printf("Riesgo borrado.\n");
}

void manejar_archivos() {
    printf("Nombre del nuevo archivo (ej. planta1.csv): ");
    fgets(archivo_actual, 50, stdin);
    archivo_actual[strcspn(archivo_actual, "\n")] = 0;
    cargar_csv();
}

void guardar_csv() {
    FILE* file = fopen(archivo_actual, "w");
    if(file == NULL) {
        printf("Error al crear archivo.\n");
        return;
    }
    fprintf(file, "ID,Bien,Dano,F,S,P,E,A,V,ER,Clase\n");
    Nodo* actual = cabeza;
    while(actual != NULL) {
        fprintf(file, "%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%s\n",
            actual->dato.id, actual->dato.bien, actual->dato.dano,
            actual->dato.F, actual->dato.S, actual->dato.P,
            actual->dato.E, actual->dato.A, actual->dato.V,
            actual->dato.ER, actual->dato.clase);
        actual = actual->sig;
    }
    fclose(file);
    printf("Datos guardados en %s\n", archivo_actual);
}

void cargar_csv() {
    FILE* file = fopen(archivo_actual, "r");
    if(file == NULL) return; // Si no existe, no hace nada

    // Liberar memoria actual si existe
    while(cabeza != NULL) {
        Nodo* temp = cabeza;
        cabeza = cabeza->sig;
        free(temp);
    }

    char linea[200];
    fgets(linea, sizeof(linea), file); // Saltar cabecera
    while(fgets(linea, sizeof(linea), file)) {
        Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
        char* token = strtok(linea, ",");
        nuevo->dato.id = atoi(token);
        if(nuevo->dato.id >= contador_id) contador_id = nuevo->dato.id + 1;

        token = strtok(NULL, ","); strcpy(nuevo->dato.bien, token);
        token = strtok(NULL, ","); strcpy(nuevo->dato.dano, token);
        token = strtok(NULL, ","); nuevo->dato.F = atoi(token);p0.
        token = strtok(NULL, ","); nuevo->dato.S = atoi(token);
        token = strtok(NULL, ","); nuevo->dato.P = atoi(token);
        token = strtok(NULL, ","); nuevo->dato.E = atoi(token);
        token = strtok(NULL, ","); nuevo->dato.A = atoi(token);
        token = strtok(NULL, ","); nuevo->dato.V = atoi(token);
        token = strtok(NULL, ","); nuevo->dato.ER = atoi(token);
        token = strtok(NULL, "\n"); strcpy(nuevo->dato.clase, token);

        nuevo->sig = cabeza;
        cabeza = nuevo;
    }
    fclose(file);
    printf("Datos cargados desde %s\n", archivo_actual);
}
