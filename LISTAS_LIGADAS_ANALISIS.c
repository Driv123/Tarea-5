//Analisis 3

#include <stdio.h>      // Libreria para imprimir en pantalla
#include <stdlib.h>     // Libreria para funciones de manejo de memoria (malloc, free)
// Crea una estructura para un bloque de memoria
typedef struct MemoryBlock {
    int id;                     // Identifica el bloque de memoria
    size_t size;                // Tamaño del bloque de memoria
    struct MemoryBlock *next;   // Puntero al siguiente bloque en la lista
} MemoryBlock; 
// Funcion para inicializar un bloque de memoria
MemoryBlock* createMemoryBlock(int id, size_t size) {
    MemoryBlock *block = (MemoryBlock *)malloc(sizeof(MemoryBlock));  // Reserva espacio en memoria para el bloque
    if (block != NULL) {  // Si la asignacion de memoria fue exitosa
        block->id = id;         // Asigna el ID al bloque
        block->size = size;     // Asigna el tamaño al bloque
        block->next = NULL;     // Inicializa el puntero al siguiente bloque como NULL
    }
    return block;  // Retorna el puntero al bloque de memoria creado
}

// Funcion para liberar un bloque de memoria
void freeMemoryBlock(MemoryBlock *block) {
    free(block);  // Libera la memoria ocupada por el bloque
}

// Funcion para imprimir la lista de bloques de memoria
void printMemoryList(MemoryBlock *head) {
    MemoryBlock *current = head;  // Crea  un puntero para recorrer la lista
    printf("Lista de bloques de memoria:\n");  // Mensaje para indicar el inicio de la lista
    while (current != NULL) {  // Entra si hay bloques en la lista
        printf("ID: %d, Tamano: %zu\n", current->id, current->size);  // Imprime el ID y tamaño del bloque actual
        current = current->next;  // Avanza al siguiente bloque en la lista
    }
}


int main() {  // La funcion principal o main god
    MemoryBlock *memoryList = NULL;  // Inicializa la lista enlazada de bloques de memoria
    // Creacion de bloques de memoria simulados
    MemoryBlock *block1 = createMemoryBlock(1, 100);  // Crea el bloque 1 con ID 1 y tamaño 100
    MemoryBlock *block2 = createMemoryBlock(2, 200);  // creamos el bloque 2 con ID 2 y tamaño 200
    MemoryBlock *block3 = createMemoryBlock(3, 150);  // Crea el bloque 3 con ID 3 y tamaño 150
    // Inserta los bloques en la lista de memoria
    block1->next = block2;  // Hace que el bloque 1 apunte al bloque 2
    block2->next = block3;  // Hace que el bloque 2 apunte al bloque 3
    memoryList = block1;     // La cabeza de la lista es el bloque 1
    // Imprimir la lista de bloques de memoria
    printMemoryList(memoryList);  // Llama a la funcion para imprimir la lista
    freeMemoryBlock(block1);  // Libera el bloque 1
    freeMemoryBlock(block2);  // Libera el bloque 2
    freeMemoryBlock(block3);  // Libera el bloque 3
    return 0;  // Termina el programa
}


