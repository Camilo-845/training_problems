
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int Kill(int pid, int sig) {
  usleep(1000);
  return kill(pid, sig);
}

void handler(int sig) {}

int main() {
  int i = 0, j = 0;
  pid_t pid = fork();
  pid_t spids[2];
  signal(SIGUSR1, handler);
  // Creacion de creacion de procesos
  if (pid == 0) {
    i++;
    pid = fork();
    if (pid == 0) {
      i++;
    }
  }
  if (i == 2) {
    for (; j < 2; j++) {
      pid = fork();
      spids[j] = pid;
      if (pid == 0) {
        break;
      }
    }
  }

  // Logica de señales

  // Padre
  if (i == 0) {
    printf("soy el padre, pid(%d)\n", pid);
    Kill(pid, SIGUSR1);
    pause();
    printf("Soy el padre, pid(%d)\n", pid);
  }
  // Hijo 1
  else if (i == 1) {
    pause();
    printf("Soy el hijo 1, pid(%d)\n", pid);
    Kill(pid, SIGUSR1);
    pause();
    printf("Soy el hijo 1, pid(%d)\n", pid);
    Kill(getppid(), SIGUSR1);
  } else if (i == 2) {
    // Hijo 21
    if (j == 0) {
      pause();
      printf("Soy el hijo 21, pid(%d)\n", pid);
      Kill(getppid(), SIGUSR1);
    }
    // Hijo 22
    if (j == 1) {
      pause();
      printf("Soy el hijo 22, pid(%d)\n", pid);
      Kill(getppid(), SIGUSR1);
    }
    // Hijo 2
    if (j == 2) {
      pause();
      printf("Soy el hijo 2, pid(%d)\n", pid);
      Kill(spids[1], SIGUSR1);
      pause();
      printf("Soy el hijo 2, pid(%d)\n", pid);
      Kill(spids[0], SIGUSR1);
      pause();
      printf("Soy el hijo 2, pid(%d)\n", pid);
      Kill(getppid(), SIGUSR1);
    }
  }
  return 0;
}
