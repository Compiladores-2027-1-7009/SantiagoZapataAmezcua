#include <stdio.h>

// Si no se indica la escala al compilar, se usa Fahrenheit
#ifndef ESCALA
#define ESCALA 1
#endif

#if ESCALA == 1
#define NOMBRE "Fahrenheit"
#define convertir(c) ((c) * 9.0 / 5.0 + 32)
#elif ESCALA == 2
#define NOMBRE "Kelvin"
#define convertir(c) ((c) + 273.15)
#else
#error "ESCALA solo puede ser 1 (Fahrenheit) o 2 (Kelvin)"
#endif

#define PASO 10

int main(void) {
    float c;

    printf("Celsius a %s de %d en %d\n", NOMBRE, PASO, PASO);
    for (c = 0; c <= 30; c += PASO)
        printf("%6.1f C = %7.2f\n", c, convertir(c));

#undef PASO
#define PASO 25

    printf("\nCelsius a %s de %d en %d\n", NOMBRE, PASO, PASO);
    for (c = 0; c <= 100; c += PASO)
        printf("%6.1f C = %7.2f\n", c, convertir(c));

    return 0;
}
