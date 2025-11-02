#ifndef __SIMULADOR_DESICIONES_H__
#define __SIMULADOR_DESICIONES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simulador_combate.h"

#define ACCION_ATACAR 'a'
#define ACCION_DEFENDER 'd'
#define ACCION_CURAR 'c'
#define VICTORIA_1 1
#define VICTORIA_2 2
#define INICIO_PARTIDA 3
#define TIEMPO 4

#define TURNO_JUGADOR 1
#define TURNO_IA 2
#define VALIDO 0
#define INVALIDO 1

/*
Recibe dos punteros a char que contienen la variable->nombre de una estructura personaje_t. 
Tambien recibe un int que decide que plantilla char se va a usar para imprimirla en consola y
en el puntero a FILE que se recibe como parametro. Reserva memoria en el Heap segun el largo 
de los nombres y la plantilla a utilizar, para luego llamar a la funcion registar_accion(), 
pasarle como parámetro la plantilla completa y el puntero FILE. Luego libera de la memoria 
la plantilla temporal creada.

@param nombre_entidad[in] Variable char nombre de la estructura personaje_t. Es el personaje del usuario.
@pre Debe ser un nombre válido y conocido.

@param nombre_oponente[in] Variable char nombre de la estructura personaje_t, Es la IA del programa.
@pre Debe ser un nombre válido y conocido.

@param accion Entero que determina que plantilla de caracteres se utilizará
@pre Debe estar dentro de los valores válidos: 1, 2, 3, 4, 'a'(97), 'd'(100), 'c'(99).

@param log[out] Puntero a FILE que representa el archivo de texto en el que será registrada la plantilla dinámica.
@pre No debe apuntar a NULL ni tampoco a una direccion de memoria no válida.
@post Se escribirá la plantilla elegida creada dinamicamente en el archivo de texto.
*/
void imprimir_accion(const char *nombre_entidad, const char *nombre_oponente, const int accion, FILE *log);

/*
Recibe dos punteros a personaje_t y decide por orden de prioridad la acción que 
realizará la IA en el combate. Esta accion la registra con la funcion imprimir_accion() 
y le pasa como parámetro, el parámetro recibido puntero a FILE log.

@param IA[in, out] Puntero a personaje_t. Representa la IA y es la que toma la accion.
@pre Debe tener valores válidos y conocidos.
@post Su variable->energía/defensa se modificará según la accion realizada.

@param jugador[out] Puntero a personaje_t. Representa al jugador/usuario.
@pre Debe tener valores válidos y conocidos.
@post Se modificará su variable->vida en caso de que la accion de la IA sea atacar.

@param log[out] Puntero a FILE que representa el archivo de texto en el que será registrada la accion.
@pre No debe apuntar a NULL ni tampoco a una direccion de memoria no válida.
@post Se escribirá la accion realizada en el archivo de texto.
*/
void decidir_accion(personaje_t *IA, personaje_t *jugador, FILE *log);

/*
Recibe dos punteros a personaje_t los cuales sus serán constantemente modificadas según las acciones
realizadas. Mientras las variables->vida de jugador y IA sean > 0 la funcion permanecerá en un bucle
en el cual se tomarán acciones por turnos manualmente por el usuario y automaticamente por la IA.
Las acciones realizadas se escribirán en el archivo de texto apuntado por el puntero a FILE log.
Cuando el bucle termine, se escribirá el resultado en el archivo de texto.

@param jugador[in, out] Puntero a personaje_t. Representa al jugador/usuario.
@pre Debe tener valores válidos y conocidos.
@post Se modificará su variable->vida en caso de que la accion de la IA sea atacar.

@param IA[in, out] Puntero a personaje_t. Representa la IA y es la que toma la accion.
@pre Debe tener valores válidos y conocidos.
@post Su variable->energía/defensa se modificará según la accion realizada.

@param log[out] Puntero a FILE que representa el archivo de texto en el que serán registradas las acciones.
@pre No debe apuntar a NULL ni tampoco a una direccion de memoria no válida.
@post Se escribirán las acciones realizadas en el archivo de texto.
*/
void logica_turnos(personaje_t *jugador, personaje_t *IA, FILE *log);

/*
Recibe un puntero a FILE el cual tiene abierto un archivo de texto, en el cual
se escribirá la cadena de texto que contenga accion[].

@param log[out] Puntero a FILE que representa el archivo de texto en el que serán registradas las acciones.
@pre No debe apuntar a NULL ni tampoco a una direccion de memoria no válida.
@post Se escribirán las acciones realizadas en el archivo de texto.

@param accion[in] Cadena de texto constante que se registrará en el log.
@pre Debe tener una cadena de texto válida
*/
void registrar_historial(FILE *log, const char accion[]);

#endif