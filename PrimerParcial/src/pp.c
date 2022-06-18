/*
 * pp.c
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
#include "validaciones.h"
#define lleno 1
#define vacio 0
#define sinDiagnostico 0
#define sizeMedicos 8
#define sizeDiagnostico 4
#define sizeEspecialidad 4
#define sizeObraSocial 4
static int idIncremental=999;

static sMedico listaMedicos[sizeMedicos]={{1,"Dra. Marisa Videla",1},
										{2,"Dr. Ronan Videla",2},
										{3,"Dra. Adriana Videla",3},
										{4,"Dra. Daiana Cañete",4},
										{5,"Dra. Julieta Giusti",2},
										{6,"Dr. Gonzalo Ortiz",3},
										{7,"Dr. Sergio Ortiz",1},
										{8,"Dra.Fernanda Cañete",3}};

static sDiagnostico listaDiagnosticos[sizeDiagnostico]={{0,"Sin Diagnostico"},
														{1,"Covid-19"},
														{2,"Gripe A"},
														{3,"Pre infarto"}};

static sEspecialidadMedico listaEspecialidad[sizeEspecialidad]={{1,"Traumatologia"},
																{2,"Neurologia"},
																{3,"Neumonologia"},
																{4,"Cirujana"}};

static sObraSocial listaObraSocial[sizeObraSocial]={{1,"Swiss Medical"},
													{2,"OSDE"},
													{3,"Galeno"},
													{4,"Sin Obra Social"}};

void ponerListaEnVacio(sPaciente listaPacientes[], int sizePacientes)
{
	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado!=lleno)
		{
			listaPacientes[i].estado=vacio;
		}
		else
		{
			encontrarEspecialidad(listaPacientes[i], &listaPacientes[i].idEspecialidad);

		}
	}
}
int generadorId()
{

	idIncremental++;

	return idIncremental;
}

sPaciente ingresarUnPaciente()
{
	sPaciente unPaciente;


	unPaciente.idPaciente= generadorId();//Se pide un id generada automaticamente.

	PedirCadena(unPaciente.nombrePaciente, "Ingrese nombre de paciente:\n");

	printf("Ingrese fecha.\n");

	unPaciente.fechaConsulta.dia=PedirEntero("Dia:");
	validarFecha(&unPaciente.fechaConsulta.dia, 31 , 1,"\nERROR: Ingrese un dia existente.\n");//Se valida los valores que se puede ingresar en dia(entre 1-31)

	unPaciente.fechaConsulta.mes=PedirEntero("\nMes:");
	validarFecha(&unPaciente.fechaConsulta.mes, 12, 1,"\nERROR: Ingrese un mes existente.\n");//Se valida que se pueden ingresar en mes (entre 1-12)
	validarMes(unPaciente.fechaConsulta.dia,&unPaciente.fechaConsulta.mes);//Se valida que el mes que ingreso tenga la cantidad de dias que ya fueron ingresados.

	unPaciente.fechaConsulta.anio=PedirEntero("\nAño:");
	validarFecha(&unPaciente.fechaConsulta.anio, 2027, 2019,"\nERROR: Ingrese un año exitente.\n");//Se valida los valores que se pueden ungresar en año(Entre 2022 y 2027)

	mostrarObraSocial();
	unPaciente.idObraSocial=PedirEntero("Ingrese Obra Social:\n");
	validarObraSocial(listaObraSocial, sizeObraSocial, &unPaciente.idObraSocial);


	mostrarMedicos();//Muestra la lista de medicos para que el usurio elija
	unPaciente.idMedico=PedirEntero("Ingrese el medico que lo va a atender:\n");
	validarMedico(listaMedicos, sizeMedicos, &unPaciente.idMedico);//Valido que el id ingresado exista.

	encontrarEspecialidad(unPaciente,&unPaciente.idEspecialidad);

	unPaciente.estado=lleno;
	unPaciente.idDiagnostico=sinDiagnostico;

	return unPaciente;
}
void encontrarEspecialidad(sPaciente unPaciente ,int* idEspecialidad)
{
	int indexEspecialidad;

	buscarMedico(unPaciente, &indexEspecialidad);

	*idEspecialidad=listaEspecialidad[indexEspecialidad].idEspecialidad;
}
int buscarLibre(sPaciente lista[], int size)
{
	int index;
	index=-1;
	for(int i=0; i<size; i++)
	{
		if(lista[i].estado==vacio)
		{
			index=i;
			break;
		}
	}

	return index;
}
int cargarEnLista(sPaciente lista[], int size)
{
	int index;

	index=buscarLibre(lista, size);//Se busca un posicion libre y se guada en index.

	if(index!=-1)
	{
		lista[index]=ingresarUnPaciente(listaMedicos,sizeMedicos);//En la posicion libre encontrada se cargan los datos.
	}

	return index;
}
void mostrarObraSocial()
{
	for(int i=0;i<sizeObraSocial;i++)
	{
		printf("%d. %s.\n",listaObraSocial[i].idObraSocial,listaObraSocial[i].descripcion);
	}//Recorre el array de obra social y los muestra.
}
void mostrarMedicos()
{
	int indexEspecialidad;


	for(int i=0;i<sizeMedicos;i++)
	{
		indexEspecialidad=buscarEspecialidad(listaMedicos[i]);
		printf("%d. %s, %s\n",listaMedicos[i].idMedico,
							listaMedicos[i].nombreMedico,
							listaEspecialidad[indexEspecialidad].descripcion);
	}//Recorre el array de medicos y los muestra.

}
int buscarEspecialidad(sMedico unMedico)
{
	int index;

	for(int i=0; i<sizeEspecialidad; i++)
	{
		if(unMedico.idEspecialidad==listaEspecialidad[i].idEspecialidad)
		{
			index=i;
			break;
		}
	}

	return index;
}
void mostrarListaPacientes(sPaciente listaPacientes[],int sizePacientes)
{

	printf("%5s||%10s||%10s||%15s||%19s||%13s||%15s\n","Id","Nombre","Fecha","Obra Social",
															"Medico","Especialidad","Diagnostico");
	printf("_______________________________________________________________________________________________________\n\n");

	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==lleno)//Verifica que la posicion que va a mostrar este llena.
		{

			mostrarPacientes(listaPacientes[i]);

		}
	}

}
int buscarObraSocial(sPaciente unPaciente)
{
	int index;

	for(int i=0; i<sizeObraSocial;i++)
	{
		if(unPaciente.idObraSocial==listaObraSocial[i].idObraSocial)
		{
			index=i;
			break;
		}
	}
	return index;
}
int buscarMedico(sPaciente unPaciente,int* indexEspecialidad)
{
	int index;
	index=-1;



	for(int i=0; i<sizeMedicos; i++)//Recorro el array de medico
	{

		if(unPaciente.idMedico==listaMedicos[i].idMedico)//Verifico donde los id son iguales
		{
			*indexEspecialidad=buscarEspecialidad(listaMedicos[i]);
			index=i;//Guardo la posicion donde son iguales.
			break;//Corto la itarecion porque solo puede coincidir con un solovalor.
		}
	}

	return index;//Retorno esa posicion.
}
void mostrarUnPaciente(sPaciente unPaciente, sMedico medico, sDiagnostico diagnostico, sEspecialidadMedico especialidad, sObraSocial obraSocial)//Recibo como parametro la lista de pacientes en una posicion de array y el medico en la posicion donde los id coinciden.
{
	printf("%5d||%10s||%2d/%2d/%4d||%15s||%19s||%13s||%15s\n", unPaciente.idPaciente, unPaciente.nombrePaciente,
												unPaciente.fechaConsulta.dia, unPaciente.fechaConsulta.mes,
												unPaciente.fechaConsulta.anio, obraSocial.descripcion,
												medico.nombreMedico,especialidad.descripcion,
												diagnostico.descripcion);//Muestro los datos.
}
int pedirIdPaciente(sPaciente listaPacientes[],int sizePacientes)
{
	int indexPaciente;
	int idIngresado;

	mostrarListaPacientes(listaPacientes, sizePacientes);//Muestro la lista de pacientes
	idIngresado=PedirEntero("Ingrese ID de paciente que desea modificar.\n");
	indexPaciente=encontrarPacientePorId(listaPacientes, sizePacientes, idIngresado);//Busca la posicion donde las id coincidan y la guarda en indexPaciente.


	while(indexPaciente==-1)//Valido que la id ingresada exista en la lista.
	{
		printf("\nERROR: El ID ingresado no coincide.\n");
		mostrarListaPacientes(listaPacientes, sizePacientes);//Muestro la lista de pacientes
		idIngresado=PedirEntero("Ingrese ID de paciente que desea modificar.\n");
		indexPaciente=encontrarPacientePorId(listaPacientes, sizePacientes, idIngresado);
	}

	return indexPaciente;
}
void modificarConsulta(sPaciente listaPacientes[],int sizePacientes)
{
	int opcion;
	int indexPaciente;
	sPaciente auxiliar;
	char respuesta;

	indexPaciente=pedirIdPaciente(listaPacientes, sizePacientes);

	do
	{
		printf("Ingrese lo que desee modificar.\n");
		printf("1. Nombre del paciente. [%s]\n",listaPacientes[indexPaciente].nombrePaciente);
		printf("2. Medico asignado.\n");
		printf("3. Fecha ingresada. [%d/%d/%d]\n",listaPacientes[indexPaciente].fechaConsulta.dia,
												listaPacientes[indexPaciente].fechaConsulta.mes,
												listaPacientes[indexPaciente].fechaConsulta.anio);
		printf("4. Volver.\n");
		scanf("%d", &opcion);

		switch(opcion)
		{
			case 1:
				PedirCadena(auxiliar.nombrePaciente, "Ingrese nombre:\n");//Pido nuevo nombre y lo guardo en un auxiliar.
				respuesta=confirmacion("¿Desea cambiar el nombre?s/n");//Confirmo que quiera cambiarlo.
				if(respuesta=='s')//Si la respuesta es si, cambia el valor en la lista
				{
					strcpy(listaPacientes[indexPaciente].nombrePaciente,auxiliar.nombrePaciente);
					printf("Cambio realizado con exito.\n");

				}
				else//Si la respuesta es no se cancela la operacion.
				{
					printf("Cambio cancelado.\n");
				}

			break;

			case 2:
				mostrarMedicos();
				auxiliar.idMedico=PedirEntero("Ingrese el medico que lo va a atender.\n");
				respuesta=confirmacion("¿Desea cambiar el medico?s/n");//Confirmo que quiera cambiarlo.
				if(respuesta=='s')//Si la respuesta es si, cambia el valor en la lista
				{
					listaPacientes[indexPaciente].idMedico=auxiliar.idMedico;
					printf("Cambio realizado con exito.\n");

				}
				else
				{
					printf("Cambio cancelado.\n");
				}
			break;

			case 3:
				printf("Ingrese fecha.\n");
				auxiliar.fechaConsulta.dia=PedirEntero("Dia:");
				auxiliar.fechaConsulta.mes=PedirEntero("\nMes:");
				auxiliar.fechaConsulta.anio=PedirEntero("\nAño:");
				respuesta=confirmacion("¿Desea cambiar la fecha?s/n");//Confirmo que quiera cambiarlo.
				if(respuesta=='s')//Si la respuesta es si, cambia el valor en la lista
				{
					listaPacientes[indexPaciente].fechaConsulta.dia=auxiliar.fechaConsulta.dia;
					listaPacientes[indexPaciente].fechaConsulta.mes=auxiliar.fechaConsulta.mes;
					listaPacientes[indexPaciente].fechaConsulta.anio=auxiliar.fechaConsulta.anio;
					printf("Cambio realizado con exito.\n");

				}
				else
				{
					printf("Cambio cancelado.\n");
				}
			break;

			case 4:
				printf("Volviendo....\n");
			break;

			default:
				printf("\n ERROR: Opcion incorrecta.\n");
			break;
		}

	}while(opcion!=4);

}

int encontrarPacientePorId(sPaciente listaPacientes[], int sizePacientes, int idIngresado)
{
	int index;

	index=-1;//Si no se encuentra una igualdad se retorna el valor -1

	for(int i=0; i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==lleno && listaPacientes[i].idPaciente==idIngresado)//Encuento la igualdad del id
		{
			index=i;//Guardo la posicion donde los id son iguales.
			break;
		}
	}
	return index;
}

char confirmacion(char mensaje[])
{
	char respuesta;


	PedirCadena(&respuesta, mensaje);

	while(respuesta!='s' && respuesta!='n')//Valido que la respuesta solo pueda ser s o n
	{
		printf("\n ERROR: Ingrese opcion correcta.\n");
		printf("%s (s/n).\n",mensaje);
		scanf("%c",&respuesta);
	}

	return respuesta;
}
void darDeBaja(sPaciente listaPacientes[], int sizePacientes)
{
	int indexPaciente;
	char respuesta;

	indexPaciente=pedirIdPaciente(listaPacientes, sizePacientes);

	printf("%d || %s \n",listaPacientes[indexPaciente].idPaciente,listaPacientes[indexPaciente].nombrePaciente);
	respuesta=confirmacion("¿Desea eliminar este paciente?s/n");
	if(respuesta=='s')
	{
		listaPacientes[indexPaciente].estado=vacio;
		printf("Paciente eliminado con exito.\n");
	}
	else
	{
		printf("La operacion ha sido candelada.\n");
	}
}
void mostrarDiagnosticos()
{
	for(int i=1;i<sizeDiagnostico;i++)
	{
		printf("%d. %s\n",listaDiagnosticos[i].idDiagnostico, listaDiagnosticos[i].descripcion);
	}
}
void diagnosticar(sPaciente listaPacientes[], int sizePacientes)
{
	int idMedico;
	int indexMedico;
	int idPaciente;
	int indexPaciente;
	int bandera;


	mostrarMedicos();
	idMedico=PedirEntero("Ingrese Medico:\n");
	indexMedico=buscarMedicoPorId(idMedico);
	while(indexMedico==-1)
	{
		printf("\nERROR. No se encontro id ingresado.\n");
		mostrarMedicos();
		idMedico=PedirEntero("Ingrese Medico:\n");
		indexMedico=buscarMedicoPorId(idMedico);
	}

	bandera=mostrarPacientesSinDiagnostico(listaPacientes, sizePacientes, indexMedico);

	if(bandera==1)
	{
		idPaciente=PedirEntero("Ingrese Id del paciente que desea modificar.\n");
		indexPaciente=encontrarPacientePorId(listaPacientes, sizePacientes, idPaciente);

		while(indexPaciente==-1||listaMedicos[indexMedico].idMedico!=listaPacientes[indexPaciente].idMedico)
		{
			printf("\nERROR: ID ingresado es inexsistente o no corresponde a un paciente de este medico.\n");
			idPaciente=PedirEntero("Ingrese Id del paciente que desea modificar.\n");
			indexPaciente=encontrarPacientePorId(listaPacientes, sizePacientes, idPaciente);

		}

		mostrarDiagnosticos();
		listaPacientes[indexPaciente].idDiagnostico=PedirEntero("Ingrese cual es la patologia del paciente.\n");
		validarDiagnostico(listaDiagnosticos, sizeDiagnostico, &listaPacientes[indexPaciente].idDiagnostico);

		if(listaPacientes[indexPaciente].idDiagnostico==sinDiagnostico)
		{
			printf("Ha ocurrido un error y no se pudo cargar el diagnostico\n.");
		}
		else
		{
			printf("Paciente diagnosticado con exito.\n");
		}
	}
	else
	{
		printf("Este medico no tiene ningun paciente sin diagnosticar.\n");
	}
}
int buscarDiagnostico(sPaciente unPaciente)
{
	int indexDiagnostico;
	indexDiagnostico=-1;

	for(int i=0; i<sizeDiagnostico;i++)
	{
		if(unPaciente.idDiagnostico==listaDiagnosticos[i].idDiagnostico)
		{
			indexDiagnostico=i;
			break;
		}
	}

	return indexDiagnostico;
}
int buscarMedicoPorId(int idIngresado)
{
	int indexMedico;
	indexMedico=-1;

	for(int i=0;i<sizeMedicos;i++)
	{
		if(listaMedicos[i].idMedico==idIngresado)
		{
			indexMedico=i;
			break;
		}
	}
	return indexMedico;
}
int mostrarPacientesSinDiagnostico(sPaciente listaPacientes[], int sizePacientes, int indexMedico)
{
	int indexDiagnostico;
	int bandera;

	bandera=0;

	printf("\n__________________________________________________\n");
	printf("%s\nLista de pacientes:\n",listaMedicos[indexMedico].nombreMedico);


	for(int i=0;i<sizePacientes;i++)
	{
		//printf("%d\n",listaPacientes[i].idDiagnostico);
		if(listaPacientes[i].idDiagnostico==sinDiagnostico && listaMedicos[indexMedico].idMedico==listaPacientes[i].idMedico)
		{
			bandera=1;
			indexDiagnostico=buscarDiagnostico(listaPacientes[i]);
			printf("%d || %s || %s \n",listaPacientes[i].idPaciente,listaPacientes[i].nombrePaciente,
										listaDiagnosticos[indexDiagnostico].descripcion);
		}
	}
	printf("\n__________________________________________________\n");
	return bandera;
}
void mostrar(sPaciente listaPacientes[],int sizePacientes)
{
	int opcion;
	int idEspecialidad;
	int idObraSocial;
	int respuesta;


	do
	{
		printf("\n___________________________________________________________________________________________________________________\n");
		printf("1. Listar Medicos.\n");
		printf("2. Listar consultas.\n");
		printf("3. Listar Medicos con consultas diagnosticadas.\n");
		printf("4. Listado de consultas ordenadas por fecha.\n");
		printf("5. Listado de consultas diagnosticadas.\n");
		printf("6. Listado de las consultas diagnosticadas con covid-19 desde el inicio de la pandemia hasta la actualidad.\n");
		printf("7. Listado de consultas ordenadas por especialidad alfabéticamente.\n");
		printf("8. Listado de todas las consultas entre el mes de abril y julio para una especialidad determinada.\n");
		printf("9. Porcentaje de consultas diagnosticadas que atiende cada médico en función del total de diagnósticos.\n");
		printf("10.Enfermedad menos diagnosticada.\n");
		printf("11.La especialidad más estudiada por los médicos.\n");
		printf("12.Mostrar por medicos, los pacientes que tengan fecha en 2021 con diagnostico de una obra social que elija el usuario.\n");
		printf("13.Volver.");
		printf("\n___________________________________________________________________________________________________________________\n");
		scanf("%d",&opcion);

		switch(opcion)
		{
			case 1:
				mostrarMedicos();
				system("pause");
			break;

			case 2:
				mostrarListaPacientes(listaPacientes, sizePacientes);
				system("pause");
			break;

			case 3:
				mostrarMedicosConPacientes(listaPacientes, sizePacientes);
				system("pause");
			break;

			case 4:
				ordenarPorFechaMayor(listaPacientes, sizePacientes);
				mostrarListaPacientes(listaPacientes, sizePacientes);
				ordenarPorIdPacientes(listaPacientes, sizePacientes);
				system("pause");
			break;

			case 5:
				mostrarListaDiagnosticados(listaPacientes, sizePacientes);
				system("pause");
			break;

			case 6:

				mostrarPacientesCovid(listaPacientes, sizePacientes);
				system("pause");
			break;

			case 7:
				ordenarEspecialidad();
				mostrarPorEspecialidad(listaPacientes, sizePacientes);
				ordenarEspecialidadPorId();
				system("pause");
			break;

			case 8:
				mostrarEspecialidad();
				idEspecialidad=PedirEntero("Ingrese especialidad.\n");
				respuesta=mostrarEntreAbilJunio(idEspecialidad, listaPacientes, sizePacientes);

				if(respuesta==0)
				{
					printf("No hay pacientes con estas caracteristicas.\n");
				}
				system("pause");
			break;

			case 9:
				contarConsultasDiagnosticadas(listaPacientes, sizePacientes);
				system("pause");
			break;

			case 10:
				contadorEnfermedades(listaPacientes, sizePacientes);
				system("pause");
			break;

			case 11:
				contadorEspecialidad();
				system("pause");
			break;

			case 12:
				mostrarObraSocial();
				idObraSocial=PedirEntero("Ingrese que obra social quiere listar");
				mostrarMedicosConConsultas2021(listaPacientes, sizePacientes, idObraSocial);
				system("pause");
			break;

			case 13:
			break;

			default:
				printf("Opcion incorrecta.\n");
			break;

		}

	}while(opcion!=13);
}
void mostrarMedicosConConsultas2021(sPaciente listaPacientes[], int sizePacientes, int idObraSocial)
{
	int bandera;
	for(int i=0;i<sizeMedicos;i++)
	{
		printf("%s\n",listaMedicos[i].nombreMedico);
		bandera=mostrarPacientesPorMedicosConConsultas2021(listaPacientes, sizePacientes, idObraSocial, listaMedicos[i].idMedico);
		if(bandera==0)
		{
			printf("No tiene ningun paciente que cumpla estas condiciones.\n");
		}
	}
}
int mostrarPacientesPorMedicosConConsultas2021(sPaciente listaPacientes[], int sizePacientes, int idObraSocial, int idMedico)
{
	int bandera;
	bandera=0;
	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==lleno && listaPacientes[i].idMedico==idMedico && listaPacientes[i].fechaConsulta.anio==2021 && listaPacientes[i].idObraSocial==idObraSocial && listaPacientes[i].idDiagnostico!=sinDiagnostico)
		{
			bandera=1;
			mostrarPacientes(listaPacientes[i]);
		}
	}
	return bandera;
}
void contadorEspecialidad()
{
	int contadorEspecialidad[sizeEspecialidad];

	for(int i=0;i<sizeEspecialidad;i++)
	{
		contadorEspecialidad[i]=0;
	}

	for(int i=0;i<sizeMedicos;i++)
	{
		switch(listaMedicos[i].idEspecialidad)
		{

			case 1:
				contadorEspecialidad[0]++;
			break;

			case 2:
				contadorEspecialidad[1]++;
			break;

			case 3:
				contadorEspecialidad[2]++;
			break;

			case 4:
				contadorEspecialidad[3]++;
			break;

		}
	}

	mostrarEspecialidadMasEstudiada(contadorEspecialidad);

}
void mostrarEspecialidadMasEstudiada(int contadorEspecialidad[])
{
	if(contadorEspecialidad[0]>contadorEspecialidad[1] && contadorEspecialidad[0]>contadorEspecialidad[2])
		{
			printf("La especialidad mas estudiada es %s.\n",listaEspecialidad[0].descripcion);
		}
		else
		{
			if(contadorEspecialidad[1]>contadorEspecialidad[2])
			{
				if(contadorEspecialidad[0]==contadorEspecialidad[1])
				{
					printf("Las especialidades mas estudiadas son %s y %s.\n",listaEspecialidad[1].descripcion,listaEspecialidad[0].descripcion);
				}
				else
				{
					printf("La especialidad mas estudiada es %s.\n",listaEspecialidad[0].descripcion);
				}

			}
			else
			{
				if(contadorEspecialidad[0]==contadorEspecialidad[2])
				{
					printf("Las especialidades mas estudiadas son %s y %s.\n",listaEspecialidad[2].descripcion,listaEspecialidad[0].descripcion);
				}
				else
				{
					if(contadorEspecialidad[1]==contadorEspecialidad[2])
					{
						printf("Las especialidades mas estudiadas son %s y %s.\n",listaEspecialidad[2].descripcion,listaEspecialidad[1].descripcion);

					}
					else
					{
						printf("La especialidad mas estudiada es %s.\n",listaEspecialidad[2].descripcion);
					}
				}

			}
		}
}

void contadorEnfermedades(sPaciente listaPacientes[], int sizePacientes)
{
	int contadorPorEnfermedad[sizeDiagnostico];

	for(int i=0;i<sizeDiagnostico;i++)
	{
		contadorPorEnfermedad[i]=0;
	}

	for(int i=0;i<sizePacientes;i++)
	{
		switch(listaPacientes[i].idDiagnostico)
		{
			case 0:
			break;

			case 1:
				contadorPorEnfermedad[1]++;
			break;

			case 2:
				contadorPorEnfermedad[2]++;
			break;

			case 3:
				contadorPorEnfermedad[3]++;
			break;
		}

	}

	mostrarEnfermedadMenosDiagnosticada(contadorPorEnfermedad);



}
void mostrarEnfermedadMenosDiagnosticada(int contadorPorEnfermedad[])
{
	if(contadorPorEnfermedad[1]<contadorPorEnfermedad[2] && contadorPorEnfermedad[1]<contadorPorEnfermedad[3])
	{
		printf("La enfermedad menos diagnosticada es %s.\n",listaDiagnosticos[1].descripcion);
	}
	else
	{
		if(contadorPorEnfermedad[2]<contadorPorEnfermedad[3])
		{
			if(contadorPorEnfermedad[1]==contadorPorEnfermedad[2])
			{
				printf("Las enfermedades menos diagnosticada son %s y %s.\n",listaDiagnosticos[2].descripcion,listaDiagnosticos[1].descripcion);
			}
			else
			{
				printf("La enfermedad menos diagnosticada es %s.\n",listaDiagnosticos[2].descripcion);
			}

		}
		else
		{
			if(contadorPorEnfermedad[1]==contadorPorEnfermedad[3])
			{
				printf("Las enfermedades menos diagnosticada son %s y %s.\n",listaDiagnosticos[3].descripcion,listaDiagnosticos[1].descripcion);
			}
			else
			{
				if(contadorPorEnfermedad[2]==contadorPorEnfermedad[3])
				{
					printf("Las enfermedades menos diagnosticada son %s y %s.\n",listaDiagnosticos[3].descripcion,listaDiagnosticos[2].descripcion);

				}
				else
				{
					printf("La enfermedad menos diagnosticada es %s.\n",listaDiagnosticos[3].descripcion);
				}
			}

		}
	}
}
void contarConsultasDiagnosticadas(sPaciente listaPacientes[], int sizePacientes)
{
	int contadorConsultasDiagnosticadas=0;
	int contadorPorMedico[sizeMedicos];

	for(int i=0;i<sizeMedicos;i++)
	{
		contadorPorMedico[i]=contarConsultasDiagnosticadasPorMedico(listaMedicos[i].idMedico,listaPacientes, sizePacientes, &contadorConsultasDiagnosticadas);

	}
	mostrarPromedioConsultasDiagnosticadas(contadorConsultasDiagnosticadas, contadorPorMedico);

}
void mostrarPromedioConsultasDiagnosticadas(int contadorConsultasDiagnosticadas,int contadorPorMedico[])
{
	float porcentaje;


	for(int i=0;i<sizeMedicos;i++)
	{
		porcentaje=((float)contadorPorMedico[i])*100/contadorConsultasDiagnosticadas;

		printf("%s\nEl porcentaje de consultas diagnosticadas es de:%s%.2f\n\n",listaMedicos[i].nombreMedico,"%",porcentaje);
	}
}
int contarConsultasDiagnosticadasPorMedico(int idMedico, sPaciente listaPacientes[], int sizePacientes, int* contadorConsultasDiagnosticadas )
{
	int contador;
	contador=0;

	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==lleno && listaPacientes[i].idDiagnostico!=sinDiagnostico && idMedico==listaPacientes[i].idMedico)
		{
			contador++;
			*contadorConsultasDiagnosticadas=*contadorConsultasDiagnosticadas+1;
		}

	}

	return contador;
}
int mostrarEntreAbilJunio(int idEspecialidad, sPaciente listaPacientes[], int sizePacientes)
{
	int bandera;
	bandera=0;

	for(int i=0;i<sizePacientes;i++)
	{
		if(idEspecialidad==listaPacientes[i].idEspecialidad && listaPacientes[i].fechaConsulta.mes>3 && listaPacientes[i].fechaConsulta.mes<8)
		{
			bandera=1;
			mostrarPacientes(listaPacientes[i]);
		}

	}
	return bandera;
}
void mostrarEspecialidad()
{
	for(int i=0;i<sizeEspecialidad;i++)
	{
		printf("%d. %s.\n",listaEspecialidad[i].idEspecialidad,listaEspecialidad[i].descripcion);
	}
}
void ordenarEspecialidadPorId()
{
	sEspecialidadMedico aux;

	for(int i=0;i<sizeEspecialidad;i++)
	{
		for(int j=i+1;j<sizeEspecialidad;j++)
		{
			if(listaEspecialidad[i].idEspecialidad>listaEspecialidad[j].idEspecialidad)
			{
				aux= listaEspecialidad[i];
				listaEspecialidad[i]=listaEspecialidad[j];
				listaEspecialidad[j]=aux;
			}
		}
	}
}
void ordenarEspecialidad()
{
	sEspecialidadMedico aux;

	for(int i=0;i<sizeEspecialidad;i++)
	{
		for(int j=i+1;j<sizeEspecialidad;j++)
		{
			if(strcmp(listaEspecialidad[i].descripcion,listaEspecialidad[j].descripcion)>0)
			{
				aux= listaEspecialidad[i];
				listaEspecialidad[i]=listaEspecialidad[j];
				listaEspecialidad[j]=aux;
			}
		}
	}
}
void mostrarPorEspecialidad(sPaciente listaPacientes[], int sizePacientes)
{
	for(int i=0;i<sizeEspecialidad;i++)
	{
		mostrarPacientesPorEspecialidad(listaEspecialidad[i].idEspecialidad, listaPacientes, sizePacientes);

	}
}
void mostrarPacientesPorEspecialidad(int idEspecialidad, sPaciente listaPacientes[], int sizePacientes)
{
	for(int i=0;i<sizePacientes;i++)
	{
		if(idEspecialidad==listaPacientes[i].idEspecialidad)
		{
			mostrarPacientes(listaPacientes[i]);
		}

	}
}
void ordenarPorFechaMayor(sPaciente listaPacientes[], int sizePacientes)
{
	sPaciente aux;


	for(int i=0;i<sizePacientes;i++)
	{
		for(int j=i+1;j<sizePacientes;j++)
		{
			if(listaPacientes[i].fechaConsulta.anio<listaPacientes[j].fechaConsulta.anio)
			{
				aux= listaPacientes[i];
				listaPacientes[i]=listaPacientes[j];
				listaPacientes[j]=aux;

			}
			else
			{
				if(listaPacientes[i].fechaConsulta.anio==listaPacientes[j].fechaConsulta.anio)
				{
					if(listaPacientes[i].fechaConsulta.mes<listaPacientes[j].fechaConsulta.mes)
					{
						aux= listaPacientes[i];
						listaPacientes[i]=listaPacientes[j];
						listaPacientes[j]=aux;
					}
					else
					{
						if(listaPacientes[i].fechaConsulta.mes==listaPacientes[j].fechaConsulta.mes)
						{
							if(listaPacientes[i].fechaConsulta.dia<listaPacientes[j].fechaConsulta.dia)
							{
								aux= listaPacientes[i];
								listaPacientes[i]=listaPacientes[j];
								listaPacientes[j]=aux;
							}
						}
					}
				}
			}
		}
	}
}
void ordenarPorIdPacientes(sPaciente listaPacientes[], int sizePacientes)
{
	sPaciente aux;

		for(int i=0;i<sizePacientes;i++)
		{
			for(int j=i+1;j<sizePacientes;j++)
			{
				if(listaPacientes[i].idPaciente>listaPacientes[j].idPaciente)
				{
					aux= listaPacientes[i];
					listaPacientes[i]=listaPacientes[j];
					listaPacientes[j]=aux;
				}
			}
		}

}
void mostrarPacientesCovid(sPaciente listaPacientes[],int sizePacientes)
{


	for(int i=0; i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==lleno && listaPacientes[i].idDiagnostico==listaDiagnosticos[1].idDiagnostico && listaPacientes[i].fechaConsulta.anio>2019)
		{
			if(listaPacientes[i].fechaConsulta.anio==2020)
			{
				switch(listaPacientes[i].fechaConsulta.mes)
				{
					case 1:
					case 2:
					break;

					case 3:
						if(listaPacientes[i].fechaConsulta.dia>15)
						{
							mostrarPacientes(listaPacientes[i]);
						}
					break;

					default:
						mostrarPacientes(listaPacientes[i]);
					break;

				}

			}
			else
			{
				mostrarPacientes(listaPacientes[i]);
			}
		}

	}
}
void mostrarMedicosConPacientes(sPaciente listaPacientes[], int sizePacientes)
{
	int bandera;

	for(int i=0;i<sizeMedicos;i++)
	{
		bandera=buscarPacienteConDiagnostico(listaMedicos[i], listaPacientes, sizePacientes);
		if(bandera==0)
		{
			printf("Este medico no tiene pacientes Diagnosticados.\n");
		}

	}
	printf("\n__________________________________________________\n");
}
int buscarPacienteConDiagnostico(sMedico unMedico,sPaciente listaPacientes[], int sizePacientes)
{
	int bandera;
	int indexEspecialidad;

	bandera=0;
	indexEspecialidad=buscarEspecialidad(unMedico);
	printf("\n__________________________________________________\n");
	printf("%s (%s)\nLista de pacientes:\n",unMedico.nombreMedico,listaEspecialidad[indexEspecialidad].descripcion);



	for(int i=0; i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==lleno && unMedico.idMedico==listaPacientes[i].idMedico && listaPacientes[i].idDiagnostico!=sinDiagnostico)
		{
			bandera=1;
			mostrarPacientes(listaPacientes[i]);

		}

	}
	return bandera;

}
void mostrarListaDiagnosticados(sPaciente listaPacientes[], int sizePacientes)
{



	printf("%5s||%10s||%10s||%15s||%19s||%13s||%15s\n","Id","Nombre","Fecha","Obra Social",
														"Medico","Especialidad","Diagnostico");
	printf("_______________________________________________________________________________________________________\n\n");

	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==lleno && listaPacientes[i].idDiagnostico!=sinDiagnostico )//Verifica que la posicion que va a mostrar este llena.
		{
			mostrarPacientes(listaPacientes[i]);
			/*indexMedico=buscarMedico(listaPacientes[i],&indexEspecialidad);//Busca la posicion donde los idMedico son iguales y lo guarda en indexMedico.
			indexDiagnostico=buscarDiagnostico(listaPacientes[i]);
			indexObraSocial=buscarObraSocial(listaPacientes[i]);
			mostrarUnPaciente(listaPacientes[i],listaMedicos[indexMedico],
								listaDiagnosticos[indexDiagnostico],
								listaEspecialidad[indexEspecialidad],
								listaObraSocial[indexObraSocial]);//Muestro un paciente*/

		}
	}

}
void mostrarPacientes(sPaciente unPaciente)
{
	int indexMedico;
	int indexDiagnostico;
	int indexEspecialidad;
	int indexObraSocial;


	indexMedico=buscarMedico(unPaciente,&indexEspecialidad);//Busca la posicion donde los idMedico son iguales y lo guarda en indexMedico.
	indexDiagnostico=buscarDiagnostico(unPaciente);
	indexObraSocial=buscarObraSocial(unPaciente);
	mostrarUnPaciente(unPaciente,listaMedicos[indexMedico],
						listaDiagnosticos[indexDiagnostico],
						listaEspecialidad[indexEspecialidad],
						listaObraSocial[indexObraSocial]);//Muestro un paciente
}
