#include <stdio.h>

/*
 ███████╗██╗   ██╗███╗   ██╗ ██████╗██╗ ██████╗ ███╗   ██╗███████╗███████╗
 ██╔════╝██║   ██║████╗  ██║██╔════╝██║██╔═══██╗████╗  ██║██╔════╝██╔════╝
 █████╗  ██║   ██║██╔██╗ ██║██║     ██║██║   ██║██╔██╗ ██║█████╗  ███████╗
 ██╔══╝  ██║   ██║██║╚██╗██║██║     ██║██║   ██║██║╚██╗██║██╔══╝  ╚════██║
 ██║     ╚██████╔╝██║ ╚████║╚██████╗██║╚██████╔╝██║ ╚████║███████╗███████║
 ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚══════╝
*/

/** 
 * Un lector para el archivo a pasar si se desea cargar un  juego. No debe
 * verificar la sintaxis del archivo, evite cometer errores al crear archivos
 *  de prueba. Se incluyen juegos de prueba.
 **/
char *lector_de_archivo();

/**
* Una función para verificar si los datos introducidos por el 
* usuario son válidos.
**/

/**
* Una función para inicializar los tableros
**/
int iniciar_tableros();

/**
* Una función para añadir buques
**/
int crear_buque();

/**
* Una función para eliminar buques
**/
int eliminar_buque();

/**
* Una función para determinar si el disparo es un fallo, un acierto..
**/
int acerto_disparo();

/**
* Una función para calcular aleatoriamente el lanzamiento de la computadora.
* Esta función no tiene que ser una inteligencia artificial, basta con que
* la computadora pueda hacer lanzamientos “aleatorios” cada vez que se 
* ejecuta la función.
**/
int lanzamiento_pc();

/**
* Una función para determinar si el disparo ya fue hecho, importante
* para el punto anterior.
**/
int repitio_disparo();

/**
* Una función para exportar el registro de un juego a un archivo. Esto incluye
* movimientos realizados, quién ganó y barcos hundidos.
**/
int exportar_registro();

/**
* Todas las funciones que considere necesarias para hacer cada
* una de las partes del juego.
**/

/**
 * imprime la pantalla de carga
 **/
int pantalla_carga();

/* variables
 ██████╗ ██╗      ██████╗ ██████╗  █████╗ ██╗     ███████╗███████╗
██╔════╝ ██║     ██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝██╔════╝
██║  ███╗██║     ██║   ██║██████╔╝███████║██║     █████╗  ███████╗
██║   ██║██║     ██║   ██║██╔══██╗██╔══██║██║     ██╔══╝  ╚════██║
╚██████╔╝███████╗╚██████╔╝██████╔╝██║  ██║███████╗███████╗███████║
 ╚═════╝ ╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝╚══════                                                                                                                                                      
*/

char tablero_ataque1[10][10], tablero_ataque2[10][10];
char tablero_flota1[10][10], tablero_flota2[10][10];

int main()
{
    pantalla_carga();
}

char *lector_de_archivo()
{
}

int iniciar_tableros()
{
}

int crear_buque()
{
}

int eliminar_buque()
{
}

int acerto_disparo()
{
}

int lanzamiento_pc()
{
}

int repitio_disparo()
{
}

int exportar_registro()
{
}

int pantalla_carga()
{

    printf("eres marico o loco");
}