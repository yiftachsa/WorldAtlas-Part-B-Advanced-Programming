/*
 * KeyValuePair.h
 *
 *  Created on: Nov 29, 2018
 *      Author: Merav 205795537, Yiftach 312141369
 */

#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_

#include "Defs.h"


typedef struct t_KeyValuePair *KeyValuePair;

KeyValuePair createKeyValuePair (Element eKey, Element eValue, copyFunction copyKeyF, copyFunction copyValueF, freeFunction freeKeyF, freeFunction freeValueF , printFunction printKeyF , printFunction printValueF , transformIntoNumberFunction transformIntoNumberKeyF , equalFunction equalKeyF);
status destroyKeyValuePair(Element);
void displayValue(KeyValuePair);
void displayKey(KeyValuePair);
Element getValue(KeyValuePair);
Element getKey(KeyValuePair);
bool isEqualKey(Element,Element);
Element copyKeyValuePair(Element);
status printKeyValuePair(Element);

#endif /* KEYVALUEPAIR_H_ */
