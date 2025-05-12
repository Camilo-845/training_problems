
#include <pthread.h> // Para usar funciones de hilos POSIX
#include <stdio.h>   // Librería estándar de entrada y salida
#include <stdlib.h>  // Para usar la macro EXIT_SUCCESS
#include <string.h>
#include <unistd.h> // Proporciona acceso a la API POSIX del sistema operativo

// Declaración de funciones para los hilos
void *funcion_hilo(void *arg);
int leerArchivo(const char *nombreArchivo, char **buffer);
int contarCaracteres(char *cadena, int **buffer, char *charToFound);

typedef struct {
  int idx;
  char *adn;
  int adn_len;
  char *patron;
  int n_hilos;
} ThreadArgs;

int contador = 0;

int main(int argc, char *argv[]) {
  char *cadena = "AGCT";
  int nHilos = atoi(argv[1]);
  char *fileName = argv[2];
  pthread_t tid[nHilos];
  char *adn;
  int l_and = leerArchivo(fileName, &adn);

  for (int i = 0; i < nHilos; i++) {
    ThreadArgs *args = malloc(sizeof(ThreadArgs));
    args->idx = i;
    args->adn = adn;
    args->adn_len = l_and;
    args->patron = "GCGTGA";
    args->n_hilos = nHilos;
    pthread_create(&tid[i], NULL, funcion_hilo, (void *)args);
  }

  // Cuenta cuantas veces se repite cada caracter
  int *count;
  int size_cadena = contarCaracteres(adn, &count, cadena);

  // Espera a que todos los hilos secundarios terminen
  for (int i = 0; i < nHilos; i++) {
    pthread_join(tid[i], NULL);
  }

  for (int j = 0; j < size_cadena; j++) {
    printf("char %c: %d\n", cadena[j], (count)[j]);
  }

  printf("Secuencia [GCGTGA] encontrada %d veces\n", contador);
}

void *funcion_hilo(void *arg) {
  ThreadArgs *args = (ThreadArgs *)arg;
  int tam = args->adn_len / args->n_hilos;
  int start = args->idx * tam;
  printf("idx:%d, n_hilos %d\n", args->idx, args->n_hilos);
  int end =
      ((args->n_hilos - 1) == args->idx) ? args->adn_len - 1 : start + tam - 1;

  printf("start: %d, end: %d\n", start, end);

  for (int i = start; i < end; i++) {
    char *cpy = (char *)malloc((strlen(args->patron) + 1) * sizeof(char));
    strncpy(cpy, args->adn + i, strlen(args->patron));
    if (strcmp(cpy, args->patron) == 0) {
      contador++;
    }
  }
  return 0;
}

/*
 * Recorre el arreglo de caracteres y cuenta las repeticicones de
 * cada caracter de queriere buscar
 *
 *
 */
int contarCaracteres(char *cadena, int **buffer, char *charToFound) {
  int sizecadena = strlen(cadena);
  int sizeToFound = strlen(charToFound);

  *buffer = (int *)calloc(sizeToFound + 1, sizeof(int));
  for (int i = 0; i < sizecadena; i++) {
    for (int j = 0; j < sizeToFound; j++) {
      if (cadena[i] == charToFound[j]) {
        (*buffer)[j]++;
      }
    }
  }
  return sizeToFound;
}

/**
 * Lee un archivo donde la primera línea contiene la cantidad total de
 * caracteres que siguen.
 *
 * @param nombreArchivo Nombre del archivo a leer.
 * @param buffer Puntero al vector donde se almacenarán los caracteres.
 * @return La cantidad de caracteres leídos, o -1 si hubo un error.
 */
int leerArchivo(const char *nombreArchivo, char **buffer) {
  FILE *archivo = fopen(nombreArchivo, "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return -1;
  }

  int cantidad;
  if (fscanf(archivo, "%d\n", &cantidad) != 1) {
    perror("Error al leer la cantidad de caracteres");
    fclose(archivo);
    return -1;
  }

  *buffer = (char *)malloc((cantidad + 1) * sizeof(char));
  if (*buffer == NULL) {
    perror("Error al reservar memoria");
    fclose(archivo);
    return -1;
  }

  size_t leidos = fread(*buffer, sizeof(char), cantidad, archivo);
  (*buffer)[leidos] = '\0'; // Asegura que sea una cadena válida

  fclose(archivo);
  return (int)leidos;
}
