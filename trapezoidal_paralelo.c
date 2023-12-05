/* Version paralela de la regla de trapecio para calcular el area bajo la curva de una función
 * Proyecto 4 -- IE0521 - Estructuras de computadoras II
 * Grupo 1:
 *      Marvin Castro Castro
 *      Andrés Chaves Vargas
 *      Kevin Delgado Rojas
 *      Gabriel Briceño Cambronero
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>


void regla_trapezoide(int num_trapecios, double lim_izq, double lim_der, double *resultado_final);
int cant_threads = 6;                   // Cantidad de threads con los que se ejecuta el programa

int main(int argc, char* argv[]) {
    clock_t start, end;
    double cpu_time_used;
    double lim_izq,  lim_der, resultado_final;
    int num_trapecios;
    num_trapecios = 1000000000;         // Cantidad de trapecios con los que se calcula el área
    lim_izq = 0.0;                      // Límite izquierdo para el cálculo del área
    lim_der = 3.1415926;                       // Límite derecho para el cálculo del área
    resultado_final = 0.0;

    start = clock();                    // Inicio de reloj
#   pragma omp parallel num_threads(cant_threads)       // sección paralela del código
    regla_trapezoide(num_trapecios,  lim_izq,  lim_der, &resultado_final);

    end = clock();                      // Fin de reloj
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Area bajo la curva: %lf \n", resultado_final);
    printf("Time used: %f seconds\n", cpu_time_used);
}
// función f(x) a calcular el área: f(x) = 1 + sin(x)
double funcion(double x) {
    return (1.0 + sin(x));
}

/* Función para la regla de trapecio
// Recibe:  num_trapecios: cantidad de trapecios con los que se correrá el programa
            lim_izq: límite izquierdo o inferior de la integral
            lim_der: limite derecho o superior de la integral
   Da:      *resultado: Resultado final del área
  */
void regla_trapezoide(int num_trapecios, double  lim_izq, double  lim_der, double *resultado){

    int core_actual = omp_get_thread_num();         // Número del thread que está corriendo la sección
    printf("Num threads: %d \n", omp_get_num_threads());
    int cant_local_trapecios;
    double local_izq, local_der;

    double h, x, total;
    int i;

    h = ( lim_der- lim_izq)/num_trapecios;      // Ancho de cada trapecio - Entre más trapecios, menor el ancho, menor error
    cant_local_trapecios = num_trapecios/cant_threads;  // Cantidad de trapecios que le toca calcular a cada thread
    local_izq = lim_izq + core_actual*cant_local_trapecios*h;  // límite izquierdo para cierto trapecio de cierto thread
    local_der = local_izq + cant_local_trapecios*h; // límite derecho para cierto trapecio de cierto thread

    total = (funcion( local_izq) + funcion( local_der))/2.0;    // Regla de trapecio
    for(i = 1; i <= cant_local_trapecios - 1; i ++){                  // iterar en todos los trapecios locales
        x =  local_izq + i*h;
        total += funcion(x);

    }
    total = total * h;
#   pragma omp critical         // Region crítica
    *resultado += total;        // un solo thread se encarga de actualizar el resultado total
}