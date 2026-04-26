#include <stdio.h>

int main() {
    FILE *fp = fopen("archivo.txt", "r");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }
    
    // Mover el cursor al último byte del archivo
    fseek(fp, -1, SEEK_END);
    
    // Leer y mostrar el último carácter
    int c = fgetc(fp);
    printf("Ultimo caracter: %c\n", c);
    
    fclose(fp);
    return 0;
}
