#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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
                           int tipo, int jugador); // Verifica si los datos introducidos por el usuario son válidos.
int crear_buque(int hj, int hi, int bj,
                int bi, int tipo, int jugador); // Función para añadir buques.
int lector_de_archivo();                        // Lector para el archivo a pasar si se desea cargar un juego.
int eliminar_buque(int tipo, int jugador);      // Función para eliminar buques.
int acerto_disparo(int y, int x);               // Función para determinar si el disparo es un fallo, un acierto..
int lanzamiento_pc();                           //Función para calcular aleatoriamente el lanzamiento de la computadora.
int repitio_disparo(int y, int x);              // Función para determinar si el disparo ya fue hecho.
int exportar_registro();                        // Función para exportar el registro de un juego a un archivo.

int iniciar_tableros();
int barcos_alrededos(int j, int i, int tipo, int jugador);
int cargar_tableros();
int posicionar_barcos();
int robot_posiciona();
int popas_posibles(int hj, int hi, int tipo, int jugador, int (*popas_validas)[2]);
int proas_posibles(int jugador, int tipo, int (*popas_proas)[2]);
int mostrar_tableros(char ataque[10][10][5], char flota[10][10][5]);
int mostrar_tablero(char tablero[10][10][5]);
int mostrar_filas(int i, char tabla[10][5]);
int pantalla_inicial();
int pantalla_numero_de_jugadores();
int mostrar_preparado_jugador(int jugador);
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
int numero_de_jugadores;

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
    limpiar();
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

    numero_de_jugadores = pantalla_numero_de_jugadores();

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
            strcpy(tablero_ataque1[i][j], "__");
            strcpy(tablero_flota1[i][j], "__");
            strcpy(tablero_flota2[i][j], "__");
            strcpy(tablero_flota2[i][j], "__");
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
    int cabeza;
    int cola;
    int tipo;
    int hi;
    int hj;
    int bi;
    int bj;

    for (int jugador = 1; jugador < 3; jugador++)
    {
        limpiar();
        mostrar_preparado_jugador(jugador);

        for (int i = 0; i < 5; i++)
        {
            limpiar();

            if (jugador == 1)
            {
                mostrar_tablero(tablero_flota1);
            }
            else
            {
                if (n_jugadores == 2)
                    mostrar_tablero(tablero_flota2);
            }

            tipo = 5 - i; // para empezar desde el portaaviones (5);
            printf("\n\n Indique la coordenada de la PROA del barco %s (%d): ", barcos[tipo - 1], tipo);

            do
            {
                cabeza = filtro_scanf_posicion();
                hi = cabeza % 10;
                hj = (cabeza - cabeza % 10) / 10;
                if (barcos_alrededos(hj, hi, tipo, jugador))
                    break;
            } while (1);

            //Si el barco es de 1
            if (tipo == 1)
            {
                crear_buque(hj, hi, hj, hi, tipo, jugador);
            }

            else
            {
                do
                {
                    printf("\n Indique la coordenada de la POPA del barco %s (%d): ", barcos[tipo - 1], tipo);

                    cola = filtro_scanf_posicion();

                    bi = cola % 10;
                    bj = (cola - cola % 10) / 10;
                    if (validar_posicion_barco(hj, hi, bj, bi, tipo, jugador) != 0 && barcos_alrededos(bj, bi, tipo, jugador) != 0)
                        break;
                } while (1);
            }

            crear_buque(hj, hi, bj, bi, tipo, jugador);
        }

        limpiar();

        if (jugador == 1)
        {
            mostrar_tablero(tablero_flota1);
        }
        else
        {
            if (n_jugadores == 2)
                mostrar_tablero(tablero_flota2);
        }
        printf("\n\nPresione una tecla para continuar.");
        fflush(stdin);
        getchar();

        if (n_jugadores == 1)
        {
            robot_posiciona();
            break;
        }
    }
}

