#ifndef __SIMULADOR_COMBATE_H__
#define __SIMULADOR_COMBATE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFENSA 0
#define ATAQUE 1
#define CURACION 2

#define PERSONAJE_1 (personaje_t){.nombre = "Astolfo", .ataque = 20, .defensa = 25, .energia = 80, .energia_total = 80, .vida_total = 100, .vida = 100, .se_defendio = 0}
#define PERSONAJE_2 (personaje_t){.nombre = "Ka'or", .ataque = 15, .defensa = 20, .energia = 55, .energia_total = 55, .vida_total = 70, .vida = 70, .se_defendio = 0}
#define PERSONAJE_3 (personaje_t){.nombre = "Lyra", .ataque = 25, .defensa = 15, .energia = 70, .energia_total = 70, .vida_total = 85, .vida = 85, .se_defendio = 0}
#define PERSONAJE_4 (personaje_t){.nombre = "Grom", .ataque = 12, .defensa = 35, .energia = 60, .energia_total = 60, .vida_total = 130, .vida = 130, .se_defendio = 0}
#define PERSONAJE_5 (personaje_t){.nombre = "Sylas", .ataque = 18, .defensa = 18, .energia = 100, .energia_total = 100, .vida_total = 100, .vida = 100, .se_defendio = 0}
#define PERSONAJE_6 (personaje_t){.nombre = "Vex", .ataque = 30, .defensa = 10, .energia = 50, .energia_total = 50, .vida_total = 75, .vida = 75, .se_defendio = 0}

#define DESCRIPCION_ASTOLFO "1 - Astolfo: Un 'Paladin'. Balanceado pero resistente. Buen ataque (20) y defensa (25), con una reserva de vida (100) y energia (80) solida.\n"
#define DESCRIPCION_KAOR "2 - Ka'or: Un 'Mounstruo'. Estadisticas base modestas. Ataque bajo (15) y defensa (20) decentes, pero con poca vida (70) y energia (55).\n"
#define DESCRIPCION_LYRA "3 - Lyra: Una 'Glass Cannon'. Alto ataque (25), pero baja defensa (15) y vida (85).\n"
#define DESCRIPCION_GROM "4 - Grom: Un 'Tanque'. Defensa (35) y vida (130) muy altas, pero con el ataque mas bajo (12).\n"
#define DESCRIPCION_SYLAS "5 - Sylas: Un 'Balanceado' (All-rounder). Todas sus estadisticas estan en un punto medio (18/18) con buena energia y vida.\n"
#define DESCRIPCION_VEX "6 - Vex: Un 'Berserker'. El ataque mas alto (30), pero con la defensa (10) y vida (75) mas bajas.\n"

#define ELIGE_JUGADOR 0
#define ELIGE_IA 1

/*
Representa a un personaje para una simulacion de un videojuego de combate por turnos simple.

La estructura almacena el nombre y los atributos necesarios para que pueda ser
utilizado en todas las funciones de los archivos simulador_combate y simulador_desiciones.

Invariantes:
    - Todas las variables menos nombre y se_defendio deben > 0.
    - vida no puede ser mayor a vida_total.
    - energia no puede ser mayor a energia_total.
    - se_defendio debe mantenerse entre los valores 0 y 1.
*/
typedef struct
{
    char nombre[20];    // Nombre del personaje
    int vida_total;     // Vida total fija
    int vida;           // Vida actual variable
    int energia_total;  // Energía total fija
    int energia;        // Energía actual variable
    int ataque;         // Ataque total fijo
    int defensa;        // Defensa total variable
    int se_defendio;    // Variable para saber si se llamo a la funcion defender()
}personaje_t;

/*
Representa un nodo almacenado en una variable tipo lista_t

Esta estructura ontiene un personaje con sus atributos sin 
inicializar para luego ser asignadas con la funcion crear_nodo().
Tambien contiene un puntero a nodo_t que será enlazado a otra variable tipo nodo_t.

Miembros:
    - personaje: Personaje del simulador de combate.
    - siguiente: Puntero a otra variable nodo_t.

Invariantes:
    - siguiente debe apuntar a otra variable tipo nodo_t o a NULL.
*/
typedef struct nodo
{   
    personaje_t personaje;
    struct nodo *siguiente;
}nodo_t;

/*
Representa una lista de personajes seleccionables para combatir.

Esta estructura almacena un puntero a una variable nodo_t
y una variable contador de cuantas variables tipo nodo_t estan
enlazadas contiguamente.

Miembros:
    - inicio Es un puntero a nodo_t.
    - capacidad Es el contador de variables nodo_t.

Invariantes:
    - inicio debe apuntar a otra variable tipo nodo_t o a NULL.
    - capacidad debe ser >= 0.
*/
typedef struct
{   
    nodo_t *inicio;
    int capacidad;
}lista_t;

