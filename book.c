/**CFile***********************************************************************

  Fichero     [book.c]
  
  Resumen     [Fichero para las funciones que muestran información de los libros.]

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
  TIPO DE GARANTÃAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#include "book.h"

/*---------------------------------------------------------------------------*/
/* DefiniciÃ³n de las funciones                                               */
/*---------------------------------------------------------------------------*/


/**Funciónn********************************************************************

  Resumen       Función que pide la entrada de informacion por teclado para crear un libro.

  Parámetros   @param ptr_book Un puntero a una estructura de tipo struct book_info.
		@return ptr_book Devuelve la estructura del libro actualizada.

  Efec. Colat.  Todos los efectos están controlados. La entrada de un dato de otro tipo será sustituida por un int(0) en señal de error.

******************************************************************************/

struct book_info *crear_libro(struct book_info *ptr_book){
BEGINF(crear_libro, 100318675, 100317556, 100307091, 100317556)  
    printf(INTRODUZCASIG);
    printf(QIDLIBRO);
    ptr_book->l_book_id = int_read();
    printf(QTITLIBRO);
    ptr_book->ptr_title = string_read();
    printf(QNUMPAGINAS);
    ptr_book->i_num_pages = int_read();
    printf(QANYO);
    ptr_book->i_year = int_read();
    printf(QCALIDAD);
    ptr_book->f_quality = float_read();
    printf(QAUTORID);
    ptr_book->l_author_id = int_read();
    printf(QAUTORN);
    ptr_book->ptr_name = string_read();
    printf(QAUTORA);
    ptr_book->ptr_surname = string_read();
    printf(LIBROCREADO, ptr_book->l_book_id, ptr_book->ptr_title);
    return ptr_book;
ENDF(crear_libro)
}

/**Función********************************************************************

  Resumen      Imprime la información del libro resumida.

  Parámetros  @param ptr_book Se pasa un libro por parámetro.  

  Efec. Colat. No esperados.

******************************************************************************/

void mostrar_resumen(struct book_info ptr_book){
BEGINF(mostrar_resumen, 100318675, 100317556, 100307091, 100317556) 
    LISTALIBRO(ptr_book.l_book_id, ptr_book.ptr_title, ptr_book.l_author_id);
ENDF(mostrar_resumen)
}

/**Funciónn********************************************************************

  Resumen      Obtiene un libro por parámetro y lo imprime detalladamente.

  ParÃ¡metros  @param ptr_book Se pasa un libro por parámetro. 

  Efec. Colat. No esperados.

******************************************************************************/

void mostrar_libro(struct book_info ptr_book){
BEGINF(mostrar_libro, 100291133, 100317575, 100318675, 100317575) 
    printf(DETALLADA, ptr_book.l_book_id);
    printf(IDLIBROF, ptr_book.l_book_id, ptr_book.l_book_id);
    printf(TITLIBROF, ptr_book.l_book_id, ptr_book.ptr_title);
    printf(ANYOF, ptr_book.l_book_id, ptr_book.i_year);
    printf(NUMPAGINASF, ptr_book.l_book_id, ptr_book.i_num_pages);
    printf(CALIDADF, ptr_book.l_book_id, ptr_book.f_quality);
    printf(AUTIDF, ptr_book.l_book_id, ptr_book.l_author_id);
    printf(AUTORNF, ptr_book.l_book_id, ptr_book.ptr_name);
    printf(AUTORAF, ptr_book.l_book_id, ptr_book.ptr_surname);
ENDF(mostrar_libro)
}

/**Función********************************************************************

  Resumen      Obtiene un libro por parámetro e imprime la información resumida, incluyendo la calidad.

  Parámetros  @param ptr_book Se pasa un libro por parámetro. 

  Efec. Colat. No esperados.

******************************************************************************/

void mostrar_resumen_calidad(struct book_info ptr_book){
BEGINF(mostrar_resumen_calidad, 100291133, 100317575, 100318675, 100317575) 
      LISTALIBROCALIDAD(ptr_book.l_book_id, ptr_book.ptr_title, ptr_book.l_author_id, ptr_book.f_quality);
ENDF(mostrar_resumen_calidad)
}