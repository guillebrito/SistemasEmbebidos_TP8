# Trabajo Práctico Número 6

-----

Gestión de poncho con display de 7 segmentos 

**Table of Contents**

- [Forma de uso](#forma-de-uso)
- [License](#license)

## Forma de uso

Para utilizar este proyecto se debe:

1. Crear un fork del repositorio en la página de Github. Esto creará un repositorio independiente propiedad del alumno pero que comparte los primeros commits con este repositorio.

2. Clonar el repositorio e iniciarlizar el submodulo (muju):
```
git submodule init

git submodule update
```
3. Compilar todo el programa con el comando `make`.

4. Conectar mediante USB la placa a la PC, se debe utilizar el puerto "DEBUG" de la placa.

5. Cargar los archivos en la placa con el comando `make download`.

- Con el comando `make clean` se elimina la carpeta build.
- Con el comando `make docs` se genera la documentación.


## License

This template is distributed under the terms of the [MIT](https://spdx.org/licenses/MIT.html) license.
