#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main() {
  int num;
  MPI_Init(NULL, NULL);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int nprocs;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  if (rank == 0) {
    num = 42;
    MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    printf("[Processo: %d, Mensagem %d]\n", rank, num);
  }
  else if (rank == 1) {
    MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("[Processo: %d, Mensagem %d]", rank, num);
  }

  MPI_Finalize();
  return 0;
}