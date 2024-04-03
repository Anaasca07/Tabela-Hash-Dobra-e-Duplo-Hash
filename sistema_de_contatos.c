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

int concatenacao(char c[]) {
    int key = 0, i = 0;
    while (c[i] != '\0') {
        key += c[i];
        i++;
    }
    return key % HASH_SIZE;
}

void insertContact(HashTable *hashTable, Contact *contato) {
    unsigned int index = hash(contato->name);

    Contact *newContact = (Contact *)malloc(sizeof(Contact));
    if (newContact == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        return;
    }
 *newContact = *contato;
    newContact->next = hashTable->table[index];
    hashTable->table[index] = newContact;
}


Contact *searchContact(HashTable *hashTable, const char *name) {
    unsigned int index = hash(name);
    Contact *current = hashTable->table[index];

    while (current != NULL) {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }

    return NULL;
}

void printContacts(HashTable *hashTable) {
    printf("Contacts:\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        Contact *current = hashTable->table[i];
        while (current != NULL) {
            printf("name: %s, phone: %s\n", current->name, current->phone);
            current = current->next;
        }
    }
}

void ler_arquivo(HashTable *hashTable) {
    FILE *arquivo;
    Contact *contatos;
    int count = 0;

    arquivo = fopen("todosOsContatos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro: falha ao abrir o arquivo.\n");
        exit(1);
    }
