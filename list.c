#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* nuevaLista = (List *)malloc(sizeof(List));;
    nuevaLista->tail = NULL;
    nuevaLista->head = NULL;
    nuevaLista->current = NULL;

    return nuevaLista;
}

void * firstList(List * list) {
    if (list->current == NULL) return NULL;
    list->current = list->head;
    return (list->current->data);
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return (list->current->data);
}

void * lastList(List * list) {
    if(list->tail == NULL) return NULL;
    list->current = list->tail;

    return list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return (list->current->data);
}

void pushFront(List * list, void * data) {
    Node* nuevo = createNode(data);
    if (list->head != NULL){
        list->head->prev = nuevo;
        nuevo->next = list->head;
    }
    list->head = nuevo;
}

void pushBack(List * list, void * data) {
    Node* nuevo = createNode(data);
    if (list->tail != NULL){
        list->tail->prev = nuevo;
        nuevo->next = list->tail;
    }
    list->tail = nuevo;
}

void pushCurrent(List * list, void * data) {
    Node* nuevo = createNode(data);
    Node* prox = list->current->next;
    list->current->next = nuevo;
    prox->prev = nuevo;
    nuevo->prev = list->current;
    nuevo->next = prox;
    list->current = nuevo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}