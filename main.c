#include "linkedlist.h"
#include <stdio.h>
#include <string.h>

void print_string(const void* s) {
    printf("%s", (char*)s);
}

int cmp_string(const void* a, const void* b) {

    char* s1 = (char*)a;
    char* s2 = (char*)b;

    if (s1 == s2) return 0;
    if (s1 == NULL) return -1;
    if (s2 == NULL) return 1;

    return strcmp(s1, s2);
}

int main() {

    list* lista = new_list(NULL, cmp_string, print_string);

    list_add_last(lista, "Davi");
    list_add_last(lista, "Fred");
    list_add_last(lista, "Guedes");
    list_add_last(lista, "Miguel");
    list_add_last(lista, "Matheus");
    list_add_first(lista, NULL);
    list_add(lista, "Vazio", 2);
    list_remove_index(lista, 2);
    list_remove_value(lista, NULL);
    list_get(lista, 0);
    list_size(lista);
    list_contains(lista, NULL);
    list_print(lista);
    list_free(lista);

    return 0;
}