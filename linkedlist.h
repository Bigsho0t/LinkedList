#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "../status/status.h"

typedef struct list list;

/**
 * @brief Inicializa e aloca uma nova instância de lista encadeada.
 * * Reserva memória para a estrutura de controle da lista. A função de comparação
 * é obrigatória para operações de busca e remoção.
 * * @param free_function  Opcional: Callback para desalocação dos elementos (pode ser NULL).
 * @param cmp_function   Obrigatório: Função para comparação de igualdade/ordem entre elementos.
 * @param print_function Opcional: Callback para exibição dos elementos (pode ser NULL).
 * @return
 * - `list*`: Endereço da nova instância alocada.
 * - `NULL`: Caso ocorra falha de alocação ou se `cmp_function` for nulo.
 */
list* new_list(void (*free_function)(void*), int (*cmp_function)(const void*, const void*), void (*print_function)(const void*));

/**
 * @brief Insere um novo elemento no início da lista (cabeça).
 * * @param l     Instância da lista.
 * @param value Referência do valor a ser armazenado.
 * @return
 * - `SUCCESS`: Inserção realizada com sucesso.
 * - `NULL_POINTER`: Se 'l' for nulo.
 * - `ALLOC_FAIL`: Falha ao alocar memória para o novo nó.
 */
status list_add_first(list* l, void* value);

/**
 * @brief Insere um novo elemento ao final da lista (cauda).
 * * @param l     Instância da lista.
 * @param value Referência do valor a ser armazenado.
 * @return
 * - `SUCCESS`: Inserção realizada com sucesso.
 * - `NULL_POINTER`: Se 'l' for nulo.
 * - `ALLOC_FAIL`: Falha ao alocar memória para o novo nó.
 */
status list_add_last(list* l, void* value);

/**
 * @brief Insere um novo elemento em uma posição específica via índice.
 * * @param l     Instância da lista.
 * @param value Referência do valor a ser armazenado.
 * @param index Índice de destino (base zero).
 * @return
 * - `SUCCESS`: Inserção realizada com sucesso.
 * - `OUT_OF_RANGE`: Se o índice for superior ao tamanho atual da lista.
 * - `ALLOC_FAIL`: Falha de alocação de memória para o nó.
 * - `NULL_POINTER`: Se 'l' for nulo.
 */
status list_add(list* l, void* value, size_t index);

/**
 * @brief Localiza e remove a primeira ocorrência de um valor na lista.
 * * Utiliza a 'cmp_function' configurada no `new_list` para comparar os elementos.
 * Se uma 'free_function' foi fornecida, ela será aplicada ao valor removido.
 * * @param l     Instância da lista.
 * @param value Referência do valor de busca para remoção.
 * @return
 * - `SUCCESS`: Elemento encontrado e removido com sucesso.
 * - `UNDERFLOW`: A lista está vazia.
 * - `NOT_FOUND`: O valor não foi localizado após percorrer a lista.
 * - `NULL_POINTER`: Se 'l' for nulo.
 */
status list_remove_value(list* l, const void* value);

/**
 * @brief Remove o elemento posicionado em um índice específico.
 * * @param l     Instância da lista.
 * @param index Índice do elemento a ser removido (base zero).
 * @return
 * - `SUCCESS`: Remoção realizada com sucesso.
 * - `UNDERFLOW`: A lista está vazia.
 * - `OUT_OF_RANGE`: Índice inválido para o estado atual da lista.
 * - `NULL_POINTER`: Se 'l' for nulo.
 */
status list_remove_index(list* l, size_t index);

/**
 * @brief Recupera a referência do valor em uma posição específica.
 * * @param l     Instância da lista.
 * @param index Índice do elemento desejado (base zero).
 * @return
 * - `void*`: Endereço do valor armazenado na posição.
 * - `NULL`: Se a lista for nula, o índice estiver fora de alcance ou o valor for nulo.
 */
void* list_get(const list* l, size_t index);

/**
 * @brief Verifica a existência de um valor na lista.
 * * @param l     Instância da lista.
 * @param value Referência do valor para busca.
 * @return
 * - `true`: O elemento foi localizado.
 * - `false`: O elemento não existe ou a lista está vazia/nula.
 */
bool list_contains(const list* l, const void* value);

/**
 * @brief Verifica se a lista não possui elementos.
 * * @note Esta função utiliza `assert` internamente para garantir que a
 * instância da lista seja válida em tempo de depuração.
 * * @param l Instância da lista.
 * @return
 * - `true`: Lista vazia.
 * - `false`: Lista contém um ou mais elementos.
 */
bool list_is_empty(const list* l);

/**
 * @brief Retorna a quantidade atual de elementos na lista.
 * * @note Esta função utiliza `assert` internamente para validar a instância da lista.
 * * @param l Instância da lista.
 * @return `size_t`: Número de nós presentes na estrutura.
 */
size_t list_size(const list* l);

/**
 * @brief Remove e desaloca todos os nós e valores contidos na lista.
 * * Invoca a 'free_function' para cada elemento e redefine os ponteiros
 * internos da estrutura, deixando-a pronta para reuso.
 * * @param l Instância da lista a ser limpa.
 * @return
 * - `SUCCESS`: Lista esvaziada com sucesso.
 * - `NULL_POINTER`: Se 'l' for nulo.
 */
status list_clear(list* l);

/**
 * @brief Percorre a lista e exibe seus elementos no terminal.
 * * Utiliza a 'print_function' configurada na inicialização. Se o callback
 * for nulo, a operação não irá gerar saída.
 * * @param l Instância da lista.
 */
void list_print(const list* l);

/**
 * @brief Desaloca completamente a estrutura da lista e seus recursos.
 * * Realiza a limpeza interna de todos os nós e valores antes de liberar
 * o ponteiro da estrutura principal.
 * * @param l Instância da lista a ser destruída.
 */
void list_free(list* l);