#include <stdio.h>

int main() {
    FILE *ftxt, *fbin;
    char c;
    {
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
    }
    // Leemos el archivo modo_texto.txt como binario
    printf("Contenido de modo_texto.txt (leido como binario): ");
    ftxt = fopen("modo_texto.txt", "rb");
    while ((c = fgetc(ftxt)) != EOF) {
        printf("%02X ", c);
    }
    fclose(ftxt);
    printf("\n");

    // Leemos el archivo modo_binario.bin como binario
    printf("Contenido de modo_binario.bin (leido como binario): ");
    fbin = fopen("modo_binario.bin", "rb");
    while ((c = fgetc(fbin)) != EOF) {
        printf("%02X ", c);
    }
    // while (fread (&c, sizeof(char),1,fbin)) {
    //     printf ("%02X ", c);
    // }
    fclose(fbin);
    printf("\n");

    return 0;
}
