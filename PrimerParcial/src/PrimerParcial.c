/*
 ============================================================================
 Name        : PrimerParcial.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pp.h"
#include "inputs.h"
#define lleno 1
#define vacio 0
#define sinDiagnostico 0
#define sizePacientes 20

int main(void)
{
	setbuf(stdout, NULL);

	sPaciente listaPacientes[sizePacientes]={{generadorId(),"Gonzalo",{15,4,2020},1,1,1,1},
											{generadorId(),"German",{12,12,2021},2,1,2,2},
											{generadorId(),"Federico",{1,2,2023},3,1,3,3},
											{generadorId(),"Lautaro",{28,5,2023},4,1,1,4},
											{generadorId(),"Martina",{18,6,2021},5,1,2,2},
											{generadorId(),"Ramiro",{23,7,2021},6,1,3,3},
											{generadorId(),"Ignacio",{11,7,2023},7,1,1,1},
											{generadorId(),"Alan",{4,6,2021},8,1,2,3}};

	ponerListaEnVacio(listaPacientes, sizePacientes);

		int opcion;
		int index;
		int banderaAlta;

		banderaAlta=0;

		do
		{
			printf("1. ALTA\n");
			printf("2. MODIFICAR CONSULTA\n");
			printf("3. CANCELAR CONSULTA\n");
			printf("4. DIAGNOSTICAR\n");
			printf("5. LISTAR\n");
			printf("6. SALIR\n");
			opcion=PedirEntero("Seleccione una opcion:");

			switch(opcion)
			{
			case 1:
				index= cargarEnLista(listaPacientes, sizePacientes);
				switch(index)
				{
					case -1:
						printf("No hay espacio disponible\n");
					break;

					default:
						index=index+1;
						printf("\nLa carga se realizó con éxito en la posición %d\n", index);
						banderaAlta=1;
					break;
				}

			break;

			case 2:

				if(banderaAlta==1)
				{
					modificarConsulta(listaPacientes, sizePacientes);
				}
				else
				{
					printf("Todavia no se ingreso ningun paciente.\n");
				}
			break;

			case 3:
				if(banderaAlta==1)
				{
					darDeBaja(listaPacientes, sizePacientes);
				}
				else
				{
					printf("Todavia no se ingreso ningun paciente.\n");
				}
			break;

			case 4:

				if(banderaAlta==1)
				{
					diagnosticar(listaPacientes, sizePacientes);
				}
				else
				{
					printf("Todavia no se ingreso ningun paciente.\n");
				}

			break;

			case 5:

				if(banderaAlta==1)
				{
					mostrar(listaPacientes, sizePacientes);
				}
				else
				{
					printf("Todavia no se ingreso ningun paciente.\n");
				}

			break;
			case 6:
				printf("Vuelva pronto\n");
			break;
			default:
				printf("ERROR: opcion incorrecta \n");
			break;
			}

			}while(opcion!=9);


	return EXIT_SUCCESS;
}
