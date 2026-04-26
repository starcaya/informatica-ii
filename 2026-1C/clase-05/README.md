# Clase 05

**Tema:** Manejo de archivos binarios en C — `fread` / `fwrite`, `fseek` / `ftell`, `<stdint.h>`, modos binarios (`"wb"`, `"rb"`, `"r+b"`, `"w+"`), distinción texto vs binario, manejo de errores con `feof` y `ferror`, endianness.

## Ejemplos

**Tema:** Escritura y lectura binaria básica

* **ejemplo01.c** — Escribe un vector de 10 enteros (0 al 9) en `datos.dat` con una sola llamada a `fwrite`, en modo binario (`"wb"`).
  Probar: ejecutar y luego mirar el archivo con `xxd datos.dat` o `hexdump -C datos.dat` para ver los 40 bytes (10 ints × 4 bytes) en little-endian. Notar que cada entero ocupa 4 bytes consecutivos, con el byte menos significativo primero (ej: el `1` aparece como `01 00 00 00`).

* **ejemplo02.c** — Lee `datos.dat` entero por entero con `fread` dentro de un `while`, usando aritmética de punteros (`ptr++`) para avanzar por el vector. Al salir del loop chequea `feof` para confirmar fin de archivo.
  Probar: ejecutar después de `ejemplo01.c`. Debe imprimir `0 - 1 - 2 - ... - 9 -`. Probar también con un archivo más chico de lo esperado para ver que el contador refleja cuántos enteros leyó realmente.

**Tema:** Lectura por bloque y validación

* **ejemplo03_v0.c** — Lee los 10 enteros de un solo `fread`, pero usa `feof` directamente como condición de fin **sin** chequear el retorno del `fread`. Anti-patrón típico.
  Probar: ejecutar con `datos.dat` exactamente de 40 bytes. Ver que `feof` da falso (porque `fread` leyó todo lo pedido sin intentar leer más allá) y entra al `else` reportando un "error" inexistente. Es el bug clásico que motiva chequear el retorno de `fread`.

* **ejemplo03_v1.c** — Misma idea que el v0 pero con el patrón correcto: primero compara `leidos < 10`, y solo si hay lectura parcial usa `feof` para distinguir EOF legítimo de error real.
  Probar: ejecutar con un archivo de 40 bytes (caso normal), luego truncarlo a 36 bytes (`truncate -s 36 datos.dat`) y ver que detecta fin de archivo. Comparar el flujo con el v0.

**Tema:** Modo texto vs modo binario

* **ejemplo04.c** — Escribe el byte `0x0A` (newline) en dos archivos: `modo_texto.txt` (modo `"w"`) y `modo_binario.bin` (modo `"wb"`).
  Probar: ejecutar y comparar el tamaño de ambos archivos (`ls -l`). En Linux pesan lo mismo (1 byte cada uno); en Windows, `modo_texto.txt` pesa 2 bytes porque `\n` se convierte en `\r\n`. Confirmar con `xxd` lo que hay dentro.

* **ejemplo05.c** — Genera los mismos dos archivos del ejemplo04 y luego los relee en modo binario (`"rb"`) imprimiendo cada byte en hexadecimal.
  Probar: ejecutar en Windows y ver `0D 0A` en `modo_texto.txt` y `0A` solo en `modo_binario.bin`. En Linux, ambos muestran `0A`. Es la demostración directa de la conversión EOL del modo texto.

**Tema:** Tipos enteros y portabilidad

* **ejemplo06.c** — Imprime el tamaño en bytes (`sizeof`) y el rango de valores (vía `<limits.h>`) de cada tipo entero estándar: `char`, `short`, `int`, `long`, `long long` y sus variantes `unsigned`.
  Probar: compilar y ejecutar en la PC del alumno (típicamente x86_64: `int = 4`, `long = 8`). Comparar contra una arquitectura distinta si tienen acceso (Raspberry Pi, microcontrolador) para ver que el estándar C solo garantiza mínimos, no tamaños exactos. Esto justifica usar `<stdint.h>` (`uint32_t`, etc.) cuando se necesita tamaño fijo.

**Tema:** Posicionamiento con fseek / ftell

* **ejemplo07.c** — Lee el 5º `uint32_t` de `numeros.bin` saltando los 4 anteriores con `fseek(fp, 4 * sizeof(uint32_t), SEEK_SET)`, sin escribir nada antes (asume que el archivo ya existe).
  Probar: requiere que `numeros.bin` exista (lo genera `ejemplo08.c`). Cambiar el factor 4 por 0 para leer el primero, o por 9 para leer el último. Probar con factor 10 (más allá del fin) y ver que `fread` devuelve 0.

* **ejemplo08.c** — Programa completo: primero escribe 10 enteros (1 al 10) en `numeros.bin`, después reabre el archivo en modo lectura, salta a la posición del 5º con `fseek` y lo lee.
  Probar: ejecutar una sola vez y debe imprimir `El quinto numero es: 5`. Modificar el bucle de escritura para guardar 20 números y leer el 15º. Notar el patrón: `offset = (N-1) * sizeof(elemento)` para acceder directamente al elemento N-ésimo.

* **ejemplo10.c** — Obtiene el tamaño de `imagen.png` con la combinación canónica `fseek(fp, 0, SEEK_END)` + `ftell(fp)`, y vuelve al inicio con `fseek(fp, 0, SEEK_SET)`.
  Probar: ejecutar con la `imagen.png` provista (debe imprimir `3141707 bytes` aprox). Probar con cualquier otro archivo binario o de texto para confirmar que la técnica es general. Comparar con el tamaño que reporta `ls -l`.

**Tema:** Modificación in-place y depuración con breakpoint

* **ejemplo09.c** — Editor minimalista: lee caracteres de stdin, los escribe a `texto.txt` (modo `"w+"`), permite borrar el último con `!` y termina con `#`. **Tiene un bug lógico inyectado** (el comentario de la primera línea lo aclara) que se detecta usando un breakpoint en VSCode.
  Probar: compilar con `gcc -g ejemplo09.c -o ejemplo09` (la flag `-g` es necesaria para el debugger). Tipear `hola!#` (todo en una línea). Resultado esperado: el archivo final es `hol!` en lugar de `hol ` — el `!` se escribe literal después de borrar. Poner un breakpoint dentro del `while` y ver paso a paso cómo el archivo cambia dos veces dentro de la misma iteración. Discutir el fix (cambiar el segundo `if` por `else if`).

**Tema:** Distinción de EOF vs error

* **ejemplo11.c** — Lee `archivo.txt` carácter por carácter con `fgetc` hasta `EOF`, y al salir del loop usa `ferror()` y `feof()` para distinguir si fue fin legítimo o error real de lectura.
  Probar: crear un `archivo.txt` con texto y ejecutar — debe terminar con "Lectura finalizada correctamente (EOF)". Para forzar el caso de error, leer un archivo desde un pendrive y desconectarlo durante la lectura (similar al experimento de los ejemplos 12/13 de la clase 04). Es la versión limpia del patrón ferror/feof.

**Recursos auxiliares**

* **imagen.png** — Imagen PNG de prueba para `ejemplo10.c` (medir tamaño).
