
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void createFile(const char *nombreArchivo, int n) {
  FILE *archivo = fopen(nombreArchivo, "w");
  if (archivo == NULL) {
    perror("Error al crear el archivo");
    return;
  }

  for (int i = 1; i <= n; i++) {
    fprintf(archivo, "Línea número %d: Este es un ejemplo de contenido.\n", i);
  }

  fclose(archivo);
}

/* Comunicación por pipes entre n procesos hijos de un proceso padre,
 * Lectura de archivo en el hijo 1
 * Salida en pantalla en ultimo hijo
 */
int main() {
  createFile("file.txt", 10);
  int i = 0, nProcess = 2;
  printf("n procesos: ");
  scanf("%d", &nProcess);
  // Arreglo de descriptores de archivo 0 -> Lectura, 1-> Escritura
  int tubs[nProcess - 1][2];

  pid_t pids[nProcess];
  // Crea un canal de comunicación
  for (int j = 0; j < nProcess - 1; j++) {
    pipe(tubs[j]);
  } // Creación de procesos
  for (; i < nProcess; i++) {
    if (!fork())
      break;
  }
  // Proceso Padre
  if (i == nProcess) {
    for (int j = 0; i < nProcess - 1; i++) {
      // Cierra los dos extremos del pipe ya que no lo va a usar
      close(tubs[j][0]);
      close(tubs[j][1]);
    }
    // Procesos Hijos
  } else {
    // Primer hijo
    if (i == 0) {
      // Pipe de Escritura
      close(tubs[0][0]);
      // Lectura de archivo
      FILE *file = fopen("file.txt", "r");
      char buffer[1024];
      while (fgets(buffer, sizeof(buffer), file)) {
        write(tubs[0][1], buffer, strlen(buffer));
      }
      close(tubs[0][1]);
      fclose(file);
    }
    // Ultimo hijo
    else if (i == nProcess - 1) {
      // Pipe de Lectura
      close(tubs[i - 1][1]);
      char buffer[1024];
      while (read(tubs[i - 1][0], buffer, sizeof(buffer))) {
        // Salida en pantalla
        printf("%s", buffer);
      }
      close(tubs[i - 1][0]);
    }
    // Hijos intermedios
    else {
      // Tiene 2 pipes en la primera es lector y el la segundo escritor
      // Pipe Lectura (i-1)
      close(tubs[i - 1][1]);
      close(tubs[i][0]);
      char buffer[1024];
      while (read(tubs[i - 1][0], buffer, sizeof(buffer))) {
        // Pipe Escritura (i)
        write(tubs[i][1], buffer, strlen(buffer) + 1);
      }
      close(tubs[i - 1][0]);
      close(tubs[i][1]);
    }
  }
  remove("file.txt");
  return 0;
}
