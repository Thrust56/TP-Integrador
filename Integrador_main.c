#include <stdio.h>
#include "simulador_combate.h"
#include "simulador_desiciones.h"

int main()
{
    FILE *log = NULL;
    personaje_t jugador = PERSONAJE_1;
    personaje_t enemigo = PERSONAJE_2;
    
    logica_turnos(&jugador, &enemigo, log);

    return 0;
}
