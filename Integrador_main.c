#include <stdio.h>
#include "simulador_combate.h"
#include "simulador_desiciones.h"

int main()
{
    personaje_t jugador = {.nombre = "Astolfo", .ataque = 20, .defensa = 25, .energia = 80, .vida_total = 100, .vida = 100};
    personaje_t enemigo = {.nombre = "Ka'or", .ataque = 15, .defensa = 20, .energia = 55, .vida_total = 70, .vida = 70};
    
    logica_turnos(&jugador, &enemigo);

    return 0;
}
