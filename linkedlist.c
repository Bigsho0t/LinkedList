#include "linkedlist.h"
#include "../node/node.h"
#include <stdlib.h>
#include <assert.h>

typedef struct list {
    node* head;
    node* tail;
    size_t size;
    void (*free_function)(void*);
    int (*cmp_function)(const void*, const void*);
    void (*print_function)(const void*);
} list;

list* new_list(void (*free_function)(void*), int (*cmp_function)(const void*, const void*), void (*print_function)(const void*)) {

    if (cmp_function == NULL) {
        return NULL;
    }

    list* l = malloc(sizeof(*l));

    if (l == NULL) {
        return NULL;
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    l->free_function = free_function;
    l->cmp_function = cmp_function;
    l->print_function = print_function;

    return l;
}

status list_add_first(list* l, void* value) {

    if (l == NULL) {
        return NULL_POINTER;
    }

    node* n = new_node(value);

    if (n == NULL) {
        return ALLOC_FAIL;
    }

    if (l->size == 0) {
        l->head = l->tail = n;
    }

    else {
        n->next = l->head;
        l->head = n;
    }

    l->size++;

    return SUCCESS;
}

status list_add_last(list* l, void* value) {

    if (l == NULL) {
        return NULL_POINTER;
    }

    node* n = new_node(value);

    if (n == NULL) {
        return ALLOC_FAIL;
    }

    if (l->size == 0) {
        l->head = l->tail = n;
    }

    else {
        l->tail->next = n;
        l->tail = n;
    }

    l->size++;

    return SUCCESS;
}

status list_add(list* l, void* value, size_t index) {

    if (l == NULL) {
        return NULL_POINTER;
    }

    if (index > l->size) {
        return OUT_OF_RANGE;
    }

    if (index == 0) {
        return list_add_first(l, value);
    }

    if (index == l->size) {
        return list_add_last(l, value);
    }

    node* n = new_node(value);

    if (n == NULL) {
        return ALLOC_FAIL;
    }

    node* current = l->head;

    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }

    n->next = current->next;
    current->next = n;
    l->size++;

    return SUCCESS;
}

static void list_remove_node(list* l, node* current, node* previous) {
    if (current == l->head) {
        l->head = current->next;
    } else {
        previous->next = current->next;
    }

    if (current == l->tail) { 
        l->tail = previous;
    }
}

status list_remove_value(list* l, const void* value) {

    if (l == NULL) {
        return NULL_POINTER;
    }

    if (l->size == 0) {
        return UNDERFLOW;
    }

    node* current = l->head;
    node* previous = NULL;

    while (current != NULL && l->cmp_function(current->value, value) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return NOT_FOUND;
    }

    list_remove_node(l, current, previous);

    if (l->free_function != NULL && current->value != NULL) {
        l->free_function(current->value);
    }

    free(current);
    l->size--;

    return SUCCESS;
}

status list_remove_index(list* l, size_t index) {

    if (l == NULL) {
        return NULL_POINTER;
    }

    if (l->size == 0) {
        return UNDERFLOW;
    }

    if (index >= l->size) {
        return OUT_OF_RANGE;
    }

    node* current = l->head;
    node* previous = NULL;

    for (size_t i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }   

    list_remove_node(l, current, previous);

    if (l->free_function != NULL && current->value != NULL) {
        l->free_function(current->value);
    }

    free(current);
    l->size--;

    return SUCCESS;
}

void* list_get(const list* l, size_t index) {

    if (l == NULL || index >= l->size) {
        return NULL;
    }

    node* current = l->head;

    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    return current->value;
}

bool list_contains(const list* l, const void* value) {
    
    assert(l != NULL);

    node* current = l->head;

    while (current != NULL) {
        if (l->cmp_function(current->value, value) == 0) {
            return true;
        }
        current = current->next;
    }

    return false;
}

bool list_is_empty(const list* l) {
    assert(l != NULL);
    return l->size == 0;
}

size_t list_size(const list* l) {
    assert(l != NULL);
    return l->size;
}

status list_clear(list* l) {

    if (l == NULL) {
        return NULL_POINTER;
    }

    node* current = l->head;

    while (current != NULL) {

        node* next = current->next;

        if (l->free_function != NULL && current->value != NULL) {
            l->free_function(current->value);
        }

        free(current);
        current = next;
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;

    return SUCCESS;
}

void list_print(const list* l) {

    if (l == NULL || l->print_function == NULL) {
        return;
    }

    node* current = l->head;

    printf("[");

    while (current != NULL) {

        l->print_function(current->value);
        if (current->next != NULL) printf(", ");
        current = current->next;
    }

    printf("]");
}

void list_free(list* l) {

    if (l == NULL) return;
    list_clear(l);
    free(l);
}