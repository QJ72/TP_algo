/**
 * @file list.c
 * @brief Implementation file for a linked list
 *
 * This file contains the implementation of the linked list data structure
 * and its associated functions.
 *
 * @author Loïck Lhote
 * @date February 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * @brief Creates a new linked list
 *
 * @return A pointer to the newly created linked list
 */
List newList() {
    return NULL;
}

/**
 * @brief Frees the memory used by a linked list
 *
 * @param L Pointer to the linked list to be freed
 */
void freeList(List L) {
	if (L != NULL){
		freeList(L->nextCell);
		free(L->key);
		free(L);
	}
    return;
}

/**
 * @brief Prints the contents of a linked list
 *
 * @param L Pointer to the linked list to be printed
 * @param type If type==0, prints only the values, otherwise print the couples (key,value)
 *
 * Prints the linked list in the following way if k!=0:
 * [(key 1, value 1),(key 2, value 2), … ,(key k, value k)]
 * Prints the linked list in the following way if k==0:
 * [value 1,value 2,…,value k]
 */

void printList(List L, int type) {
	List current = L;
	if (L==NULL){
		printf("[]");
	} else {
		printf("[");
		if (type == 0){
			while (current != NULL){
				printf("%d", current->value);
				if (current->nextCell != NULL){printf(",");}
				current = current->nextCell;
			}
		} else {
			while (current != NULL){
				printf("(%s,%d)", current->key, current->value);
				if (current->nextCell != NULL){printf(",");}
				current = current->nextCell;
			}
		}
		printf("]");
	}
    return;
}

/**
 * @brief Finds a key in a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to search for
 *
 * @return A pointer to the first cell containing the key, or NULL if the key is not found
 */
Cell* findKeyInList(List L, string key) {
	List current = L  ;
	while (current != NULL){
		if (key == NULL){
			if (current->key == key ){
				return current ;
			} else {
				current = current->nextCell ;
			}
		} else {
			if (current->key == NULL){
				current = current->nextCell;
			} else {
				if (strcmp(current->key,key)==0){
					return current;
				}
				else {
					current = current->nextCell;
				}
			}
		}
	}
    return NULL;
}

int isEqualKey(string key1, string key2){
	if (key1 == NULL){
		if (key2 == NULL){
			return 1;
		}else {
			return 0;
		}
	} else {
		if (key2 == NULL){
			return 0;
		}
		else{
			if (strcmp(key1,key2) == 0){
				return 1;
			}
			else {
				return 0;
			}
		}
	}
}

/**
 * @brief Deletes a key from a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to delete
 *
 * @return A pointer to the modified linked list
 * Only the first occurrence of the key is deleted.
 */
List delKeyInList(List L, string key) {
	if (L == NULL){return L;}
	if (isEqualKey(L->key,key)){
		List temp = L->nextCell;
		if (key != NULL){
			free(L->key);
		}
        free(L);
		L = NULL;
        return temp;
	}
	List current = L;
	while(current->nextCell != NULL){
		if (isEqualKey(current->nextCell->key, key)) {
            List temp = current->nextCell;
            current->nextCell = current->nextCell->nextCell;
			if (temp->key != NULL){
				free(temp->key);
			}
            free(temp);
			temp = NULL;
            return L;
        }
        current = current->nextCell;
    }
    return L;
}

/**
 * @brief Adds a key-value pair to a linked list
 *
 * @param L Pointer to the linked list to add to
 * @param key Key to add
 * @param value Value to add
 *
 * @return A pointer to the modified linked list
 *
 * The key-value pair is added at the beginning of the list
 */

 List addKeyValueInList(List L, string key, int value) {
	List temp = NULL;
	temp = (List)calloc(1,sizeof(Cell));
	temp->value = value;
	temp->key = NULL;
	temp->nextCell = NULL;
	if (key != NULL){
		temp->key= (string)calloc(strlen(key)+1,sizeof(char));
		strcpy(temp->key,key);
	}
	if (L != NULL){
		temp->nextCell = L;
	}
    return temp;
}


