/*
 * validaciones.h
 *
 *  Created on: 16 may. 2022
 *      Author: Sergio
 */

#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_
#include "pp.h"
#include "inputs.h"

/// \brief verifico que la fecha ingresada este entre el maximo y el minimo
/// \param fecha puntero de fecha que ingresa el usuario y donde la quiero guardar por si hay que pedir de nuevo la fecha
/// \param maximo maximo deseado
/// \param minimo minimo deseado
/// \param mensaje mensaje que se le muestra al usuario en caso de error
void validarFecha(int* fecha, int maximo, int minimo,char mensaje[]);
/// \brief verifica que el mes que se ingresa tengo la cantidad de dias que se ingreso anteriormente
/// \param dia. dia ingresado
/// \param mes. mes ingresado
void validarMes(int dia,int* mes);
/// \brief valida que la id ingresada exista en el arrays de medicos
/// \param listaMedicos. Arrays de medicos
/// \param sizeMedicos. tamaño de arryas de medicos
/// \param idMedico. puntero donde esta guardado lo que ingreso el usuario y donde quiero guardar el nuevo id en caso de error
void validarMedico(sMedico listaMedicos[], int sizeMedicos, int* idMedico);
/// \brief valida que la id ingresada exista en el arrays de diagnostico
/// \param listaDiagnostico. arrays de diagnostico
/// \param sizeDiagnostico. tamaño de arrays de diagnostico
/// \param idDiagnostico.puntero donde esta guardado lo que ingreso el usuario y donde quiero guardar el nuevo id en caso de error
void validarDiagnostico(sDiagnostico listaDiagnostico[], int sizeDiagnostico, int* idDiagnostico);
/// \brief valida que la id ingresada exista en el arrays de Obra social
/// \param listaObrasocial. Arrays de obra social
/// \param sizeObraSocial. Tamaño de arrays de obra social
/// \param idObraSocial.puntero donde esta guardado lo que ingreso el usuario y donde quiero guardar el nuevo id en caso de error
void validarObraSocial(sObraSocial listaObrasocial[], int sizeObraSocial, int* idObraSocial);



#endif /* VALIDACIONES_H_ */
