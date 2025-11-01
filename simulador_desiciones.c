#include "simulador_desiciones.h"
#include "simulador_combate.h"

void imprimir_accion(personaje_t *entidad, personaje_t *oponente, int accion, FILE *log)
{
    const char *plantilla_atacar = "\n%s ataco a %s";
    const char *plantilla_defender = "\n%s se defendio, su defensa aumento el doble por un turno";
    const char *plantilla_curar = "\n%s se aplico curacion";
    const char *plantilla_victoria1 = "\n%s ha caido en manos de %s!";
    const char *plantilla_victoria2 = "\n%s ha sido asesinado por %s!";
    const char *plantilla_separador = "\n-------------------------------\n";
    const char *plantilla_tiempo = "\n\nFecha de la partida: %Y-%m-%d %H:%M:%S\n";

    char *reservar_accion = NULL;
    int tamano_necesario = 0;

    switch (accion)
    {
        case ACCION_ATACAR:
            tamano_necesario = snprintf(NULL, 0, plantilla_atacar, entidad->nombre, oponente->nombre);

            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion == NULL)
            {
                printf("Error al reservar memoria\n");
            }
            else
            {
                sprintf(reservar_accion, plantilla_atacar, entidad->nombre, oponente->nombre);
            }
            break;

        case ACCION_DEFENDER:
            tamano_necesario = snprintf(NULL, 0, plantilla_defender, entidad->nombre);

            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion == NULL)
            {
                printf("Error al reservar memoria\n");
            }
            else
            {
                sprintf(reservar_accion, plantilla_defender, entidad->nombre);
            }
            break;
        
        case ACCION_CURAR:
            tamano_necesario = snprintf(NULL, 0, plantilla_curar, entidad->nombre);

            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion == NULL)
            {
                printf("Error al reservar memoria\n");
            }
            else
            {
                sprintf(reservar_accion, plantilla_curar, entidad->nombre);
            }
            break;
        
        case VICTORIA_1:
            tamano_necesario = snprintf(NULL, 0, plantilla_victoria1, entidad->nombre, oponente->nombre);

            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion == NULL)
            {
                printf("Error al reservar memoria\n");
            }
            else
            {
                sprintf(reservar_accion, plantilla_victoria1, entidad->nombre, oponente->nombre);
            }
            break;
        
        case VICTORIA_2:
            tamano_necesario = snprintf(NULL, 0, plantilla_victoria2, entidad->nombre, oponente->nombre);

            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion == NULL)
            {
                printf("Error al reservar memoria\n");
            }
            else
            {
                sprintf(reservar_accion, plantilla_victoria2, entidad->nombre, oponente->nombre);
            }
            break;
        
        case INICIO_PARTIDA:
            tamano_necesario = snprintf(NULL, 0, plantilla_separador);

            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion == NULL)
            {
                printf("Error al reservar memoria\n");
            }
            else
            {
                sprintf(reservar_accion, plantilla_separador);
            }
            break;

        case TIEMPO:
            tamano_necesario = 100;
            reservar_accion = (char *)malloc(tamano_necesario);

            if(reservar_accion == NULL)
            {
                printf("Error al reservar memoria\n");
            }
            else
            {
                time_t tiempo = time(NULL);
                struct tm *tiempo_local = localtime(&tiempo);

                strftime(reservar_accion, tamano_necesario, plantilla_tiempo, tiempo_local);
            }
            break;
        
        default:
            break;
    }

    printf("%s\n", reservar_accion);
    registrar_historial(log, reservar_accion);

    free(reservar_accion);
    reservar_accion = NULL;
}

void decidir_accion(personaje_t *entidad, personaje_t *oponente, FILE *log)
{
    if(entidad->energia < 15)
    {
        defender(entidad);
        imprimir_accion(entidad, oponente, ACCION_DEFENDER, log);
    }
    else if(entidad->vida < entidad->vida_total * 0.35)
    {
        curar(entidad);
        imprimir_accion(entidad, oponente, ACCION_CURAR, log);
    }
    else if(entidad->energia >= 20)
    {
        atacar(entidad, oponente);
        imprimir_accion(entidad, oponente, ACCION_ATACAR, log);
    }
    else
    {
        defender(entidad);
        imprimir_accion(entidad, oponente, ACCION_DEFENDER, log);
    }
}

void logica_turnos(personaje_t *entidad_1, personaje_t *entidad_2, FILE *log)
{
    int inicio_partida = 0;

    if(inicio_partida == 0)
    {

        elegir_personajes(entidad_1, ELIGE_JUGADOR);
        elegir_personajes(entidad_2, ELIGE_IA);
        
        imprimir_accion(NULL, NULL, TIEMPO, log);
        imprimir_accion(NULL, NULL, INICIO_PARTIDA, log);
        inicio_partida = 1;
    }

    int turno = TURNO_ENTIDAD_1;

    while(entidad_1->vida > 0 && entidad_2->vida > 0)
    {
        char buffer[3];
        int validacion = INVALIDO;

        if(turno == TURNO_ENTIDAD_1)
        {
            printf("\nTurno de %s\n", entidad_1->nombre);
            imprimir_estado(entidad_1, entidad_2);

            while(validacion == INVALIDO)
            {
                printf("Cual sera tu proximo movimiento?\n");
                printf("Atacar: 'a'  --  Defender: 'd'  --  Curar: 'c'\n");
                fgets(buffer, 3, stdin);
                //printf("\n----%d----\n", desicion);

                switch (buffer[0])
                {
                case ACCION_ATACAR:
                    if(entidad_1->energia < 20)
                    {
                        printf("No tienes suficiente energia!\n");
                    }
                    else
                    {
                        atacar(entidad_1, entidad_2);
                        imprimir_accion(entidad_1, entidad_2, ACCION_ATACAR, log);
                        validacion = VALIDO;
                    }
                    break;

                case ACCION_DEFENDER:
                    defender(entidad_1);
                    imprimir_accion(entidad_1, entidad_2, ACCION_DEFENDER, log);
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
                        imprimir_accion(entidad_1, entidad_2, ACCION_CURAR, log);
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

            decidir_accion(entidad_2, entidad_1, log);
            turno = TURNO_ENTIDAD_1;
        }
    }

    if(entidad_2->vida <= 0)
    {
        imprimir_accion(entidad_1, entidad_2, VICTORIA_1, log);
        imprimir_accion(NULL, NULL, INICIO_PARTIDA, log);
    }
    else
    {
        imprimir_accion(entidad_2, entidad_1, VICTORIA_2, log);
        imprimir_accion(NULL, NULL, INICIO_PARTIDA, log);
    }

}

void registrar_historial(FILE *log, char accion[])
{
    log = fopen("log.txt", "a");

    if(log == NULL)
    {
        perror("\nError al acceder al log\n");
    }
    else
    {
        if(fputs(accion, log) == EOF)
        {
            perror("\nError al escribir en el log\n");
        }
        fclose(log);
    }
}