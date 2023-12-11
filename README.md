Control de pacientes implementado con TDA Lista.
======

---
**Antes de Empezar**

*   Se utilizó Replit para programar en C y se creó un repositorio en GitHub con el siguiente link: https://github.com/fabipv/EjemploTareaControlPacientes
*   Para ejecutar el codigo comenzamos compilando nuestros archivos .c a traves de la terminal con el siguiente comando: `gcc -g main.c list.c `

⭕ Consideren incorporar: Una descripción del paso a paso para compilar y ejecutar el código

---

En esta aplicacion es implementada con una **lista enlazada**. Para esto se utiliza la siguiente estructura:

````c
typedef struct Node Node;

struct Node {
    void * data; // Puntero al dato
    Node * next; // Puntero al siguiente nodo
    Node * prev; // Puntero al nodo previo
};

typedef struct {
    Node * head; // Puntero al primer elemento
    Node * tail; // Puntero al ultimo elemento
    Node * current; // Puntero para poder recorrer la lista
} List;
````
---

Se pidió crear una aplicación que teoricamente seria utilizada en un/a hospital/clinica,
teniendo como objetivo registrar, almacenar y eliminar datos sobre los pacientes que asistiran al recinto. Se utiliza las siguientes estructuras:

````c
typedef struct{
    char nombre[MAXCHAR];
    char apellido[MAXCHAR];
    int edad;
    char telefono[MAXCHAR];
    char direccion[MAXCHAR];
    char num_seguridad_social[MAXCHAR];
    List* medicosAsignados;
}Paciente;

typedef struct{
    char nombreMedico[MAXCHAR];
}Medico;
````

---

Este programa comienza con el main mostrando el menu de opciones, para esto llamamos a la `funcion menu()`, este menu que se integra dentro de un bucle do-while ya que cada vez que elijamos una opcion siempre se vuelve al menu despues de completarla o si ingresemos un valor erroneo volverá al menu.

Para ingresar las opciones del menu, se debe ingresar valores enteros entre 1 y 4, dependiendo de lo que uno desee realizar, para esto se utiliza un switch, y asi se estructura adecuadamente todas las funciones que debemos implementar.

Funciones Implementadas:
----

- **Opcion 1:** `registrarPacientes(List* listaPacientes, char* nombreAux, char* apellidoAux, int edadAux, char* telefonoAux, char* direccionAux, char* num_seguridad_socialAux, List * medicosIngresados, int opcion)`:

    Una vez elegida la opción 1, antes de llamar a la función `registrarPacientes()`, se ingresan los datos del paciente y validamos que las variables de `tipo char*` no superen los 30 caracteres y que la edad ingresada sea mayor a 0.
    
    Además, para agregar médicos al paciente utilizamos un ciclo do-while en donde el usuario elige si quiere o no asignar médicos, si el usuario ingresa un dato invalido (p.ej. un carácter o un número entero distinto de 1 o 0) se vuelve a preguntar hasta que se ingrese un dato válido para responder la pregunta.

    Si el usuario decide asignar médicos, se llama a la función `registrarMedicos()` a la cual le ingresamos como parámetro la lista de médicos del paciente en cuestión. Una vez dentro de la función para registrar los médicos al paciente, nuevamente con el uso del bucle do-while, el usuario debe ingresar la cantidad de médicos a asignar (el número a ingresar debe ser mayor a 0), luego con un ciclo for se ingresa el nombre del médico a asignar, para esto se valida que el nombre del médico no sobrepase los 30 caracteres y mediante el uso de las funciones de listas enlazadas buscamos que el médico no exista en la lista de médicos del paciente, una vez que se cumplan las condiciones mencionadas anteriormente, el nombre del médico se guarda en la lista de médicos del paciente con el uso del `pushBack()`.

    Si se da el caso de que el usuario asigna un médico que ya está asignado al paciente, se muestra un mensaje por pantalla indicando que ya está registrado, y se vuelve a pedir un médico no ingresado .

    Y finalmente se llama a la función `registrarPaciente()` con los parámetros ya ingresados, en la función se crea una variable paciente asignando la memoria correspondiente con la `función malloc()`,luego con el uso de `firstList()` y `nextList()` recorremos la lista enlazada de pacientes para comprobar si el paciente ya está registrado, esta comprobación  es a través del número de seguridad social ya que este es único para cada paciente. Finalmente se copian los datos a la variable paciente creada anteriormente, se agrega el paciente a la lista de pacientes con `pushBack()` y se muestra un mensaje por pantalla diciendo que el paciente se registró exitosamente.

    Para esta opción del menú, al momento de llamar a la función `registrarPaciente()` asignamos el último parámetro de esta como un 1, esto ya que esta función se usa tanto para registrar pacientes ingresados por el usuario y para registrar pacientes leídos desde un csv.

    

