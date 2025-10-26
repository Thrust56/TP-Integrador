#ifndef __SIMULADOR_COMBATE_H__
#define __SIMULADOR_COMBATE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[20];
    int vida_total;
    int vida;
    int energia;
    int ataque;
    int defensa;
    int se_defendio;
}personaje_t;

int calcular_energia(personaje_t *entidad, int accion);
int defender(personaje_t *entidad);
int atacar(personaje_t *entidad_1, personaje_t *entidad_2);
int curar(personaje_t *entidad);

void imprimir_estado(personaje_t *entidad_1, personaje_t *entidad_2);

#endif