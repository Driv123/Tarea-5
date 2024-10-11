//Analisis 1

#include <stdio.h>       // Libreria estandar de entrada y salida
#include <stdlib.h>      // Librería con funciones como malloc, free, entre otras
#include <unistd.h>      // Librería con funciones de bajo nivel del sistema 
#include <string.h>      // Librería con funciones para manipulacion de strings

#define MAX_ITEMS 10     // Define el tamaño de elementos en la RAM en 10
#define SWAP_THRESHOLD 8 // Define un intervalo o rango para el swap cuando la RAM tiene 8 elementos 

typedef struct { //Estructura para datos
    int id;               // Identificador para cada elemento
    char data[20];        // Datos referentes al elemento como arreglo de 20
} DataItem;               // Estructura para representar un item en memoria RAM


DataItem ram[MAX_ITEMS];  // Crea un arreglo de 10 elementos que simula una ram donde se almacenaran los DataItem
// Funcion que imprime los elementos almacenados en la RAM

void printRAM() {
    printf("Contenido en RAM:\n");
    for (int i = 0; i < MAX_ITEMS; ++i) {   // Recorre la RAM simulada
        if (ram[i].id != -1) {  // Si el id no es -1, significa que hay un dato valido en esa posicion
            printf("ID: %d, Data: %s\n", ram[i].id, ram[i].data);  // Imprime el id y los datos del elemento
        }
    }
}

// Funcion para simular el intercambio de un elemento desde la RAM al disco
void swapToDisk(DataItem item) {
    printf("Intercambiando elemento ID: %d a disco duro.\n", item.id);  // Mensaje para indicar que se esta intercambiando
    printf("Elemento ID: %d, Data: %s fue intercambiado a disco.\n", item.id, item.data); //Imprime el intercambio
}


// Funcion para agregar un nuevo elemento a la RAM
void addToRAM(DataItem item) {
    int added = 0;    // Variable para controlar si el item fue agregado a la RAM
    for (int i = 0; i < MAX_ITEMS; ++i) {   // Recorre la RAM buscando un espacio vacio
        if (ram[i].id == -1) {    // Si encuentra un id igual a -1, significa que el espacio esta libre
            ram[i] = item;    // Le da el nuevo elemento a esa posicion en la RAM
            added = 1;   // Marca que el item se agrego
            break;      // Sale del bucle cuando se agrega
        }
    }
    if (!added) {     // Si no se pudo agregar el item (RAM llena)
        swapToDisk(ram[0]);  // Simula el swap del primer elemento de la RAM al disco
        ram[0] = item;     // Reemplaza el primer elemento en la RAM con el nuevo
    }
}

int main() { //El poderoso main
    // Inicializa la RAM simulada, marcando todos los elementos como vacios 
    for (int i = 0; i < MAX_ITEMS; ++i) {
        ram[i].id = -1;  // Todos los elementos inician vacios
    }

    // E Agrega varios elementos a la RAM
    addToRAM((DataItem) {1, "Datos de prueba 1"});
    addToRAM((DataItem) {2, "Datos de prueba 2"});
    addToRAM((DataItem) {3, "Datos de prueba 3"});
    addToRAM((DataItem) {4, "Datos de prueba 4"});
    addToRAM((DataItem) {5, "Datos de prueba 5"});
    addToRAM((DataItem) {6, "Datos de prueba 6"});
    addToRAM((DataItem) {7, "Datos de prueba 7"});
    addToRAM((DataItem) {8, "Datos de prueba 8"});
    addToRAM((DataItem) {9, "Datos de prueba 9"});
    addToRAM((DataItem) {10, "Datos de prueba 10"});  // Aqui la RAM se llena y comenzara a intercambiar elementos

    // Muestra el contenido final de la RAM
    printRAM();

    return 0;  // Termina con el confiable return 0
}


