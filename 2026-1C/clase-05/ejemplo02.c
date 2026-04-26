#include <stdio.h>

int main()
{
    int numeros[10];
    int contador=0;
    int *ptr = numeros;

    FILE *fp = fopen("datos.dat", "rb");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;  }

    while (fread (ptr, sizeof(int), 1, fp) == 1) {
        contador++;
        ptr++;  }

    if (feof(fp))
        printf ("Fin de archivo correcto. %d enteros leidos\n", contador);
    else {
        perror ("Error en la lecutra");
        fclose(fp);
        return 1;    }

    printf ("\nImprimimos el contenido del archivo:\n");
    for (int i=0; i<contador; i++) {
        printf ("%d - ", numeros[i] ); }

    printf ("\n\nFin del programa.\n");
    fclose (fp);
    return 0;
}