// Liberías.
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Dinámica de la memoria.
#include "actuator.h"

// Estructura de datos propia del buzzer.
typedef struct {
    bool is_on; // Guardará si está encendido o apagado.
} buzzer_params_t; // Alias.

// Para activar el actuator.
static void buzzer_activate(void *p) { // Entra un puntero generico.
    buzzer_params_t *bp = (buzzer_params_t*)p; // Le asignamos un modelo específico.
    bp->is_on = true; // Activamos el actuator.
    printf("[Buzzer] Activado.\n"); // Mostramos al usuario.
}

// Misma lógica pero ahora para desactivar.
static void buzzer_deactivate(void *p) {
    buzzer_params_t *bp = (buzzer_params_t*)p;
    bp->is_on = false;
    printf("[Buzzer] Silenciado.\n");
}

// Mostramos el estado (on o off) del Buzzer.
static bool buzzer_status(void *p) {
    buzzer_params_t *bp = (buzzer_params_t*)p;
    return bp->is_on;
}

// Le asignamos la estructura de un actuador a Buzzer.
actuator_t *create_buzzer_actuator(void) {
    actuator_t *a = malloc(sizeof(actuator_t)); // Actuator.
    buzzer_params_t *bp = malloc(sizeof(buzzer_params_t)); // Parámetros.
    bp->is_on = false;

    a->params = bp;
    a->activate = buzzer_activate;
    a->deactivate = buzzer_deactivate;
    a->status = buzzer_status;

    return a;
}

