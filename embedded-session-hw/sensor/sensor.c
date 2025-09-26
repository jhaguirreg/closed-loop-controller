// Librerias.
#include <stdio.h>
#include <stdlib.h> 
#include <limits.h>
#include "sensor.h"

// Puntero de archivo global (visible solo en este .c)
static FILE *fp = NULL; // Se inicializa con NULL pues en sensor_init se lee el archivo.

// Inicializa el sensor abriendo /dev/urandom.
void sensor_init(void) {
    fp = fopen("/dev/urandom", "rb"); // rb es lectura binaria.
    if (fp == NULL) {
        perror("No se pudo abrir /dev/urandom");
        exit(EXIT_FAILURE); // Indica que el programa terminó con error.
    }
}

// Lee un valor aleatorio y lo convierte a double.
double sensor_read(void) {
    unsigned int number; // Para guardar el valor leído.
    size_t result = fread(&number, sizeof(number), 1, fp); // Se guarda en el espacio de memoria de number.
							   // El tamaño en bit de los elementos a leer es el tamaño de number (usualmente 4 bits).
							   // Se leerá solo un elemento.
							   // El archivo es fp.
							   // Si lo logra 1, sino 0. 
    if (result != 1) {
        perror("Error leyendo de /dev/urandom");
        exit(EXIT_FAILURE);
    }

    // Número entre 0 y 1, se normaliza con UINT_MAX.
    return (double)number / (double)UINT_MAX;
}
