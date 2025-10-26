#include "simulador_combate.h"
#include "simulador_desiciones.h"

/*
Objetivo: Combate por turnos entre jugador y enemigo. 
Requisitos: 
● Personajes con atributos: vida, energía, ataque, defensa. 
● Funciones: atacar, defender, curarse. 
● Enemigo con modo inteligente: decide acción según reglas simples: 
○ Vida baja → curar 
○ Energía baja → defender 
○ Jugador débil → atacar 
● Registrar historial de turnos. 
● Modularización: main, combate, decisiones. 
● Validación de entradas y estados de personajes. 
*/


/*

*/
int calcular_energia(personaje_t *entidad, int accion)
{
    int energia_final = 0;

    switch (accion)
    {
    case 0: // Entidad se defiende
        energia_final = entidad->energia = entidad->energia + 30;
        break;

    case 1: // Entidad ataca
        energia_final = entidad->energia = entidad->energia - 20;
        break;

    case 2: // Entidad se cura
        energia_final = entidad->energia = entidad->energia - 15;
        break;
    default:
        break;
    }

    return energia_final;
}

/*

*/
int defender(personaje_t *entidad)
{
    #define DEFENSA 0
    (entidad->energia) = calcular_energia(entidad->energia, DEFENSA);
    (entidad->se_defendio) = 1;
    return entidad->defensa * 2;
}

/*

*/
int atacar(personaje_t *entidad_1, personaje_t *entidad_2)
{
    #define ATAQUE 1

    if(entidad_1->se_defendio == ATAQUE)
    {
        entidad_1->defensa = entidad_1->defensa / 2;
        entidad_1->se_defendio = 0;
    }

    entidad_1->energia = calcular_energia(entidad_1->energia, 1);
    entidad_2->vida = entidad_2->vida - (entidad_1->ataque - (entidad_2->defensa/10));

    return entidad_2->vida;
}

/*

*/
int curar(personaje_t *entidad)
{
    #define CURACION 2

    if(entidad->se_defendio == 1)
    {
        entidad->defensa = entidad->defensa / 2;
        entidad->se_defendio = 0;
    }

    entidad->energia = calcular_energia(entidad->energia, CURACION);

    return (entidad->vida) + (entidad->vida_total) * 0.15;
}

/*

*/
void imprimir_estado(personaje_t *entidad_1, personaje_t *entidad_2)
{
    printf("\n");

    printf("\t\t--%s--\n", entidad_1->nombre);
    printf("\tVida: %d\n", entidad_1->vida);
    printf("\tAtaque: %d\n", entidad_1->ataque);
    printf("\tDefensa: %d\n", entidad_1->defensa);
    printf("\tEnergia: %d\n", entidad_1->energia);

    printf("\n");

    printf("\t\t--%s--\n", entidad_2->nombre);
    printf("\tVida: %d\n", entidad_2->vida);
    printf("\tAtaque: %d\n", entidad_2->ataque);
    printf("\tDefensa: %d\n", entidad_2->defensa);
    printf("\tEnergia: %d\n", entidad_2->energia);

    printf("\n");
}

