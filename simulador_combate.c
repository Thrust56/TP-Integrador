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


void calcular_energia(personaje_t *entidad, int accion)
{
    int energia_defensa = entidad->energia + 30;
    int energia_ataque = entidad->energia - 20;
    int energia_curacion = entidad->energia - 15;

    switch (accion)
    {
    case 0: // Entidad se defiende
        if(energia_defensa > entidad->energia_total)
        {
            entidad->energia = entidad->energia_total;
        }
        else
        {
            entidad->energia = energia_defensa;
        }
        break;

    case 1: // Entidad ataca
        entidad->energia = energia_ataque;
        break;

    case 2: // Entidad se cura
        entidad->energia = energia_curacion;
        break;

    default:
        break;
    }
}

void defender(personaje_t *entidad)
{
    if(entidad->se_defendio == 0)
    {
        calcular_energia(entidad, DEFENSA);
        entidad->se_defendio = 1;
        entidad->defensa = entidad->defensa * 2;
    }
}

void atacar(personaje_t *entidad_1, personaje_t *entidad_2)
{
    if(entidad_1->se_defendio == 1)
    {
        entidad_1->defensa = entidad_1->defensa / 2;
        entidad_1->se_defendio = 0;
    }

    calcular_energia(entidad_1, 1);
    entidad_2->vida = entidad_2->vida - (entidad_1->ataque - (entidad_2->defensa/10));
}

void curar(personaje_t *entidad)
{
    if(entidad->se_defendio == 1)
    {
        entidad->defensa = entidad->defensa / 2;
        entidad->se_defendio = 0;
    }

    calcular_energia(entidad, CURACION);
    
    int curacion = entidad->vida + entidad->vida_total * 0.15;

    if(curacion > entidad->vida_total)
    {
        entidad->vida = entidad->vida_total;
    }
    else
    {
        entidad->vida = curacion;
    }
}

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

