#include <stdio.h>
#include <stdint.h>

int main() {

    FILE *fp = fopen("numeros.bin", "rb");
    if (!fp) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Saltar los primeros 4 números (4 * 4 bytes = 16 bytes)
    fseek(fp, 4 * sizeof(uint32_t), SEEK_SET);

    uint32_t numero;
    fread(&numero, sizeof(uint32_t), 1, fp);
    printf("El quinto numero es: %u\n", numero);

    fclose(fp);
    return 0;
}
