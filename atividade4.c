#include <omp.h>
#include <stdio.h>
#include <time.h>

#define NUM 100000000

int main() {
    double somaS = 0.0, somaP = 0.0;

    double t_i = omp_get_wtime();
    int i;
    for(i = 1; i <= NUM; i++) {
        if(NUM % i == 0) {
            somaS += i;
        }
    }

    double t_f = omp_get_wtime();
    double t_s = t_f - t_i;
    printf("Tempo Sequencial: %fs\nSoma Sequencial: %f\n", t_s, somaS);


    t_i = omp_get_wtime();
    double somaP2 = 0.0;
    #pragma omp parallel private(somaP) num_threads(3)
    {
        #pragma omp for
            for(i = 1; i <= NUM; i++) {
                if(NUM % i == 0) {
                    somaP += i;
                }
            }
        #pragma omp critical
            somaP2 += somaP;
    }
    t_f = omp_get_wtime();
    double t_p = t_f - t_i;
    printf("Tempo paralelo: %fs\nSoma Paralela: %f\n",t_p, somaP2);
    printf("Speedup: %f\n", (t_s/t_p));


    t_i = omp_get_wtime();
    double somaStatic = 0.0;
    #pragma omp parallel num_threads(3)
    {
        double soma = 0.0;
        #pragma omp for schedule(static, 3)
            for(i = 1; i <= NUM; i++) {
                if(NUM % i == 0) {
                    soma += i;
                }
            }
        #pragma omp critical
            somaStatic += soma;
    }
    t_f = omp_get_wtime();
    double t_ps = t_f - t_i;
    printf("Tempo paralelo static: %fs\nSoma Paralela Static: %f\n", t_ps, somaStatic);
    printf("Speedup: %f\n", (t_s/t_ps));


    t_i = omp_get_wtime();
    double somaDynamic = 0.0;
    #pragma omp parallel num_threads(3)
    {
        double soma = 0.0;
        #pragma omp for schedule(dynamic, 3)
            for(i = 1; i <= NUM; i++) {
                if(NUM % i == 0) {
                    soma += i;
                }
            }
        #pragma omp critical
            somaDynamic += soma;
    }
    t_f = omp_get_wtime();
    double t_pd = t_f - t_i;
    printf("Tempo paralelo dynamic: %fs\nSoma paralelo dynamic: %f\n", t_pd, somaDynamic);
    printf("Speedup: %f\n", (t_s/t_pd));
    return 0;
}
