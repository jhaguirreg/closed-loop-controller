#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>           // Para free()
#include "../actuators/actuator.h"

// Declaración de función definida en led_actuator.c
actuator_t *create_led_actuator(void);

int main(void) {
    printf("=== Test LED ===\n");

    // Crear actuador LED
    actuator_t *led = create_led_actuator();
    if (!led) {
        printf("Error al crear LED.\n");
        return 1;
    }

    // Encender LED y verificar estado
    printf("Encendiendo LED...\n");
    led->activate(led->params);
    printf("Estado LED (1=ON, 0=OFF): %d\n", led->status(led->params));

    // Apagar LED y verificar estado
    printf("Apagando LED...\n");
    led->deactivate(led->params);
    printf("Estado LED (1=ON, 0=OFF): %d\n", led->status(led->params));

    // Liberar memoria
    free(led->params);
    free(led);

    printf("Test LED finalizado.\n");
    return 0;
}

