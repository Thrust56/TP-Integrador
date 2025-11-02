#include "simulador_combate.h"
#include "simulador_desiciones.h"

/*
Crea un puntero a variable de tipo nodo_t, le reserva memoria con malloc de tamaño nodo_t y almacena en su variable->personaje 
el parametro recibido de tipo personaje_t. 
@param personaje_data Variable de tipo personaje_t solo de lectura.
@pre Debe tener todas sus variables inicializadas a un valor conocido y válido
@return Puntero a variable de tipo nodo_t con su variable->personaje inicializada y su variable->siguiente apuntando a NULL
*/
nodo_t *crear_nodo(const personaje_t personaje_data)
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

/*
Crea un puntero a variable tipo lista_t y reserva memoria con un tamaño de lista_t.
@return Devuelve el puntero a variable tipo lista_t con su variable->inicio apuntando a NULL
y su variable->capacidad inicializada a 0.
*/
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

/*
Crea un puntero a variable tipo lista_t inicializada con la funcion crear_lista(), crea punteros 
a variable tipo nodo_t inicializados con la funcion crear_nodo() y los enlaza entre sí
con la variable->siguiente. La variable lista->inicio estará enlazada a una variable nodo_t.
@return Un puntero a variable tipo lista_t su variable->siguiente apuntando a una de memoria
válida y su variable->capacidad inicializada a un valor conocido y válido.
*/
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

/*
Recibe un puntero a variable tipo lista_t y libera de su memoria a los nodos
que contenga seguido de la lista.
@param lista Puntero a variable tipo lista_t.
@pre La variable lista no debe apuntar a NULL, sino a una direccion de memoria
que contenga una variable tipo nodo_t válida.
*/
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

/*
Recibe un puntero a variable tipo personaje_t y inicializa sus variables a un valor
conocido y válido.
@param entidad Puntero a variable tipo personaje_t a ser inicializado.
@post Devuelve todas sus variables inicializadas a un valor conocido y válido.
@param quien_elije Entero que determina que printf() se va a mostrar.
@pre Debe valer 0 o 1, de lo contrario se frenará la funcion.
*/
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
            printf("Error: valor de variable quien_elije invalido.\n");
            return;
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

/*
Recibe puntero a variable tipo personaje_t y modifica su variable->energia segun
la accion realizada.
@param entidad Puntero a variable tipo personaje_t.
@pre Su variable->energia_total debe ser válida.
@post Su variable->energia aumentará o disminuirá segun corresponda.
@param accion Entero que define la modificacion de la variable->energia del puntero entidad
@pre Debe valer 0, 1 o 2.
*/
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
        printf("Error: No se pudo calcular la energia de la accion.\n");
        break;
    }
}

/*
Recibe un puntero a variable tipo personaje_t y modifica su variable->defensa.
@param entidad Puntero a variable tipo personaje_t.
@pre La variable->defensa de entidad debe estar inicializada a un valor conocido.
@post La variable->defensa de entidad será el doble en caso de que la variable->se_defendio sea 0
@post La variable->energia cambiara su valor en funcion de calcular_energia(entidad, DEFENSA).
@post La variable->se_defendio pasará a valer 1 en caso de que antes valiera 0.
*/
void defender(personaje_t *entidad)
{
    if(entidad->se_defendio == 0)
    {
        calcular_energia(entidad, DEFENSA);
        entidad->se_defendio = 1;
        entidad->defensa = entidad->defensa * 2;
    }
}

/*
Recibe dos punteros a variable tipo personaje_t y modifica la variable->vida del segundo
puntero recibido. 

@param entidad_1 Puntero a variable tipo personaje_t del cual se recupera su variable->ataque.
@pre La variable->ataque debe estar inicializada a un valor conocido.
@post Si la variable->se_defendio valia 1, pasa a valer 0.
@post La variable->energia cambiara su valor en funcion de calcular_energia(entidad, ATAQUE).

@param entidad_2 Puntero a variable tipo personaje_t el cual se modifica su variable->vida.
@pre La variable->vida y ->defensa deben estar inicializadas a un valor conocido.
@post La variable->vida disminuirá segun entidad_1->ataque y entidad_2->defensa/10.
*/
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

/*
Recibe un puntero a variable tipo personaje_t y modifica su variable->vida.
@param entidad Puntero a variable tipo personaje_t.
@pre La variable->vida de entidad debe estar inicializada a un valor conocido.
@post La variable->vida de entidad aumentará en funcion de la variable->vida_maxima.
@post La variable->energia cambiara su valor en funcion de calcular_energia(entidad, VIDA).
@post La variable->se_defendio pasará a valer 1 en caso de que antes valiera 0.
*/
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

/*
Recibe dos punteros a variable tipo personaje_t e imprime sus variables relevantes.
@param entidad_1 Puntero a variable tipo personaje_t.
@pre Todas sus variables menos ->vida_maxima, ->eneriga_maxima y ->se_defendio
deben estar inizialicadas a un valor conocido.
@param entidad_2 Puntero a variable tipo personaje_t.
@pre Todas sus variables menos ->vida_maxima, ->eneriga_maxima y ->se_defendio
deben estar inizialicadas a un valor conocido.
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

/*
Crea un archivo FILE y lo abre para escribir en un archivo de texto. Tambien crea 2
variables tipo personaje_t y llama a la funcion logica_turnos usando como parametro la
direccion de memoria de las 3 variables mencionadas anteriormente.
Una vez que la funcion logica_turnos termina, se cierra el archivo FILE.
*/
void empezar_partida()
{
    FILE *log = NULL;

    log = fopen("log.txt", "a");
    if(log == NULL)
    {
        perror("Error: No se pudo crear el archivo log.txt");
        return;
    }

    personaje_t jugador;
    personaje_t enemigo;

    logica_turnos(&jugador, &enemigo, log);

    fclose(log);
}