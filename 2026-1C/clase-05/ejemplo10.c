#include <stdio.h>

int main() {
    // Abrimos el archivo PNG en modo lectura binaria
    FILE *fp = fopen("imagen.png", "rb");
    if (!fp) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Usamos fseek para mover el cursor al final del archivo
    fseek(fp, 0, SEEK_END);

    // Usamos ftell para obtener la posición actual del cursor (tamaño total)
    long size = ftell(fp);

    // Volvemos al inicio del archivo (podría usarse rewind o fseek)
    fseek(fp, 0, SEEK_SET);

    // Mostramos el tamaño del archivo en bytes
    printf("El archivo imagen.png pesa %ld bytes\n", size);

    // Cerramos el archivo
    fclose(fp);

    return 0;
}
