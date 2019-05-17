#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 ██████╗ ███████╗ ██████╗██╗      █████╗ ██████╗  █████╗  ██████╗██╗ ██████╗ ███╗   ██╗███████╗███████╗
 ██╔══██╗██╔════╝██╔════╝██║     ██╔══██╗██╔══██╗██╔══██╗██╔════╝██║██╔═══██╗████╗  ██║██╔════╝██╔════╝
 ██║  ██║█████╗  ██║     ██║     ███████║██████╔╝███████║██║     ██║██║   ██║██╔██╗ ██║█████╗  ███████╗
 ██║  ██║██╔══╝  ██║     ██║     ██╔══██║██╔══██╗██╔══██║██║     ██║██║   ██║██║╚██╗██║██╔══╝  ╚════██║
 ██████╔╝███████╗╚██████╗███████╗██║  ██║██║  ██║██║  ██║╚██████╗██║╚██████╔╝██║ ╚████║███████╗███████║
 ╚═════╝ ╚══════╝ ╚═════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚══════╝
*/

int validar_posicion_barco(int cabeza_j, int cabeza_i,
                           int cola_i, int cola_j,
                           int tipo); // Verifica si los datos introducidos por el usuario son válidos.
int crear_buque(int cabeza[3], int cola[3],
                int tipo, int jugador);    // Función para añadir buques.
int lector_de_archivo();                   // Lector para el archivo a pasar si se desea cargar un juego.
int eliminar_buque(int tipo, int jugador); // Función para eliminar buques.
int acerto_disparo(int y, int x);          // Función para determinar si el disparo es un fallo, un acierto..
int lanzamiento_pc();                      //Función para calcular aleatoriamente el lanzamiento de la computadora.
int repitio_disparo(int y, int x);         // Función para determinar si el disparo ya fue hecho.
int exportar_registro();                   // Función para exportar el registro de un juego a un archivo.

int iniciar_tableros();
int cargar_tableros();
int posicionar_barcos();
int mostrar_tableros(char ataque[10][10][5], char flota[10][10][5]);
int mostrar_tablero(char tablero[10][10][5]);
int mostrar_filas(int i, char tabla[10][5]);
int pantalla_inicial();
int pantalla_numero_de_jugadores();
int limpiar();
int filtro_scanf(int max);
int nadie_gano();
int juega_1();
int juega_2(int n_jugadores);
int pantalla_ganador(int ganador);
int filtro_scanf_posicion();
int validar_coordenadas(char coord[3]);
int ctoi(char n);

char tablero_ataque1[10][10][5], tablero_ataque2[10][10][5];
char tablero_flota1[10][10][5], tablero_flota2[10][10][5];
const char barcos[5][15] = {"Destructor", "Submarino", "Crucero", "Acorazado", "Portaaviones"};
const char letras_barcos[5] = {'D', 'S', 'C', 'A', 'P'};
/*
 ███╗   ███╗ █████╗ ██╗███╗   ██╗
 ████╗ ████║██╔══██╗██║████╗  ██║
 ██╔████╔██║███████║██║██╔██╗ ██║
 ██║╚██╔╝██║██╔══██║██║██║╚██╗██║
 ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
 ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ 
*/
int main()
{
    pantalla_inicial();

    // Opciones de la pantalla de carga.
    switch (filtro_scanf(3))
    {
    case 1: // Juego Nuevo
        iniciar_tableros();
        break;

    case 2: // Carga un juego
        cargar_tableros();
        break;

    case 3: // EXIT
        return 0;
    }

    limpiar();

    int numero_de_jugadores = pantalla_numero_de_jugadores();

    limpiar();

    posicionar_barcos(numero_de_jugadores);

    // Bucle del juego
    while (nadie_gano())
    {
        juega_1();
        juega_2(numero_de_jugadores);
    }

    limpiar();
    pantalla_ganador(nadie_gano());
}

/* 
 ███████╗██╗   ██╗███╗   ██╗ ██████╗██╗ ██████╗ ███╗   ██╗███████╗███████╗
 ██╔════╝██║   ██║████╗  ██║██╔════╝██║██╔═══██╗████╗  ██║██╔════╝██╔════╝
 █████╗  ██║   ██║██╔██╗ ██║██║     ██║██║   ██║██╔██╗ ██║█████╗  ███████╗
 ██╔══╝  ██║   ██║██║╚██╗██║██║     ██║██║   ██║██║╚██╗██║██╔══╝  ╚════██║
 ██║     ╚██████╔╝██║ ╚████║╚██████╗██║╚██████╔╝██║ ╚████║███████╗███████║
 ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚══════╝
*/

