#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Falta un numero como argumento.\n");
        return 1;
    }

    char *fin;
    long valor = strtol(argv[1], &fin, 10);

    if (*fin != '\0') {
        printf("El texto '%s' no es un numero valido.\n", argv[1]);
    } else {
        printf("Numero convertido: %ld\n", valor);
    }

    return 0;
}


