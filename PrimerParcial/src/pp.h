/*
 * pp.h
 *
 *  Created on: 16 may. 2022
 *      Author: Sergio
 */

#ifndef PP_H_
#define PP_H_

typedef struct
{
	int dia;
	int mes;
	int anio;

}sFecha;

typedef struct
{
	int idPaciente;
	char nombrePaciente[50];
	sFecha fechaConsulta;
	int idMedico;
	int estado;
	int idDiagnostico;
	int idObraSocial;
	int idEspecialidad;

}sPaciente;

typedef struct
{
	int idMedico;
	char nombreMedico[50];
	int idEspecialidad;

}sMedico;

typedef struct
{
	int idEspecialidad;
	char descripcion[50];
}sEspecialidadMedico;

typedef struct
{
	int idDiagnostico;
	char descripcion[50];

}sDiagnostico;

typedef struct
{
	int idObraSocial;
	char descripcion[50];

}sObraSocial;

/// \brief pone los estados en vacio y si estan llenos busca el id de especialidad
/// \param listaPacientes
/// \param sizePacientes
void ponerListaEnVacio(sPaciente listaPacientes[], int sizePacientes);
/// \brief Genera un id
/// \return retorna el id generado
int generadorId();
/// \brief Es donde se ingresan los datos del paciente
/// \return retorna una varaible sPciente con todos los datos
sPaciente ingresarUnPaciente();
/// \brief busca un lugra libre en la lista de pacientes
/// \param lista. Es el array de pacientes
/// \param size. el tamaño del array de pacientes
/// \return la posicion del array en donde esta libre.
int buscarLibre(sPaciente lista[], int size);
/// \brief carga un paciente en el array
/// \param lista. Es el array de pacientes
/// \param size. el tamaño del array de pacientes
/// \return retona si hubo un lugar libre o no.
int cargarEnLista(sPaciente lista[], int size);
/// \brief mustra los medicos.
void mostrarMedicos();
/// \brief muetra la lista de pacientes
/// \param listaPacientes.Es el array de pacientes
/// \param sizePacientes. el tamaño del array de pacientes
void mostrarListaPacientes(sPaciente listaPacientes[],int sizePacientes);
/// \brief busca los index de lo que tiene que mostrar.
/// \param unPaciente
void mostrarPacientes(sPaciente unPaciente);
/// \brief muestra un solo paciente
/// \param unPaciente. lista de paciente en la posicion que lo quiero mostrar
/// \param medico. lista de medicos en la posicion que lo quiero mostrar
/// \param diagnostico. lista de diagnostico  en la posicion que lo quiero mostrar
/// \param especialidad. lista de especialidad en la posicion que lo quiero mostrar
/// \param obraSocial. lista de obra social en la posicion que lo quiero mostrar
void mostrarUnPaciente(sPaciente unPaciente, sMedico medico, sDiagnostico diagnostico, sEspecialidadMedico especialidad, sObraSocial obraSocial);
/// \brief busca la posicion en donde el idMedico de un paciente es igual al id medico de la lista de medicos
/// \param unPaciente. Lista de paciente en una posicion
/// \param indexEspecialidad. Puntero en donde tiene que guardar la busqueda de especialidad
/// \return retorna el lugar donde son iguales los id
int buscarMedico(sPaciente unPaciente,int* indexEspecialidad);
/// \brief compara un id ingresado por el usuario con los id en la lista de pacientes
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
/// \param idIngresado. Id que ingreso el usuario
/// \return retorna el index de la posicion en la que los id son iguales
int encontrarPacientePorId(sPaciente listaPacientes[], int sizePacientes, int idIngresado);
/// \brief submenu que pide el ingreso de un id y al paciente seleccionado se le puede modificar lo que tiene cargado
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void modificarConsulta(sPaciente listaPacientes[],int sizePacientes);
/// \brief confirma si se quiere realizar la operacion
/// \param mensaje. Mensaje que se le muestra al usuario
/// \return retorna la respuesta
char confirmacion(char mensaje[]);
/// \brief le pide un id al paciente y lo valida
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
/// \return	retorna la posicion donde se encuentra el paciente buscado
int pedirIdPaciente(sPaciente listaPacientes[],int sizePacientes);
/// \brief cambia el estado del paciente elegido
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void darDeBaja(sPaciente listaPacientes[], int sizePacientes);
/// \brief pide el id del medico, muestra sus consultas sin diagnosticar, pide id del paciente que quiere diagnosticar, mustra diagnosticos y pide diagnostico
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void diagnosticar(sPaciente listaPacientes[], int sizePacientes);
/// \brief busca la posicion donde el id de la lista de diagnostico es igual al de la lista de pacientes
/// \param unPaciente. Una posicion del array del
/// \return retorna la posicion en donde son iguales
int buscarDiagnostico(sPaciente unPaciente);
/// \brief compara el id ingresado por el usuario con los id que se encuentran en la lista de medicos
/// \param idIngresado. Id que ingreso el usuario
/// \return retorna la posicion en donde son iguales
int buscarMedicoPorId(int idIngresado);
/// \brief compara los id medico ingresado con el que esta en la lista de pacientes, si no tiene diagnostico y sise cumple lo muestra
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
/// \param indexMedico. Id ingresado por el usuario
/// \return retorna una bandara que indica si se se imprimio o no algun paciente
int mostrarPacientesSinDiagnostico(sPaciente listaPacientes[], int sizePacientes, int indexMedico);
/// \brief muestra los diagnosticos
void mostrarDiagnosticos();
/// \brief busca la posicion donde el id de un medico es igual al de la lista de especialidades
/// \param unMedico. La lista de medicos en una posicion
/// \return retorna la posicion en la que son iguales
int buscarEspecialidad(sMedico unMedico);
/// \brief muestra la lista de obra social
void mostrarObraSocial();
/// \brief busca la posicion donde el idObraSocial de un paciente es igual al de la lista de obra social
/// \param unPaciente. La lista de pacientes en una posicion
/// \return la posicion en la que son iguales
int buscarObraSocial(sPaciente unPaciente);
/// \brief submenu de listar
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void mostrar(sPaciente listaPacientes[],int sizePacientes);
/// \brief muestra los pacientes que tienen diagnostico y tienen el mismo idMedico que el de un medico
/// \param unMedico. Lista medicos en una posicion
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
/// \return retorna si se mostro o no un paciente
int buscarPacienteConDiagnostico(sMedico unMedico,sPaciente listaPacientes[], int sizePacientes);
/// \brief
/// \param listaPacientes
/// \param sizePacientes
void mostrarMedicosConPacientes(sPaciente listaPacientes[], int sizePacientes);
/// \brief recorre el arrays de lista de medicos
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void mostrarListaDiagnosticados(sPaciente listaPacientes[], int sizePacientes);
/// \brief verifica que el paciente que tiene diagnosticado covid su fecha haya sido despues de la pandemia (16/3/2022)
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void mostrarPacientesCovid(sPaciente listaPacientes[],int sizePaciente);
/// \brief ordena los ide de los pacientes de menor a mayor
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void ordenarPorIdPacientes(sPaciente listaPacientes[], int sizePacientes);
/// \brief ordena la lista de pacientes por fecha de la mas actual a la mas antigua
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void ordenarPorFechaMayor(sPaciente listaPacientes[], int sizePacientes);
/// \brief ordena las especialidades por orden alfabetico
void ordenarEspecialidad();
/// \brief encuentra la especialidad por la que va a ser atendido el paciente segun el medico que tenga
/// \param unPaciente. la lista de paciente en una posicion del arrrays
/// \param idEspecialidad. lugar donde quiero que se guarde el id de la especialidad
void encontrarEspecialidad(sPaciente unPaciente ,int* idEspecialidad);
/// \brief ordena la especialidad por id de menor a mayor
void ordenarEspecialidadPorId();
/// \brief verifica que el id especialidad de la lista de pasajeros sea igual a idEspecialidad
/// \param idEspecialidad. id de la especialidad
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void mostrarPacientesPorEspecialidad(int idEspecialidad, sPaciente listaPacientes[], int sizePacientes);
/// \brief recorre el array de especialidad
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void mostrarPorEspecialidad(sPaciente listaPacientes[], int sizePacientes);
/// \brief muetra la lista de especialidad
void mostrarEspecialidad();
/// \brief muestra al paciente si los id especialidad son iguales y si la fecha entre entre el mes de junio y abril
/// \param idEspecialidad. Id de la especialidad
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
/// \return retorna si se imprimio un paciente o no
int mostrarEntreAbilJunio(int idEspecialidad, sPaciente listaPacientes[], int sizePacientes);
/// \brief cuenta la cantidad total de consultas diagnosticadas y la cantidad de consultas diagnosticadas por cada medico
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void contarConsultasDiagnosticadas(sPaciente listaPacientes[], int sizePacientes);
/// \brief saca el promedio y los muestra
/// \param contadorConsultasDiagnosticadas. cantidad total de consultas diagnosticadas
/// \param contadorPorMedico. cantidad de pacientes diagnosticador por medico
void mostrarPromedioConsultasDiagnosticadas(int contadorConsultasDiagnosticadas,int contadorPorMedico[]);
/// \brief recorre el array de pacientes verifica de que sea paciente del medico que se esta contando y cuenta cuantos estan diagnosticados
/// \param idMedico. Id del medico que quiero contar
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
/// \param contadorConsultasDiagnosticadas. Puntero donde quiero guardar la cantidad total
/// \return la cantidad por medico de consultas diagnosticadas
int contarConsultasDiagnosticadasPorMedico(int idMedico, sPaciente listaPacientes[], int sizePacientes, int* contadorConsultasDiagnosticadas );
/// \brief muestra el o las enfermedades menos diagnosticadas
/// \param contadorPorEnfermedad. Arrays de cantidades de personas por cada enfermedad
void mostrarEnfermedadMenosDiagnosticada(int contadorPorEnfermedad[]);
/// \brief cuenta cuantas personas padecen cada enfermedad
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
void contadorEnfermedades(sPaciente listaPacientes[], int sizePacientes);
/// \brief muetra la especialidad menos estudiada
/// \param contadorEspecialidad. arrays con cantidad de medicos por cada especialidad
void mostrarEspecialidadMasEstudiada(int contadorEspecialidad[]);
/// \brief cuenta cuantos medicos estudiaron cada especialidad
void contadorEspecialidad();
/// \brief recorre el arrays de medicos para poder mostrar la lista por medicos
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
/// \param idObraSocial. id de obra social que el usuario ingreso
void mostrarMedicosConConsultas2021(sPaciente listaPacientes[], int sizePacientes, int idObraSocial);
/// \brief recorre el arryas de pacientes, verifica que este lleno, que los id de medico sean iguales, que la fecha sea del 2021, que este diagnosticado y que el id de obra social sea el mismo que ingreso el usario
/// \param listaPacientes. array de pacientes
/// \param sizePacientes. tamaño del array de pacientes
/// \param idObraSocial. id de obra social que quiero mostrar
/// \param idMedico. id del medico que quiero mostrar
/// \return retorna si imprimio algo o no
int mostrarPacientesPorMedicosConConsultas2021(sPaciente listaPacientes[], int sizePacientes, int idObraSocial, int idMedico);















#endif /* PP_H_ */
