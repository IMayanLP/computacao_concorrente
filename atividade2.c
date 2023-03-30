#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUMSTEPS 100000000
#define NUM_THREADS 3

int main() {
    double step;
    int i;
    double x, pi, somaS = 0.0, somaP = 0.0;

    double t_inicio = omp_get_wtime();
    step = 1.0 / NUMSTEPS;

    for(i = 0; i < NUMSTEPS; i++) {
        x = (i + 0.5) * step;
        somaS = somaS + 4.0 / (1.0 + x * x);
    }

    pi = step * somaS;
    double t_fim = omp_get_wtime();
    double t_serial = t_fim - t_inicio;
    printf("Tempo Sequencial: %f\nPi: %f\n", t_serial, pi);

    x = 0;
    pi = 0;
    t_inicio = omp_get_wtime();
    step = 1.0 / NUMSTEPS;

    #pragma omp parallel private (x) num_threads(NUM_THREADS)
    {
        #pragma omp for reduction (+:somaP)
            for(i = 0; i < NUMSTEPS; i++) {
                x = (i + 0.5) * step;
                somaP = somaP + 4.0 / (1.0 + x * x);
            }
    }

    pi = step * somaP;
    t_fim = omp_get_wtime();
    double t_paralelo = t_fim - t_inicio;
    double speedup = t_serial/t_paralelo;

    printf("Tempo Sequencial: %f\nPi: %f\n", t_paralelo, pi);
    
    printf("Speedup: %f\n", speedup);
	printf("Eficiencia: %f\n",speedup/NUM_THREADS);
    return 0;
}