/*
Crea un puntero a variable de tipo nodo_t, le reserva memoria con malloc de tamaño nodo_t y almacena en su variable->personaje 
el parametro recibido de tipo personaje_t.

@param personaje_data Variable de tipo personaje_t solo de lectura.
@pre Debe tener todas sus variables inicializadas a un valor conocido y válido
@return Puntero a variable de tipo nodo_t con su variable->personaje inicializada y su variable->siguiente apuntando a NULL
*/
nodo_t *crear_nodo(const personaje_t personaje_data);

/*
Crea un puntero a variable tipo lista_t y reserva memoria con un tamaño de lista_t.

@return Devuelve el puntero a variable tipo lista_t con su variable->inicio apuntando a NULL
y su variable->capacidad inicializada a 0.
*/
lista_t *crear_lista(void);

/*
Crea un puntero a variable tipo lista_t inicializada con la funcion crear_lista(), crea punteros 
a variable tipo nodo_t inicializados con la funcion crear_nodo() y los enlaza entre sí
con la variable->siguiente. La variable lista->inicio estará enlazada a una variable nodo_t.

@return Un puntero a variable tipo lista_t su variable->siguiente apuntando a una de memoria
válida y su variable->capacidad inicializada a un valor conocido y válido.
*/
lista_t *lista_personajes(void);

/*
Recibe un puntero a variable tipo lista_t y libera de su memoria a los nodos
que contenga seguido de la lista.

@param lista Puntero a variable tipo lista_t.
@pre La variable lista no debe apuntar a NULL, sino a una direccion de memoria
que contenga una variable tipo nodo_t válida.
*/
void liberar_lista(lista_t *lista);

/*
Recibe un puntero a personaje_t y inicializa sus variables a un valor
conocido y válido.

@param entidad Puntero a personaje_t a ser inicializado.
@post Devuelve todas sus variables inicializadas a un valor conocido y válido.

@param quien_elije Entero que determina que printf() se va a mostrar.
@pre Debe valer 0 o 1, de lo contrario se frenará la funcion.
*/
void elegir_personajes(personaje_t *entidad, const int quien_elije);

/*
Recibe puntero a personaje_t y modifica su variable->energia segun
la accion realizada.

@param entidad Puntero a personaje_t.
@pre Su variable->energia_total debe ser válida.
@post Su variable->energia aumentará o disminuirá segun corresponda.

@param accion Entero que define la modificacion de la variable->energia del puntero entidad
@pre Debe valer 0, 1 o 2.
*/
void calcular_energia(personaje_t *entidad, const int accion);

/*
Recibe un puntero a personaje_t y modifica su variable->defensa.

@param entidad Puntero a personaje_t.
@pre La variable->defensa de entidad debe estar inicializada a un valor conocido.
@post La variable->defensa de entidad será el doble en caso de que la variable->se_defendio sea 0
@post La variable->energia cambiara su valor en funcion de calcular_energia(entidad, DEFENSA).
@post La variable->se_defendio pasará a valer 1 en caso de que antes valiera 0.
*/
void defender(personaje_t *entidad);

/*
Recibe dos punteros a personaje_t y modifica la variable->vida del segundo
puntero recibido. 

@param entidad_1 Puntero personaje_t del cual se recupera su variable->ataque.
@pre La variable->ataque debe estar inicializada a un valor conocido.
@post Si la variable->se_defendio valia 1, pasa a valer 0.
@post La variable->energia cambiara su valor en funcion de calcular_energia(entidad, ATAQUE).

@param entidad_2 Puntero a personaje_t el cual se modifica su variable->vida.
@pre La variable->vida y ->defensa deben estar inicializadas a un valor conocido.
@post La variable->vida disminuirá segun entidad_1->ataque y entidad_2->defensa/10.
*/
void atacar(personaje_t *entidad_1, personaje_t *entidad_2);

/*
Recibe un puntero a variable tipo personaje_t y modifica su variable->vida.

@param entidad Puntero a personaje_t.
@pre La variable->vida de entidad debe estar inicializada a un valor conocido.
@post La variable->vida de entidad aumentará en funcion de la variable->vida_maxima.
@post La variable->energia cambiara su valor en funcion de calcular_energia(entidad, VIDA).
@post La variable->se_defendio pasará a valer 1 en caso de que antes valiera 0.
*/
void curar(personaje_t *entidad);

/*
Recibe dos punteros personaje_t e imprime sus variables relevantes.

@param entidad_1 Puntero a personaje_t.
@pre Todas sus variables menos ->vida_maxima, ->eneriga_maxima y ->se_defendio
deben estar inizialicadas a un valor conocido.

@param entidad_2 Puntero a personaje_t.
@pre Todas sus variables menos ->vida_maxima, ->eneriga_maxima y ->se_defendio
deben estar inizialicadas a un valor conocido.
*/
void imprimir_estado(const personaje_t *entidad_1, const personaje_t *entidad_2);

/*
Crea un archivo FILE y lo abre para escribir en un archivo de texto. Tambien crea 2
variables personaje_t y llama a la funcion logica_turnos usando como parametro la
direccion de memoria de las 3 variables mencionadas anteriormente.
Una vez que la funcion logica_turnos termina, se cierra el archivo FILE.
*/
void empezar_partida(void);

#endif