#ifndef LISTA_H
#define LISTA_H

// Estrutura para o nó da lista duplamente encadeada
typedef struct Node {
    int x;
    int y;
    struct Node* next;
    struct Node* prev;
} Node;

// Estrutura para a lista
typedef struct {
    Node* head;  // Aponta para o primeiro nó da lista
    Node* tail;  // Aponta para o último nó da lista
} Lista;

// Função para inicializar a lista
void inicializaLista(Lista* l);

// Função para inserir um novo elemento (x, y) no início da lista
void insereInicio(Lista* l, int x, int y);

// Função para inserir um novo elemento (x, y) no final da lista
void insereFim(Lista* l, int x, int y);

// Função para remover o primeiro elemento da lista e retornar seus valores
int removeInicio(Lista* l, int* x, int* y);

// Função para remover o último elemento da lista e retornar seus valores
int removeFim(Lista* l, int* x, int* y);

// Função para verificar se a lista está vazia
int listaVazia(Lista* l);

// Função para liberar a memória ocupada pela lista
void liberaLista(Lista* l);

// Função para obter o valor do primeiro elemento da lista (sem removê-lo)
int getInicio(Lista* l, int* x, int* y);

// Função para obter o valor do último elemento da lista (sem removê-lo)
int getFim(Lista* l, int* x, int* y);

// Função para setar o valor do último elemento da lista (sem removê-lo)
void setFim(Lista* l, int x, int y);

#endif