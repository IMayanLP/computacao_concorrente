#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUMSTEPS 1000000000

int main() {
    double x, pi, somaS = 0.0, somaP = 0.0;
    double step;


    double t_ini = omp_get_wtime();
    step = 1.0 / NUMSTEPS;

    int i;
    for(i = 0; i < NUMSTEPS; i++) {
        x = (i + 0.5) * step;
        somaS = somaS + 4.0 / (1.0 + x * x);
    }
    pi = step * somaS;
    
    double t_fim = omp_get_wtime();
    double t_s = t_fim - t_ini;
    printf("Tempo sequencial: %fs\nPi: %f\n", t_s, pi);


    x = 0; // reinicializando as variaveis
    pi = 0;
    t_ini = omp_get_wtime();
    step = 1.0 / NUMSTEPS;

    #pragma omp parallel private(somaP, x)num_threads(3)
    {
        #pragma omp for
            for(i = 0; i < NUMSTEPS; i++) {
                x = (i + 0.5) * step;
                somaP = somaP + 4.0 / (1.0 + x * x); 
            }
        #pragma omp critical
            pi += somaP * step;
    }

    t_fim = omp_get_wtime();
    double t_p = t_fim - t_ini;
    printf("Tempo paralelo: %fs\nPi: %f\n",t_p, pi);
    printf("Speedup: %f\n", (t_s/t_p));
    return 0;
}