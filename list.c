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

List* createList(){
  List* nuevo = (List*) calloc(1, sizeof(List));
  return nuevo;
}

void * firstList(List * list) {
  list->current =  list->head;
  if(list->head == NULL) return NULL;
  else return list-> head -> data;
}

void * nextList(List * list) {
  if(list->current==NULL) return NULL;
  
  list -> current = list->current->next;

  if(list->current==NULL)  return NULL;
  else return list->current->data;
}

void * lastList(List * list) {

  list->current = list->tail;
  if(list->tail == NULL) return NULL;
  else return list->tail->data;
}

void * prevList(List * list) {
  if(list->current == NULL) return NULL;
  list -> current = list->current->prev;
  if(list->current==NULL) return NULL;
  else return list->current->data;
}

void pushFront(List * list, void * data) {

  Node* nuevo =createNode(data);
  
  if(list -> head == NULL){
    list -> tail = list->head = list->current = nuevo;
  }else{
    nuevo->next =  list->head;
    list->head = nuevo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node* nuevo =createNode(data);

  if(list->current==NULL){
    list -> tail = list->head = list->current = nuevo;  
  }else{
    nuevo->prev = list->current;
    nuevo->next = list->current->next;
    if(list->current->next != NULL) list->current->next->prev = nuevo;
    else list->tail = nuevo;
    list->current->next = nuevo;
  } 
  
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

  void* datito = list-> current->data;

  if(list->current->prev == NULL && list->current->next == NULL){
    free(list->current);
    list -> tail = list->head = list->current = NULL;
  }else if(list->current->prev == NULL){

    list->head = list->current->next;
    list->current->next->prev = NULL;
    free(list->current);
    
  }else if(list->current->next == NULL){
    list->tail = list->current->prev;
    list->current->prev->next = NULL;
    free(list->current);
  }else{
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    free(list->current);
  }

  return datito;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}