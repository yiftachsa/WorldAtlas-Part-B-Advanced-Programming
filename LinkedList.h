/*
 * LinkedList.h
 *
 *  Created on: Nov 29, 2018
 *      Author: Merav 205795537, Yiftach 312141369
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Defs.h"

typedef struct t_LinkedList *LinkedList;
typedef struct t_Node *Node;

LinkedList createLinkedList (copyFunction copyElementF, freeFunction freeElementF, printFunction printElementF, equalFunction isEqualElementF); //transformIntoNumber???
status destroyList (LinkedList);
status appendNode (LinkedList, Element);
status deleteNode (LinkedList, Element);
void displayList (LinkedList);
Element searchInList (LinkedList, Element);
int getNumberOfNodes(LinkedList);

#endif /* LINKEDLIST_H_ */
