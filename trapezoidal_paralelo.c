/* Version serial de la regla de trapezoide
 * para calcular el area bajo la curva de una función */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define pi 3.14159265358
void regla_trapezoide(int num_trapecios, double lim_izq, double lim_der, double *resultado_final);
int cant_threads = 6;

int main(int argc, char* argv[]) {

    clock_t start, end;
    double cpu_time_used;
    double lim_izq,  lim_der, resultado_final;
    int num_trapecios;
    num_trapecios = 1000000000;
    lim_izq = 0.0;
    lim_der = pi;
    resultado_final = 0.0;

    //if (argc == 2)
    //{
    //    cant_threads = strtol(argv[1], NULL, 10);
    //}

    start = clock();
#   pragma omp parallel num_threads(cant_threads)
    regla_trapezoide(num_trapecios,  lim_izq,  lim_der, &resultado_final);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Area bajo la curva: %lf \n", resultado_final);
    printf("Time used: %f seconds\n", cpu_time_used);
}

double funcion(double x) {
    return (1.0 + sin(x));
}

void regla_trapezoide(int num_trapecios, double  lim_izq, double  lim_der, double *resultado){

    int core_actual = omp_get_thread_num();
    //int cant_threads = omp_get_num_threads();
    printf("Num threads: %d \n", omp_get_num_threads());
    int cant_local_trapecios;
    double local_izq, local_der;

    double h, x, total;
    int i;

    h = ( lim_der- lim_izq)/num_trapecios;
    cant_local_trapecios = num_trapecios/cant_threads;
    local_izq = lim_izq + core_actual*cant_local_trapecios*h;
    local_der = local_izq + cant_local_trapecios*h;

    total = (funcion( local_izq) + funcion( local_der))/2.0;
    for(i = 1; i <= cant_local_trapecios - 1; i ++){
        x =  local_izq + i*h;
        total += funcion(x);

    }
    total = total * h;
#   pragma omp critical
    *resultado += total;
}