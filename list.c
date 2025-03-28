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
        nuevo->next = list->head;
        list->head->prev = nuevo;
    }
    if(list->tail == NULL){
        list->tail = nuevo;
    }
    list->head = nuevo;
}

void pushBack(List * list, void * data) {
    Node* nuevo = createNode(data);
    if (list->tail != NULL){
        nuevo->next = list->tail;
        list->tail->prev = nuevo;
    }
    if(list->head == NULL){
        list->head = nuevo;
    }
    list->tail = nuevo;
}

void pushCurrent(List * list, void * data) {
    Node* nuevo = createNode(data);
    nuevo->prev = list->current;
    nuevo->next = list->current->next;
    if (list->current->next != NULL){
        list->current->next->prev = nuevo;
    }else{
        list->tail = nuevo;
    } 
    list->current->next = nuevo;
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
    if(list->current == NULL) return NULL;
        
    Node *eliminar = list->current;
    void *num = eliminar->data;
    
    if(list->head == eliminar && list->tail == eliminar) {
            list->head = NULL;
            list->tail = NULL;
            list->current = NULL;
    }
    else if(list->head == eliminar) {
            list->head = eliminar->next;
            list->head->prev = NULL;
            list->current = list->head;
    }
    else if(list->tail == eliminar) {
            list->tail = eliminar->prev;
            list->tail->next = NULL;
            list->current = NULL;
    }
    else {
            eliminar->prev->next = eliminar->next;
            eliminar->next->prev = eliminar->prev;
            list->current = eliminar->next;
    }
    
    free(eliminar);
    return num;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}