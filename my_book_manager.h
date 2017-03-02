/**CHeaderFile*****************************************************************

  Fichero     [my_book_manager.h]

  Resumen     [Fichero header principal del proyecto.]

  Autor       [100317575, 100307091, 100317556, 100318675, 100291133]

  Copyright   [Copyright (c) 2012 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningún tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentación para cualquier propósito siempre y cuando esta advertencia
  y los siguientes dos párrafos aparezcan en las copias.

  EN NINGÚN CASO SE RECONOCERÃ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÑOS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÓN, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÑOS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÃFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÃAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#ifndef MY_BOOK_MANAGER_H_
#define MY_BOOK_MANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#if defined(DEBUG)
#define BEGINF(a,b,c,d,e)  fprintf(stderr, "beginf %s creator=%s tester=%s integrator=%s systemtester=%s (%d)\n", #a, #b, #c, #d, #e __LINE__);
#define ENDF(a)  fprintf(stderr, "endf %s (%d)\n", #a, __LINE__);
#else
#define BEGINF(a,b,c,d,e) 
#define ENDF(a)
#endif

#ifndef LANG_EN
  #ifndef LANG_ES
  #define LANG_ES
  #endif
#endif

#ifdef LANG_ES  
#define OPCIONESMENU() {    printf("\n\t[0] \tSalir"); printf("\n\t[1] \tInsertar libro"); printf("\n\t[2] \tMostrar todos los libros"); printf("\n\t[3] \tMostrar un libro por ID"); printf("\n\t[4] \tModificar un libro por ID"); printf("\n\t[5] \tBorrar un libro por ID"); printf("\n\t[6] \tExportar catálago"); printf("\n\t[7] \tImportar catálago"); printf("\n\t[8] \tMostrar registros corruptos"); printf("\n\t[9] \tActivar autosalvado (cada 10 segundos)");    }
#define OPCIONESAVANZADAS() { printf("\n\t[10] \tMostrar todos los libros (ordenados por calidad)"); }
#define EJECUTADOS "\n\n\t\t#INFO: %4d comandos ejecutados.\n\t\tTeclee su opción [0-9]:  "
#define EJECUTADO "\n\n\t\t#INFO: %4d comando ejecutado.\n\t\tTeclee su opción [0-9]:  "
#define ERROR "\n\t\tIntroduzca una opción válida."
#define SALIRSEGURO "\n\t\tSeguro de que desea salir (s/N): "
#define DAMEIDLIBRO "\t\t\tDame el ID del libro: "
#define RUNNING "\n\t\t Autosave corriendo"
#endif
#ifdef LANG_EN  
#define OPCIONESMENU() {    printf("\n\t[0] \tExit"); printf("\n\t[1] \tInsert a book"); printf("\n\t[2] \tShow all books"); printf("\n\t[3] \tShow a book by ID"); printf("\n\t[4] \tModify a book by ID"); printf("\n\t[5] \tRemove a book by ID"); printf("\n\t[6] \tExport catalogue"); printf("\n\t[7] \tImport catalogue"); printf("\n\t[8] \tShow corrupt records"); printf("\n\t[9] \tActivate autosave (every 10 seconds)"); }
#define OPCIONESAVANZADAS() { printf("\n\t[10] \tShow all books (ordered by quality)"); }
#define EJECUTADOS "\n\n\t\t#INFO: %4d commands executed.\n\t\tType your option [0-9]:  "
#define EJECUTADO "\n\n\t\t#INFO: %4d command executed.\n\t\tType your option [0-9]:  "
#define ERROR "\n\t\tIntroduce a valid option."
#define SALIRSEGURO "\n\t\tReady to exit (s/N): "
#define DAMEIDLIBRO "\t\t\tGive me the ID of the book: "
#define RUNNING "\n\t\t Autosave running "
#endif

#define CABECERAMENU() {printf("\n\n\t=================================================="); printf("\n\t[*][2015][SAUCEM APPS][My_Book_Manager] =========="); printf("\n\t==================================================");}
#define NOMBREFICHERO	"data_demo.sbm"
#define THREADAUTOSAVE	"\n\t\t[THREAD_AUTOSAVE] %d"
#define THREADAUTOSAVEEXIT	"\n\t\t[TREAD_AUTOSAVE] Exiting\n"

/*
 * Añadir a partir de aquí las macros, tipos o cabeceras desarrolladas para el proyecto
 */

#include "data_read.h"
#include "linked_list.h"
#include "book.h"
#include "export_import.h"

/*---------------------------------------------------------------------------*/
/* Declaración de macros                                                     */
/*---------------------------------------------------------------------------*/

/**Macro***********************************************************************

  Resumen      [Constantes usadas para el campo de la estructura arg_hilos: modificado.]

  Efec. Colat. [No actualizar el valor del campo de la estructura en alguna función
		que modifique los datos de la lista enlazada. ]

******************************************************************************/

#define TRUE 1
#define FALSE 0

/*---------------------------------------------------------------------------*/
/* Declaración de estructuras                                                */
/*---------------------------------------------------------------------------*/

/**Structura*******************************************************************

  Resumen     [Estructura que contiene el primer elemento de la lista enlazada, 
	      un mutex para manejar los dos hilos, la opción que introduce el usuario 
	      por teclado y la variable modificado que indica si se ha realizado alguna 
	      operación que pudiese haber modificado los datos de la lista enlazada.]

  DescripciÃ³n [Manejamos las variables de la estructura para que los hilos usen los mismos valores.]

******************************************************************************/

struct arg_hilos
{
 nodo_ptr *head;
 pthread_mutex_t mutex;
 long opcion;
 int modificado;
};

/*---------------------------------------------------------------------------*/
/* Prototipos de las funciones                                               */
/*---------------------------------------------------------------------------*/

int salir();
void menu();
void *autosave(void *);
int main(int argc, char *argv[]);

 
#endif