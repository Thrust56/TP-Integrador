#include "simulador_combate.h"
#include "simulador_desiciones.h"

nodo_t *crear_nodo(personaje_t personaje_data)
{
    nodo_t *nuevo_nodo = (nodo_t *)malloc(sizeof(nodo_t));
    if (nuevo_nodo == NULL)
    {
        printf("Error: No se pudo crear un nodo para la creacion del personaje\n");
    }
    
    nuevo_nodo->personaje = personaje_data;
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}

lista_t *crear_lista(void)
{
    lista_t *lista = NULL;
    
    lista = malloc(sizeof(lista_t));
    
    if (lista == NULL)
    {
        return NULL;
    }
    
    lista->inicio = NULL;
    lista->capacidad = 0;
    
    return lista;
}

lista_t *lista_personajes(void)
{
    lista_t *lista = crear_lista();

    nodo_t *personaje_1 = crear_nodo(PERSONAJE_1);
    nodo_t *personaje_2 = crear_nodo(PERSONAJE_2);
    nodo_t *personaje_3 = crear_nodo(PERSONAJE_3);
    nodo_t *personaje_4 = crear_nodo(PERSONAJE_4);
    nodo_t *personaje_5 = crear_nodo(PERSONAJE_5);
    nodo_t *personaje_6 = crear_nodo(PERSONAJE_6);
    
    lista->inicio = personaje_1;
    personaje_1->siguiente = personaje_2;
    personaje_2->siguiente = personaje_3;
    personaje_3->siguiente = personaje_4;
    personaje_4->siguiente = personaje_5;
    personaje_5->siguiente = personaje_6;

    lista->capacidad = 6;

    return lista;
}

void liberar_lista(lista_t *lista)
{
    if (lista != NULL)
    {
        nodo_t *actual = lista->inicio;
        nodo_t *siguiente;
        
        while (actual != NULL) {
            siguiente = actual->siguiente;
            free(actual); // Libera el nodo
            actual = siguiente;
        }
        
        free(lista); // Libera la estructura de la lista
    }
}

void elegir_personajes(personaje_t *entidad, int quien_elije)
{
    lista_t *personajes_disponibles = lista_personajes();
    if (personajes_disponibles == NULL)
    {
        printf("Error: No se pudo crear la lista de personajes.\n");
    }

    nodo_t *apuntador = personajes_disponibles->inicio;
    int cant_personajes = personajes_disponibles->capacidad;
    
    int eleccion = 0;
    char buffer[10];
    int validacion = INVALIDO;

    while(validacion == INVALIDO)
    {
        switch (quien_elije)
        {
        case ELIGE_JUGADOR:
            printf("Que personaje vas a seleccionar?\n");
            printf(DESCRIPCION_ASTOLFO);
            printf(DESCRIPCION_KAOR);
            printf(DESCRIPCION_LYRA);
            printf(DESCRIPCION_GROM);
            printf(DESCRIPCION_SYLAS);
            printf(DESCRIPCION_VEX);
            break;
        
        case ELIGE_IA:
            printf("Contra que personaje vas a combatir?\n");
            printf(DESCRIPCION_ASTOLFO);
            printf(DESCRIPCION_KAOR);
            printf(DESCRIPCION_LYRA);
            printf(DESCRIPCION_GROM);
            printf(DESCRIPCION_SYLAS);
            printf(DESCRIPCION_VEX);
            break;
        
        default:
            break;
        }

        fgets(buffer, sizeof(buffer), stdin);
        eleccion = atoi(buffer);

        if(eleccion > cant_personajes)
        {
            printf("\nError: Ingrese un personaje valido (1-%d).\n", cant_personajes);
        }

        else if(eleccion < 1)
        {
            printf("\nError: No ingrese caracteres, numeros negativos o 0.\n");
        }

        else
        {
            for(int i = 0; i < eleccion - 1; i++)
            {
                apuntador = apuntador->siguiente;
            }
            *entidad = apuntador->personaje;

            validacion = VALIDO;
        }
    }
    liberar_lista(personajes_disponibles);
}

void calcular_energia(personaje_t *entidad, int accion)
{
    int energia_defensa = entidad->energia + 30;
    int energia_ataque = entidad->energia - 20;
    int energia_curacion = entidad->energia - 15;

    switch (accion)
    {
    case DEFENSA:
        if(energia_defensa > entidad->energia_total)
        {
            entidad->energia = entidad->energia_total;
        }
        else
        {
            entidad->energia = energia_defensa;
        }
        break;

    case ATAQUE:
        entidad->energia = energia_ataque;
        break;

    case CURACION:
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

    calcular_energia(entidad_1, ATAQUE);
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

void empezar_partida()
{
    FILE *log = NULL;

    personaje_t jugador;
    personaje_t enemigo;

    logica_turnos(&jugador, &enemigo, log);
}