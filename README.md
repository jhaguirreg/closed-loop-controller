# Controlador en Lazo Cerrado en C

Este proyecto implementa un **controlador en lazo cerrado** que simula la interacción entre un **sensor** y dos **actuadores** (LED y buzzer).  

El comportamiento es el siguiente:

- El sensor se muestrea cada **100 ms** y devuelve un valor aleatorio entre 0 y 1.
- Si el valor del sensor es **mayor o igual al umbral (`threshold`, por defecto 0.7)**:
  - Se activan inmediatamente el **LED** y el **buzzer**.
  - Se cancelan los temporizadores de apagado.
- Si el valor del sensor es **menor al umbral**:
  - Se programa el apagado del **buzzer después de 1 segundo**.
  - Se programa el apagado del **LED después de 5 segundos**.
- En cada ciclo, el programa imprime en formato **CSV**: time(ms),sensor_value,led_state,buzzer_state donde `led_state` y `buzzer_state` son `1` si el dispositivo está encendido y `0` si está apagado.


## Estructura del proyecto
´´´
├── Makefile

├── controller/

│ └── ctl.c

├── sensor/

│ ├── sensor.c

│ └── sensor.h

├── actuators/

│ ├── actuator.h

│ ├── led_actuator.c

│ └── buzzer_actuator.c

└── tests/

  └── output.csv (se genera automáticamente al ejecutar)
´´´

##  Requisitos

- Compilador de C (por ejemplo, `gcc`).
- Herramientas básicas de compilación (`make`).
- Librerías multilib si se desea compilar en 32 bits.

## Compilación y ejecución

El proyecto utiliza un **Makefile** que automatiza la compilación, ejecución y análisis de binarios.

### Compilar en 64 bits
```bash
make ctl64
Genera el ejecutable ctl64 (no lo ejecuta).

### Compilar en 32 bits (opcional)
```bash
make ctl32
Genera el ejecutable ctl32 en modo 32 bits (requiere librerías multilib instaladas).

### Ejecutar y guardar resultados (64 bits)
```bash
make run64
Ejecuta ctl64.

Guarda automáticamente la salida en tests/output.csv.

### Ejecutar y guardar resultados (32 bits)
```bash
make run32
Ejecuta ctl32.

Guarda la salida en tests/output.csv.

### Inspección de binarios
Verifica la arquitectura del ejecutable y su cabecera ELF:

```bash
make inspect64
make inspect32

### Limpieza
```bash
make clean
Elimina los objetos compilados (.o), binarios (ctl64, ctl32) y la salida tests/output.csv.

### Salida del programa
El programa guarda la salida en tests/output.csv con el siguiente formato:

time(ms),sensor_value,led_state,buzzer_state
12345,0.830000,1,1
12445,0.720000,1,1
12545,0.200000,1,1
13545,0.150000,0,0
Esto permite graficar fácilmente la dinámica en herramientas como Excel, Python o GNUplot.

# Reflexión: errores de compilación vs. errores de enlace, y el uso de wrappers
## Errores de compilación
Ocurren cuando el compilador no puede traducir el código fuente a código objeto. Ejemplos:

- Sintaxis incorrecta en un archivo .c.

- Uso de variables no declaradas.

- Tipos incompatibles en operaciones o asignaciones.

Resultado: no se genera ningún archivo .o.

## Errores de enlace
Surgen en la fase de linking, al intentar construir el ejecutable a partir de los .o. Ejemplos:

- Declarar una función en un .h pero no implementarla en un .c.

- Referenciar funciones de librerías no incluidas en el enlazado.

Resultado: el ejecutable no se genera aunque los .o existan.

## Wrappers
En este proyecto se emplean wrappers como interfaz común para los actuadores (LED, buzzer).
Los wrappers encapsulan la lógica de bajo nivel de cada dispositivo y exponen funciones genéricas:

- activate

- deactivate

- status

Esto permite:

- Reducir dependencias entre el controlador y las implementaciones concretas.

- Simular polimorfismo básico en C.

- Facilitar extensiones (agregar nuevos actuadores sin modificar el controlador).

## Tests del Proyecto

El proyecto incluye tests unitarios para los módulos de sensores y actuadores.  
Los tests se encuentran en la carpeta `tests/`:

tests/
├── test_sensor.c
├── test_led.c
├── test_buzzer.c

Cada test genera un binario independiente.

---

### Compilar los tests

Compilar todos los tests:

make tests
Compilar un test específico:

make tests/test_sensor
make tests/test_led
make tests/test_buzzer
Ejecutar los tests
Después de compilar, ejecuta un test:

./tests/test_sensor
./tests/test_led
./tests/test_buzzer
O compilar y ejecutar todos los tests automáticamente (si el Makefile tiene run-tests):

make run-tests
