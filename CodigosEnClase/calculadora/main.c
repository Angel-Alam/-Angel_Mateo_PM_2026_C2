#include <stdio.h>
#include <stdlib.h>
#define SALIR 0
#define SUMAR 1
#define RESTA 2
#define MULTIPLICACION 3
#define DIVICION 4
#define ERR_OK 0
#define ERR_DivByZero 566
//Concepto de Funcion
//Concepto de puntero
//Concepto de ambito y ciclo de vida de variables
//* operador de indireccion
//& operador de direccion



//declaracion de funcion
int Suma(double num1,double num2, double *result);
int Resta(double num1,double num2, double *result);
int Multiplicacion(double num1,double num2, double *result);
int Divicion(double numerador,double denominador, double *result);
void entrada(int op);
void salida(double numero);



//variables globales
double n1 = 0.0;//esta variable siempre esta en memoria
double n2 = 0.0;
int main()
{
    int menu = -1;
    int cod_err = ERR_OK;
    //double n1 = 0.0;
    //double n2 = 0.0;
    double buff = 0.0;
    printf("\n---CALCULADORA---");



    do
    {
        printf("\n0-Salir\n1-Sumar\n2-Restar\n3-Multiplicar\n4-Dividir\n");
        scanf("%i",&menu);
        if(menu == SUMAR)
        {
            entrada(SUMAR);
            Suma(n1,n2,&buff);
            salida(buff);
        }
        else if(menu == RESTA)
        {



        }
        else if(menu == MULTIPLICACION)
        {



        }
        else if(menu == DIVICION)
        {
            entrada(DIVICION);
            cod_err = Divicion(n1,n2,&buff);
            if(cod_err != ERR_OK)
            {
               if(cod_err == ERR_DivByZero)
               {
                   printf("\nError de divicion por cero");
               }
            }else
            {
               salida(buff);
            }



        }
        else
        {
            printf("\nOpccion no valida solo 0-4");
        }
    }
    while(menu != 0);



    return 0;
}



int Suma(double num1,double num2, double *result)
{
    *result = num1 + num2;
    return ERR_OK;
}
int Resta(double num1,double num2, double *result)
{
    *result = num1 - num2;
    return ERR_OK;
}
int Multiplicacion(double num1,double num2, double *result)
{
    *result = num1 * num2;
    return ERR_OK;
}
int Divicion(double numerador,double denominador, double *result)
{
    if(denominador == 0.0)
    {
        return ERR_DivByZero;
    }
    else
    {
        *result = numerador / denominador;
        return ERR_OK;
    }
}
void entrada(int op)
{
    if(op == SUMAR || op == MULTIPLICACION)
    {
        printf("\nIngresa el primer operando:");
        scanf("%lf",&n1);
        printf("\nIngresa el segundo operando:");
        scanf("%lf",&n2);
    }
    else if(op == RESTA)
    {
        printf("\nIngresa el sustraendo:");
        scanf("%lf",&n1);
        printf("\nIngresa el minuendo:");
        scanf("%lf",&n2);
    }
    else if(op == DIVICION)
    {
        printf("\nIngresa el numerador:");
        scanf("%lf",&n1);
        printf("\nIngresa el denominador:");
        scanf("%lf",&n2);
    }
    else
    {
        printf("\nError[822] de operacion al ingresar datos.");
    }
}
void salida(double numero)
{
    printf("\nResultado:%lf\n",numero);
}