/*
  █████ █   █ █████ 
    █    █ █    █   
    █     █     █   
    █    █ █    █   
 █  █   █   █   █   
Funciones de manipulación de archivos de texto*/

/** 
 * Un lector para el archivo a pasar si se desea cargar un  juego. No debe
 * verificar la sintaxis del archivo, evite cometer errores al crear archivos
 *  de prueba. Se incluyen juegos de prueba.
 **/
int lector_de_archivo()
{
}

/**
* Una función para exportar el registro de un juego a un archivo. Esto incluye
* movimientos realizados, quién ganó y barcos hundidos.
**/
int exportar_registro()
{
}

/*
 ███ █    █ ███  ████ ███  ███  ████   ████  ████  █████  ████ 
  █  ██   █  █  █      █  █   █ █   █ █    █ █   █ █     █     
  █  █ █  █  █  █      █  █████ █   █ █    █ ████  ███    ███  
  █  █  █ █  █  █      █  █   █ █   █ █    █ █   █ █         █ 
 ███ █   ██ ███  ████ ███ █   █ ████   ████  █   █ █████ ████  
Funciones para la iniciacion de array.*/

/**
* Una función para verificar si los datos introducidos por el 
* usuario son válidos.
**/

/**
 * Una funcion para iniciar tablero
 **/
int cargar_tableros()
{
}
/**
* Una función para inicializar los tableros
**/
int iniciar_tableros()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            strcpy(tablero_ataque1[i][j], "____");
            strcpy(tablero_flota1[i][j], "____");
            strcpy(tablero_flota2[i][j], "____");
            strcpy(tablero_flota2[i][j], "____");
        }
    }
}

/*
 ████   ███  ████   ████ ████   ████ 
 █   █ █   █ █   █ █    █    █ █     
 ████  █████ ████  █    █    █  ███  
 █   █ █   █ █   █ █    █    █     █ 
 ████  █   █ █   █  ████ ████  ████  
 Funciones referentes a la creacion y manipulacion de barcos.*/

/**
 * Loop para posicionar barcos.
 **/
int posicionar_barcos(int n_jugadores)
{
    int coord_cabeza[3];
    int coord_cola[3];
    int tipo;
    if (n_jugadores == 1)
    {
        for (int i = 0; i < 5; i++)
        {
            limpiar();
            //TODO no funciona correctramente crear_buque.
            mostrar_tablero(tablero_flota1);
            tipo = 5 - i; // para empezar desde el portaaviones (5);
            printf("\n Indique la coordenada de la proa del barco %s (%d): ", barcos[tipo - 1], tipo);
            *coord_cabeza = filtro_scanf_posicion();
            printf("\n Indique la coordenada de la popa del barco %s (%d).", barcos[tipo - 1], tipo);
            *coord_cola = filtro_scanf_posicion();
            //TODO hacer q los barcos no se toquen.
            crear_buque(coord_cabeza, coord_cola, tipo, 1);
        }
    }
    else
    {
    }
}

/**
* Una función para añadir buques
**/
int crear_buque(int cabeza[3], int cola[3], int tipo, int jugador)
{
    int j, i;
    char number[20];

    int hi = cabeza[1];
    int hj = cabeza[0];
    int bi = cola[1];
    int bj = cola[0];

    //vemos si es horizontal o vertical
    int posicion = validar_posicion_barco(hj, hi, bj, bi, tipo);

    switch (posicion)
    {
    case 1: // HORIZONTAL
        for (int i = 0; i <= tipo; i++)
        {
            // itoa(i, number, 10);
            char coord[3] = {barcos[tipo][0], i, '\0'};
            if (jugador == 1)
                strcpy(tablero_flota1[hj][i], coord);
            else if (jugador == 2)
                strcpy(tablero_flota2[hj][i], coord);
        }

        break;
    case 2: // VERTICAL
        for (int i = 0; i <= tipo; i++)
        {
            // itoa(i, number, 10);
            char coord[3] = {barcos[tipo][0], i, '\0'};
            if (jugador == 1)
                strcpy(tablero_flota1[i][hi], coord);
            else if (jugador == 2)
                strcpy(tablero_flota1[i][hi], coord);
            break;
        }

    default:
        return 0;
    }
}

