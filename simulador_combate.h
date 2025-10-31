#ifndef __SIMULADOR_COMBATE_H__
#define __SIMULADOR_COMBATE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFENSA 0
#define ATAQUE 1
#define CURACION 2

typedef struct
{
    char nombre[20];
    int vida_total;
    int vida;
    int energia_total;
    int energia;
    int ataque;
    int defensa;
    int se_defendio;
}personaje_t;

void calcular_energia(personaje_t *entidad, int accion);
void defender(personaje_t *entidad);
void atacar(personaje_t *entidad_1, personaje_t *entidad_2);
void curar(personaje_t *entidad);

void imprimir_estado(personaje_t *entidad_1, personaje_t *entidad_2);

#endif