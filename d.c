#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo
struct Node {
    int data;
    struct Node* next;
};

// Función para imprimir la lista
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Función para insertar un nuevo nodo al final de la lista
void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

// Función para guardar la lista en un archivo
void saveListToFile(struct Node* head, const char* fileName) {
    FILE* file = fopen(fileName, "w");

    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    while (head != NULL) {
        fprintf(file, "%d ", head->data);
        head = head->next;
    }

    fclose(file);
}

// Función para cargar la lista desde un archivo
struct Node* loadListFromFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    struct Node* head = NULL;
    int data;

    while (fscanf(file, "%d", &data) == 1) {
        append(&head, data);
    }

    fclose(file);

    return head;
}

int main() {
    struct Node* head = NULL;
    int newData;
    char continuar;

    printf("Lista de numeros de las camisetas de las jugadoras.");
    do {
        // Solicitar información al usuario
        printf(" Ingrese numero de camiseta: ");
        scanf("%d", &newData);

        // Insertar el nuevo dato en la lista
        append(&head, newData);

        // Preguntar al usuario si quiere ingresar otro número
        printf("¿Desea ingresar otro número? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    // Imprimir la lista resultante
    printf("Lista de numeros de camisetas: ");
    printList(head);

    // Guardar la lista en un archivo
    saveListToFile(head, "lista.txt");
    printf("Lista guardada en el archivo 'lista.txt'.\n");

    // Liberar la memoria de la lista al finalizar el programa
    struct Node* current = head;
    struct Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    // Cargar la lista desde el archivo
    head = loadListFromFile("lista.txt");

    // Imprimir la lista cargada desde el archivo
    printf("Lista cargada desde el archivo: ");
    printList(head);

    // Liberar la memoria de la lista nuevamente
    current = head;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    return 0;
}
