// Librerías.
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "actuator.h" // Interfaz de actuadores.

// Estructura de datos propia del LED.
typedef struct {
    bool is_on; // Indica si LED está encendido (true) o apagado (false).
} led_params_t;

// Para activar el actuador LED.
static void led_activate(void *p) { // p es un puntero generico de actuator.h.
    led_params_t *lp = (led_params_t*)p; // Convertimos este generico a uno espeífico de la estructura.
    lp->is_on = true; // Activamos el LED.
    printf("[LED] Encendido.\n"); // Para que el usuario se de cuenta.
}

// Sigue la misma lógica del anterior.
static void led_deactivate(void *p) {
    led_params_t *lp = (led_params_t*)p;
    lp->is_on = false;
    printf("[LED] Apagado.\n");
}

// Mostrará si el LED está encendido o apagado.
static bool led_status(void *p) {
    led_params_t *lp = (led_params_t*)p;
    return lp->is_on;
}

// Aquí creamos un actuador tipo LED con la estructura de actuator.h.
actuator_t *create_led_actuator(void) {
// Iniciamos con reservaciones de memoria.
    actuator_t *a = malloc(sizeof(actuator_t)); // A será el actuator LED.
    led_params_t *lp = malloc(sizeof(led_params_t)); // lp serán los parámetros.
    lp->is_on = false; // Consideramos el led apagado.

    // Le asignamos la estructura creada.
    a->params = lp;
    a->activate = led_activate;
    a->deactivate = led_deactivate;
    a->status = led_status;

    return a;
}

