
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  int i = 0, nProcess = 2;
  printf("n procesos: ");
  scanf("%d", &nProcess);
  // Arreglo de descriptores de archivo 0 -> Lectura, 1-> Escritura
  int tubs[nProcess + 1][2];
  // Crea un canal de comunicación
  for (int j = 0; j < nProcess + 1; j++) {
    pipe(tubs[j]);
  } // Creación de procesos
  for (; i < nProcess; i++) {
    if (!fork())
      break;
  }

  // Proceso Padre
  if (i == nProcess) {
    // Pipe de escritura
    close(tubs[i][0]);
    char *msg = "mensaje";
    write(tubs[i][1], msg, strlen(msg));
    close(tubs[i][1]);
    char buffer[100];
    close(tubs[0][1]);
    read(tubs[0][0], buffer, sizeof(buffer));
    close(tubs[0][0]);
    printf("%s\n", buffer);
  } else {
    // Tiene 2 pipes en la primera es lector y el la segundo escritor
    // Pipe Lectura (i+1)
    close(tubs[i + 1][1]);
    char buffer[100];
    read(tubs[i + 1][0], buffer, sizeof(buffer));
    close(tubs[i + 1][0]);
    printf("Mensaje (%s) pasando por proceso [%d]\n", buffer, i);
    // Pipe de Escritura (i)
    close(tubs[i][0]);
    write(tubs[i][1], buffer, strlen(buffer));
    close(tubs[i][1]);
  }
  return 0;
}
