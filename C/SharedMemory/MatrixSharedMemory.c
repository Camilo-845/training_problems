
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int Kill(int pid, int sig) {
  usleep(1000);
  return kill(pid, sig);
}

void handler(int sig) {}

unsigned int sizeof_dm(int rows, int cols, size_t sizeElement) {
  size_t size;
  size = rows * sizeof(void *);
  size += (cols * rows * sizeElement);
  return size;
}

void create_index(void **m, int rows, int cols, size_t sizeElement) {
  int i;
  size_t sizeRow = cols * sizeElement;
  m[0] = m + rows;
  for (i = 1; i < rows; i++) {
    m[i] = (m[i - 1] + sizeRow);
  }
}

int main() {
  int **matrix = NULL;
  int Rows = 15, Cols = 3;
  size_t sizeMatrix = sizeof_dm(Rows, Cols, sizeof(int));
  int shmId = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT | 0600);
  matrix = shmat(shmId, NULL, 0);
  create_index((void *)matrix, Rows, Cols, sizeof(int));
  signal(SIGUSR1, handler);

  pid_t pid = fork();
  if (pid != 0) {
    // Padre
    for (int i = 0; i < Rows; i++) {
      for (int j = 0; j < Cols; j++) {
        matrix[i][j] = (i * Cols) + j;
      }
    }
    Kill(pid, SIGUSR1);

  } else {
    // Hijo
    pause();
    for (int i = 0; i < Rows; i++) {
      printf("\n");
      for (int j = 0; j < Cols; j++) {
        printf("%d", matrix[i][j]);
      }
    }
  }
}