int validar_posicion_barco(int cabeza_j, int cabeza_i, int cola_j, int cola_i, int tipo)
{
    if (cabeza_i > 9 || cabeza_j > 9 || cola_i > 9 || cola_i > 9 ||
        cabeza_i < 0 || cabeza_j < 0 || cola_i < 0 || cola_i < 0)
        return 0;
    if (cabeza_i == cola_i)
    {
        if (cabeza_j - cola_j == abs(tipo) - 1)
        {
            return 1; // HORIZONTAL
        }
    }
    else if (cabeza_j == cola_j)
    {
        if (cabeza_i - cola_i == abs(tipo) - 1)
        {
            return 2; // VERTICAL
        }
    }

    return 0; // NO VALIDO
}

/**
* Una función para eliminar buques
**/
int eliminar_buque(int tipo, int jugador)
{
    return 0;
}

/*
  ███ █████ ███   ████  █   █ █████  ████ 
 █   █  █  █   █ █    █ █   █ █     █     
 █████  █  █████ █    █ █   █ ███    ███  
 █   █  █  █   █ █ ▄  █ █   █ █         █ 
 █   █  █  █   █  ████   ███  █████ ████  
                  ▀                  
 Funciones de jugadas*/
int juega_1()
{
    return 0;
}
int juega_2(int jugadores)
{
    return 0;
}

/**
* Una función para determinar si el disparo es un fallo, un acierto..
**/
int acerto_disparo(int y, int x)
{
}

/**
* Una función para calcular aleatoriamente el lanzamiento de la computadora.
* Esta función no tiene que ser una inteligencia artificial, basta con que
* la computadora pueda hacer lanzamientos “aleatorios” cada vez que se 
* ejecuta la función.
**/
int lanzamiento_pc()
{
}

/**
* Una función para determinar si el disparo ya fue hecho, importante
* para el punto anterior.
**/
int repitio_disparo(int y, int x)
{
}

int nadie_gano()
{
}

/* 
 ████  ████  ███ █    █ █████ 
 █   █ █   █  █  ██   █   █   
 ████  ████   █  █ █  █   █   
 █     █   █  █  █  █ █   █   
 █     █   █ ███ █   ██   █   
funciones relacionadas con la impresion en pantalla. */

/**
 * Imprime una fila del tablero a partir de un array.
 **/
int mostrar_filas(int i, char tabla[10][5])
{
    if (i < 9)
    {
        printf("|_%d__|", i + 1);
    }
    else
    {
        printf("|_%d_|", i + 1);
    }
    for (int j = 0; j < 10; j++)
    {
        printf("%s|", tabla[j]);
    }
}

/**
 * Imprime dos tableros a partir de dos arrays.
 **/
int mostrar_tableros(char ataque[10][10][5], char flota[10][10][5])
{
    printf("________________________________________________________\
  ________________________________________________________\
      \n|____|_1__|_2__|_3__|_4__|_5__|_6__|_7__|_8__|_9__|_10_|\
  |____|_1__|_2__|_3__|_4__|_5__|_6__|_7__|_8__|_9__|_10_|");

    for (int i = 0; i < 10; i++)
    {
        printf("\n");
        mostrar_filas(i, ataque[i]);
        printf("  ");
        mostrar_filas(i, flota[i]);
    }
}

/**
 * Imprime un tablero a partir de un array.
 **/
int mostrar_tablero(char tablero[10][10][5])
{
    printf("________________________________________________________");
    printf("\n|____|_1__|_2__|_3__|_4__|_5__|_6__|_7__|_8__|_9__|_10_|");
    for (int i = 0; i < 10; i++)
    {
        printf("\n");
        mostrar_filas(i, tablero[i]);
    }
}

/**
 * Imprime la pantalla incial.
 **/
