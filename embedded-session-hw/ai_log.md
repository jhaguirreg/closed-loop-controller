# Registro de conversación completa - Controlador en lazo cerrado y tests en C

## 1. Uso de `extern` en C
**Pregunta:**  
> En el lenguaje de programación C, entiendo que la instrucción extern se usa como una promesa de que los archivos, objetos o librerias necesarios se importarán en otro momento, pero en un proyecto como distingo en que lugar debo usarlos y en cuales no?

**Respuesta:**  
Se explicó que `extern` se usa para declarar variables o funciones que se definen en otro archivo, no para librerías estándar. Se aclaró la diferencia entre declaración y definición y se detalló cuándo es necesario importar un archivo `.c`.

---

**Pregunta:**  
> Entiendo perfectamente, y cuando intento importar una librería como #include <stdio.h> cuando debo usar extern y cuando no es recomendable y porqué?

**Respuesta:**  
No se debe usar `extern` con librerías estándar porque sus símbolos ya están definidos por el compilador y linker. Solo se requiere `#include` para que el compilador conozca los prototipos.

---

## 2. Lectura de números aleatorios desde `/dev/random`
**Pregunta:**  
> Ahora deseo conseguir un número random de dev/random, cual es la manera en que debo importarlo y usarlo desde un archivo con extensión .c

**Respuesta:**  
Se explicó cómo abrir `/dev/random` o `/dev/urandom` con `fopen`, leer bytes con `fread` y normalizarlos a un rango de 0 a 1 usando `UINT_MAX`.

---

## 3. Polimorfismo en C
**Pregunta:**  
> Ahora, estoy interesado en crear una estructura para así manejar mejor el polimorfismo entre objetos, puede darme tips a tener en cuenta o recomendaciones en cosas que usualmente los usuarios se equivocan?

**Respuesta:**  
Se dieron recomendaciones sobre cómo usar punteros a funciones dentro de estructuras (`activate`, `deactivate`, `status`), inicialización de parámetros privados y cómo evitar errores comunes como acceso indebido a memoria o doble inclusión de headers.

---

## 4. Monotonic time
**Pregunta:**  
> Explicame por favor como funciona **monotonic time**

**Respuesta:**  
Se explicó que es un reloj que solo avanza, útil para medir intervalos, independiente de cambios en el reloj del sistema.

**Pregunta:**  
> En que medida de tiempo lo retorna?

**Respuesta:**  
Depende de la función usada; por ejemplo, `clock_gettime(CLOCK_MONOTONIC, ...)` puede devolver segundos y nanosegundos.

---

## 5. Controlador en lazo cerrado
**Pregunta:**  
> Mi objetivo es elegir un valor de threshold que permita observar de manera clara la dinámica de activación y apagado de los actuadores, es decir, que se vea en el CSV cómo el LED y el buzzer se encienden y apagan en distintos momentos dependiendo de la señal del sensor. ¿Qué valores de threshold me recomiendas probar para que el comportamiento del sistema sea interesante y no trivial (ni siempre encendido ni siempre apagado), considerando que el sensor genera valores aleatorios entre 0 y 1?

**Respuesta:**  
Se recomendó un valor intermedio alrededor de 0.5 para que los actuadores se activen y desactiven dinámicamente, mostrando claramente la lógica de encendido/apagado.

---

## 6. Revisión general del proyecto y README
**Pregunta:**  
> Ese es todo mi proyecto, recomiéndame cambios y dime que cosas faltaron, además dame el Readme.md

**Respuesta:**  
Se dieron recomendaciones sobre mejoras y documentación, y se generó un README en español que incluye:
- Estructura del proyecto
- Cómo compilar y ejecutar
- Descripción de archivos
- Explicación de errores de compilación vs. errores de enlace
- Uso de wrappers para polimorfismo

---

**Pregunta:**  
> Recuerda que tengo el makefile [...] explica la compilacion con este

**Respuesta:**  
Se explicó la compilación de objetos `.o`, la generación de los binarios `ctl64` y `ctl32`, y la limpieza con `make clean`.

---

## 7. Tests unitarios
**Pregunta:**  
> Quiero que me generes código en C para probar mi proyecto de controlador en lazo cerrado. [...]

**Respuesta:**  
Se propuso crear `test_sensor.c`, `test_led.c` y `test_buzzer.c` como tests unitarios independientes, cada uno con su propio `main()`, rutas correctas y sin depender de `ctl.c`.

**Pregunta:**  
> Si, dame las lineas que debo agregar al make

**Respuesta:**  
Se sugirieron reglas de Makefile para compilar cada test individualmente usando rutas relativas correctas y generando ejecutables en `tests/`.

**Pregunta:**  
> Iniciemos con testsensor, te comparto sensor.h y sensor.c

**Respuesta:**  
Se generó `test_sensor.c`, incluyendo rutas correctas a `sensor.h` y compilación independiente.

---

**Pregunta:**  
> Coloca cuidado con el tema de la ruta, te recuerdo, esta es la estructura embedded-session-hw/

**Respuesta:**  
Se ajustó `test_sensor.c` para usar `#include "../sensor/sensor.h"` y compilar correctamente desde `tests/`.

---

**Pregunta:**  
> Te envio ahora los archivos de actuators, escribeme por favor los .c del test, recuerda colocar sumo cuidado con la ubicación y con los extern en caso de necesitarlos

**Respuesta:**  
Se explicó cómo generar `test_led.c` y `test_buzzer.c` cuidando rutas relativas y memoria dinámica, y declarando los `create_*_actuator()` como prototipos.

**Pregunta:**  
> Buzzer actuator: [...] Led actuator: [...] actuator.h: [...]

**Respuesta:**  
Se corrigieron los tests para usar únicamente `actuator.h` y los `.c` reales, eliminando referencias a headers inexistentes y asegurando que las funciones de creación estén declaradas como prototipos en los tests.

---

**Pregunta:**  
> tests/testled.c:30:5: warning: implicit declaration of function ‘free’ [...]

**Respuesta:**  
Se agregó `#include <stdlib.h>` en ambos tests (`test_led.c` y `test_buzzer.c`) para eliminar los warnings de `free()`.

---

## 8. Resumen y próximos pasos
- Se revisaron rutas relativas y prototipos.
- Se resolvieron warnings y errores de compilación.
- Se destacó la independencia de los tests y la correcta liberación de memoria.
- Se planteó actualizar el Makefile para compilar todos los tests automáticamente con `make tests`.


