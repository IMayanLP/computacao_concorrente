#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define TAMANHO 100000000
#define MAX 100000

int main() {
    time_t t;
    srand((unsigned) time(&t));

    long int *v;
    v = (long int*)malloc(TAMANHO * sizeof(long int));
    int i;
    for(i = 0; i < TAMANHO; i++) {
        int num = 1 + (rand() % MAX);
        v[i] = num;
    }

    // Execução Serial
    int maiorSerial = v[0];
    int indiceSerial;
    double inicio = omp_get_wtime();
    for(i = 1; i < TAMANHO; i++) {
        if(v[i] > maiorSerial) {
            maiorSerial = v[i];
            indiceSerial = i;
        }
    }
    double fim = omp_get_wtime();
    double t_serial = fim - inicio;

    printf("Tempo execucao Sequencial: %fseg\n", t_serial);
    printf("Maior valor é: v[%d]=%d\n", indiceSerial, maiorSerial);
    
    //Execução Paralela
    int maiorParalelo = v[0];
    int indiceParalelo;
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        double maior_thread = v[0];
        long int indice = TAMANHO;
        #pragma omp for
            for(i = 1; i < TAMANHO; i++) {
                if(v[i] > maior_thread) {
                    maior_thread = v[i];
                    indice = i; 
                }
            }
        #pragma omp critical
            if(maior_thread > maiorParalelo) {
                maiorParalelo = maior_thread;
                indiceParalelo = indice;
            }
    }
    fim = omp_get_wtime();
    double t_paralelo = fim - inicio;

    printf("Tempo execucao paralela: %fseg\n",t_paralelo);
    printf("Maior valor é: v[%d]=%d\n", indiceParalelo, maiorParalelo);

    printf("Speedup: %f\n", t_serial/t_paralelo);

    return 0;
}