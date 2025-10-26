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

