#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define TAM 500000000
#define MAX 100000
#define NUM_THREADS 4

int main () {
    time_t t;
    srand((unsigned) time(&t));
    long int *v;
    v = (long int*)malloc(TAM*sizeof(long int));
    int i;
    double t_inicio = 0.0, t_fim = 0.0;
    double somaSerial = 0.0, somaParalela = 0.0;

    for(i = 0; i < TAM; i++) {
        int num = 1 + (rand() % (MAX + 1));
        v[i] = num;
    }
    
    t_inicio = omp_get_wtime(); // pega o tempo no inicio da execução serial
    for(i = 0; i < TAM; i++) {
        somaSerial += v[i];
    }

    t_fim = omp_get_wtime(); // pega o tempo no final da execução serial

    double t_serial = t_fim - t_inicio;
    printf("Tempo Sequencial: %f\n", t_serial);
    printf("Media do vetor: %f\n", (somaSerial / TAM));


    t_inicio = omp_get_wtime(); // pega o tempo no inicio da execução paralela
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for reduction (+:somaParalela)
            for (i = 0; i < TAM; i++) {
                somaParalela += v[i];
            }
    }
    
    t_fim = omp_get_wtime(); // pega o tempo no fim da execução paralela
    double t_paralelo = t_fim - t_inicio;
    printf("Tempo Paralela: %f\n", t_paralelo);
    printf("Media do vetor: %f\n", (somaParalela / TAM));

    double speedUp = t_serial / t_paralelo;
    printf("Speedup: %f\n", speedUp);
    printf("Eficiencia: %f\n", speedUp / NUM_THREADS);

    return 0;
}