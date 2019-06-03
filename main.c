//TODO Al destruir un barco que lo muestre en pantalla.
//TODO "q" para salirse.
//TODO opcion de reasignar un barco.
//TODO documentar funciones.
//TODO quitar fprints innecesarias.
//TODO probar en linux.

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
int ubicar_caracter(char *string_, char caracter);
int eliminar_buque(int tipo, int jugador);                                     // Función para eliminar buques.
int acerto_disparo(char (*tablero_ataque)[10][5], int j, int i);               // Función para determinar si el disparo es un fallo, un acierto..
int lanzamiento_pc();                                                          //Función para calcular aleatoriamente el lanzamiento de la computadora.
int repitio_disparo(char (*tablero_ataque)[10][5], int j, int i, int jugador); // Función para determinar si el disparo ya fue hecho.
int exportar_registro();                                                       // Función para exportar el registro de un juego a un archivo.

int guardar_registro(int j, int i, int jugador);
int pc_escoge_pais();
int iniciar_tableros();
int barcos_alrededos(int j, int i, int tipo, int jugador);
int cargar_tableros();
int posicionar_barcos();
int robot_posiciona();
int popas_posibles(int hj, int hi, int tipo, int jugador, int (*popas_validas)[2]);
int proas_posibles(int jugador, int tipo, int (*popas_proas)[2]);
int asignar_matriz(char (*matriz)[10][5]);
int mostrar_estadisticas(int jugador);
int mostrar_tableros(char ataque[10][10][5], char flota[10][10][5]);
int mostrar_tablero(char tablero[10][10][5]);
int escoger_pais(char *pais);
int mostrar_filas(int i, char tabla[10][5]);
int pantalla_inicial();
int pantalla_numero_de_jugadores();
int mostrar_preparado_jugador(int jugador);
int limpiar();
int filtro_scanf(int max);
int nadie_gano();
int juega(int turno);
int lanzamiento_jugador(int j, int i, char (*tablero_ataque)[10][5], char (*tablero_flota)[10][5], int n_barcos);
int pantalla_ganador(int ganador);
int filtro_scanf_posicion();
int validar_coordenadas(char coord[3]);
int coord_int_char(int j, int i, char *coord);
int ctoi(char n);

char tablero_ataque1[10][10][5], tablero_ataque2[10][10][5], ult_celda1[4], pais1[20];
char tablero_flota1[10][10][5], tablero_flota2[10][10][5], ult_celda2[4], pais2[20];
char registro_jugadas[200][10];
const char barcos[5][15] = {"Destructor", "Submarino", "Crucero", "Acorazado", "Portaaviones"};
char paises[23][20] = {"Australia", "Canada", "Chile", "China", "Colombia",
                       "Corea del Sur", "Estados Unidos", "Filipinas", "Francia", "India", "Indonesia", "Japon",
                       "Malasia", "Mexico", "Noruega", "Nueva Zelanda", "Paises Bajos", "Peru", "Reino Unido",
                       "Rusia", "Singapur", "Tailandia", "Tonga"};
