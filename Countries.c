/*
 * Countries.c
 *
 *  Created on: Nov 13, 2018
 *      Author: Merav 205795537, Yiftach 312141369
 */

#include "Countries.h"


struct Point_t
{
	int X;
	int Y;
};

struct Geo_Territory_t
{
	Point firstPoint;
	Point secondPoint;
};

struct City_t
{
	char cityName[20];
	char foodName[30];
	int population;
};

struct Country_t
{
	char countryName[30];
	int numberOfCities;
	GeoT territory;
	City *citiesList;
};

Point initPoint(int x , int y)
{
	Point pPoint=(Point)malloc(sizeof(struct Point_t));
	if (pPoint != NULL)
	{
		pPoint->X = x;
		pPoint->Y = y;
		return pPoint;
	}
	return NULL;
}

Point copyPoint(Point pPoint)
{
	Point pPointCopy=initPoint(pPoint->X, pPoint->Y);
	if (pPointCopy != NULL)
	{
		return pPointCopy;
	}
	return NULL;
}

void freePoint(Point pPoint)
{
	free(pPoint);
}

GeoT initGeoT(Point x, Point y)
{
	GeoT pGeoT=(GeoT)malloc(sizeof(struct Geo_Territory_t));
	if (pGeoT == NULL)
	{
		return NULL;
	}
	//else not NULL
	Point newPoint1 = copyPoint(x);
	if (newPoint1 == NULL){
		free(pGeoT);
		return NULL;
	}
	Point newPoint2 = copyPoint(y);
	if (newPoint2 == NULL){
		freePoint(newPoint1);
		free(pGeoT);
		return NULL;
	}
	pGeoT->firstPoint = newPoint1;
	pGeoT->secondPoint = newPoint2;
	return pGeoT;
}

GeoT copyGeoT(GeoT pGeoT)
{
	if(pGeoT==NULL)
	{
		return NULL;
	}
	Point newPoint1 = initPoint(pGeoT->firstPoint->X,pGeoT->firstPoint->Y);
	if (newPoint1 == NULL)
	{
		return NULL;
	}
	Point newPoint2 = initPoint(pGeoT->secondPoint->X,pGeoT->secondPoint->Y);
	if (newPoint2 == NULL)
	{
		freePoint(newPoint1);
		return NULL;
	}
	GeoT pGeoTCopy = initGeoT(newPoint1, newPoint2);
	if (pGeoTCopy == NULL)
	{
		freePoint(newPoint1);
		freePoint(newPoint2);
		return NULL;
	}
	//else not NULL
	freePoint(newPoint1);
	freePoint(newPoint2);
	return pGeoTCopy;
}

void printGeoT(GeoT pGeoT)
{
	printf ("<%d,%d> , <%d,%d>\n", pGeoT->firstPoint->X, pGeoT->firstPoint->Y, pGeoT->secondPoint->X, pGeoT->secondPoint->Y);
}


void freeGeoT(GeoT pGeoT)
{

	freePoint(pGeoT->firstPoint);
	freePoint(pGeoT->secondPoint);
	free(pGeoT);
}

City initCity(char cName[],char fName[], int numberOfPepole)
{
	City pCity=(City)malloc(sizeof(struct City_t));
	if (pCity == NULL)
	{
		return NULL;
	}
	strcpy(pCity->cityName, cName);
	strcpy(pCity->foodName, fName);
	pCity->population=numberOfPepole;
	return pCity;

}

City copyCity(City pCity)
{
	if (pCity == NULL)
	{
		return NULL;
	}
	char newCityName[20];
	strcpy(newCityName, pCity->cityName);
	char newFoodName[30];
	strcpy(newFoodName, pCity->foodName);
	City pCityCopy=initCity(newCityName, newFoodName, pCity->population);
	if (pCityCopy == NULL)
	{
		return NULL;
	}
	return pCityCopy;
}

void printCity(City pCity)
{
	printf ("\t%s includes %d residents and their favorite food is %s.\n", pCity->cityName, pCity->population, pCity->foodName);
}

void freeCity(City pCity)
{
	free(pCity);
}

Country initCountry(char cName[], GeoT terr)
{
	Country pCountry=(Country)malloc(sizeof(struct Country_t));
	if (pCountry == NULL)
	{
		return NULL;
	}
	GeoT newTerr = copyGeoT(terr);
	if (newTerr == NULL)
	{
		free(pCountry);
		return NULL;
	}
	pCountry->territory = newTerr;
	strcpy(pCountry->countryName, cName);
	pCountry->numberOfCities = 0;
	pCountry->citiesList = NULL;
	return pCountry;
}

Element copyCountry(Element eCountry)
{
	if (eCountry == NULL)
	{
		return NULL;
	}
	Country pCountry =(Country)eCountry;
	GeoT newTerr = copyGeoT(pCountry->territory);
	if (newTerr == NULL)
	{
		return NULL;
	}
	char newCountryName[30];
	strcpy(newCountryName, pCountry->countryName);
	Country pCountryCopy=initCountry(newCountryName, newTerr);
	if (pCountryCopy == NULL)
	{
		freeGeoT(newTerr);
		return NULL;
	}
	int i;
	for(i=0;i<pCountry->numberOfCities;i++)
	{
		City newCity = copyCity(*(pCountry->citiesList+i));
		addCity(newCity , pCountryCopy);
		freeCity(newCity);
	}
	freeGeoT(newTerr);
	return pCountryCopy;
}

status printCountry(Element eCountry)
{
	if (eCountry == NULL)
	{
		return failure;
	}
	Country pCountry= (Country)eCountry;
	printf ("Country %s coordinates: ", pCountry->countryName);
	printGeoT(pCountry->territory);
	int i;
	for(i=0; i<pCountry->numberOfCities; i++)
	{
		printCity(*(pCountry->citiesList+i));
	}

	return success;
}


