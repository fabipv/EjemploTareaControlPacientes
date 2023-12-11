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

void mostrarMenu() {
  puts("========================================");
  puts("          Control de Pacientes");
  puts("========================================");

  puts("1) Registrar Paciente.");
  puts("2) Importar Pacientes desde csv.");
  puts("3) Exportar Pacientes a csv.");
  puts("4) Salir.");
}


char* quitarTildes(char* cadena)
{
    const char *originales = "áéíóúÁÉÍÓÚ";
    const char *reemplazos = "aeiouAEIOU";
    char* nuevaCadena = (char*) malloc(strlen(cadena) + 1);

    if (nuevaCadena == NULL) {
        return NULL;
    }

    int j = 0;

    for(int i = 0; cadena[i] != '\0'; i++)
    {
        bool conTilde = false;
        bool flag = false;

        for(int k = 0; originales[k] != '\0'; k++)
        {
            if(cadena[i] == originales[k])
            {
                if(!flag)
                {
                    i++;
                }
                else
                {
                    conTilde = true;
                    nuevaCadena[j++] = reemplazos[k/2];
                    break;
                }

                flag = true;
            }
        }

        if(!conTilde)
        {
            nuevaCadena[j++] = cadena[i];
        }
    }

    nuevaCadena[j] = '\0';
    return nuevaCadena;
}

void registrarPaciente(List* listaPacientes, char* nombreAux, char* apellidoAux, int edadAux, char* telefonoAux, char* direccionAux, char* numSeguridadAux, List * medicosIngresados, int opcion)
{
    Paciente* p = (Paciente*) malloc(sizeof(Paciente));
    Paciente* pacienteActual = firstList(listaPacientes);

    if(opcion == 1)
    {
        while(pacienteActual != NULL)
        {
            if(strcmp(pacienteActual->numSeguridad, numSeguridadAux) == 0)
            {
                system("cls");

                puts("==============================================");
                puts("      El Paciente ya esta registrado.");
                puts("==============================================");

                sleep(2);
                return;
            }

            pacienteActual = nextList(listaPacientes);
        }

        strcpy(p->nombre, nombreAux);
        strcpy(p->apellido, apellidoAux);
        p->edad = edadAux;
        strcpy(p->telefono, telefonoAux);
        strcpy(p->direccion, direccionAux);
        strcpy(p->numSeguridad, numSeguridadAux);
        p->medicosAsignados = medicosIngresados;

        pushBack(listaPacientes, p);

        system("cls");

        puts("==============================================");
        puts("   El Paciente se registro exitosamente.");
        puts("==============================================");

        sleep(2);
    }
    else
    {
        while(pacienteActual != NULL)
        {
            if(strcmp(pacienteActual->numSeguridad, numSeguridadAux) == 0)
            {
                return;
            }

            pacienteActual = nextList(listaPacientes);
        }

        strcpy(p->nombre, nombreAux);
        strcpy(p->apellido, apellidoAux);
        p->edad = edadAux;
        strcpy(p->telefono, telefonoAux);
        strcpy(p->direccion, direccionAux);
        strcpy(p->numSeguridad, numSeguridadAux);
        p->medicosAsignados = medicosIngresados;

        pushBack(listaPacientes, p);
    }
}


int main(int argc, char *argv[]) {

  int opcion;
  List *listaPacientes = createList();

  do {
    system("cls");
    mostrarMenu();
    puts("");
    printf("Eliga una opcion: ");
    scanf("%d", &opcion);
    getchar();

    switch (opcion) {
    case 1:
      system("cls");

      char nombreAux[MAXCHAR];
      char apellidoAux[MAXCHAR];
      int edadAux;
      char telefonoAux[MAXCHAR];
      char direccionAux[MAXCHAR];
      char numSeguridadAux[MAXCHAR];
      List *medicosIngresados = createList();

      puts("========================================");
      puts("          Registrar Paciente:");
      puts("========================================");

      printf("Ingrese Nombre: ");
      scanf("%30[^\n]", nombreAux);

      while (getchar() != '\n')
        ;

      printf("Ingrese Apellido: ");
      scanf("%30[^\n]s", apellidoAux);

      while (getchar() != '\n')
        ;

      do {
        printf("Ingrese Edad: ");

        while (scanf("%d", &edadAux) != 1) {
          printf("\nEntrada invalida. Ingrese un numero entero: ");
          while (getchar() != '\n')
            ;
        }

        if (edadAux <= 0) {
          printf("\nEdad mal ingresada, intente nuevamente.\n");
        }

      } while (edadAux <= 0);

      while (getchar() != '\n')
        ;

      printf("Ingrese Telefono: ");
      scanf("%30[^\n]s", telefonoAux);

      while (getchar() != '\n')
        ;

      printf("Ingrese Direccion (sin comas): ");
      scanf("%30[^\n]s", direccionAux);

      while (getchar() != '\n')
        ;

      printf("Ingrese Numero de Seguridad Social: ");
      scanf("%30[^\n]s", numSeguridadAux);

      while (getchar() != '\n')
        ;

      int respuestaMedicos;

      do {
        printf("\nDesea Asignar Medicos al Paciente\n");
        printf("Si (1)\n");
        printf("No (0)\n");

        while (scanf("%d", &respuestaMedicos) != 1 ||
               (respuestaMedicos != 1 && respuestaMedicos != 0)) {
          printf("\nRespuesta invalida, intente nuevamente.\n");
          printf("Si (1)\n");
          printf("No (0)\n");
          while (getchar() != '\n')
            ;
        }

      } while (respuestaMedicos != 1 && respuestaMedicos != 0);

      if (respuestaMedicos == 1) {
        registrarMedicos(medicosIngresados);
      }

      registrarPaciente(listaPacientes, nombreAux, apellidoAux, edadAux, telefonoAux, direccionAux, numSeguridadAux, medicosIngresados, 1);
      break;
      
    case 2:
      system("cls");
      importarCsvPaciente(listaPacientes);
      break;
      
    case 3:
      system("cls");
      exportarCsvPaciente(listaPacientes);
      break;
      
    case 4:
      system("cls");
      printf("Saliendo...\n");
      sleep(2);
      system("cls");
      break;
      
    default:
      printf("\nOpcion no valida. Intente nuevamente.\n\n");
      system("pause");
    }
  } while (opcion != 10);

  return 0;
}