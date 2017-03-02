/**CHeaderFile*****************************************************************

  Fichero     [book.h]

  Resumen     [Archivo header para las funciones básicas de los libros.]

  Autor       [100317575, 100307091, 100317556, 100318675, 100291133]

  Copyright   [Copyright (c) 2012 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningún tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentación para cualquier propósito siempre y cuando esta advertencia
  y los siguientes dos párrafos aparezcan en las copias.

  EN NINGÚN CASO SE RECONOCERÁ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÑOS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÓN, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÑOS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÍFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÍAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/
#ifndef BOOK_H_
#define BOOK_H_

#include <stdio.h>
#include <stdlib.h>

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
#define INTRODUZCASIG "\n\t\tIntroduzca la siguiente información:\n"
#define QIDLIBRO "\t\t\tel ID del libro: "
#define QTITLIBRO "\t\t\tel título del libro: "
#define QNUMPAGINAS "\t\t\tel número de páginas: "
#define QANYO "\t\t\tel año de publicación: "
#define QCALIDAD "\t\t\tla calidad: "
#define QAUTORID "\t\t\tel identificador de autor: "
#define QAUTORN "\t\t\tel nombre del autor: "
#define QAUTORA "\t\t\tel apellido del autor: "
#define LIBROCREADO "\n\t\tLibro creado con id: %ld y título: %.20s."
#define DETALLADA "\n\t\tInformación detallada para ==(%ld)=="
#define IDLIBROF "\n\t\t=%ld= Identificador:            \t\t %ld"
#define TITLIBROF "\n\t\t=%ld= Título del libro:               \t \"%.40s\""
#define ANYOF "\n\t\t=%ld= Año de publicación:         \t %d "
#define NUMPAGINASF "\n\t\t=%ld= Número de páginas:            \t %d "
#define CALIDADF "\n\t\t=%ld= Calidad:                    \t %.2f "
#define AUTIDF "\n\t\t=%ld= Identificador de autor:        \t %ld "
#define AUTORNF "\n\t\t=%ld= Nombre del autor:              \t \"%.40s\""
#define AUTORAF "\n\t\t=%ld= Apellidos del autor:       \t\t \"%.40s\""
#endif
#ifdef LANG_EN 
#define INTRODUZCASIG "\n\t\tIntroduce the following information:\n"
#define QIDLIBRO "\t\t\tthe ID of the book: "
#define QTITLIBRO "\t\t\tthe title of the book: "
#define QNUMPAGINAS "\t\t\tthe number of pages: "
#define QANYO "\t\t\tthe publication year: "
#define QCALIDAD "\t\t\tthe quality: "
#define QAUTORID "\t\t\tthe ID of the author: "
#define QAUTORN "\t\t\tthe name of the author: "
#define QAUTORA "\t\t\tthe surname of the author: "
#define LIBROCREADO "\n\t\tAllocated book with id: %ld  and title: %.20s."
#define DETALLADA "\n\t\tDetailed information for ==(%ld)=="
#define IDLIBROF "\n\t\t=%ld= Identifier:            \t %ld"
#define TITLIBROF "\n\t\t=%ld= Title of the book:       \t \"%.40s\""
#define ANYOF "\n\t\t=%ld= Publication year:           \t %d "
#define NUMPAGINASF "\n\t\t=%ld= Number of pages:            \t %d "
#define CALIDADF "\n\t\t=%ld= Quality:                    \t %.2f "
#define AUTIDF "\n\t\t=%ld= Authors' ID:                \t %ld "
#define AUTORNF "\n\t\t=%ld= Authors' name:              \t \"%.40s\""
#define AUTORAF "\n\t\t=%ld= Surname of the author:       \t \"%.40s\""
#endif

#define LISTALIBRO(libroid, titulo, autorid) {printf("\t\t==|  %7ld | %20.20s | %10ld |\n", libroid, titulo,autorid);}
#define LISTALIBROCALIDAD(libroid, titulo, autorid, calidad) {printf("\t\t==|  %7ld | %20.20s | %10ld | %6.2f |\n", libroid, titulo, autorid, calidad);}

/*
 * Añadir a partir de aquí las macros, tipos o cabeceras desarrolladas para el proyecto
 */

#include "data_read.h"

/*---------------------------------------------------------------------------*/
/* Declaración de estructuras                                                */
/*---------------------------------------------------------------------------*/

/**Structura*******************************************************************

  Resumen     [Estructura con los campos comunes y necesarios para todos los libros.]

******************************************************************************/

struct book_info
{
    long l_book_id; 
    char *ptr_title; 
    int i_num_pages; 
    int i_year; 
    float f_quality; 
    long l_author_id; 
    char *ptr_name;
    char *ptr_surname;
};

/*---------------------------------------------------------------------------*/
/* Prototipos de las funciones                                               */
/*---------------------------------------------------------------------------*/

struct book_info *crear_libro(struct book_info *);
void mostrar_resumen(struct book_info);
void mostrar_libro(struct book_info);
void mostrar_resumen_calidad(struct book_info);

#endif