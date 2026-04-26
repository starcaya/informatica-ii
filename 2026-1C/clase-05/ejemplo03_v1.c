#include <stdio.h>

int main()
{
    int numeros[10];


    FILE *fp = fopen("datos.dat", "rb");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;  }

    size_t leidos = fread (numeros, sizeof(int), 10, fp)  ;


    if (leidos < 10) {
        if (feof(fp)) {
            printf ("Fin de archivo correcto.\n"); }
        else {
            perror ("Error en la lectura");
            fclose(fp);
            return 1;  } }
    else {
        printf ("Se leyeron los %zu enteros correctamente", leidos);
    }

    printf ("\nImprimimos el contenido del archivo:\n");
    for (int i=0; i<10; i++) {
        printf ("%d - ", numeros[i] ); }

    printf ("\n\nFin del programa.");
    fclose (fp);
    return 0;
}