- **Opcion 2:** `void importarCsvPaciente(List* listaPacientes)`:

    Luego de elegir la opción 8, se llamará a la función `ImportarCsvPacientes()`, función que tomará los datos escritos en un archivo .CSV, el cual, contiene información de pacientes y sus médicos, para luego almacenar los datos en una lista.

    Primero se le pide al usuario que ingrese el nombre del archivo CSV que desea importar con la terminación `.csv` (Si llegase a NO existir el nombre del archivo, o  este fuese inscrito con un nombre incorrecto, se notificará al usuario que no existe tal archivo, dándole la oportunidad de ingresar un nombre nuevamente). Luego, se abre el archivo en modo `read` ya que lo utilizaremos solo para leer los datos que este contiene y se lee línea por línea, Cada línea se divide en campos separados por comas utilizando la `función strtok()` y se eliminan los tildes con la función `quitar_tildes()`. Se crean variables auxiliares de tipo char correspondientes al nombre, apellido, teléfono, dirección y número de seguridad social del paciente, y una variable tipo int para la edad (que almacenarán los datos hasta que sean ingresados en la lista), así como una lista de los médicos asignados a ese paciente. En el caso de que el paciente NO tuviese médicos asignados. se registra “Sin médicos asignados”. Si el paciente posee más de un médico asignado , se utiliza el carácter ` ; ` para separar los nombres de los médicos en el campo correspondiente. Finalmente se llama a la función `registrarPaciente()` para agregar al paciente a la lista enlazada y se cierra el archivo. Una vez terminado, se muestra un mensaje informando al usuario que el archivo se ha importado de manera exitosa.


- **Opcion 3:** `void exportarCsvPaciente(List* listaPacientes)`:

    Al elegir esta opción se llamará a la función `ExportarCsvPacientes()`, la cual leerá todos los datos de la lista y los escribirá en un archivo .CSV.

    La función inicia con un puntero indicado por `firstlist()` que apunta al paciente del nodo, en caso de que la lista esté vacía, simplemente imprimirá un mensaje diciendo que la lista de pacientes está vacía y luego pedirá al usuario que ingrese una tecla para continuar. En caso omiso, se creará un puntero a FILE para luego exportarlo a un archivo. Después se le solicita al usuario que ingrese el nombre del archivo a crear, el FILE se abre en modo `write`con el nombre indicado y tiene un control de flujo en caso de que el archivo no se haya podido abrir y solicitará intentarlo nuevamente.

    Previamente a registrar el paciente, se colocarán las “columnas” de cada dato para identificar qué representa cada uno. Ahora es cuando se empezará a recorrer la lista con un while, en el cual su condición consiste en que la lista sea distinta de nulo, por tanto, recorrerá toda la lista hasta el último elemento.

    Luego, escribirá cada dato del paciente en el archivo hasta su número de seguridad social con la `funcion fprintf()`. Luego, como los médicos se encuentran separados por puntos y comas y se encuentran en una lista, se accede al `firstlist()` de la lista medicosAsignados del paciente, inicializado junto a un bool tieneMasMedicos en falso que indicará si este paciente tiene más de un médico asignado.

    Previo al procesamiento de médicos, se verifica si la lista de médicos del paciente esté vacía, y en el caso de que esto sea verdad, procederá a saltar el proceso de exportación e imprimirá un mensaje que indique que hay más de un médico. Si esto no se cumplé, se asume que hay por lo menos un médico y entrará en un ciclo que recorrerá toda la lista de estos,  por cada iteración preguntará en un control de flujo si es que el bool tieneMasMedicos es falso, en caso de que esto se cumpla, escribirá el primer médico en el archivo sin una coma y el bool se convertirá en verdadero, luego la lista de médicos va al siguiente elemento, en caso de que este sea nulo, se daría por terminado el registro del paciente en el archivo y saltaría a la siguiente línea para registrar al próximo paciente. Sin embargo, si es que la lista aún tiene médicos, entrará al else de la condición que verifica que el tieneMasMedicos era falso, por tanto ingresará los médicos restantes con una separación de punto y coma.

    Una vez registrados todos los pacientes, se imprime un mensaje que el csv fue creado y exportado exitosamente y procede a cerrar con `fclose()` el archivo FILE creado.


- **Opcion 4:** 

    Si se selecciona la opción 4, esto hará que se muestre un mensaje por pantalla que indica que se está saliendo del programa, lo cual cierre la terminal y dará término a la ejecución del programa de control de pacientes.


⭕ Consideren incorporar: 
- Las funciones que generan problemas, por ejemplo no se exporta de manera correcta el archivo CVS.
- Lo que se puede mejorara de su tarea/proyecto, por ejemplo leer la dirección con los espacios, quitar las tildes para no tener problemas al mostrar por pantalla la información de los pacientes y médicos.
- Las contibuciones de cada intregrante, por ejemplo

   **Juan Pérez:**
        - Desarrolló las funciones básicas para registar paciente y quitar tildes.
        - Diseño inicial de la interfaz de usuario.
        - **Auto-evaluación**: 2 (Aporte bueno).

   **María Rodríguez:**
        - Implementó las funciones de importar y exportar CVS.
        - Documentación y comentarios en el código.
        - Diseño y redacción del README.
        - **Auto-evaluación**: 3 (Aporte excelente).**

