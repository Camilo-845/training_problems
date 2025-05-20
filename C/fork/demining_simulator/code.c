#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void read_matrix_file(const char *filename, int *x, int *y, int ***matrix) {
  FILE *file = fopen(filename, "r");

  fscanf(file, "%d", x); // Leer el tamaño de la matriz
  fscanf(file, "%d", y); // Leer el tamaño de la matriz

  *matrix = (int **)malloc(sizeof(int *) * (*x));
  for (int i = 0; i < *x; i++) {
    (*matrix)[i] = (int *)malloc(sizeof(int) * (*y));
    for (int j = 0; j < *y; j++) {
      fscanf(file, "%1d", &(*matrix)[i][j]); // Leer cada elemento
    }
  }

  fclose(file);
}

void print_matrix(int **matrix, int n, int y) {
  printf("Matriz [%d,%d]:\n", n, y);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < y; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  char *fileName = argv[1];
  int w, h;
  int **matrix;
  read_matrix_file(fileName, &w, &h, &matrix);
  print_matrix(matrix, w, h);

  // [Columnas, Filas]

  int colsFils = atoi(argv[2]);
  // Creación de procesos
  int nProcesos = colsFils * colsFils;

  int i = 0;
  for (; i < nProcesos; i++) {
    if (!fork()) {
      break;
    }
  }

  // Logica Hijos
  if (i != nProcesos) {

    int cuadrante[2];
    cuadrante[0] = i % colsFils; // Columna
    cuadrante[1] = i / colsFils; // Fila

    int deltax = h / colsFils;
    int deltay = w / colsFils;

    // X_0, X_1, Y_0, Y_1
    int rango[4];
    rango[0] = cuadrante[0] * deltax;
    rango[1] = (cuadrante[0] == (colsFils - 1)) ? h - 1 : rango[0] + deltax - 1;
    rango[2] = cuadrante[1] * deltay;
    rango[3] = (cuadrante[1] == (colsFils - 1)) ? w - 1 : rango[2] + deltay - 1;

    for (int iterx = rango[2]; iterx <= rango[3]; iterx++) {
      for (int itery = rango[0]; itery <= rango[1]; itery++) {
        // Posible bomba
        if (matrix[iterx][itery] == 1) {
          // Recorre posiciones alrededor de la posible bomba
          int encontrada = 0;
          for (int it = iterx - 1; it <= iterx + 1; it++) {
            for (int j = itery - 1; j <= itery + 1; j++) {
              // Verifica que no se salga de la matriz
              if (it >= 0 && it < w && j >= 0 && j < h) {
                if (matrix[it][j] == 2) {
                  printf("bomba en posicion [%d,%d]\n", iterx, itery);
                  encontrada = 1;
                  break;
                }
              }
            }
            if (encontrada) {
              break;
            }
          }
        }
      }
    }
  }

  return 0;
}