int pantalla_inicial()
{
    //TITULO EN ASCII ART
    printf("\
______  ___ _____ _____ _      _____ _____ _   _ ___________\n\
| ___ \\/ _ \\_   _|_   _| |    |  ___/  ___| | | |_   _| ___ \\\n\
| |_/ / /_\\ \\| |   | | | |    | |__ \\ `--.| |_| | | | | |_/ /\n\
| ___ \\  _  || |   | | | |    |  __| `--. \\  _  | | | |  __/\n\
| |_/ / | | || |   | | | |____| |___/\\__/ / | | |_| |_| |  \n\
\\____/\\_| |_/\\_/   \\_/ \\_____/\\____/\\____/\\_| |_/\\___/\\_|");
    //SEPARADOR
    printf("\n--------------------------------------------------------------");
    //OPCIONES
    printf("\n1 Crear un juego");
    printf("\n2 Cargar un juego");
    printf("\n3 Salir del juego");
    printf("\n> Selecione una opcion: ");
}

/**
 * Imprime la pantalla de numero de jugadores.
 **/
int pantalla_numero_de_jugadores()
{
    printf("\
______  ___ _____ _____ _      _____ _____ _   _ ___________\n\
| ___ \\/ _ \\_   _|_   _| |    |  ___/  ___| | | |_   _| ___ \\\n\
| |_/ / /_\\ \\| |   | | | |    | |__ \\ `--.| |_| | | | | |_/ /\n\
| ___ \\  _  || |   | | | |    |  __| `--. \\  _  | | | |  __/\n\
| |_/ / | | || |   | | | |____| |___/\\__/ / | | |_| |_| |  \n\
\\____/\\_| |_/\\_/   \\_/ \\_____/\\____/\\____/\\_| |_/\\___/\\_|");
    //SEPARADOR
    printf("\n----------------------NUEVA PARTIDA---------------------------");
    printf("\n1 Jugar con un amigo.");
    printf("\n2 Jugar contra la maquina.");
    printf("\n> Selecione una opcion: ");

    return filtro_scanf(2);
}

int pantalla_ganador(int ganador)
{
    printf("\
______  ___ _____ _____ _      _____ _____ _   _ ___________\n\
| ___ \\/ _ \\_   _|_   _| |    |  ___/  ___| | | |_   _| ___ \\\n\
| |_/ / /_\\ \\| |   | | | |    | |__ \\ `--.| |_| | | | | |_/ /\n\
| ___ \\  _  || |   | | | |    |  __| `--. \\  _  | | | |  __/\n\
| |_/ / | | || |   | | | |____| |___/\\__/ / | | |_| |_| |  \n\
\\____/\\_| |_/\\_/   \\_/ \\_____/\\____/\\____/\\_| |_/\\___/\\_|");
    //SEPARADOR
    printf("\n----------------------GANADOR---------------------------");
    printf("\nFelicidades a jugador %d.", &ganador);

    return 0;
}

/**
 * Limpia la pantalla.
 **/
int limpiar()
{
    system("cls");
    // system("clear");
}

/*
  ████  ████  ███  █    █ 
 █     █     █   █ ██   █ 
  ███  █     █████ █ █  █ 
     █ █     █   █ █  █ █ 
 ████   ████ █   █ █   ██ 
Funciones de toma de decisiones a partir de scanf*/

int filtro_scanf(int max)
{
    int numero;
    int orden = scanf("%d", &numero);
    while (orden == 0 || numero > max || numero < 0)
    {
        printf("Debe seleccionar una opcion Valida: ");
        fflush(stdin);
        orden = scanf("%d", &numero);
    }
    return numero;
}

/**
 * Captura las coordenadas y regresa un array [j,i]
 **/
int filtro_scanf_posicion()
{
    char posicion[3];
    int j, i;

    int orden = scanf("%s", &posicion);

    while (orden == 0 || !validar_coordenadas(posicion))
    {
        printf("La posicion debe ser del tipo LETRA-NUMERO (Ejemplo: A2, F5): ");
        fflush(stdin);
        orden = scanf("%s", &posicion);
    }

    j = ctoi(posicion[0]) - 97;
    i = atoi(&posicion[1]) - 1;
    printf("j=%d, i=%d", j,i); //! TEST

    int coord[2] = {j, i};
    return *coord;
}

/**
 * Evalua si el string es de forma LETRA-NUMERO (Ejemplo: A2, F5)
 **/
int validar_coordenadas(char coord[3])
{
    int j = ctoi(coord[0]) - 97;
    int i = atoi(&coord[1]) - 1;

    if (i < 0 || j < 0 || i > 9 || j > 9)
        return 0;
    else
        return 1;
}

int ctoi(char n)
{
    return tolower(n);
}