int numero_de_jugadores;
int n_barcos1, n_disparos1;
int n_barcos2, n_disparos2;

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
    int turno = 0;

    limpiar();
    pantalla_inicial();

    // Opciones de la pantalla de carga.
    switch (filtro_scanf(3))
    {
    case 1: // Juego Nuevo

        iniciar_tableros();

        limpiar();

        numero_de_jugadores = pantalla_numero_de_jugadores();

        limpiar();

        posicionar_barcos(numero_de_jugadores);

        break;

    case 2: // Carga un juego
        iniciar_tableros();

        cargar_tableros();
        break;

    case 3: // EXIT
        return 0;
    }

    // Bucle del juego

    while (nadie_gano() == 0)
    {
        juega((turno++ % 2) + 1);
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
    FILE *archivo;
    char linea[100];
    int n_linea = 0;
    int jugador = 1;
    int tipo = 0;
    int len_linea = 0;
    int hj = 0;
    int hi = 0;
    int bj = 0;
    int bi = 0;
    int cabeza;
    int cola;
    int zero_jump = 0;
    archivo = fopen("partida.txt", "r");

    while (fgets(linea, 100, (FILE *)archivo))
    {
        switch (n_linea)
        {
        case 0: // INDIVIUAL O MULTIJUGADOR
            if (linea[0] == 'U')
                numero_de_jugadores = 1;
            else if (linea[0] == 'M')
                numero_de_jugadores = 2;
            break;

        case 1: //Que jugador es
            if (strstr(linea, "J1"))
            {
                jugador = 1;
            }
            else if (strstr(linea, "J2"))
            {
                jugador = 2;
            }
            break;
        case 2: // PAIS
            if (jugador == 1)
                strcpy(pais1, linea);
            else if (jugador == 2)
                strcpy(pais2, linea);
            break;
        default: // Ubicacion de barcos
            switch (linea[0])
            {
            case 'P':
                tipo = 5;
                break;
            case 'A':
                tipo = 4;
                break;
            case 'C':
                tipo = 3;
                break;
            case 'S':
                tipo = 2;
                break;
            case 'D':
                tipo = 1;
                break;

            default:
                break;
            }

            if (tipo > 0)
            {

                len_linea = ubicar_caracter(linea, ',');

                hj = ctoi(linea[len_linea + 1]) - 97;
                hi = atoi(&linea[len_linea + 2]) - 1;
                if (linea[len_linea + 3] != ','){
                    hi = 9;
                    zero_jump++;
                }
                bj = ctoi(linea[len_linea + 4 + zero_jump]) - 97;
                bi = atoi(&linea[len_linea + 5 + zero_jump]) - 1;
                if (linea[len_linea + 6 + zero_jump] == '0'){
                    bi = 9;
                    zero_jump = 0;    
                }

                while (!crear_buque(hj, hi, bj, bi, tipo, jugador))
                {
                    limpiar();
                    printf("\n*** Coordenadas %c%d, %c%d invalidas para buque de largo (%d). ***\n", hj+97,hi+1,bj+97,bi+1, tipo);

                    if (jugador == 1)
                    {
                        mostrar_tablero(tablero_flota1);
                    }
                    else
                    {
                        if (numero_de_jugadores == 2)
                            mostrar_tablero(tablero_flota2);
                    }
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
                            printf("%d %d", n_barcos1,n_barcos2);
                            printf("\n Indique la coordenada de la POPA del barco %s (%d)\n", barcos[tipo - 1], tipo);

                            cola = filtro_scanf_posicion();

                            bi = cola % 10;
                            bj = (cola - cola % 10) / 10;
                            if (validar_posicion_barco(hj, hi, bj, bi, tipo, jugador) != 0 && barcos_alrededos(bj, bi, tipo, jugador) != 0)
                                break;
                        } while (1);
                    }
                }
            }
            if (tipo == 1)
                n_linea = 0;
        }
        n_linea++;
    }
}

int ubicar_caracter(char *string_, char caracter)
{
    int i = 0;
    int k = 0;

    while (!(string_[i] == caracter))
    {
        i++;
    }
    return i;
}

/**
* Una función para exportar el registro de un juego a un archivo. Esto incluye
* movimientos realizados, quién ganó y barcos hundidos.
**/
int exportar_registro()
{
    FILE *archivo;
    archivo = fopen("registro.txt", "wt");
    int i = 0;
    while (i < n_disparos1+n_disparos2)
    {
        fputs(registro_jugadas[i],archivo);
        fputs("\n",archivo);
        i++;
    }
    
    fclose(archivo);
    return 0;
}

/**
 * Guarda las coordenadas en el array de registro.
 **/
