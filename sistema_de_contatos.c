#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 50
#define MAX_CONTACTS 75

typedef struct Contact {
    char name[50];
    char phone[20];
    char email[30];
    struct Contact *next;
} Contact;

typedef struct HashTable {
    Contact *table[HASH_SIZE];
} HashTable;


unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASH_SIZE;
}
