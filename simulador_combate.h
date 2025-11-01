#ifndef __SIMULADOR_COMBATE_H__
#define __SIMULADOR_COMBATE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFENSA 0
#define ATAQUE 1
#define CURACION 2

#define PERSONAJE_1 {.nombre = "Astolfo", .ataque = 20, .defensa = 25, .energia = 80, .energia_total = 80, .vida_total = 100, .vida = 100}
#define PERSONAJE_2 {.nombre = "Ka'or", .ataque = 15, .defensa = 20, .energia = 55, .energia_total = 55, .vida_total = 70, .vida = 70}
#define PERSONAJE_3 {.nombre = "Ka'or", .ataque = 15, .defensa = 20, .energia = 55, .energia_total = 55, .vida_total = 70, .vida = 70}
#define PERSONAJE_4 {.nombre = "Ka'or", .ataque = 15, .defensa = 20, .energia = 55, .energia_total = 55, .vida_total = 70, .vida = 70}
#define PERSONAJE_5 {.nombre = "Ka'or", .ataque = 15, .defensa = 20, .energia = 55, .energia_total = 55, .vida_total = 70, .vida = 70}
#define PERSONAJE_6 {.nombre = "Ka'or", .ataque = 15, .defensa = 20, .energia = 55, .energia_total = 55, .vida_total = 70, .vida = 70}

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

typedef struct
{   
    personaje_t personaje;
    nodo_t *siguiente;
}nodo_t;

typedef struct
{   
    nodo_t *inicio;
    size_t capacidad;
}lista_t;

void calcular_energia(personaje_t *entidad, int accion);
void defender(personaje_t *entidad);
void atacar(personaje_t *entidad_1, personaje_t *entidad_2);
void curar(personaje_t *entidad);
void imprimir_estado(personaje_t *entidad_1, personaje_t *entidad_2);
void elegir_personajes(personaje_t *entidad_1, personaje_t *entidad_2);

lista_t *crear_lista(void);
lista_t *lista_personajes(void);

#endif