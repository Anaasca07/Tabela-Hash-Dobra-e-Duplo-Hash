#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 50
#define MAX_CONTACTS 75

// Estrutura para armazenar um Contact
typedef struct Contact {
    char name[50];
    char phone[20];
    char email[30];
    struct Contact *next;
} Contact;
