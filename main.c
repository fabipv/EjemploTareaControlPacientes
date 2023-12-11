#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Se define una constante para la longitud máxima de cadenas
#define MAXCHAR 31

// Se define la estructura para un paciente y un médico
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

//===================================================================================================
// FUNCIONES HERRAMIENTAS
//===================================================================================================

void mostrarMenu() {
  puts("========================================");
  puts("          Control de Pacientes");
  puts("========================================");

  puts("1) Registrar Paciente.");
  puts("2) Importar Pacientes desde cvs.");
  puts("3) Exportar Pacientes a cvs.");
  puts("4) Salir.");
}

// Esta función elimina las tildes de una cadena de caracteres y retorna una
// nueva cadena sin tildes
char *quitarTildes(char *cadena) {
  const char *originales = "áéíóúÁÉÍÓÚ";
  const char *reemplazos = "aeiouAEIOU";

  // Se reserva memoria para la nueva cadena (se agrega 1 para el carácter nulo
  // '\0')
  char *nuevaCadena = (char *)malloc(strlen(cadena) + 1);

  // Verifica si se pudo reservar memoria
  if (nuevaCadena == NULL) {
    return NULL;
  }

  int j = 0; // Índice para la nueva cadena

  // Itera sobre cada carácter de la cadena original
  for (int i = 0; cadena[i] != '\0'; i++) {
    bool conTilde = false;
    bool flag = false;

    // Itera sobre los caracteres originales con tilde
    for (int k = 0; originales[k] != '\0'; k++) {
      // Compara el carácter actual con los caracteres originales con tilde
      if (cadena[i] == originales[k]) {
        if (!flag) {
          i++;
        } else {
          conTilde = true; // Indica que el carácter tiene tilde
          nuevaCadena[j++] = reemplazos[k / 2]; // Reemplaza el carácter por su
                                                // equivalente sin tilde
          break;
        }
        flag = true; // Marca que se encontró un carácter con tilde
      }
    }

    // Si el carácter no tiene tilde, se agrega a la nueva cadena
    if (!conTilde) {
      nuevaCadena[j++] = cadena[i];
    }
  }

  nuevaCadena[j] = '\0'; // Agrega el carácter nulo al final de la nueva cadena
  return nuevaCadena;
}

