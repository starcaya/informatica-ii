#include <stdio.h>

#define ARCHIVO_IN "productos_original.dat"
#define ARCHIVO_OUT "productos2.dat"
#define MAX_PRODUCTOS 200

typedef struct {
    int codigo;
    char nombre[31];
    float precio;
} Producto;

void bubbleSort(Producto [], int );
void mostrarArchivo (const char *);

int main() {

    // Mostrar archivo original
    mostrarArchivo(ARCHIVO_IN);

    Producto productos[MAX_PRODUCTOS];

    FILE *fp = fopen(ARCHIVO_IN, "rb");
    if (!fp) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Determinar tamaño del archivo en bytes
    fseek(fp, 0, SEEK_END);
    long tam_bytes = ftell(fp);
    int total = tam_bytes / sizeof(Producto);
    fseek(fp, 0, SEEK_SET);
    // Verificar límite
    if (total > MAX_PRODUCTOS) {
        printf("Advertencia: el archivo contiene %d productos, pero solo se cargaran los primeros %d.\n", total, MAX_PRODUCTOS);
        total = MAX_PRODUCTOS;
    }

    fread(productos, sizeof(Producto), total, fp);
    fclose(fp);
    getchar();

    bubbleSort(productos, total);

    // Reescribir el archivo ordenado
    fp = fopen(ARCHIVO_OUT, "wb");
    if (!fp) {
        perror("Error al escribir el archivo");
        return 1;
    }

    fwrite(productos, sizeof(Producto), total, fp);
    fclose(fp);

    // Mostrar archivo después de ordenar
    printf("\n----- Archivo luego del ordenamiento -----\n");
    mostrarArchivo(ARCHIVO_OUT);
    return 0;
}


//void bubbleSort(Producto *v, int n)
void bubbleSort(Producto v[], int n) {
    Producto aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j].precio > v[j + 1].precio) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

void mostrarArchivo(const char *nombreArchivo) {
    FILE *f = fopen(nombreArchivo, "rb");
    if (!f) {
        perror("Error al abrir el archivo");
        return;
    }

    Producto p;
    printf("----- Contenido del archivo '%s' -----\n", nombreArchivo);

    while (fread(&p, sizeof(Producto), 1, f) == 1) {
        printf("Codigo: %3d | Nombre: %-15s | Precio: $%7.2f\n", p.codigo, p.nombre, p.precio);
    }

    fclose(f);
}
