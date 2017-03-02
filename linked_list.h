/**CHeaderFile*****************************************************************

  Fichero     [linked_list.h]

  Resumen     [Fichero header de las funciones de la lista enlazada.]

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
  TIPO DE GARANTÍAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>

#if defined(DEBUG)
#define BEGINF(a,b,c,d,e)  fprintf(stderr, "beginf %s creator=%s tester=%s integrator=%s systemtester=%s (%d)\n", #a, #b, #c, #d, #e __LINE__);

#define ENDF(a)  fprintf(stderr, "endf %s (%d)\n", #a, __LINE__);
#else
#define BEGINF(a,b,c,d,e) 
#define ENDF(a)
#endif

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
#define LIBROID "Libro id"
#define TIT20 "Título(20 caract.)"
#define AUTID "Autor id"
#define NOTFOUND "\n\t\tEl libro con id: %ld no ha sido encontrado."
#define INTRODUZCASIG "\n\t\tIntroduzca la siguiente información:\n"
#define DAMEIDLIBRO "\t\t\tDame el ID del libro: "
#define QTITLIBRO "\t\t\tel título del libro: "
#define QNUMPAGINAS "\t\t\tel número de páginas: "
#define QANYO "\t\t\tel año de publicación: "
#define QCALIDAD "\t\t\tla calidad: "
#define QAUTORID "\t\t\tel identificador de autor: "
#define QAUTORN "\t\t\tel nombre del autor: "
#define QAUTORA "\t\t\tel apellido del autor: "
#define LIBROCREADO "\n\t\tLibro creado con id: %ld y título: %.20s."
#define CABECERALISTADOCALIDAD "\t\t  CALIDAD | ID | TITULO Y AUTOR \n"
#define NOHAY "\n\t\tNo hay ningún libro.\n"
#define WRONG_SHAREDM "\n\t\t\[WRONG_SHARED ID] Dos libros con mismo ID: %ld"
#define WRONG_DUALM "\n\t\t[WRONG_DUAL_ID] Dos autores con mismo ID: %ld, pero distintos datos"
#define NOWRONG "\n\t\tNo hay entradas corruptas"
#endif
#ifdef LANG_EN  
#define INTRODUZCASIG "\n\t\tIntroduce the following information:\n"
#define DAMEIDLIBRO "\t\t\tGive me the ID of the book: "
#define QIDLIBRO "\t\t\tthe ID of the book: "
#define QTITLIBRO "\t\t\tthe title of the book: "
#define QNUMPAGINAS "\t\t\tthe number of pages: "
#define QANYO "\t\t\tthe publication year: "
#define QCALIDAD "\t\t\tthe quality: "
#define QAUTORID "\t\t\tthe ID of the author: "
#define QAUTORN "\t\t\tthe name of the author: "
#define QAUTORA "\t\t\tthe surname of the author: "
#define LIBROCREADO "\n\t\tAllocated book with id: %ld  and title: %.20s."
#define NOHAY "\n\t\tThere are no books.\n"
#define LIBROID "Book id"
#define TIT20 "Title (20 chars)"
#define AUTID "Author id"
#define NOTFOUND "\n\t\tThe book with id: %ld has not been found."
#define WRONG_SHAREDM "\n\t\t\[WRONG_SHARED ID] Two books with the same ID: %ld"
#define WRONG_DUALM "\n\t\t[WRONG_DUAL_ID] Two authors with the same ID: %ld, but different data"
#define NOWRONG "\n\t\tThere are not any corrupt records"
#define NOTFOUND "\n\t\tThe book with id: %ld has not been found."
#endif

#define CABECERALISTADO() { printf("\n\t\t=====================================================================================================\n"); printf("\t\t== \"%5s\" |\"%20s\"| \"%s\" ===================================================\n", LIBROID, TIT20, AUTID); printf("\t\t=====================================================================================================\n"); }
#define LISTALIBROCALIDAD(libroid, titulo, autorid, calidad) {printf("\t\t==|  %7ld | %20.20s | %10ld | %6.2f |\n", libroid, titulo, autorid, calidad);}
#define PIELISTADO() { printf("\t\t=====================================================================================================\n");}

/*
 * Añadir a partir de aquí las macros, tipos o cabeceras desarrolladas para el proyecto
 */

#include "book.h"

/*---------------------------------------------------------------------------*/
/* Declaración de estructuras                                                */
/*---------------------------------------------------------------------------*/

/**Structura*******************************************************************

  Resumen     [Estructura de cada nodo de la lista enlazada. 
	      Contiene una estructura de un libro y el puntero al nodo siguiente.]

  Descripción [Para facilitar la creación de nodos, hemos definido la estructura como tipo nodo_ptr.]

******************************************************************************/

struct nodo 
{
    struct book_info datos;
    struct nodo *siguiente;
};

typedef struct nodo nodo_ptr;

/*---------------------------------------------------------------------------*/
/* Prototipos de las funciones                                               */
/*---------------------------------------------------------------------------*/

void destruir_nodo(nodo_ptr *);
void borrar_lista(nodo_ptr *);
nodo_ptr *insertar_lista(struct book_info *, nodo_ptr *);
nodo_ptr *insertar_importados(struct book_info *, nodo_ptr *);
void mostrar_corruptos(nodo_ptr *);
void imprimir_resumen(nodo_ptr *);
void imprimir_libro(long, nodo_ptr *);
void modificar_porID(nodo_ptr *);
struct nodo* borrar_libro(long, nodo_ptr *);
void ordenar_lista (nodo_ptr **);
void imprimir_resumen_calidad (nodo_ptr *);
void mostrar_resumen_calidad(struct book_info);

#endif