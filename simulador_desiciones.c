#include "simulador_desiciones.h"
#include "simulador_combate.h"

/*

*/
void decidir_accion(personaje_t entidad, personaje_t oponente)
{
    if(entidad.energia < 15)
    {
        entidad.defensa = defender(entidad);
    }
    else if(entidad.vida < entidad.vida_total * 0.35)
    {
        entidad.vida = curar(entidad);
    }
    else
    {
        oponente.vida = atacar(entidad, oponente);
    }
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