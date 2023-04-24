#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define TAMANHO 100000000

int main() {
    time_t t;
    srand((unsigned) time(&t));

    float *v;
    v = (float*)malloc(TAMANHO * sizeof(float));
    int i;
    for(i = 0; i < TAMANHO; i++) {
        int num = (float) rand() / RAND_MAX;
        v[i] = num;
    }

    // EXECUÇÃO SEQUENCIAL

    float somaSerial = 0;
    double inicio = omp_get_wtime();
    for(i = 0; i < TAMANHO; i++) {
        somaSerial += v[i];
    }
    float media = somaSerial / TAMANHO;

    somaSerial = 0;
    for(i = 0; i < TAMANHO; i++) {
        somaSerial += pow(v[i] - media, 2);
    }

    float dp_serial = sqrt(somaSerial / TAMANHO);

    double fim = omp_get_wtime();
    double t_serial = fim - inicio;
    
    printf("Tempo execucao Sequencial: %fseg\n", t_serial);
    printf("Desvio padrão: %f", dp_serial);

    // EXECUÇÃO PARALELA
    float somaParalela = 0;
    float mediaParalela = 0;
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        float somaThread = 0;
        #pragma omp for
            for(i = 0; i < TAMANHO; i++) {
                somaThread += v[i];
            }
        #pragma omp critical
            mediaParalela += somaThread / TAMANHO;

        somaThread = 0;
        #pragma omp for
            for(i = 0; i < TAMANHO; i++) {
                somaThread += pow(v[i] - mediaParalela, 2);
            }
        #pragma omp critical
            somaParalela += somaThread;
    }
    float dp_paralelo = sqrt(somaParalela / TAMANHO);

    fim = omp_get_wtime();
    double t_paralelo = fim - inicio;

    printf("Tempo execucao Paralela: %fseg\n", t_paralelo);
    printf("Desvio padrão: %f", dp_paralelo);

    return 0;
}