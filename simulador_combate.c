#include "simulador_combate.h"
#include "simulador_desiciones.c"

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
int calcular_energia(int energia, int accion)
{
    int energia_final = 0;

    switch (accion)
    {
    case 0: // Entidad se defiende
        energia_final = energia = energia + 30;
        break;

    case 1: // Entidad ataca
        energia_final = energia = energia - 20;
        break;

    case 2: // Entidad se cura
        energia_final = energia = energia - 15;
        break;
    default:
        break;
    }

    return energia_final;
}

/*

*/
int defender(personaje_t entidad)
{
    #define DEFENSA 0
    entidad.energia = calcular_energia(entidad.energia, DEFENSA);
    entidad.se_defendio = 1;
    return entidad.defensa * 2;
}

/*

*/
int atacar(personaje_t entidad_1, personaje_t entidad_2)
{
    #define ATAQUE 1

    if(entidad_1.se_defendio == ATAQUE)
    {
        entidad_1.defensa = entidad_1.defensa / 2;
        entidad_1.se_defendio = 0;
    }

    entidad_1.energia = calcular_energia(entidad_1.energia, 1);
    entidad_2.vida = entidad_2.vida - (entidad_1.ataque - (entidad_2.defensa/10));

    return entidad_2.vida;
}

/*

*/
int curar(personaje_t entidad)
{
    #define CURACION 2

    if(entidad.se_defendio == 1)
    {
        entidad.defensa = entidad.defensa / 2;
        entidad.se_defendio = 0;
    }

    entidad.energia = calcular_energia(entidad.energia, CURACION);

    return entidad.vida + entidad.vida_total * 0.15;
}

/*

*/
void imprimir_estado(personaje_t entidad_1, personaje_t entidad_2)
{
    printf("\n");

    printf("\t\t--%s--\n", entidad_1.nombre);
    printf("\tVida: %d\n", entidad_1.vida);
    printf("\tAtaque: %d\n", entidad_1.ataque);
    printf("\tDefensa: %d\n", entidad_1.defensa);
    printf("\tEnergia: %d\n", entidad_1.energia);

    printf("\n");

    printf("\t\t--%s--\n", entidad_2.nombre);
    printf("\tVida: %d\n", entidad_2.vida);
    printf("\tAtaque: %d\n", entidad_2.ataque);
    printf("\tDefensa: %d\n", entidad_2.defensa);
    printf("\tEnergia: %d\n", entidad_2.energia);

    printf("\n");
}

void logica_turnos(personaje_t entidad_1, personaje_t entidad_2)
{
    #define TURNO_ENTIDAD_1 1
    #define TURNO_ENTIDAD_2 2
    #define ASCII_a 97
    #define ASCII_c 99
    #define ASCII_d 100
    #define VALIDO 0
    #define INVALIDO 1

    int turno = TURNO_ENTIDAD_1;

    while(entidad_1.vida > 0 || entidad_2.vida > 0)
    {
        char buffer[2];
        int desicion = 0;
        int validacion = INVALIDO;

        if(turno == TURNO_ENTIDAD_1)
        {
            printf("Turno de %s\n", entidad_1.nombre);
            imprimir_estado(entidad_1, entidad_2);

            while(validacion == INVALIDO)
            {
                printf("Elija una de las siguientes acciones:\n");
                printf("Atacar: 'a'  --  Defender: 'd'  --  Curar: 'c'\n");
                desicion = atoi(fgets(buffer, 2, stdin));

                switch (desicion)
                {
                case ASCII_a:
                    entidad_2.vida = atacar(entidad_1, entidad_2);
                    validacion = VALIDO;
                    break;

                case ASCII_d:
                    entidad_1.defensa = defender(entidad_1);
                    validacion = VALIDO;
                    break;
                
                case ASCII_c:
                    entidad_1.vida = curar(entidad_1);
                    validacion = VALIDO;
                    break;
                
                default:
                    printf("Accion invalida\n");
                    break;
                }
            }
            turno = TURNO_ENTIDAD_2;
        }

        else if(turno == TURNO_ENTIDAD_2)
        {
            printf("Turno de %s\n", entidad_1.nombre);
            imprimir_estado(entidad_1, entidad_2);

            decidir_accion(entidad_2, entidad_1);
            turno = TURNO_ENTIDAD_1;
        }
    }
}