int guardar_registro(int j, int i, int jugador){
    char registro[10] = "";
    char coord[4]="";
    strcpy(registro, jugador == 0 ? "PC (" : jugador == 1 ? "J1 (" : "J2 (");
    coord_int_char(j,i,coord);
    strcat(registro, coord);
    strcat(registro, ")");
    strcpy(registro_jugadas[n_disparos1+n_disparos2], registro);
    return 0;
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
    printf("*** Se cargara el archivo con nombre: partida.txt ***\n");
    printf("    Presione una tecla para continuar. ");
    lector_de_archivo();
    fflush(stdin);
    getchar();
    return 0;
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
            strcpy(tablero_ataque2[i][j], "__");
            strcpy(tablero_flota1[i][j], "__");
            strcpy(tablero_flota2[i][j], "__");
        }
    }
    strcpy(ult_celda1, " ");
    strcpy(ult_celda2, " ");
    n_barcos1 = 0;
    n_barcos2 = 0;
    n_disparos1 = 0;
    n_disparos2 = 0;
    strcpy(pais1, "");
    strcpy(pais2, "");
    return 0;
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
        limpiar();
        if (jugador == 1)
            escoger_pais(pais1);
        else if (numero_de_jugadores == 2)
            escoger_pais(pais2);

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
                {

                    mostrar_tablero(tablero_flota2);
                }
                else
                {
                    pc_escoge_pais();
                }
            }

            tipo = 5 - i; // para empezar desde el portaaviones (5);
            printf("\n\n Indique la coordenada de la PROA del barco %s (%d): ", barcos[tipo - 1], tipo < 3 ? tipo+1:tipo);

            do
            {
                cabeza = filtro_scanf_posicion();
                hi = cabeza % 10;
                hj = (cabeza - cabeza % 10) / 10;
                if (barcos_alrededos(hj, hi, tipo, jugador))
                    break;
            } while (1);

            //Si el barco es de 1
            // if (tipo == 1 )
            // {
            //     crear_buque(hj, hi, hj, hi, tipo, jugador);
            // }
            // else
            // {
                do
                {
                    printf("\n Indique la coordenada de la POPA del barco %s (%d): ", barcos[tipo - 1], tipo < 3 ? tipo+1:tipo);

                    cola = filtro_scanf_posicion();

                    bi = cola % 10;
                    bj = (cola - cola % 10) / 10;
                    if (validar_posicion_barco(hj, hi, bj, bi, tipo, jugador) != 0 && barcos_alrededos(bj, bi, tipo, jugador) != 0)
                        break;
                } while (1);
                crear_buque(hj, hi, bj, bi, tipo, jugador);
            // }
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
    // printf("\n creando buque: (%d %d), (%d %d).", hj, hi, bj, bi);
    int j, i;
    int init,tipo_;
    char number[20];

    //vemos si es horizontal o vertical
    int posicion = validar_posicion_barco(hj, hi, bj, bi, tipo, jugador);
    tipo_ = tipo;
    tipo = tipo < 3 ? tipo+1 : tipo;
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
            char objeto_tablero[3] = {barcos[tipo_ - 1][0], (i + 1) + '0', '\0'};
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
            char objeto_tablero[3] = {barcos[tipo_ - 1][0], (i + 1) + '0', '\0'};
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
    // if (tipo == 1)
    //     return 1;
    int menor;
    tipo = tipo < 3 ? tipo+1 : tipo;

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
    // printf("(%d %d) ", j, i);
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
int pc_escoge_pais()
{
    return 0;
}

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

    limpiar();
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
    int tipo_ = 0;
    tipo_ = tipo < 3 ? tipo+1 : tipo;

    int popas[4][2] = {{hj - abs(tipo_ - 1), hi},  //arriba
                       {hj, hi + tipo_ - 1},       //derecha
                       {hj + tipo_ - 1, hi},       //abajo
                       {hj, hi - abs(tipo_ - 1)}}; //izquierda
    //!test
    // printf("\nposiciones aleatorias hj=%d, hi=%d:\n", hj, hi);

    for (int u = 0; u < 4; u++)
    {
        j = popas[u][0];
        i = popas[u][1];
        //!test
        // printf("\n popas posible j=%d, i=%d: ", j, i);
        // popas_validas = malloc(4 * 2 * sizeof(int));
        if (barcos_alrededos(j, i, tipo, jugador) != 0)
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

/**
* Una función para calcular aleatoriamente el lanzamiento de la computadora.
* Esta función no tiene que ser una inteligencia artificial, basta con que
* la computadora pueda hacer lanzamientos “aleatorios” cada vez que se 
* ejecuta la función.
**/
int lanzamiento_pc()
{
    int suma = 0;
    int j = 0;
    int i = 0;

    do
    {
        limpiar();
        srand(time(NULL));
        suma = rand() % 100;
        i = suma % 10;
        j = (suma - i) / 10;

    } while (repitio_disparo(tablero_ataque2, j, i, 2) != 0);
    guardar_registro(j,i,0);
    return lanzamiento_jugador(j, i, tablero_ataque2, tablero_flota1, 1);
}

/*
  ███ █████ ███   ████  █   █ █████  ████ 
 █   █  █  █   █ █    █ █   █ █     █     
 █████  █  █████ █    █ █   █ ███    ███  
 █   █  █  █   █ █ ▄  █ █   █ █         █ 
 █   █  █  █   █  ████   ███  █████ ████  
                  ▀                  
 Funciones de jugadas*/

int juega(int turno)
{
    int acerto = 0;
    int i, j;
    int suma;

    limpiar();
    limpiar();
    if (turno == 2 && numero_de_jugadores == 1)
    {
        printf("\n\n\n\n          ######################################\n");
        printf("          #  La computadora jugo. Es tu turno. #\n");
        printf("          # Presione una tecla para continuar. #\n");
        printf("          ######################################");
        fflush(stdin);
        getchar();
    }
    else if (numero_de_jugadores == 2)
        mostrar_preparado_jugador(turno);

    do
    {
        limpiar();

        if (acerto)
        {
            // la cantidad de barcos que ha destruido, cantidad
            // de barcos que ha perdido, cantidad de tiros que ha hecho, y la última celda atacada por el jugador.
            printf("*** Haz acertado. Vuelve a jugar! ***\n");
        }

        if (turno == 1)
        {
            mostrar_estadisticas(1);
            mostrar_tableros(tablero_flota1, tablero_ataque1);
            printf("%d %d", n_barcos1,n_barcos2);
            printf("\n> Indique coordenadas para atacar: ");

            do
            {
                suma = filtro_scanf_posicion();
                i = suma % 10;
                j = (suma - i) / 10;

            } while (repitio_disparo(tablero_ataque1, j, i, 2) != 0);
            guardar_registro(j,i,1);
            acerto = lanzamiento_jugador(j, i, tablero_ataque1, tablero_flota2, 2);
            n_disparos1++;
            coord_int_char(j, i, ult_celda1);

            if (!acerto)
            {
                limpiar();
                mostrar_estadisticas(1);
                mostrar_tableros(tablero_flota1, tablero_ataque1);
                printf("\nFin del turno. Aprete una tecla para continuar.");
                fflush(stdin);
                getchar();
            }
        }
        else
        {
            if (numero_de_jugadores == 2)
            {
                mostrar_estadisticas(2);
                mostrar_tableros(tablero_flota2, tablero_ataque2);
                printf("%d %d", n_barcos1,n_barcos2);
                printf("\n Indique coordenadas para atacar: ");

                do
                {
                    suma = filtro_scanf_posicion();
                    i = suma % 10;
                    j = (suma - i) / 10;

                } while (repitio_disparo(tablero_ataque2, j, i, 2) != 0);
                guardar_registro(j,i,2);

                acerto = lanzamiento_jugador(j, i, tablero_ataque2, tablero_flota1, 1);
                n_disparos2++;
                coord_int_char(j, i, ult_celda2);

                if (!acerto)
                {
                    limpiar();
                    mostrar_estadisticas(2);
                    mostrar_tableros(tablero_flota2, tablero_ataque2);
                    printf("\nFin del turno. Aprete una tecla para continuar.");
                    fflush(stdin);
                    getchar();
                }
            }
            else
            {
                acerto = lanzamiento_pc();
            }
        }

        if (nadie_gano() != 0)
            break;
    } while (acerto != 0);

    return 0;
}

int lanzamiento_jugador(int j, int i, char (*tablero_ataque)[10][5], char (*tablero_flota)[10][5], int n_barcos)
{
    int tipo_barco = 0;
    int golpe = 0;

    if (strstr(tablero_flota[j][i], "__"))
    {
        tablero_ataque[j][i][0] = 'O';
        tablero_flota[j][i][0] = 'O';
        return 0;
    }
    else
    {
        tablero_ataque[j][i][0] = 'X';
        // tablero_ataque[j][i][0] = tablero_flota[j][i][0];
        // tablero_ataque[j][i][2] = '_';
        tablero_flota[j][i][2] = '!';

        switch (tablero_flota[j][i][0])
        {
            //"Destructor", "Submarino", "Crucero", "Acorazado", "Portaaviones"
        case 'P':
            golpe = 10000;
            tipo_barco = 5;
            break;
        case 'A':
            golpe = 1000;
            tipo_barco = 4;
            break;
        case 'C':
            golpe = 100;
            tipo_barco = 3;
            break;
        case 'S':
            golpe = 10;
            tipo_barco = 2;
            break;
        case 'D':
            tipo_barco = 1;
            golpe = 1;
            break;
        default:
            break;
        }

        if (n_barcos == 1)
            n_barcos1 += golpe;
        else
            n_barcos2 += golpe;
        return tipo_barco;
    }
}

/**
* Una función para determinar si el disparo es un fallo, un acierto..
**/
int acerto_disparo(char (*tablero_ataque)[10][5], int j, int i)
{
    return 0;
}

/**
* Una función para determinar si el disparo ya fue hecho, importante
* para el punto anterior.
**/
int repitio_disparo(char (*tablero_ataque)[10][5], int j, int i, int jugador)
{
    if (strstr(tablero_ataque[j][i], "__"))
        return 0;
    else
    {
        if (jugador == 2 && numero_de_jugadores == 2)
            printf("\n Lo que esta muerto no puede morir. Elija otra coordenada: ");
        return 1;
    }
}

int nadie_gano()
{
    // printf("n_barcos1: %d, n_barcos2: %d", n_barcos1, n_barcos2);
    // fflush(stdin);
    // getchar();
    if (n_barcos1 >= 54332)
        return 2;
    else if (n_barcos2 >= 54332)
        return 1;
    else
        return 0;
}

/* 
 ████  ████  ███ █    █ █████ 
 █   █ █   █  █  ██   █   █   
 ████  ████   █  █ █  █   █   
 █     █   █  █  █  █ █   █   
 █     █   █ ███ █   ██   █   
funciones relacionadas con la impresion en pantalla. */

int mostrar_estadisticas(int jugador)
{
    int n_barcos_propios, n_barcos_enemigos;
    int n_disparos;
    int n_barcos_destruidos = 0;
    int n_barcos_muertos = 0;

    n_barcos_enemigos = (jugador == 1) ? n_barcos2 : n_barcos1;
    n_barcos_propios = (jugador == 1) ? n_barcos1 : n_barcos2;
    n_disparos = (jugador == 1) ? n_disparos1 : n_disparos2;

    n_barcos_destruidos += (n_barcos_enemigos % 10 == 2) ? 1 : 0;
    n_barcos_destruidos += (n_barcos_enemigos % 100 >= 30) ? 1 : 0;
    n_barcos_destruidos += (n_barcos_enemigos % 1000 >= 300) ? 1 : 0;
    n_barcos_destruidos += (n_barcos_enemigos % 10000 >= 4000) ? 1 : 0;
    n_barcos_destruidos += (n_barcos_enemigos >= 50000) ? 1 : 0;

    // printf("%d %d %d %d ", n_barcos_destruidos, n_barcos_muertos, n_barcos_enemigos, n_barcos_propios);
    // printf("%d %d %d %d ",  n_barcos2, n_barcos1, n_barcos_enemigos, n_barcos_propios );

    n_barcos_muertos += n_barcos_propios % 10 == 2 ? 1 : 0;
    n_barcos_muertos += n_barcos_propios % 100 >= 30 ? 1 : 0;
    n_barcos_muertos += n_barcos_propios % 1000 >= 300 ? 1 : 0;
    n_barcos_muertos += n_barcos_propios % 10000 >= 4000 ? 1 : 0;
    n_barcos_muertos += n_barcos_propios >= 50000 ? 1 : 0;
    // printf("ene %d pro %d ", n_barcos_enemigos, n_barcos_propios);

    printf("Haz destruido %d barcos. Te han destruido %d barcos. Haz atacado %d veces. ", n_barcos_destruidos, n_barcos_muertos, n_disparos);
    if (jugador == 1 && ult_celda1[0] != ' ')
        printf("Ultima jugada %s.\n", ult_celda1);
    else if (jugador == 2 && ult_celda1[0] != ' ')
        printf("Ultima jugada %s.\n", ult_celda2);
    else
        printf("\n");
}

int escoger_pais(char *pais)
{
    int num;
    int len;
    char zero = '0';
    printf("Paises:");
    for (int i = 0; i < 23; i++)
    {
        printf("\n%d : %s", i + 1, paises[i]);
        len = ubicar_caracter(paises[i], '\0');
        i++;
        if (i < 23)
        {
            if (i > 9)
                len++;
            for (int j = 0; j < 30 - len; j++)
            {
                printf(" ");
            }
            printf("%d : %s", i + 1, paises[i]);
        }
    }
    printf("\n> Escoja un pais: ");
    num = filtro_scanf(23);
    num = num <= 0 ? 1 : num;
    num--;
    strcpy(pais, paises[num]);

    return 0;
}

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
        if (strstr(tabla[j], "!"))
        {
            printf("_%s|", tabla[j]);
        }
        else
            printf("_%s_|", tabla[j]);
    }
}

