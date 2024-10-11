//Propuesta de codigo
//Hanna Montana OS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SIZE 5

typedef struct {
    int id;
    char data[20];
} CacheItem;

CacheItem cache[CACHE_SIZE];
int usage[CACHE_SIZE]; 

void initializeCache() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].id = -1; 
        usage[i] = 0; 
    }
}

void printCache() {
    printf("Contenido de la cache:\n");
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].id != -1) {
            printf("ID: %d, Data: %s, Usage: %d\n", cache[i].id, cache[i].data, usage[i]);
        }
    }
}

int findLRU() {
    int minUsage = usage[0], lruIndex = 0;
    for (int i = 1; i < CACHE_SIZE; i++) {
        if (usage[i] < minUsage) {
            minUsage = usage[i];
            lruIndex = i;
        }
    }
    return lruIndex; 
}

void accessCache(CacheItem item) {
    int found = 0;
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].id == item.id) {
            found = 1;
            usage[i]++; 
            break;
        }
    }

    if (!found) {
        int lruIndex = findLRU(); 
        printf("Reemplazando elemento ID: %d con ID: %d\n", cache[lruIndex].id, item.id);
        cache[lruIndex] = item; 
        usage[lruIndex] = 1; 
    }
}

int main() {
    initializeCache();
    
   
    accessCache((CacheItem){1, "Cache data 1"});
    accessCache((CacheItem){2, "Cache data 2"});
    accessCache((CacheItem){3, "Cache data 3"});
    accessCache((CacheItem){4, "Cache data 4"});
    accessCache((CacheItem){5, "Cache data 5"});
    printCache();
    
   
    accessCache((CacheItem){6, "Cache data 6"}); 
    accessCache((CacheItem){3, "Cache data 3"}); 

    printCache();
    return 0;
}
