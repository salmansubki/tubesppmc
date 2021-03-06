#include "konfigurasi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initializeArrKata(arrKata *ptr) {
  ptr->array = NULL;
  ptr->next = NULL;
  ptr->length = 0;
}

void printArrKata(arrKata arr_kata) {
  printf("[");
  for (int i = 0; i < arr_kata.length; i++) {
    if (i) printf(", ");
    printf("\"%s\"", arr_kata.array[i]);
  }
  printf("]\n");
}

void pushArrKata(arrKata *arr_kata, char *kata){
  // printf("%d -> ", arr_kata->length);
  arr_kata->length = arr_kata->length + 1;
  arr_kata->array = realloc(arr_kata->array, arr_kata->length * sizeof(char*));
  arr_kata->array[arr_kata->length-1] = strdup(kata);
  // printf("%d\n", arr_kata->length);
}

void deleteHeadArrKata (arrKata *arr_kata) {
  arr_kata->length--;
  char *temp = arr_kata->array[0];
  memmove(arr_kata->array, arr_kata->array+1, arr_kata->length*sizeof(char*));
}


void freeArrKata(arrKata *arr_kata) {
  free(arr_kata->array);
}


void printKey(arrKata dict, int n) {
  dict.length = n;
  printArrKata(dict);
}

void printValue(arrKata dict, int n) {
  dict.length = dict.length - n;
  dict.array = &dict.array[n];
  printArrKata(dict);
}

void initializeDictionary(arrKata *dict) {
    dict = NULL;
}

void printDictionary(arrKata dict, int n) {
  arrKata *current = &dict;
  int i = 1;
  while (current->next != NULL){
    printf("row %d\n", i);
    printf("key\t= ");
    printKey(*current, n);
    printf("value\t= ");
    printValue(*current, n);
    current = current->next;
    i++;
  }
  printf("row %d\n", i);
  printf("key\t= ");
  printKey(*current, n);
  printf("value\t= ");
  printValue(*current, n);
}

int compareKey(arrKata dict1, arrKata dict2, int n) {
  // true if same
  for (int i = 0; i < n; i++)
    if ( strcmp(dict1.array[i], dict2.array[i]) )
      return 0;
  return 1;
}

int wordUnique(arrKata dict, char *word, int n) {
  for (int i = 0; i < dict.length - n; i++) {
    if ( !strcmp(dict.array[n + i], word ) )
      return 0;
  }
  return 1;
}

void pushDictionary(arrKata **dict, arrKata *key, char *value, int n) {
    arrKata* new_node = (arrKata*) malloc(sizeof(arrKata*));
    initializeArrKata(new_node);

    for (int i = 0; i < key->length; i++) {
      pushArrKata(new_node, key->array[i]);
    }

    pushArrKata(new_node, value);

    if (*dict == NULL) {
       *dict = new_node;
       return;
    }


    arrKata *current = *dict;
    while (current->next != NULL) {
      if ( compareKey(*current, *new_node, n) ) {
        if ( wordUnique(*current, value, n) )
          pushArrKata(current, value);
          freeArrKata(new_node);
          free(new_node);
        return;
      }
      current = current->next;
    }
    if ( compareKey(*current, *new_node, n) ) {
      if ( wordUnique(*current, value, n) )
        pushArrKata(current, value);
        freeArrKata(new_node);
        free(new_node);
      return;
    }

    current->next = new_node;
    return;
}

void freeDictionary(arrKata *dict) {
  if (dict->next != NULL) freeDictionary(dict->next);
  freeArrKata(dict);
}

int getDictionaryLength (arrKata *dict) {
  if (dict == NULL) return 0;
  return 1 + getDictionaryLength(dict->next);
}

arrKata peekDictionary(arrKata *dict, int i) {
  if (i == 0) return *dict;
  else return peekDictionary(dict->next, i - 1);
}
