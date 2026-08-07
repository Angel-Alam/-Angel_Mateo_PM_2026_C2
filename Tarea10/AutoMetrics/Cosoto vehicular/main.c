/* ============================================================================
 *  PROGRAMA: CALCULADORA DE AMORTIZACION Y COSTO REAL DE USO DE VEHICULOS
 * ============================================================================
 *
 *  OBJETIVO PEDAGOGICO (para clase de mecatronica):
 *  Este programa demuestra como aplicar formulas de ingenieria de costos
 *  (amortizacion lineal, prorrateo de mantenimiento, desgaste de neumaticos,
 *  seguro y consumo de combustible) para obtener el "costo real por
 *  kilometro" de un vehiculo, separando el costo en ciudad y en autopista.
 *
 *  El programa esta organizado en "modulos" (secciones de funciones) aunque
 *  se entrega en un solo archivo .c para que sea facil de compilar:
 *
 *      MODULO 1: Estructura de datos y constantes globales
 *      MODULO 2: Utilidades generales (lectura segura, division segura)
 *      MODULO 3: Persistencia (leer/guardar vehiculos y configuracion)
 *      MODULO 4: Modelo matematico (formulas de costo por km)
 *      MODULO 5: Gestion de vehiculos (crear, listar, seleccionar, borrar,
 *                modificar)
 *      MODULO 6: Calculo de viaje (combustible vs costo real)
 *      MODULO 7: Menu principal (interfaz de consola) y main()
 *
 *  PERSISTENCIA:
 *  - "vehiculos.csv"  -> una linea por vehiculo, campos separados por coma.
 *  - "config.csv"     -> una sola linea con el precio actual del combustible
 *                         (RD$ por galon).
 *
 *  Si estos archivos no existen al iniciar el programa, se crean vacios
 *  automaticamente (no se considera un error).
 *
 *  UNIDADES:
 *  - Moneda: Pesos Dominicanos (RD$)
 *  - Volumen de combustible: Galones
 *  - Rendimiento: Kilometros por Galon (Km/Gal)
 *
 *  COMPILACION:
 *      gcc costo_vehicular.c -o costo_vehicular -Wall
 *  EJECUCION:
 *      ./costo_vehicular
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================================
 *  MODULO 1: ESTRUCTURA DE DATOS Y CONSTANTES GLOBALES
 * ==========================================================================*/

#define MAX_VEHICULOS      50      /* Cantidad maxima de vehiculos en memoria */
#define TAM_MODELO         100     /* Tamano maximo del nombre del modelo    */
#define TAM_LINEA          512     /* Tamano de buffer para leer una linea   */
#define ARCHIVO_VEHICULOS  "vehiculos.csv"
#define ARCHIVO_CONFIG     "config.csv"

/*
 * Estructura que representa un vehiculo y todos los parametros necesarios
 * para calcular su costo real de uso. Los nombres de las variables se
 * mantienen en espanol, tal como se definieron en los requisitos.
 */
typedef struct {
    char  modelo[TAM_MODELO];      /* Identificador del vehiculo            */
    float precio_compra;           /* Costo inicial del vehiculo (RD$)      */
    float valor_residual;          /* Valor de reventa al final de vida util*/
    float vida_util_km;            /* Km totales que se espera que dure     */
    float km_promedio_anual;       /* Estimacion de recorrido anual         */
    float rend_ciudad_kmgal;       /* Rendimiento en ciudad (Km/Gal)        */
    float rend_auto_kmgal;         /* Rendimiento en autopista (Km/Gal)     */
    float costo_mant_preventivo;   /* Costo de un mantenimiento de rutina   */
    float intervalo_mant_km;       /* Cada cuantos km se hace mantenimiento */
    float costo_set_neumaticos;    /* Precio de los 4 neumaticos nuevos     */
    float vida_neumaticos_km;      /* Cuantos km duran los neumaticos       */
    float costo_seguro_anual;      /* Pago del seguro por ano               */
} Vehiculo;

/* ============================================================================
 *  PROTOTIPOS DE FUNCIONES
 *  (declararlos aqui permite leer el programa "de arriba hacia abajo" y
 *   usarlos en main() antes de ver su implementacion completa mas abajo)
 * ==========================================================================*/

