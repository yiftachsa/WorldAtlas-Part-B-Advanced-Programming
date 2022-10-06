
/*
 ============================================================================
 Name        : MyCountries.c
 Author      : Merav 205795537, Yiftach 312141369
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Countries.h"
#include "HashTable.h"


int main(int argc, char* argv[]) {
	int hashNumber;
	if (argv[1] != NULL){
		hashNumber = atoi(argv[1]);
	}
	int numberOfCountries = atoi(argv[2]);
	char *configurationFile;
	configurationFile = argv[3];

	hashTable Countries = createHashTable(copyCountryName,freeName, printName, copyCountry, freeCountry, printCountry, isNameEquals , transfromStringToNumber, hashNumber);

	FILE *pFile;
	pFile = fopen(configurationFile, "r");
	if(pFile == NULL)
	{
		printf("Failed to open the file.\n");
		return 1;
	}
	int cCount=0;
	while(cCount != numberOfCountries)
	{
		char newCountryName[30];
		char line[100];
		int X1,Y1;
		int X2,Y2;
		fscanf(pFile, "%s", line);
		char *token1;
		token1 = strtok (line,",");
		strcpy(newCountryName,token1);
		token1 = strtok (NULL,",");
		X1 = atoi(token1);
		token1 = strtok (NULL,",");
		Y1 = atoi(token1);
		token1 = strtok (NULL,",");
		X2 = atoi(token1);
		token1 = strtok (NULL,",");
		Y2 = atoi(token1);

		Point pPoint1 = initPoint(X1,Y1);
		Point pPoint2 = initPoint(X2,Y2);
		GeoT newGeoT = initGeoT(pPoint1, pPoint2);
		Country newCountry = initCountry(newCountryName, newGeoT);

		while(fgetc(pFile) == '\n' && fgetc(pFile) == '\t')
		{
			//city insert
			fseek(pFile, (-1), SEEK_CUR);
			char newCityName[20];
			char newFavoriteFood[30];
			int numOfResidents;
			char line2[100];
			fscanf(pFile, "%*c%s", line2);
			char *token2;
			token2 = strtok (line2,",");
			strcpy(newCityName,token2);
			token2 = strtok (NULL,",");
			strcpy(newFavoriteFood,token2);
			token2 = strtok (NULL,",");
			numOfResidents = atoi(token2);
			City newCity = initCity(newCityName, newFavoriteFood, numOfResidents);
			addCity(newCity, newCountry);
			freeCity(newCity);
		}
		addToHashTable(Countries, newCountryName, newCountry);
		freePoint(pPoint1);
		freePoint(pPoint2);
		freeGeoT(newGeoT);
		freeCountry(newCountry);
		cCount++;
		fseek(pFile, (-1), SEEK_CUR);
	}
	fclose(pFile);

	int ch = 0;
	while( ch != 8 ) {
		printf("please choose one of the following numbers:\n");
		printf("1 : print Countries \n");
		printf("2 : add country \n");
		printf("3 : add city to country \n");
		printf("4 : delete city from country \n");
		printf("5 : print country by name \n");
		printf("6 : delete country \n");
		printf("7 : is country in area \n");
		printf("8 : exit\n");
		scanf("%d", &ch );
		switch( ch )
		{
		case 1:
		{
			/* print countries */
			displayHashElements(Countries);
		}
		break;

		case 2:
		{
			char newCountryName[30];
			printf("please enter a new country name\n");
			scanf("%s", newCountryName);
			if (lookupInHashTable(Countries, newCountryName) != NULL)
			{
				printf("country with this name already exist\n");
				break;
			}
			int X1,Y1;
			int X2,Y2;
			char userInput[128];
			printf("please enter two x and y coordinates :x1,y1,x2,y2\n");
			scanf("%s", userInput);
			char *token1;
			token1 = strtok (userInput,",");
			X1 = atoi(token1);
			token1 = strtok (NULL,",");
			Y1 = atoi(token1);
			token1 = strtok (NULL,",");
			X2 = atoi(token1);
			token1 = strtok (NULL,",");
			Y2 = atoi(token1);
			Point newPoint1 = initPoint(X1,Y1);
			Point newPoint2 = initPoint(X2,Y2);
			GeoT newGeoT = initGeoT(newPoint1, newPoint2);
			Country newCountry = initCountry(newCountryName, newGeoT);
			addToHashTable(Countries, newCountryName, newCountry);
			freePoint(newPoint1);
			freePoint(newPoint2);
			freeGeoT(newGeoT);
			freeCountry(newCountry);

		}
		break;

		case 3:
		{
			/* add city to country */
			char inputCountryName[30];
			printf("please enter a country name\n");
			scanf("%s", inputCountryName);
			Country countryToAddTo = lookupInHashTable(Countries, inputCountryName);
			if (countryToAddTo == NULL){
				printf("country not exist\n");
				break;
			}

			char inputCityName[20];
			printf("please enter a city name\n");
			scanf("%s", inputCityName);
			if (searchCity(countryToAddTo, inputCityName) == true)
			{
				printf("this city already exist in this country\n");
				break;
			}
			else
			{
				char inputFavoriteFood[30];
				printf("please enter the city favorite food\n");
				scanf("%s", inputFavoriteFood);
				int inputResidents;
				printf("please enter number of residents in city\n");
				scanf("%d", &inputResidents);
				City newCity = initCity(inputCityName, inputFavoriteFood, inputResidents);
				addCity(newCity, countryToAddTo);
				freeCity(newCity);
			}
			break;
		}


		case 4:
		{
			/* delete city from country */
			char inputCountryName[30];
			printf("please enter a country name\n");
			scanf("%s", inputCountryName);
			Country countryToAddTo = lookupInHashTable(Countries, inputCountryName);
			if (countryToAddTo == NULL){
				printf("country name not exist.\n");
				break;
			}

			char inputCityName[20];
			printf("please enter a city name\n");
			scanf("%s", inputCityName);
			if (searchCity(countryToAddTo, inputCityName) == false)
			{
				printf("the city not exist in this country\n");
				break;
			}
			else
			{
				deleteCity(countryToAddTo, inputCityName);
			}
			break;
		}

		case 5:
		{
			/* print country by name */
			char inputCountryName[30];
			printf("please enter a country name\n");
			scanf("%s", inputCountryName);
			Country countryToAddTo = lookupInHashTable(Countries, inputCountryName);
			if (countryToAddTo == NULL){
				printf("country name not exist\n");
				break;
			}
			printCountry(countryToAddTo);
			break;
		}

		case 6:
		{
			/*delete country*/
			char inputCountryName[30];
			printf("please enter a country name\n");
			scanf("%s", inputCountryName);
			Country countryToAddTo = lookupInHashTable(Countries, inputCountryName);
			if (countryToAddTo == NULL){
				printf("can't delete the country\n");
				break;
			}

			if(removeFromHashTable(Countries, getCountryNameField(countryToAddTo)) == success)
			{
				printf("country deleted\n");
				break;
			} else { //This step isn't a part of the instructions but it's still a crucial step!
				printf("can't delete the country\n");
				break;
			}
		}
		break;

		case 7:
		{
			/* is country in area */
			char inputCountryName[30];
			printf("please enter a country name\n");
			scanf("%s", inputCountryName);
			Country countryToAddTo = lookupInHashTable(Countries, inputCountryName);
			if (countryToAddTo == NULL){
				printf("country name not exist\n");
				break;
			}

			int inputX;
			int inputY;
			char coordinates[30];
			printf("please enter x and y coordinations:x,y\n");
			scanf("%s", coordinates);
			char *token3;
			token3 = strtok (coordinates,",");
			inputX = atoi(token3);
			token3 = strtok (NULL,",");
			inputY = atoi(token3);
			Point pPoint = initPoint(inputX, inputY);
			if (isInRange(pPoint , countryToAddTo) == true)
			{
				printf("the coordinate in the country\n");
				freePoint(pPoint);
				break;
			} else {
				printf("the coordinate not in the country\n");
				freePoint(pPoint);
				break;
			}
			break;
		}

		case 8:
		{
			/* exit */
			destroyHashTable(Countries);
			printf("all the memory cleaned and the program is safely closed\n");
			break;
		}

		default:
			printf("please choose a valid number\n");
			break;

		}
	}

	return EXIT_SUCCESS;
}
