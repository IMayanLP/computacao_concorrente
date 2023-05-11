#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>

#define TAMANHO 1000

int main() {
    MPI_Init(NULL, NULL);
    int nprocs, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        time_t t;
        srand((unsigned) time(&t));
        
        long int somaT,somaT_2;
        long int *vetor;
        vetor = malloc(TAMANHO*sizeof(long int));
        for (int i = 0;i < TAMANHO; i++) {
            long int num = (rand() % (TAMANHO+1));
            vetor[i] = num;
        }
        MPI_Bcast(vetor,TAMANHO,MPI_LONG,0,MPI_COMM_WORLD);
        MPI_Recv(&somaT, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&somaT_2, 1, MPI_LONG, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Total: %ld\nTotal dobro: %ld",somaT, somaT_2);
   } else {
        long int *vetor;
        vetor = malloc(TAMANHO*sizeof(long int));
        MPI_Bcast(vetor,TAMANHO,MPI_LONG,0,MPI_COMM_WORLD);
        long int soma = 0;
        for (int i = 0; i < TAMANHO; i++) {
            if (rank == 1) soma += vetor[i];
            else if (rank == 2) soma += 2 * vetor[i];
        }
        MPI_Send(&soma, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
   }
    MPI_Finalize();
    return 0;
}
