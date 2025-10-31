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

#define TURNO_ENTIDAD_1 1
#define TURNO_ENTIDAD_2 2
#define VALIDO 0
#define INVALIDO 1

void decidir_accion(personaje_t *entidad, personaje_t *oponente, FILE *log);
void imprimir_accion(personaje_t *entidad, personaje_t *oponente, int accion, FILE *log);
void logica_turnos(personaje_t *entidad_1, personaje_t *entidad_2, FILE *log);
void registrar_historial(FILE *log, char accion[]);

#endif