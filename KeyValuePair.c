/*
 * KeyValuePair.c
 *
 *  Created on: Nov 29, 2018
 *      Author: Merav 205795537, Yiftach 312141369
 */

#include "KeyValuePair.h"


struct t_KeyValuePair
{
	Element key;
	Element value;
	copyFunction copyKey;
	copyFunction copyValue;
	copyFunction copyPair;
	freeFunction freeKey;
	freeFunction freeValue;
	printFunction printKey;
	printFunction printValue;
	printFunction printPair;
	transformIntoNumberFunction transformIntoNumberKey;
	equalFunction equalKey;

};

KeyValuePair createKeyValuePair (Element eKey, Element eValue, copyFunction copyKeyF, copyFunction copyValueF, freeFunction freeKeyF, freeFunction freeValueF , printFunction printKeyF , printFunction printValueF , transformIntoNumberFunction transformIntoNumberKeyF , equalFunction equalKeyF)
{
	KeyValuePair newPair = (KeyValuePair)malloc(sizeof(struct t_KeyValuePair));
	if (newPair == NULL)
	{
		return NULL;
	}
	Element newKeyCopy = copyKeyF(eKey);
	if (newKeyCopy == NULL)
	{
		free(newPair);
		return NULL;
	}
	Element newValueCopy = copyValueF(eValue);
	if (newValueCopy == NULL)
	{
		free(newPair);
		freeKeyF(newKeyCopy);
		return NULL;
	}
	newPair->key = newKeyCopy;
	newPair->value = newValueCopy;
	newPair->copyKey = copyKeyF;
	newPair->copyValue = copyValueF;
	newPair->freeKey = freeKeyF;
	newPair->freeValue = freeValueF;
	newPair->printKey = printKeyF;
	newPair->printValue = printValueF;
	newPair->transformIntoNumberKey = transformIntoNumberKeyF;
	newPair->equalKey = equalKeyF;

	return newPair;
}

status destroyKeyValuePair(Element toDelete)
{
	if(toDelete == NULL){
		return success;
	}
	if (((KeyValuePair)toDelete)->freeKey(((KeyValuePair)toDelete)->key) == success && ((KeyValuePair)toDelete)->freeValue(((KeyValuePair)toDelete)->value) == success)
	{
		free((KeyValuePair)toDelete);
		return success;
	}
	return failure;
}

void displayValue(KeyValuePair toDisplay)
{
	if (toDisplay != NULL)
	{
		toDisplay->printValue(toDisplay->value);
	}
}

void displayKey(KeyValuePair toDisplay)
{
	if (toDisplay != NULL)
	{
		toDisplay->printKey(toDisplay->key);
	}
}

Element getValue(KeyValuePair toGet)
{
	if (toGet == NULL)
	{
		return NULL;
	}

	return toGet->value;
}

Element getKey(KeyValuePair toGet)
{
	if (toGet == NULL)
	{
		return NULL;
	}

	return toGet->key;
}

bool isEqualKey(Element pair1,Element pair2)
{
	if ( pair1 == NULL || pair2 == NULL)
	{
		return false;
	}
	if (((KeyValuePair)pair1)->equalKey != ((KeyValuePair)pair2)->equalKey) //are the pairs keys are of the same type.
	{
		return false;
	}
	if (((KeyValuePair)pair1)->equalKey(((KeyValuePair)pair1)->key, ((KeyValuePair)pair2)->key) != true)
	{
		return false;
	}
	return true;
}

Element copyKeyValuePair(Element keyValuePairToCopy)
{
	if(keyValuePairToCopy == NULL)
	{
		return NULL;
	}
	Element newKey=((KeyValuePair)keyValuePairToCopy)->copyKey(((KeyValuePair)keyValuePairToCopy)->key);
	if(newKey == NULL)
	{
		return NULL;
	}
	Element newValue=((KeyValuePair)keyValuePairToCopy)->copyValue(((KeyValuePair)keyValuePairToCopy)->value);
	if(newValue == NULL)
	{
		((KeyValuePair)keyValuePairToCopy)->freeKey(newKey);
		return NULL;
	}
	KeyValuePair newKeyValuePair=createKeyValuePair(newKey, newValue, ((KeyValuePair)keyValuePairToCopy)->copyKey, ((KeyValuePair)keyValuePairToCopy)->copyValue, ((KeyValuePair)keyValuePairToCopy)->freeKey, ((KeyValuePair)keyValuePairToCopy)->freeValue, ((KeyValuePair)keyValuePairToCopy)->printKey, ((KeyValuePair)keyValuePairToCopy)->printValue, ((KeyValuePair)keyValuePairToCopy)->transformIntoNumberKey, ((KeyValuePair)keyValuePairToCopy)->equalKey);
	if(newKeyValuePair == NULL)
	{
		((KeyValuePair)keyValuePairToCopy)->freeKey(newKey);
		((KeyValuePair)keyValuePairToCopy)->freeValue(newValue);
		return NULL;
	}
	((KeyValuePair)keyValuePairToCopy)->freeKey(newKey);
	((KeyValuePair)keyValuePairToCopy)->freeValue(newValue);
	return newKeyValuePair;
}

status printKeyValuePair(Element keyValuePairToDispley)
{
	if (keyValuePairToDispley == NULL){
		return failure;
	}
	displayValue((KeyValuePair)keyValuePairToDispley);
	return success;
}