/* --- Modulo 2: Utilidades --- */
void  limpiarBufferEntrada(void);
void  pausar(void);
float leerFloat(const char *mensaje);
void  leerTexto(const char *mensaje, char *destino, int tamano);
float divisionSegura(float numerador, float denominador, const char *nombreFormula);

/* --- Modulo 3: Persistencia --- */
int   cargarVehiculos(Vehiculo lista[]);
void  guardarVehiculos(Vehiculo lista[], int total);
float cargarPrecioCombustible(void);
void  guardarPrecioCombustible(float precio);

/* --- Modulo 4: Modelo matematico --- */
float calcularAmortizacionPorKm(Vehiculo v);
float calcularMantenimientoPorKm(Vehiculo v);
float calcularNeumaticosPorKm(Vehiculo v);
float calcularSeguroPorKm(Vehiculo v);
float calcularCombustibleCiudadPorKm(Vehiculo v, float precio_combustible_galon);
float calcularCombustibleAutopistaPorKm(Vehiculo v, float precio_combustible_galon);
float calcularCostoRealCiudadPorKm(Vehiculo v, float precio_combustible_galon);
float calcularCostoRealAutopistaPorKm(Vehiculo v, float precio_combustible_galon);

/* --- Modulo 5: Gestion de vehiculos --- */
void  imprimirVehiculo(Vehiculo v, int indice);
void  listarVehiculos(Vehiculo lista[], int total);
int   seleccionarVehiculo(Vehiculo lista[], int total);
void  crearVehiculo(Vehiculo lista[], int *total);
void  borrarVehiculo(Vehiculo lista[], int *total);
void  modificarVehiculo(Vehiculo lista[], int total);

/* --- Modulo 6: Calculo de viaje --- */
void  calcularViaje(Vehiculo lista[], int total, float precio_combustible_galon);

/* --- Modulo 7: Menu principal --- */
void  mostrarMenu(void);


/* ============================================================================
 *  MODULO 2: UTILIDADES GENERALES
 * ==========================================================================*/

/*
 * limpiarBufferEntrada:
 * Despues de usar scanf() suelen quedar caracteres pendientes en el buffer
 * de entrada (por ejemplo el '\n' que deja pulsar Enter). Si no se limpian,
 * la siguiente lectura de texto puede fallar o leer datos basura. Esta
 * funcion descarta todo hasta el siguiente salto de linea.
 */
void limpiarBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descartar caracter */
    }
}

/*
 * pausar:
 * Detiene la ejecucion hasta que el usuario presione Enter, para que pueda
 * leer los resultados en pantalla antes de que el menu vuelva a mostrarse.
 */
void pausar(void) {
    printf("\nPresione ENTER para continuar...");
    getchar();
}

/*
 * leerFloat:
 * Pide un numero decimal al usuario de forma segura. Si el usuario escribe
 * algo que no es un numero, se le vuelve a pedir el dato en lugar de que
 * el programa falle o quede en un estado inconsistente.
 */
float leerFloat(const char *mensaje) {
    float valor;
    int   resultado;

    printf("%s", mensaje);
    resultado = scanf("%f", &valor);

    while (resultado != 1) {
        /* Si se llego al final de la entrada (EOF), no tiene sentido seguir
         * pidiendo datos: se evita un bucle infinito terminando el programa
         * de forma controlada. En uso normal por teclado esto no ocurre. */
        if (resultado == EOF) {
            printf("\n[ERROR] Se alcanzo el final de la entrada de datos. Cerrando el programa.\n");
            exit(EXIT_FAILURE);
        }
        printf("  -> Valor invalido. Ingrese un numero valido: ");
        limpiarBufferEntrada();
        resultado = scanf("%f", &valor);
    }

    limpiarBufferEntrada(); /* limpiar el '\n' que dejo el scanf */
    return valor;
}

/*
 * leerTexto:
 * Pide una linea de texto (por ejemplo, el modelo del vehiculo) y la guarda
 * en "destino". Se asegura de no desbordar el buffer y de quitar el salto
 * de linea final. Ademas, como el archivo CSV usa la coma como separador,
 * se reemplaza cualquier coma que el usuario escriba por un espacio, para
 * no romper el formato del archivo.
 */