/**
* Una función para añadir buques
**/
int crear_buque(int hj, int hi, int bj, int bi, int tipo, int jugador)
{
    printf("\n creando buque: (%d %d), (%d %d).", hj, hi, bj, bi);
    int j, i;
    int init;
    char number[20];

    //vemos si es horizontal o vertical
    int posicion = validar_posicion_barco(hj, hi, bj, bi, tipo, jugador);

    //!test------
    // printf("\nEn crearbuque la posicion es: %d, tipo: %d, hj=%d, hi=%d, bj=%d, bi=%d", posicion, tipo, hj, hi, bj, bi);
    // getchar();
    // getchar();
    //!-----------

    switch (posicion)
    {
    case 1: // HORIZONTAL
        init = hi > bi ? bi : hi;
        for (int i = 0; i < tipo; i++)
        {
            char objeto_tablero[3] = {barcos[tipo - 1][0], (i + 1) + '0', '\0'};
            if (jugador == 1)
                strcpy(tablero_flota1[hj][i + init], objeto_tablero);
            else if (jugador == 2)
                strcpy(tablero_flota2[hj][i + init], objeto_tablero);

            //!test------
            // printf("tablero flota en %d %d = %s", hj, i, tablero_flota1[hj + init][i]);
            // getchar();
            // getchar();
            //!---------
        }
        break;

    case 2: // VERTICAL
        init = hj > bj ? bj : hj;
        for (int i = 0; i < tipo; i++)
        {
            char objeto_tablero[3] = {barcos[tipo - 1][0], (i + 1) + '0', '\0'};
            if (jugador == 1)
                strcpy(tablero_flota1[i + init][hi], objeto_tablero);
            else if (jugador == 2)
                strcpy(tablero_flota2[i + init][hi], objeto_tablero);

            //!test------
            // printf("tablero flota en %d %d = %s", hj, i, tablero_flota1[i][hi + init]);
            // getchar();
            // getchar();
            //!-----------
        }
        break;

    default:
        return 0;
    }
}

int validar_posicion_barco(int cabeza_j, int cabeza_i, int cola_j, int cola_i, int tipo, int jugador)
{
    if (tipo == 1)
        return 1;
    int menor;

    //!test------
    // printf("\n en validar posicion %d %d %d %d %d", cabeza_j, cabeza_i, cola_j, cola_i, tipo);
    //!---------
    if (cabeza_i > 9 || cabeza_j > 9 || cola_i > 9 || cola_j > 9 || cabeza_i < 0 || cabeza_j < 0 || cola_i < 0 || cola_j < 0)
    {
        if (jugador == 1 || numero_de_jugadores == 2)
            printf(" Las coordenadas no estan dentro del rango!");
        return 0;
    }

    if (cabeza_i == cola_i)
    {
        if (tipo == 5)
        {
            menor = cabeza_j > cola_j ? cola_j : cabeza_j;
            if (barcos_alrededos(menor + 2, cola_i, tipo, jugador) == 0)
                return 0;
        }

        if (abs(cabeza_j - cola_j) == tipo - 1)
        {
            return 2; // HORIZONTAL
        }
    }
    else if (cabeza_j == cola_j)
    {
        if (tipo == 5)
        {
            menor = cabeza_i > cola_i ? cola_i : cabeza_i;
            if (barcos_alrededos(cola_j, menor + 2, tipo, jugador) == 0)
                return 0;
        }

        if (abs(cabeza_i - cola_i) == tipo - 1)
        {
            return 1; // VERTICAL
        }
    }
    if (jugador == 1 || numero_de_jugadores == 2)
        printf(" La longitud del barco no es correcta, debe ser de %d!", tipo);
    return 0; // NO VALIDO
}

