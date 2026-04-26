#include <stdio.h>

int main()
{
    int numeros[10] = {0,1,2,3,4,5,6,7,8,9};

    FILE *fp = fopen("datos.dat", "wb");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    size_t escritos = fwrite (numeros, sizeof(int), 10, fp);
    if (escritos < 10) {
            perror("Ocurrió un error en la escritura\n");
    }

    printf("Fin de programa alcanzado habiendo escrito %zu enteros\n", escritos);
    fclose (fp);
    return 0;
}