//===================================================================================================
// OPCION 1: REGISTRAR PACIENTE
//===================================================================================================
void registrarPaciente(List *listaPacientes, char *nombreAux, char *apellidoAux,
                       int edadAux, char *telefonoAux, char *direccionAux,
                       char *numSeguridadAux, List *medicosIngresados,
                       int opcion) {

  // Se reserva memoria para el paciente a registrar
  Paciente *p = (Paciente *)malloc(sizeof(Paciente));
  Paciente *pacienteActual = firstList(listaPacientes);

  // Verifica si se está registrando un nuevo paciente
  if (opcion == 1) {
    // Comprueba si el paciente ya está registrado mediante el número de
    // seguridad social
    while (pacienteActual != NULL) {
      if (strcmp(pacienteActual->numSeguridad, numSeguridadAux) == 0) {
        // Imprime un mensaje si el paciente ya existe y finaliza la función
        puts("==============================================");
        puts("      El Paciente ya esta registrado.");
        puts("==============================================");
        sleep(2);
        return;
      }
      pacienteActual = nextList(listaPacientes);
    }

    // Si el paciente no está registrado, se asignan los datos y se agrega a la
    // lista
    strcpy(p->nombre, nombreAux);
    strcpy(p->apellido, apellidoAux);
    p->edad = edadAux;
    strcpy(p->telefono, telefonoAux);
    strcpy(p->direccion, direccionAux);
    strcpy(p->numSeguridad, numSeguridadAux);
    p->medicosAsignados = medicosIngresados;
    pushBack(listaPacientes, p);

    // Imprime un mensaje de registro exitoso
    puts("==============================================");
    puts("   El Paciente se registro exitosamente.");
    puts("==============================================");
    sleep(2);
  } else {
    // Si se busca registrar un paciente existente, no realiza la verificación y
    // registra el paciente directamente
    while (pacienteActual != NULL) {
      if (strcmp(pacienteActual->numSeguridad, numSeguridadAux) == 0) {
        return;
      }
      pacienteActual = nextList(listaPacientes);
    }

    // Se asignan los datos y se agrega el paciente a la lista
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

// Función para registrar médicos asignados a un paciente
void registrarMedicos(List *medicosIngresados) {
  int medicosAsignados;

  // Se pide al usuario la cantidad de médicos a asignar
  do {
    printf("\nCuantos Medicos desea asignar: ");
    while (scanf("%d", &medicosAsignados) != 1) {
      printf("\nEntrada invalida. Ingrese un numero entero: ");
      while (getchar() != '\n')
        ;
    }
    if (medicosAsignados <= 0) {
      printf("\nCantidad mal ingresada, intente nuevamente.\n");
    }
  } while (medicosAsignados <= 0);

  getchar();

  // Se solicita el nombre de cada médico y se verifica si ya está asignado al
  // paciente
  for (int i = 1; i <= medicosAsignados; i++) {
    bool medicoRepetido = false;
    char medicoAuxiliar[MAXCHAR];

    printf("Ingrese medico %d: ", i);
    scanf("%30[^\n]s", medicoAuxiliar);
    while (getchar() != '\n')
      ;

    // Comprueba si el médico ya está asignado
    Medico *medicoActual = firstList(medicosIngresados);
    while (medicoActual != NULL) {
      if (strcmp(medicoAuxiliar, medicoActual->nombreMedico) == 0) {
        // Imprime un mensaje si el médico ya está asignado al paciente
        puts("========================================");
        printf("El/La %s ya esta asignado al paciente.\n", medicoAuxiliar);
        puts("========================================\n");
        medicoRepetido = true;
        i--;
        break;
      }
      medicoActual = nextList(medicosIngresados);
    }

    // Si el médico no está asignado, se agrega a la lista de médicos del
    // paciente
    if (medicoRepetido == false) {
      Medico *med = (Medico *)malloc(sizeof(Medico));
      strcpy(med->nombreMedico, medicoAuxiliar);
      pushBack(medicosIngresados, med);

      // Imprime un mensaje indicando que el médico fue agregado exitosamente
      puts("========================================");
      printf("%s agregado exitosamente.\n", medicoAuxiliar);
      puts("========================================");
      puts("");
    }
  }
  sleep(2);
}

//===================================================================================================
// OPCION 2: IMPORTAR CVS PACIENTE
//===================================================================================================
void importarCvsPaciente(List *listaPacientes) {
  FILE *archivoPacientes;
  char nombreArchivo[MAXCHAR];

  // Se solicita el nombre del archivo y se abre para lectura
  while (true) {
    printf("Ingrese Nombre Archivo (incluir extension .cvs): ");
    scanf("%s", nombreArchivo);
    getchar();

    archivoPacientes = fopen(nombreArchivo, "r");

    // Si hay un error al abrir el archivo, se muestra un mensaje y se pide el
    // nombre nuevamente
    if (archivoPacientes == NULL) {
      puts("\n==============================");
      printf("Error al abrir el archivo.\n");
      printf("Intentelo nuevamente.\n");
      puts("==============================\n");
    } else {
      break;
    }
  }

  char linea[8 * MAXCHAR];
  char *campo;
  char *campoMedicos;

  char nombreAux[MAXCHAR];
  char apellidoAux[MAXCHAR];
  int edadAux;
  char telefonoAux[MAXCHAR];
  char direccionAux[MAXCHAR];
  char numSeguridadAux[MAXCHAR];

  // Se lee la primera línea del archivo (encabezado)
  fgets(linea, 8 * MAXCHAR, archivoPacientes);

  // Se procesa cada línea del archivo (datos de pacientes)
  while (fgets(linea, 8 * MAXCHAR, archivoPacientes)) {
    List *medicosIngresados =
        createList(); // Se crea una lista para los médicos

    // Variables para el procesamiento de cada campo de la línea
    char *existeMasMedicos;

    // Se tokeniza la línea utilizando ',' como separador para obtener cada
    // campo de información
    campo = strtok(linea, ",");
    campo = quitarTildes(campo);
    strcpy(nombreAux, campo);

    campo = strtok(linea, ",");
    campo = quitarTildes(campo);
    strcpy(nombreAux, campo);

    campo = strtok(NULL, ",");
    campo = quitarTildes(campo);
    strcpy(apellidoAux, campo);

    campo = strtok(NULL, ",");
    edadAux = atoi(campo);

    campo = strtok(NULL, ",");
    strcpy(telefonoAux, campo);

    campo = strtok(NULL, ",");
    strcpy(direccionAux, campo);

    campo = strtok(NULL, ",");
    strcpy(numSeguridadAux, campo);

    campo = strtok(NULL, "\n");
    // Se verifica si hay múltiples médicos asignados al paciente
    existeMasMedicos = strchr(campo, ';');

    // Se procesan los médicos asignados al paciente
    if (existeMasMedicos == NULL) {
      if (strcmp(campo, "Sin medicos asignados") != 0) {
        // Si solo hay un médico, se agrega a la lista de médicos
        Medico *med = (Medico *)malloc(sizeof(Medico));
        campo = quitarTildes(campo);
        strcpy(med->nombreMedico, campo);
        pushBack(medicosIngresados, med);
      }
    } else {
      // Si hay múltiples médicos, se procesan uno por uno
      while (campo != NULL) {
        // Se agrega cada médico a la lista de médicos del paciente
        Medico *med = (Medico *)malloc(sizeof(Medico));

        campoMedicos = strtok(campo, ";");
        campoMedicos = quitarTildes(campoMedicos);

        strcpy(med->nombreMedico, campoMedicos);
        pushBack(medicosIngresados, med);

        campo = strtok(NULL, "\n");
      }
    }

    // Se registra el paciente con la información obtenida
    registrarPaciente(listaPacientes, nombreAux, apellidoAux, edadAux,
                      telefonoAux, direccionAux, numSeguridadAux,
                      medicosIngresados, 2);
  }

  // Mensaje de éxito después de importar el archivo CVS
  puts("==============================================");
  puts("        El CVS se importo exitosamente.");
  puts("==============================================");

  sleep(2);

  // Se cierra el archivo
  fclose(archivoPacientes);
}

//===================================================================================================
// OPCION 3: EXPORTAR CVS PACIENTE
//===================================================================================================
void exportarCvsPaciente(List *listaPacientes) {
  Paciente *pacienteActual = firstList(listaPacientes);

  // Se verifica si la lista de pacientes está vacía
  if (pacienteActual == NULL) {
    puts("========================================");
    puts("  La Lista de Pacientes esta vacia.");
    puts("========================================\n");
    system("pause");
  } else {
    FILE *archivoPacientes;
    char nombreArchivo[MAXCHAR];

    // Se pide al usuario el nombre del archivo de salida y se abre para
    // escritura
    while (true) {
      printf("Ingrese Nombre Archivo (incluir extension .cvs): ");
      scanf("%s", nombreArchivo);
      getchar();

      archivoPacientes = fopen(nombreArchivo, "w");

      // Si hay un error al abrir el archivo, se muestra un mensaje y se pide el
      // nombre nuevamente
      if (archivoPacientes == NULL) {
        puts("\n==============================");
        printf("Error al abrir el archivo.\n");
        printf("Intentelo nuevamente.\n");
        puts("==============================\n");
      } else {
        break;
      }
    }

    // Se escribe el encabezado del archivo CVS con los nombres de los campos
    fprintf(archivoPacientes, "Nombre,Apellido,Edad,Telefono,Direccion,Num_"
                              "Seguridad_Social,Medicos\n");

    // Se recorre la lista de pacientes para escribir la información de cada uno
    // en el archivo CVS
    while (pacienteActual != NULL) {
      fprintf(archivoPacientes, "%s,%s,%d,%s,%s,%s,", pacienteActual->nombre,
              pacienteActual->apellido, pacienteActual->edad,
              pacienteActual->telefono, pacienteActual->direccion,
              pacienteActual->numSeguridad);

      // Se obtienen los médicos asignados al paciente y se escriben en el
      // archivo
      void *medicoActual = firstList(pacienteActual->medicosAsignados);
      bool tieneMasMedicos = false;

      if (medicoActual != NULL) {
        while (medicoActual != NULL) {
          // Se escribe cada médico asignado separado por ';'
          if (!tieneMasMedicos) {
            fprintf(archivoPacientes, "%s", medicoActual);
            tieneMasMedicos = true;
          } else {
            fprintf(archivoPacientes, ";%s", medicoActual);
          }

          medicoActual = nextList(pacienteActual->medicosAsignados);
        }
      } else {
        // Si no hay médicos asignados, se escribe "Sin medicos asignados"
        fprintf(archivoPacientes, "Sin medicos asignados");
      }

      pacienteActual =
          nextList(listaPacientes); // Se avanza al siguiente paciente
      fprintf(archivoPacientes,
              "\n"); // Se pasa a la siguiente línea en el archivo
    }

    // Mensaje de éxito después de exportar el archivo CVS
    puts("==============================================");
    puts("        El CVS se exporto exitosamente.");
    puts("==============================================");

    sleep(2);

    // Se cierra el archivo
    fclose(archivoPacientes);
  }
}

//===================================================================================================
// FUNCION PRINCIPAL
//===================================================================================================

int main(int argc, char *argv[]) {

  int opcion;
  List *listaPacientes =
      createList(); // Se crea una lista para almacenar pacientes

  do {
    mostrarMenu(); // Se muestra el menú de opciones
    puts("");
    printf("Eliga una opcion: ");
    scanf("%d", &opcion);
    getchar();

    switch (opcion) {
    case 1: {
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

      // Se solicita información para registrar un paciente

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

      registrarPaciente(listaPacientes, nombreAux, apellidoAux, edadAux,
                        telefonoAux, direccionAux, numSeguridadAux,
                        medicosIngresados, 1);
      break;
    }
    case 2:
      // Opción para importar pacientes desde un archivo CVS
      importarCvsPaciente(listaPacientes);
      break;

    case 3:
      // Opción para exportar pacientes a un archivo CVS
      exportarCvsPaciente(listaPacientes);
      break;

    case 4:
      // Opción para salir del programa
      printf("Saliendo...\n");
      sleep(2);
      break;

    default:
      // Mensaje de opción inválida
      printf("\nOpcion no valida. Intente nuevamente.\n\n");
      system("pause");
    }
  } while (opcion != 4);

  return 0;
}