status freeCountry(Element eCountry)
{
	if(eCountry == NULL)
	{
		return success;
	}
	Country pCountry =(Country)eCountry;
	freeGeoT(pCountry->territory);
	int i;
	for(i=pCountry->numberOfCities-1 ;i>-1 ;i--)
	{
		freeCity(*(pCountry->citiesList+i));
	}
	free(pCountry->citiesList);
	free(pCountry);
	return success;
}


Country addCountry(char cName[], int x1, int x2, int y1, int y2)
{
	Point pointA = initPoint( x1, y1 );
	Point pointB = initPoint( x2, y2 );
	GeoT territory = initGeoT( pointA, pointB );
	Country country = initCountry( cName , territory );
	return country;
}

status addCity(City cityToAdd, Country countryToAddTo)
{
	if (cityToAdd == NULL || countryToAddTo == NULL)
	{
		return failure;
	}
	//first city addition
	if ( countryToAddTo->numberOfCities == 0 && countryToAddTo->citiesList == NULL)
	{
		City newCity = copyCity(cityToAdd);
		if (newCity == NULL){
			return failure;
		}
		City *newCitiesList = (City*)malloc(sizeof(City));
		if (newCitiesList == NULL){
			freeCity(newCity);
			return failure;
		}
		countryToAddTo->citiesList = newCitiesList;
		*(countryToAddTo->citiesList)=newCity;
		countryToAddTo->numberOfCities = 1;
		return success;
	}
	else
	{
		City newCity = copyCity(cityToAdd);
		if (newCity == NULL){
			return failure;
		}
		countryToAddTo->citiesList = (City*)realloc(countryToAddTo->citiesList, sizeof(City)*((countryToAddTo->numberOfCities)+1));
		if (countryToAddTo->citiesList == NULL){
			freeCity(newCity);
			return failure;
		}
		countryToAddTo->citiesList[countryToAddTo->numberOfCities] = newCity;
		countryToAddTo->numberOfCities++;
	}
	return success;
}

status deleteCity(Country pCountry, char *cName)
{
	if (pCountry == NULL || cName == NULL)
	{
		return failure;
	}
	int i;
	for (i=0; i < pCountry->numberOfCities; i++)
	{
		// Deleting the City and reassigning the city array pointers, in order to delete the free spaces.
		if(strcmp(cName,(*(pCountry->citiesList + i))->cityName)==0)
		{
			freeCity(*(pCountry->citiesList + i));
			int j;
			for (j = i; j<(pCountry->numberOfCities - 1);j++)
			{
				*(pCountry->citiesList + j) = *(pCountry->citiesList + (j+1));
			}
			pCountry->numberOfCities--;
			if(pCountry->numberOfCities == 0 && pCountry->citiesList != NULL)
			{
				return success;
			}
			else
			{
				pCountry->citiesList = (City*)realloc(pCountry->citiesList, sizeof(City)*(pCountry->numberOfCities));
				return success;
			}
		}
	}
	return failure;
}


bool isInRange(Point pPoint, Country pCountry)
{
	if (pPoint == NULL || pCountry == NULL)
	{
		return false;
	}
	if(!((((pCountry->territory->firstPoint->X) <= pPoint->X) && (pPoint->X <= (pCountry->territory->secondPoint->X))) || (((pCountry->territory->secondPoint->X) <= pPoint->X) && (pPoint->X <= (pCountry->territory->firstPoint->X)))))
	{
		return false;
	}
	if(!((((pCountry->territory->firstPoint->Y) <= pPoint->Y) && (pPoint->Y <= (pCountry->territory->secondPoint->Y))) || (((pCountry->territory->secondPoint->Y) <= pPoint->Y) && (pPoint->Y <= (pCountry->territory->firstPoint->Y)))))
	{
		return false;
	}
	return true;
}

Country getCountryFromName(Country* Countries, int numberOfCountries, char* countryName ){ //country* as hashTable
	int i;
	for (i=0; i < numberOfCountries; i++)
	{
		if (strcmp(Countries[i]->countryName, countryName) == 0)
		{
			return Countries[i];
		}
	}
	return NULL;
}

bool searchCity( Country pCountry, char *inputCityName)
{
	int i;
	for (i=0; i < pCountry->numberOfCities; i++)
	{
		if(strcmp(inputCityName,(*(pCountry->citiesList + i))->cityName)==0)
		{
			return true;
		}
	}
	return false;
}
char* getCountryNameField (Country pCountry)
{
	return pCountry->countryName;
}

Element copyCountryName (Element element)
{
	if (element == NULL)
	{
		return NULL;
	}
	char* copyName = (char*)malloc(sizeof(char)*30);
	strcpy(copyName, (char*)element);
	return copyName;
}
status freeName (Element toFree)
{
	free(toFree);
	return success;
}
status printName (Element toPrint)//CHANGE NAME###
{
	printf("%s", (char*)toPrint);
	return success;
}
bool isNameEquals (Element element1, Element element2)
{
	if (element1 == NULL || element2 == NULL)
	{
		return false;
	}
	if (strcmp(((char*)element1),((char*)element2)) == 0)
	{
		return true;
	}
	return false;
}
int transfromStringToNumber (Element element)
{
	if (element == NULL)
	{
		return -1;
	}
	char countryName[30];
	strcpy(countryName,(char*)element);
	int sum=0;
	int counter=0;
	while(countryName[counter]!='\0')
	{
		sum = sum+(int)countryName[counter];
		counter++;
	}
	return sum;
}

