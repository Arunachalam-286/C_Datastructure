#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 5  // Define the LRU Cache capacity

// Structure to represent a stack node
typedef struct StackNode {
    int key;
    struct StackNode* next;
    struct StackNode* prev;
} StackNode;

// Structure for LRU Cache
typedef struct LRUCache {
    StackNode* head;           // Points to the most recently used (MRU)
    StackNode* tail;           // Points to the least recently used (LRU)
    int size;                  // Current size of the cache
    int capacity;              // Maximum capacity of the cache
    StackNode* hashMap[1000];  // Hash map for fast key lookup
} LRUCache;

// Function to create a new stack node
StackNode* createNode(int key) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->key = key;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Initialize LRU Cache
LRUCache* createLRUCache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->head = NULL;
    cache->tail = NULL;
    cache->size = 0;
    cache->capacity = capacity;
    memset(cache->hashMap, 0, sizeof(cache->hashMap));
    return cache;
}

// Move a node to the top (MRU position)
void moveToTop(LRUCache* cache, StackNode* node) {
    if (cache->head == node) return; // Already at the top

    // Remove node from its current position
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (cache->tail == node) cache->tail = node->prev;

    // Insert node at the top
    node->next = cache->head;
    node->prev = NULL;

    if (cache->head) cache->head->prev = node;
    cache->head = node;

    if (!cache->tail) cache->tail = node; // If only one node exists
}

// Remove the least recently used (LRU) node
void evictLRU(LRUCache* cache) {
    if (!cache->tail) return; // Cache is empty

    StackNode* lru = cache->tail;
    if (lru->prev) lru->prev->next = NULL;
    cache->tail = lru->prev;

    if (cache->head == lru) cache->head = NULL;

    cache->hashMap[lru->key] = NULL; // Remove from hash map
    free(lru);
    cache->size--;
}

// Add a key to the cache
void put(LRUCache* cache, int key) {
    // If key already exists, move it to the top
    if (cache->hashMap[key]) {
        moveToTop(cache, cache->hashMap[key]);
        return;
    }

    // Create a new node
    StackNode* newNode = createNode(key);

    // Add to hash map and insert at the top
    cache->hashMap[key] = newNode;
    newNode->next = cache->head;
    if (cache->head) cache->head->prev = newNode;
    cache->head = newNode;

    if (!cache->tail) cache->tail = newNode;

    cache->size++;

    // If cache exceeds capacity, evict LRU
    if (cache->size > cache->capacity) {
        evictLRU(cache);
    }
}

// Display the current state of the cache
void displayCache(LRUCache* cache) {
    StackNode* current = cache->head;
    printf("Cache state (MRU -> LRU): ");
    while (current) {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}

int main() {
    // Create LRU cache with a capacity
    LRUCache* cache = createLRUCache(CAPACITY);

    // Example operations
    put(cache, 1);
    displayCache(cache);

    put(cache, 2);
    displayCache(cache);

    put(cache, 3);
    displayCache(cache);

    put(cache, 4);
    displayCache(cache);

    put(cache, 5);
    displayCache(cache);

    // Access key 2 (move it to the top)
    put(cache, 2);
    displayCache(cache);

    // Add a new key, which causes eviction of the LRU (key 1)
    put(cache, 6);
    displayCache(cache);

    return 0;
}