/**
 * Imprime dos tableros a partir de dos arrays.
 **/
int mostrar_tableros(char ataque[10][10][5], char flota[10][10][5])
{
    printf("________________________________________________________  ");
    printf("________________________________________________________\n");
    printf("|____|_1__|_2__|_3__|_4__|_5__|_6__|_7__|_8__|_9__|_10_|");
    printf("  |____|_1__|_2__|_3__|_4__|_5__|_6__|_7__|_8__|_9__|_10_|");

    for (int i = 0; i < 10; i++)
    {
        printf("\n");
        mostrar_filas(i, flota[i]);
        printf("  ");
        mostrar_filas(i, ataque[i]);
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
    printf("\n<-------------------------------------------Resolucion minima 120 caracteres---------------------------------------->\n");
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
    fflush(stdin);
    getchar();
}

int pantalla_ganador(int ganador)
{
    if (ganador == 1)
        mostrar_tablero(tablero_ataque1);
    else
        mostrar_tablero(tablero_ataque2);
    //SEPARADOR
    printf("\n----------------------FIN DEL JUEGO---------------------------\n");
    if (numero_de_jugadores == 2)
        printf("\nFelicidades al jugador %d.", ganador);
    else if (ganador == 2)
        printf("\nGano la computadora. Las maquinas somos mejores. MUAJAJAJA.", ganador);
    mostrar_estadisticas(ganador);
    printf("\nDesea guardar un registro de la partida?");
    printf("\nSi (1) No (2)");
    if (filtro_scanf(2) == 1)
    {
        exportar_registro();
    }

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

int coord_int_char(int j, int i, char *coord)
{
    coord[0] = j + 65;
    if (i == 9)
    {
        coord[1] = 1 + '0';
        coord[2] = 0 + '0';
    }
    else
    {
        coord[1] = (i + 1) + '0';
        coord[2] = '\0';
    }
    return 0;
}

int ctoi(char n)
{
    return tolower(n);
}