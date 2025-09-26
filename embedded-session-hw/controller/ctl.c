// Liberias.
#define _POSIX_C_SOURCE 200809L // Usar clock_gettime y nanosleep.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

// Cabeceras.
#include "../sensor/sensor.h"
#include "../actuators/actuator.h"

// Declaramos las funciones que crean y destruyen actuadores.
actuator_t *create_led_actuator(void);
void destroy_led_actuator(actuator_t *a);
actuator_t *create_buzzer_actuator(void);
void destroy_buzzer_actuator(actuator_t *a);

// Función que devuelve el tiempo (ms).
static int64_t now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (int64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000; // Seg. + Nano Seg.
}

// Función principal.
int main(int argc, char **argv) {
    double threshold = 0.7; // Umbral. (recordemos que sensor suelta entre 0 y 1.
    if (argc >= 2) threshold = atof(argv[1]); // Adicionamos la opción de que se pueda pasar como argumento.

    // Inicializamos el sensor.
    sensor_init();

    // Creamos los actuadores.
    actuator_t *led = create_led_actuator();
    actuator_t *buz = create_buzzer_actuator();

    // Contabilizadores para apagar los actuators.
    int64_t buzzer_off_at = 0;
    int64_t led_off_at = 0;

    const int sample_period_ms = 100; // Tiempo en el que leerá el sensor.
    printf("time(ms),sensor,led,buzzer\n"); // Encabezado del csv.
	fflush(stdout);
    // Bucle principal.
    for (int iter = 0; iter < 6000; ++iter) {
    // Se puede usar el for para que sea finito o el while para que no frene.
    //while (1==1) {
        // Obtenemos el tiempo actual y el dato del sensor.
        int64_t t = now_ms();
        double val = sensor_read();

        // Validación para encender o apagar los actuadores.
        if (val >= threshold) {
            // Valida que no esté encendido.
            if (!led->status(led->params)) led->activate(led->params);
            if (!buz->status(buz->params)) buz->activate(buz->params);
            // Reinicia los contadores para apagar.
            buzzer_off_at = 0;
            led_off_at = 0;
        } else {
            // Si ya estaban activos programamos su apagada.
            if (buz->status(buz->params) && buzzer_off_at == 0) {
                buzzer_off_at = t + 1000; // 1 seg.
            }
            if (led->status(led->params) && led_off_at == 0) {
                led_off_at = t + 5000; // 5 seg.
            }
        }

        // Apaga si ya terminó el contador.
        if (buzzer_off_at != 0 && t >= buzzer_off_at) {
            buz->deactivate(buz->params);
            buzzer_off_at = 0;
        }
        if (led_off_at != 0 && t >= led_off_at) {
            led->deactivate(led->params);
            led_off_at = 0;
        }

        // Imprimimos los valores al CSV.
        printf("%" PRId64 ",%.6f,%d,%d\n", t, val,
               led->status(led->params) ? 1 : 0,
               buz->status(buz->params) ? 1 : 0);
	fflush(stdout);

        // Dormir hasta la siguiente muestra de sensor ( espera 100 ms.)
        struct timespec req;
        req.tv_sec = sample_period_ms / 1000;
        req.tv_nsec = (sample_period_ms % 1000) * 1000000L;
        nanosleep(&req, NULL);
    }
    return 0;
}


