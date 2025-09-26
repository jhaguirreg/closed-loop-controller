#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <stdbool.h> // Para usar booleanos.

// Definimos la estructura actuator.
typedef struct {
    void *params;   // Datos específicos de cada actuador.
    void (*activate)(void *params);
    void (*deactivate)(void *params);
    bool (*status)(void *params);
} actuator_t;

#endif // ACTUATOR_H
