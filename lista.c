#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Função para inicializar a lista
void inicializaLista(Lista* l) 
{
    l->head = NULL;
    l->tail = NULL;
}

// Função para inserir um novo elemento (x, y) no início da lista
void insereInicio(Lista* l, int x, int y) 
{
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (!novoNo) 
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->x = x;
    novoNo->y = y;
    novoNo->next = l->head;
    novoNo->prev = NULL;

    if (l->head == NULL) 
    {  // Lista vazia
        l->tail = novoNo;
    } 
    
    else 
    {
        l->head->prev = novoNo;
    }
    l->head = novoNo;
}

// Função para inserir um novo elemento (x, y) no final da lista
void insereFim(Lista* l, int x, int y) 
{
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (!novoNo) 
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->x = x;
    novoNo->y = y;
    novoNo->next = NULL;
    novoNo->prev = l->tail;

    if (l->tail == NULL) 
    {  // Lista vazia
        l->head = novoNo;
    } 
    
    else 
    {
        l->tail->next = novoNo;
    }
    l->tail = novoNo;
}

// Função para remover o primeiro elemento da lista e retornar seus valores
int removeInicio(Lista* l, int* x, int* y) 
{
    if (listaVazia(l)) 
    {
        printf("Lista vazia.\n");
        return 0;  // Falha
    }
    Node* temp = l->head;
    *x = temp->x;
    *y = temp->y;

    l->head = l->head->next;
    if (l->head == NULL) 
    {  // Se a lista ficou vazia
        l->tail = NULL;
    } 
    
    else 
    {
        l->head->prev = NULL;
    }

    free(temp);
    return 1;  // Sucesso
}

// Função para remover o último elemento da lista e retornar seus valores
int removeFim(Lista* l, int* x, int* y) 
{
    if (listaVazia(l)) 
    {
        printf("Lista vazia.\n");
        return 0;  // Falha
    }

    Node* temp = l->tail;
    *x = temp->x;
    *y = temp->y;

    l->tail = l->tail->prev;
    if (l->tail == NULL) 
    {  // Se a lista ficou vazia
        l->head = NULL;
    } 
    
    else 
    {
        l->tail->next = NULL;
    }

    free(temp);
    return 1;  // Sucesso
}

// Função para verificar se a lista está vazia
int listaVazia(Lista* l) 
{
    return (l->head == NULL);
}

// Função para liberar a memória ocupada pela lista
void liberaLista(Lista* l) 
{
    int x, y;
    while (!listaVazia(l)) 
    {
        removeInicio(l, &x, &y);
    }
}

// Função para obter o valor do primeiro elemento da lista (sem removê-lo)
int getInicio(Lista* l, int* x, int* y) 
{
    if (listaVazia(l)) 
    {
        printf("Lista vazia.\n");
        return 0;  // Falha
    }
    *x = l->head->x;
    *y = l->head->y;
    return 1;  // Sucesso
}

// Função para obter o valor do último elemento da lista (sem removê-lo)
int getFim(Lista* l, int* x, int* y) 
{
    if (listaVazia(l)) 
    {
        printf("Lista vazia.\n");
        return 0;  // Falha
    }
    *x = l->tail->x;
    *y = l->tail->y;
    return 1;  // Sucesso
}

void setFim(Lista* l, int x, int y) 
{
    l->tail->x = x;
    l->tail->y = y;
}
