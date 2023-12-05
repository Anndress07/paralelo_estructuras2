
# Proyecto Paralelización IE-0521

Se implementa el algoritmo de regla del trapecio para el cálculo de áreas bajo la curva y se paraleliza utilizando OpenMP en C.




## Compilación
Sin paralelización: gcc -o ejemplo trapezoidal.c -lm \\
Con paralelización: gcc -o openmp01 -fopenmp trapezoidal_paralelo.c -lm
