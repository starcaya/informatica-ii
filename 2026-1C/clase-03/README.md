# Clase 03

**Tema:** Argumentos del main (`argc`, `argv`) y variables de entorno (`getenv`)

## Ejemplos

* **ejemplo01.c** — Imprime la cantidad y lista de argumentos recibidos.
  Probar: argumentos simples, con espacios (entre comillas), vacíos. Comparar comportamiento en Windows vs Unix (Git Bash).

* **ejemplo02.c** — Valida cantidad mínima de argumentos e implementa `--help` / `-h`.
  Probar: con `-h`, con `--help`, con menos de 2 argumentos, con más de 2.

* **ejemplo03.c** — Convierte un argumento a entero usando `atoi`.
  Probar: con un número válido (`42`), con texto (`hola`). Notar que `atoi` no reporta error.

* **ejemplo04.c** — Convierte un argumento a entero usando `strtol`, con validación.
  Probar: con `42`, con `hola`, con `42abc`. Comparar con ejemplo03.

* **ejemplo05.c** — Convierte un argumento a float usando `atof`.
  Probar: con `3.14`, con `hola`. Notar que `atof` no reporta error.

* **ejemplo06.c** — Convierte un argumento a float usando `strtof`, con validación.
  Probar: con `3.14`, con `hola`, con `3.14xyz`. Comparar con ejemplo05.

* **ejemplo07.c** — Lee la variable de entorno `VERBOSE` con `getenv`.
  Probar: `export VERBOSE=1` y ejecutar, luego `unset VERBOSE` y ejecutar. También probar con `USER` y `PATH`.

* **ejemplo08.c** — Suma dos argumentos, con logging condicional via `VERBOSE`.
  Probar: sin VERBOSE (`unset VERBOSE`), luego con VERBOSE (`export VERBOSE=1`). Ver cómo cambia la salida.

**Tema:** Streams (flujos estándar)

* **ejemplo09.c** — Lee edad (`%d`) y tipo (`%c`) de stdin, con limpieza de buffer usando `getchar`.
  Probar: primero comentar el `while` y ver que `tipo` captura el `\n` residual (ASCII 10). Luego descomentar el `while` y ver que funciona. También probar reemplazando el `while` por `scanf(" %c", &tipo)` (con espacio antes de `%c`).

* **ejemplo10.c** — Convierte un argumento a float con `strtof` e imprime por `stdout`.
  Probar: `./ejemplo10 12.34` (sale por pantalla), luego `./ejemplo10 12.34 > resultado.txt` (redirige stdout a archivo). Abrir `resultado.txt` y ver que contiene la salida.

* **ejemplo11.c** — Igual que ejemplo10 pero usa `fprintf(stderr, ...)` para los errores.
  Probar: `./ejemplo11 12.34 > salida.txt` y ver que el resultado va al archivo pero los errores siguen apareciendo en pantalla. Luego `./ejemplo11 hola > salida.txt` para ver que el error de `stderr` aparece en pantalla aunque `stdout` esté redirigido. Probar también `./ejemplo11 hola > salida.txt 2> errores.txt` para redirigir cada stream a su propio archivo.
