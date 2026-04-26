//codigo con bug a solucionar por los alumnos

#include <stdio.h>

int main() {
    FILE *fp = fopen("texto.txt", "w+"); // Abrir para lectura y escritura
    if (!fp) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    char c = 0;
    printf("Escribi caracteres (usa ! para borrar el ultimo, # para salir):\n");

    while (c != '#') {
        scanf ("%c", &c);

        if (c == '!') {
            // Retroceder un caracter y sobrescribir con espacio
            if (fseek(fp, -1, SEEK_CUR) == 0) {
                fputc(' ', fp);
                fseek(fp, -1, SEEK_CUR);  // Volver atrás para seguir escribiendo desde ahí
            }
        } 
        if (c != '#') {
            fputc(c, fp);
        }
        // Si es '#' no lo escribimos, pero salimos del ciclo en la proxima vuelta
    }

    // Mostrar el contenido final
    fseek (fp, 0, SEEK_SET);
    printf("\nContenido del archivo:\n");

    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }

    fclose(fp);
    printf("\n\n");
    return 0;
}
