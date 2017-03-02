/**CHeaderFile*****************************************************************

  Fichero     [export_import.h]

  Resumen     [Fichero header para exportar e importar.]

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

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÍFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÍAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/
#ifndef EXPORT_IMPORT_H_
#define EXPORT_IMPORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
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
#define ERRORARCH "open file: Permission denied\n"
#define ESCRITOS "\n\t\tEscritos %d libros en \"\%.20s\""
#define LEIDOS "\n\t\tLeídos %d libros en \"\%.20s\""
#define CARGANDO "\n\t\tCargando ID: id %ld"
#define IMPORTSEGURO "\n\t\t\tVa a borrar todos los datos en memoria. ¿Desea continuar (s/N)?"
#endif
#ifdef LANG_EN  
#define ERRORARCH "open file: Permission denied\n"
#define ESCRITOS "\n\t\tWritten %d books in \"\%.20s\""
#define LEIDOS "\n\t\tRead %d books in \"\%.20s\""
#define CARGANDO "\n\t\tLoading ID: id %ld"
#define IMPORTSEGURO "\n\t\t\tYou are going to remove all in memory data.Do you want to follow (s/N)?"
#endif

/*
 * Añadir a partir de aquí las macros, tipos o cabeceras desarrolladas para el proyecto
 */

#include "linked_list.h"
#include "book.h"
#include "data_read.h"

/*---------------------------------------------------------------------------*/
/* Prototipos de las funciones                                               */
/*---------------------------------------------------------------------------*/
 
void exportar_libros(nodo_ptr *, char *);
void escribir_string_fichero(char *, FILE *);
char * leer_string_fichero(FILE *);
nodo_ptr *importar_libros(nodo_ptr *, char *);
nodo_ptr *importar_seguro(nodo_ptr *, char *);

#endif