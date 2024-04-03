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
    char linha[200];

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (count >= HASH_SIZE * 0.25 && count < HASH_SIZE * 0.75) {

            if (contatos == NULL) {
                printf("Erro: falha na alocação de memória.\n");
                exit(1);
            }

            int tamanho = strcspn(linha, "\n");
            linha[tamanho] = '\0';

            Contact newContact;

            sscanf(linha, "%s %s %s", newContact.name, newContact.email, newContact.phone);

            insertContact(hashTable,&newContact);
            
            contatos = realloc(contatos, sizeof(Contact) * (count + 1));
            if (contatos == NULL) {
                printf("Erro: falha na alocação de memória.\n");
                exit(1);
            }
            contatos[count] = newContact;

            count++;
        }
    }

    fclose(arquivo);
}

int main() {
    HashTable hashTable;
    int option;
    Contact contato;

    for (int i = 0; i < HASH_SIZE; i++)
        hashTable.table[i] = NULL;

    ler_arquivo(&hashTable);

    strcpy(contato.name, "Joao");
    strcpy(contato.phone, "123456789");
    insertContact(&hashTable, &contato);

    strcpy(contato.name, "Maria");
    strcpy(contato.phone, "987654321");
    insertContact(&hashTable, &contato);

   do {
      printf("\nMenu:\n");
        printf("1. Inserir Contact\n");
        printf("2. Buscar Contact\n");
        printf("3. Imprimir Contacts\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Digite o name do Contact: ");
                scanf("%s", contato.name);
                printf("Digite o phone do Contact: ");
                scanf("%s", contato.phone);

                insertContact(&hashTable, &contato);

                break;
            case 2:
                printf("Digite o name do Contact que deseja buscar: ");
                scanf("%s", contato.name);
                Contact *result = searchContact(&hashTable, contato.name);
                if (result != NULL)
                    printf("phone de %s: %s\n", contato.name, result->phone);
                else
                    printf("Contact não encontrado.\n");
                break;
            case 3:
                printContacts(&hashTable);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (option != 4);

    return 0;
}
