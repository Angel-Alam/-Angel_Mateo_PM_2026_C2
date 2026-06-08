#include <stdio.h>
/* Universidad.
El programa, al recibir información sobre el número de alumnos que han ingresado
➥a sus ocho diferentes carreras en los dos semestres lectivos de los últimos
➥cinco años, obtiene información útil para el departamento de escolar. */
const int F = 8, C = 2, P = 5;
/* Se declaran constantes para la fila, la columna y la profundidad. */
void Lectura(int [][C][P], int, int, int);
6.5 Declaración de arreglos tridimensionales 223
6
voidFuncion1(int[][C][P], int, int, int);
void Funcion2(int [][C][P], int, int, int);
void Funcion3(int[][C][P], int, int, int);
/* Prototipo de funciones. Cada prototipo de función corresponde a uno de los
➥incisos. */
voidmain(void)
{
intUNI[F][C][P];
Lectura(UNI, F, C, P);
Funcion1(UNI, F, C, P);
Funcion2(UNI, F, C, P);
Fu     Funcion3(UNI, 6, C, P);
/* Se coloca el 6como parámetro ya que es la clave de la Ingeniería en
➥Computación. */
}
voidLectura(int A[][C][P], intFI, intCO, intPR)
/* La función Lecturase utiliza para leer un arreglo tridimensional de tipo
➥entero de FIfilas, COcolumnas y PRprofundidad. Observa que al ser
➥tridimensional se necesitan tres ciclos para recorrer el arreglo. */
{
intK, I, J;
for(K=0; K<PR; K++)
for(I=0; I<FI; I++)
for(J=0; J<CO; J++)
{
printf(”Año: %d\tCarrera: %d\tSemestre: %d  ”, K+1, I+1, J+1);
scanf(”%d”, &A[I][J][K]);
}
}
voidFuncion1(intA[][C][P],intFI, intCO, intPR)
/* Esta función se utiliza para determinar el año en el que ingresó el mayor
➥número de alumnos a la universidad. Observa que el primer ciclo externo
➥corresponde a los años. */
{
intK, I, J, MAY = 0, AO = -1, SUM;
for (K=0; K<PR; K++)
/* Por cada año se suma el ingreso de los dos semestres de las ocho carreras.
*/
{
SUM = 0;
for (I=0; I<FI; I++)
for (J=0; J<CO; J++)
SUM += A[I][J][K];
if (SUM > MAY)
{
MAY = SUM;
AO = K;
}
A continuación presentamos una serie de problemas resueltos y después de éstos
veremos problemas suplementarios cuidadosamente seleccionados.
224 Capítulo 6. Arreglos multidimensionales
}
printf(”\n\nAño con mayor ingreso de alumnos: %d    Alumnos: %d”, AO+1, MAY);
}
voidFuncion2(intA[][C][P],intFI, intCO, intPR)
/* Esta función se utiliza para determinar la carrera que recibió el mayor
➥número de alumnos el último año. Observa que no se utiliza un ciclo para los
➥planos de la profundidad, ya que es un dato (PR). */
{
intI, J, MAY = 0, CAR = -1, SUM;
for (I=0; I<FI; I++)
{
SUM = 0;
for (J=0; J<CO; J++)
SUM += A[I][J][PR-1];
if (SUM > MAY)
{
MAY = SUM;
CAR = I;
}
}
printf(”\n\nCarrera con mayor número de alumnos: %d  Alumnos: %d”, CAR+1,
MAY);
}
voidFuncion3(intA[][C][P],intFI, intCO, intPR)
/* Esta función se utiliza para determinar el año en el que la carrera
➥Ingeniería en Computación recibió el mayor número de alumnos. Observa que no
➥se utiliza un ciclo para trabajar con las filas, ya que es un dato (FI). */
{
intK, J, MAY = 0, AO = -1, SUM;
for (K=0; K<PR; K++)
{
SUM = 0;
for (J=0; J<CO; J++)
SUM += A[FI-1][J][K];
if (SUM > MAY)
{
MAY = SUM;
AO = K;
}
}
printf(”\n\nAño con mayor ingreso de alumnos: %d   Alumnos: %d”, AO+1, MAY);
}
