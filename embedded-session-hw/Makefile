# Compilador y banderas
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Archivos objeto de cada módulo
OBJS = sensor/sensor.o \
       actuators/led_actuator.o \
       actuators/buzzer_actuator.o \
       controller/ctl.o

# -------------------------------------------------------------------
# Reglas principales
# -------------------------------------------------------------------

# Regla por defecto: compila en 64 bits (no ejecuta)
all: ctl64

# Compilar ejecutable en 64 bits
ctl64: $(OBJS)
	$(CC) $(CFLAGS) -o ctl64 $(OBJS)

# Compilar ejecutable en 32 bits (requiere librerías multilib instaladas)
ctl32: CFLAGS += -m32
ctl32: $(OBJS)
	$(CC) $(CFLAGS) -o ctl32 $(OBJS)

# -------------------------------------------------------------------
# Ejecución y guardado de resultados
# -------------------------------------------------------------------

# Ejecutar versión 64 bits y guardar salida en tests/output.csv
run64: ctl64
	mkdir -p tests
	./ctl64 > tests/output.csv
	@echo "Salida guardada en tests/output.csv (64 bits)"

# Ejecutar versión 32 bits y guardar salida en tests/output.csv
run32: ctl32
	mkdir -p tests
	./ctl32 > tests/output.csv
	@echo "Salida guardada en tests/output.csv (32 bits)"

# -------------------------------------------------------------------
# Inspección de binarios
# -------------------------------------------------------------------

inspect64: ctl64
	@echo "=== file ctl64 ==="
	@file ctl64
	@echo
	@echo "=== readelf -h ctl64 ==="
	@readelf -h ctl64

inspect32: ctl32
	@echo "=== file ctl32 ==="
	@file ctl32
	@echo
	@echo "=== readelf -h ctl32 ==="
	@readelf -h ctl32

# -------------------------------------------------------------------
# Reglas para generar los .o
# Cada módulo se compila por separado en un objeto .o
# -------------------------------------------------------------------

sensor/sensor.o: sensor/sensor.c sensor/sensor.h
	$(CC) $(CFLAGS) -c -o $@ $<

actuators/led_actuator.o: actuators/led_actuator.c actuators/actuator.h
	$(CC) $(CFLAGS) -c -o $@ $<

actuators/buzzer_actuator.o: actuators/buzzer_actuator.c actuators/actuator.h
	$(CC) $(CFLAGS) -c -o $@ $<

controller/ctl.o: controller/ctl.c sensor/sensor.h actuators/actuator.h
	$(CC) $(CFLAGS) -c -o $@ $<

# -------------------------------------------------------------------
# Limpieza de compilación
# "make clean" elimina binarios y objetos para recompilar desde cero
# -------------------------------------------------------------------

clean:
	rm -f ctl64 ctl32 $(OBJS) output.csv tests/test_sensor tests/test_led tests/test_buzzer
	@echo "Limpieza completa"

# Reglas para tests unitarios

# Test del sensor
tests/test_sensor: tests/test_sensor.c sensor/sensor.c sensor/sensor.h
	$(CC) $(CFLAGS) -Wall -Wextra -std=c11 -o $@ tests/test_sensor.c sensor/sensor.c

# Test del LED
tests/test_led: tests/test_led.c actuators/led_actuator.c actuators/actuator.h
	$(CC) $(CFLAGS) -o $@ tests/test_led.c actuators/led_actuator.c

# Test del buzzer
tests/test_buzzer: tests/test_buzzer.c actuators/buzzer_actuator.c actuators/actuator.h
	$(CC) $(CFLAGS) -o $@ tests/test_buzzer.c actuators/buzzer_actuator.c

# Regla para compilar todos los tests
tests: tests/test_sensor tests/test_led tests/test_buzzer
	@echo "Todos los tests compilados. Ejecuta ./tests/test_sensor, ./tests/test_led o ./tests/test_buzzer"

run-tests: tests
	@echo "Ejecutando tests..."
	@./tests/test_sensor
	@./tests/test_led
	@./tests/test_buzzer
