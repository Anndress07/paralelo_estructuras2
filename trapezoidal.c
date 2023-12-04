/* Version serial de la regla de trapezoide
 * para calcular el area bajo la curva de una función */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define pi 3.14159265358
void regla_trapezoide(int num_trapecios, double lim_izq, double lim_der, double *resultado_final);

int main(void) {
    clock_t start, end;
    double cpu_time_used;
    double lim_izq,  lim_der, resultado_final;
    int num_trapecios;
    num_trapecios = 1500000000;
     lim_izq = 0.0;
     lim_der = pi;
    resultado_final = 0.0;
    start = clock();

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

    double h, x, total;
    int i;

    h = ( lim_der- lim_izq)/num_trapecios;

    total = (funcion( lim_izq) + funcion( lim_der))/2.0;
    for(i = 1; i <= num_trapecios - 1; i ++){
        x =  lim_izq + i*h;
        total += funcion(x);

    }
    total = total * h;
    *resultado = total;
}