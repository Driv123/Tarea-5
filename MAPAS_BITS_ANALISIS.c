//Analisis 2

#include <stdio.h>    // Libreria para imprimir en pantalla
#include <stdlib.h>   // Libreria para funciones de manejo de memoria (malloc, free)
#include <stdint.h>   // Libreria que nos permite usar tipos como uint8_t (tipos de datos con tamaño fijo)

// Se definen algunos tamaños clave para la memoria
#define MEMORY_SIZE 1024  // La memoria total con 1024 bytes
#define BLOCK_SIZE 64     // Cada bloque de memoria es de 64 bytes
#define NUM_BLOCKS (MEMORY_SIZE / BLOCK_SIZE)  // El numero de bloques es la memoria total dividida por el tamaño de cada bloque

// Estructura que representa un bloque de memoria usando un mapa de bits
typedef struct MemoryBlock {
    uint8_t bitmap[BLOCK_SIZE / 8];  // Mapa de bits de 1 byte que controla 8 bits 
    int id;     // Identificador del bloque de memoria
} MemoryBlock;

// Función para crear un nuevo bloque de memoria e inicializarlo
MemoryBlock* createMemoryBlock(int id) {
    MemoryBlock *block = (MemoryBlock *)malloc(sizeof(MemoryBlock)); 
// Reserva espacio en memoria para el bloque
    if (block != NULL) {  // Si la asignación de memoria fue exitosa
        block->id = id;   // Se asigna el ID al bloque
        for (int i = 0; i < BLOCK_SIZE / 8; ++i) {  // Se recorre el mapa de bits del bloque
            block->bitmap[i] = 0;  // Se ponen todos los bits a 0 
        }
    }
    return block;  // Retorna el puntero al bloque de memoria creado
}

// Funcion para asignar memoria dentro de un bloque utilizando el mapa de bits
int allocateMemory(MemoryBlock *block, size_t size) {
    int start = -1;  // Variable para guardar donde empieza la asignación en el bloque si detecta -1 indica que no hay espacio
    int bits_needed = (size + 7) / 8;  // Convierte el tamaño solicitado en numero de bytes necesarios, redondeando hacia arriba

    // Recorre el mapa de bits para encontrar un espacio libre que sea grande
    for (int i = 0; i <= BLOCK_SIZE / 8 - bits_needed; ++i) {  // Busca en cada posición del mapa de bits
        int j;
        for (j = 0; j < bits_needed; ++j) {  // Verifica si los siguientes bits estan libres
            if (block->bitmap[i + j] != 0) {  // Si encuentra un bit ocupado
                break;  // Sale del bucle
            }
        }
        if (j == bits_needed) {  // Si encuentra suficiente espacio libre
            start = i * 8;  // Calcula el inicio de la asignación
            for (int k = 0; k < bits_needed; ++k) {  // Marca como ocupado los bytes que se ocupan
                block->bitmap[i + k] = 0xFF;  // 0xFF significa que todos los bits en ese byte están ocupados
            }
            break;  // sale del bucle porque ya encontr el espacio
        }
    }
    return start;  // Retorna donde empieza la asignacion o -1 si no habia espacio
}

// Función para liberar memoria en el bloque, usando el mapa de bits
void freeMemory(MemoryBlock *block, int start, size_t size) {
    int bits_to_free = (size + 7) / 8;  // Calcula cuantos bytes hay que liberar
    // Recorre los bytes correspondientes y los marcamos como libres en el mapa de bits
    for (int i = start / 8; i < (start / 8) + bits_to_free; ++i) {
        block->bitmap[i] = 0;  // Libera marcando los bits como 0 
    }
}

// Funcion para imprimir el estado del bloque de memoria
void printMemoryBlock(MemoryBlock *block) {
    printf("Bloque de memoria ID: %d\n", block->id);  // Imprimime el ID del bloque
    printf("Mapa de bits:\n");  // Imprime el título para el mapa de bits
    for (int i = 0; i < BLOCK_SIZE / 8; ++i) {  // Recorre cada byte del mapa de bits
        printf("%02X ", block->bitmap[i]);  // Imprime el valor hexadecimal de cada byte
    }
    printf("\n");  // Agrega  un salto de línea al final
}

int main() { //Main god
    MemoryBlock *memoryBlock = createMemoryBlock(1);  // Creamos un bloque de memoria con ID 1


    // Ejemplos de asignación de memoria
    int start1 = allocateMemory(memoryBlock, 128);  // Intenta asignar 128 bytes
    int start2 = allocateMemory(memoryBlock, 64);   // Intenta asignar 64 bytes
    printf("Despues de la asignacion:\n");  // Mensaje para indicar el estado despues de asignar memoria
    printMemoryBlock(memoryBlock);  // Imprimimos el mapa de bits para ver como esta el bloque tras la asignación
    // Liberamos los 128 bytes que asignamos primero
    freeMemory(memoryBlock, start1, 128);
    printf("Despues de la liberacion:\n");  // Mensaje para indicar el estado despues de liberar memoria
    printMemoryBlock(memoryBlock);  // Imprime el mapa de bits para ver como esta el bloque tras liberar la memoria
    free(memoryBlock);  // Libera la memoria del bloque que creamos
    return 0;  // Terminamos el programa con el return 0
}







