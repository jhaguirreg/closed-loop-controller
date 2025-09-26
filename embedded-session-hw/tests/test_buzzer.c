#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>           // Para free()
#include "../actuators/actuator.h"

// Declaración de función definida en buzzer_actuator.c
actuator_t *create_buzzer_actuator(void);

int main(void) {
    printf("=== Test Buzzer ===\n");

    // Crear actuador Buzzer
    actuator_t *buzzer = create_buzzer_actuator();
    if (!buzzer) {
        printf("Error al crear Buzzer.\n");
        return 1;
    }

    // Activar buzzer y verificar estado
    printf("Activando buzzer...\n");
    buzzer->activate(buzzer->params);
    printf("Estado Buzzer (1=ON, 0=OFF): %d\n", buzzer->status(buzzer->params));

    // Desactivar buzzer y verificar estado
    printf("Desactivando buzzer...\n");
    buzzer->deactivate(buzzer->params);
    printf("Estado Buzzer (1=ON, 0=OFF): %d\n", buzzer->status(buzzer->params));

    // Liberar memoria
    free(buzzer->params);
    free(buzzer);

    printf("Test Buzzer finalizado.\n");
    return 0;
}