/**
* Una funcion que revisa si hay otros barcos al rededor.
**/
int barcos_alrededos(int j, int i, int tipo, int jugador)
{
    // printf(" en barcos alrededores: j=%d, i=%d, tipo=%d, jugador=%d.", j, i, tipo, jugador);

    char letra[2] = {barcos[tipo - 1][0], '\0'};
    for (int u = 0; u < 3; u++)
    {
        for (int v = 0; v < 3; v++)
        {
            // printf(" en barcos alrededores 2");

            if (j - 1 + v < 0 || j - 1 + v > 9 || i - 1 + u < 0 || i - 1 + u > 9)
                continue;
            else if (jugador == 1)
            {
                if (!strstr(tablero_flota1[j - 1 + v][i - 1 + u], letra) && !strstr(tablero_flota1[j - 1 + v][i - 1 + u], "__"))
                {
                    printf(" No puede estar tan cerca de otro buque!: ");
                    return 0;
                }
            }
            else
            {
                if (!strstr(tablero_flota2[j - 1 + v][i - 1 + u], letra) && !strstr(tablero_flota2[j - 1 + v][i - 1 + u], "__"))
                {
                    if (numero_de_jugadores == 2)
                        printf(" No puede estar tan cerca de otro buque!: ");
                    return 0;
                }
            }
        }
        // printf("fin iteracion %d", u);
    }
    //!test------
    // printf(" todo fino en j=%d i=%d con tipo=%d, jugador=%d", j, i, tipo, jugador);
    printf("(%d %d) ", j, i);
    //!----------
    return 1;
}

/**
* Una función para eliminar buques
**/
int eliminar_buque(int tipo, int jugador)
{
    return 0;
}

/*
 ████   ████  ████   ████ █████ 
 █   █ █    █ █   █ █    █  █   
 ████  █    █ ████  █    █  █   
 █   █ █    █ █   █ █    █  █   
 █   █  ████  ████   ████   █   
Funciones relacionadas al las jugadas de la computadora*/

int robot_posiciona()
{
    int n_proas;
    int proa_aleatoria;
    int n_popas;
    int popa_aleatoria;

    int proas_validas[100][2] = {0};
    int popas_validas[4][2] = {0};

    srand(time(NULL));
    int ri = rand() % 10;
    srand(time(NULL));
    int rj = rand() % 10;
    n_popas = popas_posibles(ri, rj, 5, 2, popas_validas);
    srand(time(NULL));
    popa_aleatoria = rand() % n_popas;
    crear_buque(ri, rj, popas_validas[popa_aleatoria][0], popas_validas[popa_aleatoria][1], 5, 2);

    for (int u = 0; u < 4; u++)
    {
        // limpiar();
        printf("\n\n El robotico esta jugando u=%d", u);
        printf("\n Esta posicionando el %s.", barcos[3 - u]);

        do
        {
            printf("\n proas posibles:");
            n_proas = proas_posibles(2, 4 - u, proas_validas);
            srand(time(NULL));
            proa_aleatoria = rand() % n_proas;
            printf("\n proa aleatoria %d.", proa_aleatoria);

            printf("\n popas posibles:");
            n_popas = popas_posibles(proas_validas[proa_aleatoria][0], proas_validas[proa_aleatoria][1], 4 - u, 2, popas_validas);
            srand(time(NULL));
            popa_aleatoria = rand() % n_popas;
            printf("\n popa aleatoria %d.", popa_aleatoria);

            // } while(0);
        } while (validar_posicion_barco(proas_validas[proa_aleatoria][0], proas_validas[proa_aleatoria][1], popas_validas[popa_aleatoria][0], popas_validas[popa_aleatoria][1], 4 - u, 2) == 0);

        crear_buque(proas_validas[proa_aleatoria][0], proas_validas[proa_aleatoria][1], popas_validas[popa_aleatoria][0], popas_validas[popa_aleatoria][1], 4 - u, 2);
        // printf("buque creado\n");
        // limpiar();
    }

    printf("\n\n\n\n          ######################################\n");
    printf("          #      La computadora posiciono.     #\n");
    printf("          #              Empezar (1)           #\n");
    printf("          #      Ver tablero de la pc (2)      #\n");
    printf("          ######################################\n\n");
    printf("                           > ");
    if (filtro_scanf(2) == 2)
    {
        limpiar();
        mostrar_tablero(tablero_flota2);
        fflush(stdin);
        getchar();
    }
}

