
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// Utilidad de error
void error(char *msg) {
  perror(msg);
  exit(-1);
}

// Lee enteros de un archivo de texto, retorna en número de enteros leídos
int readNumbers(char *filename, int **vec) {
  int c, number, totalNumbers;
  FILE *infile;
  infile = fopen(filename, "r");
  if (!infile) {
    error("error fopen");
  }
  fscanf(infile, "%d", &totalNumbers);
  *vec = (int *)malloc(totalNumbers * sizeof(int));
  if (!*vec) {
    error("error malloc");
  }
  for (c = 0; c < totalNumbers; ++c) {
    fscanf(infile, "%d", &number);
    (*vec)[c] = number;
  }
  fclose(infile);
  return c;
}

// Lee el resultado del archivo out.txt y lo suma
unsigned long readAll() {
  unsigned long number, suma = 0;
  int c;
  FILE *infile;
  infile = fopen("out.txt", "r");
  if (!infile) {
    error("error fopen");
  }
  for (c = 0; c < 2; ++c) {
    fscanf(infile, "%lu", &number);
    printf("nuber :%lu \n", number);
    suma += number;
  }
  fclose(infile);
  return suma;
}

int main() {
  int totalNumeros, delta;
  int limites[2][2];
  // Leer en un vector los datos del archivo de entrad input.txt
  int *vectorNumeros;
  totalNumeros = readNumbers("test3.txt", &vectorNumeros);
  // Estimar los indices (principio y fin) sobre el cual va a trabajar cada
  delta = totalNumeros / 2;
  limites[0][0] = 0;
  limites[0][1] = delta;
  limites[1][0] = limites[0][1];
  limites[1][1] = totalNumeros;
  // proceso hijo Crear los pricesos hijos Esperar la terminacińo de los hijos
  pid_t pid;

  for (int i = 0; i < 2; i++) {
    pid = fork();
    if (pid == 0) {
      // Procesos hijos
      // 1. REcorrer el vector en las pociones indicadas por el padre
      unsigned long suma = 0;
      FILE *outFile = fopen("out.txt", "a");
      for (unsigned long j = limites[i][0]; j < limites[i][1]; j++) {
        // 2. Estimar la suma de las posicicones recorridas
        suma += vectorNumeros[j];
      }
      // 3. Escribir el resultado en el archivo de salida out.txt
      fprintf(outFile, "%lu\n", suma);
      fclose(outFile);
      exit(0);
    }
    wait(NULL);
  }
  // Imprimir el resultado final
  printf("Total: %lu", readAll());
  remove("out.txt");
  return 0;
}
