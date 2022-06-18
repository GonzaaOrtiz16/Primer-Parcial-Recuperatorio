/*
 * inputs.c
 *
 *  Created on: 16 may. 2022
 *      Author: Sergio
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Inputs.h"


int PedirEntero(char mensaje[])
{
	int retorno;
	char numero[100000];
	printf(mensaje);
	scanf("%s",numero);
	while(!ValidarNumero(numero))
	{
		printf("\nERROR\n");
		printf(mensaje);
		scanf("%s",numero);
	}
	retorno=atoi(numero);
	return retorno;
}


float PedirFlotante(char mensaje[])
{
	float retorno;
	char numero[100000];
	printf(mensaje);
	scanf("%s",numero);
	while(!ValidarNumero(numero))
	{
		printf("\nERROR\n");
		printf(mensaje);
		scanf("%s",numero);
	}

	retorno=atof(numero);

	return retorno;
}

int ValidarNumero(char numero[])
{
	int retorno=1;
	int longitud;
	if(numero!=NULL)
	{
		longitud=strlen(numero);
		for(int i=0;i<longitud;i++)
		{
			if(!isdigit(numero[i]))
			{
				retorno=0;
				break;
			}
		}
	}

	return retorno;

}
void PedirCadena(char cadena[],char mensaje[])
{
	printf(mensaje);
	scanf("%s",cadena);

	while(!ValidarUnaCadena(cadena))
	{
		printf("\nERROR\n");
		printf(mensaje);
		scanf("%s",cadena);
	}

}

int ValidarUnaCadena(char cadena[])
{
	int retorno=1;
	int longitud;
	if(cadena!=NULL)
	{
		longitud=strlen(cadena);

		for(int i=0;i<longitud;i++)
		{
			if(!isalpha(cadena[i]))
			{
				retorno=0;
			}
		}
	}

	return retorno;
}
