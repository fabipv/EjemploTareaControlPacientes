#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXCHAR 31

typedef struct {
  char nombre[MAXCHAR];
  char apellido[MAXCHAR];
  int edad;
  char telefono[MAXCHAR];
  char direccion[MAXCHAR];
  char numSeguridad[MAXCHAR];
  List *medicosAsignados;
} Paciente;

typedef struct {
  char nombreMedico[MAXCHAR];
} Medico;
