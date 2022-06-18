/*
 * validaciones.c
 *
 *  Created on: 16 may. 2022
 *      Author: Sergio
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pp.h"
#include "inputs.h"

void validarFecha(int* fecha, int maximo, int minimo,char mensaje[])
{
	while(*fecha<minimo || *fecha>maximo )
	{
		*fecha=PedirEntero(mensaje);
	}
}
void validarMes(int dia,int* mes)
{
	switch(dia)
		{
			case 31:
				while(*mes!=1 && *mes!=3 && *mes!=5 && *mes!=7 && *mes!=8 && *mes!=10 && *mes!=12)
				{
					printf("\nERROR: Ingrese un mes que tenga 31 dias.\n");
					*mes=PedirEntero("\nMes:");
				}
			break;

			case 30:
				while(*mes==2)
				{
					printf("\nERROR: Ingrese un mes que tenga 31 dias.\n");
					*mes=PedirEntero("\nMes:");
				}
			break;

			default:
			break;

		}
}
void validarMedico(sMedico listaMedicos[], int sizeMedicos, int* idMedico)
{
	int auxiliar;
	auxiliar=0;

	while(auxiliar==0)
	{
		for(int i=0;i<sizeMedicos;i++)
		{
			if(*idMedico==listaMedicos[i].idMedico)
			{
				auxiliar=1;
				break;
			}
		}
		if(auxiliar==1)
		{
			break;
		}
		else
		{
			printf("\nERROR: Medico no existente.\n");
			mostrarMedicos();//Muestra la lista de medicos para que el usurio elija
			*idMedico=PedirEntero("Ingrese el medico que lo va a atender:\n");
		}
	}
}
void validarDiagnostico(sDiagnostico listaDiagnostico[], int sizeDiagnostico, int* idDiagnostico)
{
	int auxiliar;
	auxiliar=0;

	while(auxiliar==0)
	{
		for(int i=0;i<sizeDiagnostico;i++)
		{
			if(*idDiagnostico==listaDiagnostico[i].idDiagnostico)
			{
				auxiliar=1;
				break;
			}
		}
		if(auxiliar==1)
		{
			break;
		}
		else
		{
			printf("\nERROR: Diagnostico no existente.\n");
			mostrarDiagnosticos();
			*idDiagnostico=PedirEntero("Ingrese el diagnostico:\n");
		}
	}
}
void validarObraSocial(sObraSocial listaObrasocial[], int sizeObraSocial, int* idObraSocial)
{
	int auxiliar;
	auxiliar=0;

	while(auxiliar==0)
	{
		for(int i=0;i<sizeObraSocial;i++)
		{
			if(*idObraSocial==listaObrasocial[i].idObraSocial)
			{
				auxiliar=1;
				break;
			}
		}
		if(auxiliar==1)
		{
			break;
		}
		else
		{
			printf("\nERROR: La Obra Social no existente.\n");
			mostrarObraSocial();
			*idObraSocial=PedirEntero("Ingrese Obra Social:\n");
		}
	}
}


