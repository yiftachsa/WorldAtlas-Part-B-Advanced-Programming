/*
 * Countries.h
 *
 *  Created on: Nov 13, 2018
 *      Author: Merav 205795537, Yiftach 312141369
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

#ifndef COUNTRIES_H_
#define COUNTRIES_H_

typedef struct Point_t *Point;
typedef struct Geo_Territory_t *GeoT;
typedef struct City_t *City;
typedef struct Country_t *Country;

//Point
Point initPoint( int , int );
Point copyPoint(Point);
void freePoint(Point);
//GeoT
GeoT initGeoT(Point, Point);
GeoT copyGeoT(GeoT);
void freeGeoT(GeoT);
//City
City initCity(char *,char *, int );
City copyCity(City);
void freeCity(City);
//Country
Country initCountry(char *, GeoT);
Element copyCountry(Element);
status printCountry(Element);
status freeCountry(Element);
//Other functions
Country addCountry(char *, int , int , int , int );
status addCity(City, Country);
status deleteCity(Country , char *);
bool isInRange(Point , Country );
Country getCountryFromName(Country* , int , char* ); // hash table instead of country*.
bool searchCity( Country , char* );
char* getCountryNameField (Country);
status freeName (Element);
Element copyCountryName (Element);
status printName (Element);
bool isNameEquals (Element, Element);
int transfromStringToNumber (Element);

#endif /* COUNTRIES_H_ */
