#include <stdio.h>

int main() {
    FILE *ftxt, *fbin;

    // Escribimos el byte 0x0A (newline) en modo texto
    ftxt = fopen("modo_texto.txt", "w");
    fputc(0x0A, ftxt);  // mismo que fputc('\n', ftxt)
    fclose(ftxt);

    // Escribimos el byte 0x0A en modo binario
    fbin = fopen("modo_binario.bin", "wb");
    fputc(0x0A, fbin);
    // char caracter = 0x0A;
    // fwrite (&caracter, sizeof(char), 1, fbin);
    fclose(fbin);

    return 0;
}
