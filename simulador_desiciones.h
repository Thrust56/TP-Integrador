#ifndef __SIMULADOR_DESICIONES_H__
#define __SIMULADOR_DESICIONES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulador_combate.h"

void decidir_accion(personaje_t *entidad, personaje_t *oponente);
void logica_turnos(personaje_t *entidad_1, personaje_t *entidad_2);

#endif