void leerTexto(const char *mensaje, char *destino, int tamano) {
    int i;

    printf("%s", mensaje);
    if (fgets(destino, tamano, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }

    /* Quitar el salto de linea final que deja fgets */
    destino[strcspn(destino, "\n")] = '\0';

    /* Reemplazar comas por espacios para no romper el formato CSV */
    for (i = 0; destino[i] != '\0'; i++) {
        if (destino[i] == ',') {
            destino[i] = ' ';
        }
    }
}

/*
 * divisionSegura:
 * Todas las formulas del modelo matematico son divisiones (costo / algo).
 * Si el denominador es cero (por ejemplo, un vehiculo con "vida_util_km"
 * en 0), una division normal en C produciria un valor infinito o un
 * comportamiento indefinido. Esta funcion evita ese problema: si el
 * denominador es 0, avisa por consola y devuelve 0 como costo por km.
 */
float divisionSegura(float numerador, float denominador, const char *nombreFormula) {
    if (denominador == 0.0f) {
        printf("  [Aviso] '%s' tiene un divisor igual a 0. Se usara 0 como resultado.\n",
               nombreFormula);
        return 0.0f;
    }
    return numerador / denominador;
}


/* ============================================================================
 *  MODULO 3: PERSISTENCIA DE DATOS (ARCHIVOS CSV)
 * ==========================================================================*/

/*
 * cargarVehiculos:
 * Lee el archivo ARCHIVO_VEHICULOS linea por linea y llena el arreglo
 * "lista" con los vehiculos encontrados. Devuelve la cantidad de vehiculos
 * cargados (el nuevo valor de "total").
 *
 * Formato de cada linea del CSV (12 campos separados por coma):
 * modelo,precio_compra,valor_residual,vida_util_km,km_promedio_anual,
 * rend_ciudad_kmgal,rend_auto_kmgal,costo_mant_preventivo,intervalo_mant_km,
 * costo_set_neumaticos,vida_neumaticos_km,costo_seguro_anual
 *
 * Si el archivo no existe, se crea vacio y se devuelve 0 vehiculos.
 */
int cargarVehiculos(Vehiculo lista[]) {
    FILE *archivo;
    char  linea[TAM_LINEA];
    int   total = 0;

    archivo = fopen(ARCHIVO_VEHICULOS, "r");
    if (archivo == NULL) {
        /* El archivo no existe todavia: lo creamos vacio */
        archivo = fopen(ARCHIVO_VEHICULOS, "w");
        if (archivo != NULL) {
            fclose(archivo);
        }
        return 0;
    }

    while (fgets(linea, TAM_LINEA, archivo) != NULL && total < MAX_VEHICULOS) {
        Vehiculo v;
        int camposLeidos = sscanf(linea,
            "%99[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
            v.modelo,
            &v.precio_compra,
            &v.valor_residual,
            &v.vida_util_km,
            &v.km_promedio_anual,
            &v.rend_ciudad_kmgal,
            &v.rend_auto_kmgal,
            &v.costo_mant_preventivo,
            &v.intervalo_mant_km,
            &v.costo_set_neumaticos,
            &v.vida_neumaticos_km,
            &v.costo_seguro_anual);

        /* Solo aceptamos la linea si los 12 campos se leyeron bien.
         * Esto protege el programa contra lineas vacias o corruptas. */
        if (camposLeidos == 12) {
            lista[total] = v;
            total++;
        }
    }

    fclose(archivo);
    return total;
}

/*
 * guardarVehiculos:
 * Reescribe por completo el archivo ARCHIVO_VEHICULOS con el contenido
 * actual del arreglo "lista". Se usa el modo "w" (write) porque siempre
 * queremos que el archivo refleje exactamente lo que hay en memoria.
 */
void guardarVehiculos(Vehiculo lista[], int total) {
    FILE *archivo;
    int   i;

    archivo = fopen(ARCHIVO_VEHICULOS, "w");
    if (archivo == NULL) {
        printf("  [ERROR] No se pudo abrir '%s' para escritura.\n", ARCHIVO_VEHICULOS);
        return;
    }

    for (i = 0; i < total; i++) {
        Vehiculo v = lista[i];
        fprintf(archivo, "%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                v.modelo,
                v.precio_compra,
                v.valor_residual,
                v.vida_util_km,
                v.km_promedio_anual,
                v.rend_ciudad_kmgal,
                v.rend_auto_kmgal,
                v.costo_mant_preventivo,
                v.intervalo_mant_km,
                v.costo_set_neumaticos,
                v.vida_neumaticos_km,
                v.costo_seguro_anual);
    }

    fclose(archivo);
}

/*
 * cargarPrecioCombustible:
 * Lee el precio de combustible (RD$ por galon) guardado en ARCHIVO_CONFIG.
 * Si el archivo no existe o esta vacio, se asume un valor por defecto y
 * se guarda, para que el programa siempre tenga un precio de combustible
 * valido.
 */
float cargarPrecioCombustible(void) {
    FILE *archivo;
    float precio_combustible_galon = 0.0f;
    const float PRECIO_POR_DEFECTO = 1.00f;

    archivo = fopen(ARCHIVO_CONFIG, "r");
    if (archivo == NULL) {
        guardarPrecioCombustible(PRECIO_POR_DEFECTO);
        return PRECIO_POR_DEFECTO;
    }

    if (fscanf(archivo, "%f", &precio_combustible_galon) != 1) {
        /* Archivo existe pero esta vacio o corrupto */
        precio_combustible_galon = PRECIO_POR_DEFECTO;
        guardarPrecioCombustible(precio_combustible_galon);
    }

    fclose(archivo);
    return precio_combustible_galon;
}

/*
 * guardarPrecioCombustible:
 * Escribe el precio actual del combustible (RD$ por galon) en
 * ARCHIVO_CONFIG. Este valor es GLOBAL: aplica a todos los vehiculos y no
 * forma parte de la estructura Vehiculo, tal como pide el enunciado.
 */
void guardarPrecioCombustible(float precio) {
    FILE *archivo = fopen(ARCHIVO_CONFIG, "w");
    if (archivo == NULL) {
        printf("  [ERROR] No se pudo guardar el precio del combustible.\n");
        return;
    }
    fprintf(archivo, "%.2f\n", precio);
    fclose(archivo);
}


/* ============================================================================
 *  MODULO 4: MODELO MATEMATICO
 *  Cada funcion implementa EXACTAMENTE una de las formulas del enunciado.
 *  Todas devuelven un costo expresado en moneda por kilometro (RD$/km).
 * ==========================================================================*/

/* 1) Amortizacion por Km = (precio_compra - valor_residual) / vida_util_km */
float calcularAmortizacionPorKm(Vehiculo v) {
    float depreciacionTotal = v.precio_compra - v.valor_residual;
    return divisionSegura(depreciacionTotal, v.vida_util_km, "Amortizacion por Km");
}

/* 2) Mantenimiento por Km = costo_mant_preventivo / intervalo_mant_km */
float calcularMantenimientoPorKm(Vehiculo v) {
    return divisionSegura(v.costo_mant_preventivo, v.intervalo_mant_km,
                           "Mantenimiento por Km");
}

/* 3) Neumaticos por Km = costo_set_neumaticos / vida_neumaticos_km */
float calcularNeumaticosPorKm(Vehiculo v) {
    return divisionSegura(v.costo_set_neumaticos, v.vida_neumaticos_km,
                           "Neumaticos por Km");
}

/* 4) Seguro por Km = costo_seguro_anual / km_promedio_anual */
float calcularSeguroPorKm(Vehiculo v) {
    return divisionSegura(v.costo_seguro_anual, v.km_promedio_anual,
                           "Seguro por Km");
}

/* 5) Combustible Ciudad por Km = precio_combustible_galon / rend_ciudad_kmgal */
float calcularCombustibleCiudadPorKm(Vehiculo v, float precio_combustible_galon) {
    return divisionSegura(precio_combustible_galon, v.rend_ciudad_kmgal,
                           "Combustible Ciudad por Km");
}

/* 6) Combustible Autopista por Km = precio_combustible_galon / rend_auto_kmgal */
float calcularCombustibleAutopistaPorKm(Vehiculo v, float precio_combustible_galon) {
    return divisionSegura(precio_combustible_galon, v.rend_auto_kmgal,
                           "Combustible Autopista por Km");
}

/*
 * Costo Real Ciudad por Km =
 *   Amortizacion + Mantenimiento + Neumaticos + Seguro + Combustible Ciudad
 */
float calcularCostoRealCiudadPorKm(Vehiculo v, float precio_combustible_galon) {
    return calcularAmortizacionPorKm(v)
         + calcularMantenimientoPorKm(v)
         + calcularNeumaticosPorKm(v)
         + calcularSeguroPorKm(v)
         + calcularCombustibleCiudadPorKm(v, precio_combustible_galon);
}

/*
 * Costo Real Autopista por Km =
 *   Amortizacion + Mantenimiento + Neumaticos + Seguro + Combustible Autopista
 */
float calcularCostoRealAutopistaPorKm(Vehiculo v, float precio_combustible_galon) {
    return calcularAmortizacionPorKm(v)
         + calcularMantenimientoPorKm(v)
         + calcularNeumaticosPorKm(v)
         + calcularSeguroPorKm(v)
         + calcularCombustibleAutopistaPorKm(v, precio_combustible_galon);
}


/* ============================================================================
 *  MODULO 5: GESTION DE VEHICULOS (CRUD)
 * ==========================================================================*/

/*
 * imprimirVehiculo:
 * Muestra en pantalla los datos de un vehiculo, precedidos por un indice
 * (numero de lista) que el usuario usara para seleccionarlo en los menus.
 */
void imprimirVehiculo(Vehiculo v, int indice) {
    printf("--------------------------------------------------------\n");
    printf(" [%d] Modelo: %s\n", indice + 1, v.modelo);
    printf("     Precio de compra:        RD$ %.2f\n", v.precio_compra);
    printf("     Valor residual:          RD$ %.2f\n", v.valor_residual);
    printf("     Vida util:               %.0f km\n", v.vida_util_km);
    printf("     Km promedio anual:       %.0f km/anio\n", v.km_promedio_anual);
    printf("     Rendimiento ciudad:      %.2f km/Gal\n", v.rend_ciudad_kmgal);
    printf("     Rendimiento autopista:   %.2f km/Gal\n", v.rend_auto_kmgal);
    printf("     Mantenimiento preventivo:RD$ %.2f cada %.0f km\n",
           v.costo_mant_preventivo, v.intervalo_mant_km);
    printf("     Set de neumaticos:       RD$ %.2f (dura %.0f km)\n",
           v.costo_set_neumaticos, v.vida_neumaticos_km);
    printf("     Seguro anual:            RD$ %.2f\n", v.costo_seguro_anual);
}

/*
 * listarVehiculos:
 * Recorre todo el arreglo de vehiculos y los imprime uno por uno. Si no
 * hay vehiculos guardados, informa al usuario.
 */
void listarVehiculos(Vehiculo lista[], int total) {
    int i;

    if (total == 0) {
        printf("\nNo hay vehiculos guardados todavia.\n");
        return;
    }

    printf("\n===================== VEHICULOS GUARDADOS =====================\n");
    for (i = 0; i < total; i++) {
        imprimirVehiculo(lista[i], i);
    }
    printf("=================================================================\n");
}

/*
 * seleccionarVehiculo:
 * Muestra la lista de vehiculos y pide al usuario que elija uno por
 * numero. Devuelve el indice (0..total-1) del vehiculo elegido, o -1 si
 * no hay vehiculos o el usuario cancela con 0.
 */
int seleccionarVehiculo(Vehiculo lista[], int total) {
    int opcion;

    if (total == 0) {
        printf("\nNo hay vehiculos guardados. Cree uno primero.\n");
        return -1;
    }

    listarVehiculos(lista, total);
    printf("\nSeleccione el numero del vehiculo (0 para cancelar): ");
    opcion = (int) leerFloat("");

    if (opcion == 0) {
        return -1;
    }
    if (opcion < 1 || opcion > total) {
        printf("Numero fuera de rango.\n");
        return -1;
    }

    return opcion - 1; /* convertir de "numero mostrado" a indice de arreglo */
}

/*
 * crearVehiculo:
 * Pide al usuario, uno por uno, todos los parametros del vehiculo definidos
 * en la estructura, arma el registro y lo agrega al arreglo en memoria.
 * Luego persiste el arreglo completo en el archivo CSV.
 */
void crearVehiculo(Vehiculo lista[], int *total) {
    Vehiculo nuevo;

    if (*total >= MAX_VEHICULOS) {
        printf("\nSe alcanzo el limite maximo de %d vehiculos.\n", MAX_VEHICULOS);
        return;
    }

    printf("\n--- CREAR NUEVO VEHICULO ---\n");
    leerTexto("Modelo (identificador): ", nuevo.modelo, TAM_MODELO);

    nuevo.precio_compra          = leerFloat("Precio de compra: RD$ ");
    nuevo.valor_residual         = leerFloat("Valor residual al final de su vida util: RD$ ");
    nuevo.vida_util_km           = leerFloat("Vida util estimada (km): ");
    nuevo.km_promedio_anual      = leerFloat("Km promedio recorridos por anio: ");
    nuevo.rend_ciudad_kmgal      = leerFloat("Rendimiento en ciudad (km/Gal): ");
    nuevo.rend_auto_kmgal        = leerFloat("Rendimiento en autopista (km/Gal): ");
    nuevo.costo_mant_preventivo  = leerFloat("Costo de un mantenimiento preventivo: RD$ ");
    nuevo.intervalo_mant_km      = leerFloat("Intervalo entre mantenimientos (km): ");
    nuevo.costo_set_neumaticos   = leerFloat("Costo del set de 4 neumaticos: RD$ ");
    nuevo.vida_neumaticos_km     = leerFloat("Vida util de los neumaticos (km): ");
    nuevo.costo_seguro_anual     = leerFloat("Costo del seguro anual: RD$ ");

    lista[*total] = nuevo;
    (*total)++;

    guardarVehiculos(lista, *total);
    printf("\nVehiculo '%s' guardado correctamente.\n", nuevo.modelo);
}

/*
 * borrarVehiculo:
 * Permite elegir un vehiculo de la lista y lo elimina, desplazando los
 * elementos siguientes una posicion hacia atras para no dejar "huecos"
 * en el arreglo. Al final persiste los cambios en el archivo.
 */
void borrarVehiculo(Vehiculo lista[], int *total) {
    int indice;
    int i;

    printf("\n--- BORRAR VEHICULO ---");
    indice = seleccionarVehiculo(lista, *total);
    if (indice == -1) {
        return;
    }

    printf("\nSe eliminara el vehiculo '%s'. Esta accion no se puede deshacer.\n",
           lista[indice].modelo);

    /* Desplazar todos los vehiculos posteriores una posicion hacia atras */
    for (i = indice; i < (*total) - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*total)--;

    guardarVehiculos(lista, *total);
    printf("Vehiculo eliminado correctamente.\n");
}

/*
 * modificarVehiculo:
 * Permite elegir un vehiculo y luego editar, uno o varios campos, a
 * traves de un submenu. El usuario puede repetir la edicion de distintos
 * campos hasta que elija guardar y salir.
 */
void modificarVehiculo(Vehiculo lista[], int total) {
    int indice;
    int opcionCampo;
    int continuar = 1;
    Vehiculo *v; /* puntero al vehiculo elegido, para editarlo directamente */

    printf("\n--- MODIFICAR VEHICULO ---");
    indice = seleccionarVehiculo(lista, total);
    if (indice == -1) {
        return;
    }

    v = &lista[indice];

    while (continuar) {
        printf("\n--- Editando: %s ---\n", v->modelo);
        printf(" 1. Modelo (actual: %s)\n", v->modelo);
        printf(" 2. Precio de compra (actual: %.2f)\n", v->precio_compra);
        printf(" 3. Valor residual (actual: %.2f)\n", v->valor_residual);
        printf(" 4. Vida util en km (actual: %.0f)\n", v->vida_util_km);
        printf(" 5. Km promedio anual (actual: %.0f)\n", v->km_promedio_anual);
        printf(" 6. Rendimiento ciudad km/Gal (actual: %.2f)\n", v->rend_ciudad_kmgal);
        printf(" 7. Rendimiento autopista km/Gal (actual: %.2f)\n", v->rend_auto_kmgal);
        printf(" 8. Costo mantenimiento preventivo (actual: %.2f)\n", v->costo_mant_preventivo);
        printf(" 9. Intervalo de mantenimiento en km (actual: %.0f)\n", v->intervalo_mant_km);
        printf("10. Costo set de neumaticos (actual: %.2f)\n", v->costo_set_neumaticos);
        printf("11. Vida util de neumaticos en km (actual: %.0f)\n", v->vida_neumaticos_km);
        printf("12. Costo seguro anual (actual: %.2f)\n", v->costo_seguro_anual);
        printf(" 0. Terminar y guardar cambios\n");
        printf("Elija el campo a modificar: ");

        opcionCampo = (int) leerFloat("");

        switch (opcionCampo) {
            case 1:  leerTexto("Nuevo modelo: ", v->modelo, TAM_MODELO); break;
            case 2:  v->precio_compra         = leerFloat("Nuevo precio de compra: RD$ "); break;
            case 3:  v->valor_residual        = leerFloat("Nuevo valor residual: RD$ "); break;
            case 4:  v->vida_util_km          = leerFloat("Nueva vida util (km): "); break;
            case 5:  v->km_promedio_anual     = leerFloat("Nuevo km promedio anual: "); break;
            case 6:  v->rend_ciudad_kmgal     = leerFloat("Nuevo rendimiento ciudad (km/Gal): "); break;
            case 7:  v->rend_auto_kmgal       = leerFloat("Nuevo rendimiento autopista (km/Gal): "); break;
            case 8:  v->costo_mant_preventivo = leerFloat("Nuevo costo mantenimiento: RD$ "); break;
            case 9:  v->intervalo_mant_km     = leerFloat("Nuevo intervalo de mantenimiento (km): "); break;
            case 10: v->costo_set_neumaticos  = leerFloat("Nuevo costo set de neumaticos: RD$ "); break;
            case 11: v->vida_neumaticos_km    = leerFloat("Nueva vida util de neumaticos (km): "); break;
            case 12: v->costo_seguro_anual    = leerFloat("Nuevo costo de seguro anual: RD$ "); break;
            case 0:  continuar = 0; break;
            default: printf("Opcion invalida.\n"); break;
        }
    }

    guardarVehiculos(lista, total);
    printf("\nCambios guardados correctamente.\n");
}


/* ============================================================================
 *  MODULO 6: CALCULO DE VIAJE
 * ==========================================================================*/

/*
 * calcularViaje:
 * Pide un vehiculo, los km a recorrer en ciudad y en autopista, y muestra
 * dos resultados:
 *   1) Costo SOLO en combustible del viaje.
 *   2) Costo REAL del viaje (incluye amortizacion, mantenimiento,
 *      neumaticos y seguro, ademas del combustible).
 */
void calcularViaje(Vehiculo lista[], int total, float precio_combustible_galon) {
    int indice;
    Vehiculo v;
    float kmCiudad, kmAutopista;

    float costoCombustibleCiudadKm, costoCombustibleAutopistaKm;
    float costoRealCiudadKm, costoRealAutopistaKm;

    float costoSoloCombustible;
    float costoRealTotal;

    printf("\n--- CALCULAR COSTO DE VIAJE ---");
    indice = seleccionarVehiculo(lista, total);
    if (indice == -1) {
        return;
    }
    v = lista[indice];

    kmCiudad    = leerFloat("Km a recorrer en CIUDAD: ");
    kmAutopista = leerFloat("Km a recorrer en AUTOPISTA: ");

    /* Costos por km segun el modelo matematico (Modulo 4) */
    costoCombustibleCiudadKm    = calcularCombustibleCiudadPorKm(v, precio_combustible_galon);
    costoCombustibleAutopistaKm = calcularCombustibleAutopistaPorKm(v, precio_combustible_galon);
    costoRealCiudadKm           = calcularCostoRealCiudadPorKm(v, precio_combustible_galon);
    costoRealAutopistaKm        = calcularCostoRealAutopistaPorKm(v, precio_combustible_galon);

    /* Costo total del viaje = (costo por km en ciudad * km ciudad)
     *                       + (costo por km en autopista * km autopista) */
    costoSoloCombustible = (costoCombustibleCiudadKm * kmCiudad)
                          + (costoCombustibleAutopistaKm * kmAutopista);

    costoRealTotal        = (costoRealCiudadKm * kmCiudad)
                          + (costoRealAutopistaKm * kmAutopista);

    printf("\n===================== RESULTADO DEL VIAJE =====================\n");
    printf(" Vehiculo: %s\n", v.modelo);
    printf(" Precio de combustible usado: RD$ %.2f por galon\n", precio_combustible_galon);
    printf(" Km en ciudad: %.1f   |   Km en autopista: %.1f\n", kmCiudad, kmAutopista);
    printf("-----------------------------------------------------------------\n");
    printf(" Costo por km (solo combustible)  -> Ciudad: RD$ %.4f | Autopista: RD$ %.4f\n",
           costoCombustibleCiudadKm, costoCombustibleAutopistaKm);
    printf(" Costo por km (costo REAL)        -> Ciudad: RD$ %.4f | Autopista: RD$ %.4f\n",
           costoRealCiudadKm, costoRealAutopistaKm);
    printf("-----------------------------------------------------------------\n");
    printf(" >> Costo SOLO en combustible del viaje: RD$ %.2f\n", costoSoloCombustible);
    printf(" >> Costo REAL del viaje (todo incluido): RD$ %.2f\n", costoRealTotal);
    printf("===================================================================\n");
}


/* ============================================================================
 *  MODULO 7: MENU PRINCIPAL E INTERFAZ DE CONSOLA
 * ==========================================================================*/

void mostrarMenu(void) {
    printf("\n=========================================================\n");
    printf("   CALCULADORA DE AMORTIZACION Y COSTO REAL DE VEHICULOS\n");
    printf("=========================================================\n");
    printf(" 1. Crear vehiculo\n");
    printf(" 2. Borrar vehiculo\n");
    printf(" 3. Modificar parametros de un vehiculo\n");
    printf(" 4. Modificar precio del combustible\n");
    printf(" 5. Calcular viaje\n");
    printf(" 6. Salir\n");
    printf("=========================================================\n");
    printf("Seleccione una opcion: ");
}

int main(void) {
    Vehiculo listaVehiculos[MAX_VEHICULOS];
    int   totalVehiculos;
    float precio_combustible_galon;
    int   opcion;
    int   ejecutando = 1;

    /* Al iniciar, se cargan los vehiculos y el precio de combustible desde
     * disco. Si los archivos no existen, las funciones de persistencia los
     * crean automaticamente (ver Modulo 3). */
    totalVehiculos            = cargarVehiculos(listaVehiculos);
    precio_combustible_galon  = cargarPrecioCombustible();

    printf("Se cargaron %d vehiculo(s) desde '%s'.\n", totalVehiculos, ARCHIVO_VEHICULOS);
    printf("Precio de combustible actual: RD$ %.2f por galon\n", precio_combustible_galon);

    while (ejecutando) {
        mostrarMenu();
        opcion = (int) leerFloat("");

        switch (opcion) {
            case 1:
                crearVehiculo(listaVehiculos, &totalVehiculos);
                pausar();
                break;

            case 2:
                borrarVehiculo(listaVehiculos, &totalVehiculos);
                pausar();
                break;

            case 3:
                modificarVehiculo(listaVehiculos, totalVehiculos);
                pausar();
                break;

            case 4:
                printf("\nPrecio de combustible actual: RD$ %.2f por galon\n", precio_combustible_galon);
                precio_combustible_galon = leerFloat("Nuevo precio de combustible (RD$ por galon): ");
                guardarPrecioCombustible(precio_combustible_galon);
                printf("Precio de combustible actualizado.\n");
                pausar();
                break;

            case 5:
                calcularViaje(listaVehiculos, totalVehiculos, precio_combustible_galon);
                pausar();
                break;

            case 6:
                printf("\nSaliendo del programa. Todos los datos ya estan guardados.\n");
                ejecutando = 0;
                break;

            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
                pausar();
                break;
        }
    }

    return 0;
}
