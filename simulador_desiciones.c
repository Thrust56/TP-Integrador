#include "simulador_desiciones.h"
#include "simulador_combate.h"

/*

*/
void decidir_accion(personaje_t *entidad, personaje_t *oponente)
{
    if(entidad->energia < 15)
    {
        defender(entidad);
        printf("\n%s se defendio, su defensa aumento el doble por un turno\n", entidad->nombre);
    }
    else if(entidad->vida < entidad->vida_total * 0.35)
    {
        curar(entidad);
        printf("\n%s se aplico curacion\n", entidad->nombre);
    }
    else if(entidad->energia >= 20)
    {
        atacar(entidad, oponente);
        printf("\n%s ataco a %s\n", entidad->nombre, oponente->nombre);
    }
}

void logica_turnos(personaje_t *entidad_1, personaje_t *entidad_2)
{
    #define TURNO_ENTIDAD_1 1
    #define TURNO_ENTIDAD_2 2
    #define ACCION_ATACAR 'a'
    #define ACCION_DEFENDER 'd'
    #define ACCION_CURAR 'c'
    #define VALIDO 0
    #define INVALIDO 1

    int turno = TURNO_ENTIDAD_1;

    while(entidad_1->vida > 0 && entidad_2->vida > 0)
    {
        char buffer[5];
        int desicion = 0;
        int validacion = INVALIDO;

        if(turno == TURNO_ENTIDAD_1)
        {
            printf("\nTurno de %s\n", entidad_1->nombre);
            imprimir_estado(entidad_1, entidad_2);

            while(validacion == INVALIDO)
            {
                printf("Cual sera tu proximo movimiento?\n");
                printf("Atacar: 'a'  --  Defender: 'd'  --  Curar: 'c'\n");
                atoi(fgets(buffer, 5, stdin));
                desicion = buffer[0];
                //printf("\n----%d----\n", desicion);

                switch (desicion)
                {
                case ACCION_ATACAR:
                    if(entidad_1->energia < 20)
                    {
                        printf("No tienes suficiente energia!\n");
                    }
                    else
                    {
                        atacar(entidad_1, entidad_2);
                        printf("\n%s ataco a %s\n", entidad_1->nombre, entidad_2->nombre);
                        validacion = VALIDO;
                    }
                    break;

                case ACCION_DEFENDER:
                    defender(entidad_1);
                    printf("\n%s se defendio, su defensa aumento el doble por un turno\n", entidad_1->nombre);
                    validacion = VALIDO;
                    break;
                
                case ACCION_CURAR:
                    if(entidad_1->energia < 15)
                    {
                        printf("No tienes suficiente energia!\n");
                    }
                    else
                    {
                        curar(entidad_1);
                        printf("\n%s se aplico curacion\n", entidad_1->nombre);
                        validacion = VALIDO;
                    }
                    break;
                
                default:
                    printf("Elije un movimiento valido\n");
                    break;
                }
            }
            turno = TURNO_ENTIDAD_2;
        }

        else if(turno == TURNO_ENTIDAD_2)
        {
            printf("\nTurno de %s\n", entidad_2->nombre);
            imprimir_estado(entidad_1, entidad_2);

            decidir_accion(entidad_2, entidad_1);
            turno = TURNO_ENTIDAD_1;
        }
    }

    if(entidad_2->vida <= 0)
    {
        printf("\n%s ha caido en manos de %s!", entidad_2->nombre, entidad_1->nombre);
    }
    else
    {
        printf("\n%s ha sido asesinado por %s!", entidad_1->nombre, entidad_2->nombre);
    }

}