int proas_posibles(int jugador, int tipo, int (*proas_validas)[2])
{
    int validas = 0;
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            if (barcos_alrededos(j, i, tipo, jugador))
            {
                proas_validas[validas][0] = j;
                proas_validas[validas][1] = i;
                validas++;
            }
        }
    }
    return validas;
}

int popas_posibles(int hj, int hi, int tipo, int jugador, int (*popas_validas)[2])
{
    int j;
    int i;
    int validos = 0;

    int popas[4][2] = {{hj - abs(tipo - 1), hi},  //arriba
                       {hj, hi + tipo - 1},       //derecha
                       {hj + tipo - 1, hi},       //abajo
                       {hj, hi - abs(tipo - 1)}}; //izquierda
    //!test
    // printf("\nposiciones aleatorias hj=%d, hi=%d:\n", hj, hi);

    for (int u = 0; u < 4; u++)
    {
        j = popas[u][0];
        i = popas[u][1];
        //!test
        // printf("\n popas posible j=%d, i=%d: ", j, i);
        // popas_validas = malloc(4 * 2 * sizeof(int));
        if (barcos_alrededos(j,i,tipo,jugador)!=0)
        {
            if (validar_posicion_barco(hj, hi, j, i, tipo, jugador) != 0)
            {
                //!test
                popas_validas[validos][0] = j;
                popas_validas[validos][1] = i;
                // printf(" \npopas validas j i-> %d %d", j, i);
                // printf(" \n popas validas -> %d %d", popas_validas[validos][0], popas_validas[validos][1]);
                validos++;
            }
        }
    }
    // printf(" popas validas en posibles: %d %d", popas_validas[0][0], popas_validas[0][1]);
    return validos;
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
    // motrar las letras de la coordenada Y
    printf("|_%c__|", i + 65);

    //Mostrar lo que esta en el array
    for (int j = 0; j < 10; j++)
    {
        printf("_%s_|", tabla[j]);
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
    printf("\n--------------------------------------------------------------\n");
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
    printf("\n----------------------NUEVA PARTIDA---------------------------\n");
    printf("\n1 Jugar contra la maquina.");
    printf("\n2 Jugar con un amigo.");
    printf("\n> Selecione una opcion: ");

    return filtro_scanf(2);
}
int mostrar_preparado_jugador(int jugador)
{
    printf("\n\n\n\n          ######################################\n");
    printf("          #     Es el turno del jugador %d.     #\n", jugador);
    printf("          # Presione una tecla para continuar. #\n");
    printf("          ######################################");
    getchar();
    getchar();
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
    printf("\n----------------------GANADOR---------------------------\n");
    printf("\nFelicidades al jugador %d.", &ganador);

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
        printf("La posicion debe ser del tipo LETRA-NUMERO (Ejemplo: A2): ");
        fflush(stdin);
        orden = scanf("%s", &posicion);
    }

    j = ctoi(posicion[0]) - 97;
    i = atoi(&posicion[1]) - 1;

    int coord = (j * 10) + i;
    // printf("COOR EN FILTRO = %d", coord); //! TEST
    return coord;
}

/**
 * Evalua si el string es de forma LETRA-NUMERO (Ejemplo: A2, F5)
 **/
int validar_coordenadas(char coord[3])
{
    int j = ctoi(coord[0]) - 97;
    int i = atoi(&coord[1]) - 1;

    if (i < 0 || j < 0 || i > 9 || j > 9 || strstr(coord, "  ") != NULL)
        return 0;
    else
        return 1;
}

int ctoi(char n)
{
    return tolower(n);
}