#include "simulador_desiciones.h"
#include "simulador_combate.h"

void imprimir_accion(const char *nombre_entidad, const char *nombre_oponente, const int accion, FILE *log)
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
            tamano_necesario = snprintf(NULL, 0, plantilla_atacar, nombre_entidad, nombre_oponente);
            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion != NULL) {
                sprintf(reservar_accion, plantilla_atacar, nombre_entidad, nombre_oponente);
            }
            break;

        case ACCION_DEFENDER:
            tamano_necesario = snprintf(NULL, 0, plantilla_defender, nombre_entidad);
            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion != NULL) {
                sprintf(reservar_accion, plantilla_defender, nombre_entidad);
            }
            break;
        
        case ACCION_CURAR:
            tamano_necesario = snprintf(NULL, 0, plantilla_curar, nombre_entidad);
            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion != NULL) {
                sprintf(reservar_accion, plantilla_curar, nombre_entidad);
            }
            break;
        
        case VICTORIA_1:
            tamano_necesario = snprintf(NULL, 0, plantilla_victoria1, nombre_entidad, nombre_oponente);
            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion != NULL) {
                sprintf(reservar_accion, plantilla_victoria1, nombre_entidad, nombre_oponente);
            }
            break;
        
        case VICTORIA_2:
            tamano_necesario = snprintf(NULL, 0, plantilla_victoria2, nombre_entidad, nombre_oponente);
            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion != NULL) {
                sprintf(reservar_accion, plantilla_victoria2, nombre_entidad, nombre_oponente);
            }
            break;
        
        case INICIO_PARTIDA:
            tamano_necesario = snprintf(NULL, 0, plantilla_separador);
            reservar_accion = (char *)malloc(tamano_necesario + 1);
            if(reservar_accion != NULL) {
                sprintf(reservar_accion, plantilla_separador);
            }
            break;

        case TIEMPO:
            tamano_necesario = 100;
            reservar_accion = (char *)malloc(tamano_necesario);
            if(reservar_accion != NULL) {
                time_t tiempo = time(NULL);
                struct tm *tiempo_local = localtime(&tiempo);
                strftime(reservar_accion, tamano_necesario, plantilla_tiempo, tiempo_local);
            }
            break;
        
        default:
            break;
    }

    if(reservar_accion != NULL)
    {
        printf("%s\n", reservar_accion);
        registrar_historial(log, reservar_accion);

        free(reservar_accion);
        reservar_accion = NULL;
    }
    else
    {
        printf("Error al generar la accion %d\n", accion);
    }
}

void decidir_accion(personaje_t *IA, personaje_t *jugador, FILE *log)
{
    if(IA->energia < 15)
    {
        defender(IA);
        imprimir_accion(IA->nombre, NULL, ACCION_DEFENDER, log);
    }
    else if(IA->vida < IA->vida_total * 0.35)
    {
        curar(IA);
        imprimir_accion(IA->nombre, NULL, ACCION_CURAR, log);
    }
    else if(IA->energia >= 20)
    {
        atacar(IA, jugador);
        imprimir_accion(IA->nombre, jugador->nombre, ACCION_ATACAR, log);
    }
    else
    {
        defender(IA);
        imprimir_accion(IA->nombre, NULL, ACCION_DEFENDER, log);
    }
}

void logica_turnos(personaje_t *jugador, personaje_t *IA, FILE *log)
{
    int inicio_partida = 0;

    if(inicio_partida == 0)
    {

        elegir_personajes(jugador, ELIGE_JUGADOR);
        elegir_personajes(IA, ELIGE_IA);
        
        imprimir_accion(NULL, NULL, TIEMPO, log);
        imprimir_accion(NULL, NULL, INICIO_PARTIDA, log);
        inicio_partida = 1;
    }

    int turno = TURNO_JUGADOR;

    while(jugador->vida > 0 && IA->vida > 0)
    {
        char buffer[3];
        int validacion = INVALIDO;

        if(turno == TURNO_JUGADOR)
        {
            printf("\nTurno de %s\n", jugador->nombre);
            imprimir_estado(jugador, IA);

            while(validacion == INVALIDO)
            {
                printf("Cual sera tu proximo movimiento?\n");
                printf("Atacar: 'a'  --  Defender: 'd'  --  Curar: 'c'\n");
                fgets(buffer, 3, stdin);
                //printf("\n----%d----\n", desicion);

                switch (buffer[0])
                {
                case ACCION_ATACAR:
                    if(jugador->energia < 20)
                    {
                        printf("No tienes suficiente energia!\n");
                    }
                    else
                    {
                        atacar(jugador, IA);
                        imprimir_accion(jugador->nombre, IA->nombre, ACCION_ATACAR, log);
                        validacion = VALIDO;
                    }
                    break;

                case ACCION_DEFENDER:
                    defender(jugador);
                    imprimir_accion(jugador->nombre, NULL, ACCION_DEFENDER, log);
                    validacion = VALIDO;
                    break;
                
                case ACCION_CURAR:
                    if(jugador->energia < 15)
                    {
                        printf("No tienes suficiente energia!\n");
                    }
                    else
                    {
                        curar(jugador);
                        imprimir_accion(jugador->nombre, NULL, ACCION_CURAR, log);
                        validacion = VALIDO;
                    }
                    break;
                
                default:
                    printf("Elije un movimiento valido\n");
                    break;
                }
            }
            turno = TURNO_IA;
        }

        else if(turno == TURNO_IA)
        {
            printf("\nTurno de %s\n", IA->nombre);
            imprimir_estado(jugador, IA);

            decidir_accion(IA, jugador, log);
            turno = TURNO_JUGADOR;
        }
    }

    if(IA->vida <= 0)
    {
        imprimir_accion(jugador->nombre, IA->nombre, VICTORIA_1, log);
        imprimir_accion(NULL, NULL, INICIO_PARTIDA, log);
    }
    else
    {
        imprimir_accion(IA->nombre, jugador->nombre, VICTORIA_2, log);
        imprimir_accion(NULL, NULL, INICIO_PARTIDA, log);
    }

}

/*
Recibe un puntero a FILE el cual tiene abierto un archivo de texto, en el cual
se escribirá la cadena de texto que contenga accion[].

@param log[out] Puntero a FILE que representa el archivo de texto en el que serán registradas las acciones.
@pre No debe apuntar a NULL ni tampoco a una direccion de memoria no válida.
@post Se escribirán las acciones realizadas en el archivo de texto.

@param accion[in] Cadena de texto constante que se registrará en el log.
@pre Debe tener una cadena de texto válida

*/
void registrar_historial(FILE *log, const char accion[])
{
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

        fflush(log);
    }
}