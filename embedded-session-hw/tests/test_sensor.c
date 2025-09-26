// Archivo: tests/test_sensor.c
#include <stdio.h>
#include "../sensor/sensor.h"  // ruta relativa correcta desde tests/ al header

int main(void) {
    printf("=== Test Sensor ===\n");

    // Inicializar el sensor
    sensor_init();

    // Leer 10 valores del sensor y mostrarlos
    for (int i = 0; i < 10; i++) {
        double value = sensor_read();
        printf("Lectura %2d: %.6f\n", i + 1, value);
    }

    printf("Test sensor finalizado.\n");
    return 0;
}

