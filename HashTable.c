/*
 * HashTable.c
 *
 *  Created on: Nov 29, 2018
 *      Author: Merav 205795537, Yiftach 312141369
 */
#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"

struct hashTable_s
{
	copyFunction copyKey;
	freeFunction freeKey;
	printFunction printKey;
	copyFunction copyValue;
	freeFunction freeValue;
	printFunction printValue;
	equalFunction equalKey;
	transformIntoNumberFunction transformKeyIntoNumber;
	int hashNumber;
	LinkedList *table;
};

hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey, copyFunction copyValue, freeFunction freeValue, printFunction printValue, equalFunction equalKey, transformIntoNumberFunction transformKeyIntoNumber, int hashNumber)
{
	hashTable newHashTable=(hashTable)malloc(sizeof(struct hashTable_s));
	if( newHashTable == NULL)
	{
		return NULL;
	}
	else
	{
		newHashTable->copyKey=copyKey;
		newHashTable->freeKey=freeKey;
		newHashTable->printKey=printKey;
		newHashTable->copyValue=copyValue;
		newHashTable->freeValue=freeValue;
		newHashTable->printValue=printValue;
		newHashTable->equalKey=equalKey;
		newHashTable->transformKeyIntoNumber=transformKeyIntoNumber;
		newHashTable->hashNumber=hashNumber;

		newHashTable->table = (LinkedList*)malloc(sizeof(LinkedList) * hashNumber);
		if(newHashTable->table == NULL)
		{
			free(newHashTable);
			return NULL;
		}

		int i=0;
		while(i < newHashTable->hashNumber)
		{
			newHashTable->table[i]=NULL;
			i++;
		}

	}
	return newHashTable;
}

static int getAddress(hashTable table, Element key)
{
	int keyValue=table->transformKeyIntoNumber(key);
	int address=keyValue % table->hashNumber;
	return address;
}

status destroyHashTable(hashTable table)
{
	if(table == NULL)
	{
		return failure;
	}
	int counter=0;
	while(counter < table->hashNumber)
	{
		if(table->table[counter] != NULL)
		{
			destroyList((table->table[counter]));
		}
		counter++;
	}
	free(table->table);
	free(table);
	return success;
}


status addToHashTable(hashTable table, Element key,Element value)
{
	if(table == NULL || key == NULL || value == NULL)
	{
		return failure;
	}
	if(lookupInHashTable(table,key) != NULL)
	{
		return failure;
	}
	else
	{
		KeyValuePair newKeyValuePair = createKeyValuePair(key, value, table->copyKey, table->copyValue, table->freeKey, table->freeValue, table->printKey, table->printValue, table->transformKeyIntoNumber, table->equalKey);
		if(newKeyValuePair == NULL)
		{
			return failure;
		}
		int address=getAddress(table , key);
		if(table->table[address] == NULL)
		{
			table->table[address] = createLinkedList(copyKeyValuePair,destroyKeyValuePair, printKeyValuePair, table->equalKey);
			if (table->table[address] == NULL)
			{
				destroyKeyValuePair(newKeyValuePair);
				return failure;
			}
			appendNode(table->table[address], newKeyValuePair);
			destroyKeyValuePair(newKeyValuePair);

		}
		else
		{
			appendNode(table->table[address],newKeyValuePair);
			destroyKeyValuePair(newKeyValuePair);
		}
	}
	return success;
}

Element lookupInHashTable(hashTable table, Element key)
{
	if(table == NULL || key == NULL)
	{
		return NULL;
	}
	int address=getAddress(table , key);
	if(table->table[address] == NULL)
	{
		return NULL;
	}
	else
	{
		return searchInList(table->table[address], key);
	}
}

status removeFromHashTable(hashTable table, Element key)
{
	if( table == NULL || key == NULL)
	{
		return failure;
	}
	int address=getAddress(table , key);
	if(table->table[address] == NULL)
	{
		return failure; //element is not in the table
	}
	else
	{
		if( deleteNode(table->table[address], key) == success)
		{
			if(getNumberOfNodes(table->table[address]) == 0)
			{
				deleteNode(table->table[address], key);
			}
			return success;
		}
		return failure;
	}
}

status displayHashElements(hashTable table)
{
	if(table == NULL)
	{
		return failure;
	}
	int counter=0;
	while(counter < table->hashNumber)
	{
		if(table->table[counter] != NULL)
		{
			displayList((table->table[counter]));
		}
		counter++;
	}
	return success;
}
