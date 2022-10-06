/*
 * LinkedList.c
 *
 *  Created on: Nov 29, 2018
 *      Author: Merav 205795537, Yiftach 312141369
 */

#include "LinkedList.h"
#include "KeyValuePair.h"

struct t_LinkedList
{
	Node head;
	Node tail;
	int numberOfNodes;
	copyFunction copyElement;
	freeFunction freeElement;
	printFunction printElement;
	equalFunction isEqualElement;
};

struct t_Node
{
	Element value;
	Node next;
};

LinkedList createLinkedList (copyFunction copyElementF, freeFunction freeElementF, printFunction printElementF, equalFunction isEqualElementF)
{
	LinkedList newLinkedList = (LinkedList)malloc(sizeof(struct t_LinkedList));
	if (newLinkedList == NULL)
	{
		return NULL;
	}
	newLinkedList->head = NULL;
	newLinkedList->tail = NULL;
	newLinkedList->numberOfNodes = 0;
	newLinkedList->copyElement = copyElementF;
	newLinkedList->freeElement = freeElementF;
	newLinkedList->printElement = printElementF;
	newLinkedList->isEqualElement = isEqualElementF;
	return newLinkedList;
}


static Node createNode (Element elementToAdd, copyFunction copyFunctionF)
{
	if (elementToAdd == NULL)
	{
		return NULL;
	}
	Node newNode = (Node)malloc(sizeof(struct t_Node));
	if (newNode == NULL)
	{
		return NULL;
	}
	Element newElement = copyFunctionF(elementToAdd);
	if (newElement == NULL)
	{
		free(newNode);
		return NULL;
	}
	newNode->value = newElement;
	newNode->next = NULL;
	return newNode;
}

static status freeNode (Node nodeToDelete, freeFunction freeFunctionF)
{
	if (freeFunctionF == NULL){
		return failure;
	}
	if (nodeToDelete != NULL)
	{
		freeFunctionF(nodeToDelete->value);
		free(nodeToDelete);
	}
	return success;
}

status destroyList (LinkedList toDelete)
{
	if(toDelete == NULL){
		return success;
	}
	int counter = toDelete->numberOfNodes;
	while (counter > 0)
	{
		Node temp = toDelete->head->next;
		freeNode(toDelete->head, toDelete->freeElement);
		toDelete->head = temp;
		counter--;
	}
	free(toDelete);
	return success;
}
status appendNode (LinkedList listToAddTo, Element elementToAdd)
{
	if(listToAddTo == NULL || elementToAdd == NULL)
	{
		return failure;
	}

	Node newNode = createNode (elementToAdd, listToAddTo->copyElement); //next=Null
	if (newNode == NULL)
	{
		return failure;
	}
	if(listToAddTo->numberOfNodes == 0)
	{
		listToAddTo->head=newNode;
		listToAddTo->tail=newNode;
		listToAddTo->numberOfNodes++;
	}

	else
	{
		listToAddTo->tail->next = newNode;
		listToAddTo->tail = newNode;
		listToAddTo->numberOfNodes++;
	}
	return success;
}

status deleteNode (LinkedList list, Element element)
{
	if (list == NULL || element == NULL || list->numberOfNodes == 0)
	{
		return failure;
	}
	int i;
	Node current = list->head;
	Node previous = list->head;
	if(list->isEqualElement(getKey((KeyValuePair)current->value),element) == true)
	{
		Node temp = current->next;
		freeNode(list->head, list->freeElement);
		list->head = temp;
		list->numberOfNodes--;
		return success;
	}
	current = current->next;
	for (i=0; i<list->numberOfNodes; i++)
	{
		if(list->isEqualElement(getKey((KeyValuePair)current->value),element) == true)
		{
			previous->next = current->next;
			freeNode(current, list->freeElement);
			list->numberOfNodes--;
			return success;
		}
		previous = previous->next;
		current = current->next;
	}
	return failure;
}
void displayList (LinkedList list)
{
	if (list != NULL)
	{
		Node current = list->head;
		int i;
		for (i=0; i<list->numberOfNodes; i++){
			list->printElement(current->value);
			current = current->next;
		}
	}
}
Element searchInList (LinkedList list, Element elementToSearch)//elementTosearch must be key
{
	if(list == NULL || elementToSearch == NULL)
	{
		return NULL;
	}
	int i;
	Node current = list->head;
	for (i=0; i<list->numberOfNodes; i++)
	{
		char *get_key = getKey((KeyValuePair)current->value);
		if(list->isEqualElement(get_key,elementToSearch) == true)
		{
			return getValue((KeyValuePair)current->value);
		}
		current = current->next;
	}
	return NULL;
}

int getNumberOfNodes(LinkedList list)
{
	return list->numberOfNodes;
}
