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

typedef struct nodo
{   
    personaje_t personaje;
    struct nodo *siguiente;
}nodo_t;

typedef struct
{   
    nodo_t *inicio;
    int capacidad;
}lista_t;

void calcular_energia(personaje_t *entidad, int accion);
void defender(personaje_t *entidad);
void atacar(personaje_t *entidad_1, personaje_t *entidad_2);
void curar(personaje_t *entidad);
void imprimir_estado(personaje_t *entidad_1, personaje_t *entidad_2);
void elegir_personajes(personaje_t *entidad, int quien_elije);
void empezar_partida(void);

lista_t *crear_lista(void);
lista_t *lista_personajes(void);

nodo_t *crear_nodo(personaje_t personaje_data);

#endif