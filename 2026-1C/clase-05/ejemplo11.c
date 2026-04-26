#include <stdio.h>

int main() {
    FILE *fp = fopen("archivo.txt", "r");
    if (!fp) {
        perror("No se pudo abrir");
        return 1;
    }

    char c;
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }

    // Al salir del ciclo: ¿EOF o error?
    if (ferror(fp)) {
        printf("\n Ocurrio un error al leer el archivo.\n");
    } else if (feof(fp)) {
        printf("\n Lectura finalizada correctamente (EOF).\n");
    }

    fclose(fp);
    return 0;
}