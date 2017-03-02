/**CHeaderFile*****************************************************************
 
  Fichero     [linked_list.c]
 
  Resumen     [Fichero que contiene las funciones de la lista enlazada.]
 
  Autor       [100317575, 100307091, 100317556, 100318675, 100291133]
 
  Copyright   [Copyright (c) 2012 Universidad Carlos III de Madrid
 
  Se concede, sin necesidad de acuerdo por escrito y sin ningún tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentación para cualquier propósito siempre y cuando esta advertencia
  y los siguientes dos párrafos aparezcan en las copias.
 
  EN NINGÚN CASO SE RECONOCERÁ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
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
 
#include "linked_list.h"

/*---------------------------------------------------------------------------*/
/* Definición de las funciones                                               */
/*---------------------------------------------------------------------------*/

/**FunciÃ³n********************************************************************

  Resumen       Borra toda la información del nodo que le pasas por parámetro.

  ParÃ¡metros   @param nodo Nodo a borrar.

  Efec. Colat.  Que el nodo esté vacío y sea un free nulo.


******************************************************************************/

void destruir_nodo(nodo_ptr *nodo){
BEGINF(destruir_nodo, 100317556, 100307091, 100317575, 100307091)
    free(nodo->datos.ptr_title);
    free(nodo->datos.ptr_name);
    free(nodo->datos.ptr_surname);
    free(nodo);
ENDF(destruir_nodo)
}

/**Función********************************************************************

  Resumen        Esta función borra la lista entera.

  Parámetros    @param head Primer elemento de la lista a borrar.

  Efec. Colat.   No se esperan fallos.

******************************************************************************/

void borrar_lista(nodo_ptr *head){
BEGINF(borrar_lista, 100317556, 100307091, 100317575, 100307091)
    if(head != NULL){
      borrar_lista(head->siguiente);
      destruir_nodo(head);
    } 
ENDF(borrar_lista)
}

/**Función********************************************************************

  Resumen       Inserta un nuevo nodo a la lista enlazada con la información del libro que pasamos como parámetro.

  Parámetros   @param dato Libro que queremos añadir a la lista enlazada.
	        @param head Primer elemento de la lista a la que queremos añadir el libro.
	        @return nuevo_nodo Como se inserta por el principio, el nodo creado será la cabecera después de insertar.

  Efec. Colat.  Que la estructura del libro esté vacía.

******************************************************************************/

nodo_ptr *insertar_lista(struct book_info *dato, nodo_ptr *head){
BEGINF(insertar_lista, 100317556, 100318675, 100317575, 100318675)
    nodo_ptr *nuevo_nodo;
    nuevo_nodo = (nodo_ptr *)malloc(sizeof(nodo_ptr));
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->datos = *dato;
 
    if(head == NULL)
    {
      head = nuevo_nodo;
    } 
    else
    {
      nuevo_nodo->siguiente = head;
      head = nuevo_nodo;
    }
    return nuevo_nodo;
ENDF(insertar_lista)
}

/**Función********************************************************************

  Resumen       Esta función inserta un nuevo nodo al final de la lista.

  Parámetros   @param dato Libro que queremos añadir a la lista enlazada.
	        @param head Primer elemento de la lista a la que queremos añadir el libro.
	        @return head Como se inserta por al final, el primer elemento seguirá siendo el mismo.

  Efec. Colat.  Que la estructura del libro esté vacía.

******************************************************************************/

nodo_ptr *insertar_importados(struct book_info *dato, nodo_ptr *head){
BEGINF(insertar_importados, 100317575, 100318675, 100317556, 100318675)
    nodo_ptr *nuevo_nodo, *aux;
    aux = head;
    nuevo_nodo = (nodo_ptr *)malloc(sizeof(nodo_ptr));
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->datos = *dato;
 
    if(head == NULL)
    {
      head = nuevo_nodo;
    } 
    else
    {
      while(aux->siguiente != NULL){
	aux = aux->siguiente;
      }
      aux->siguiente = nuevo_nodo;
    }
    return head;
ENDF(insertar_importados)
}

/**Función********************************************************************

  Resumen       Esta función busca los archivos corruptos que son los que se repitan el ID del libro
		o los que tengan el mismo ID de autor pero distintos autores.

  Parámetros   @param head Primer elemento de la lista enlazada a recorrer.

  Efec. Colat.  No esperados.

******************************************************************************/

void mostrar_corruptos(nodo_ptr *head){
BEGINF(mostrar_corruptos, 100317575, 100317556, 100307091, 100317556)
  int corrupto = 0;
  nodo_ptr *aux, *aux2;
  if(head != NULL)
  {
    for(aux=head;aux!=NULL;aux=aux->siguiente){
      aux2 = aux->siguiente;
      for(;aux2!=NULL;aux2=aux2->siguiente){
	if(aux->datos.l_book_id == aux2->datos.l_book_id){
	  corrupto = 1;
	  printf(WRONG_SHAREDM, aux->datos.l_book_id);
	}
	if(aux->datos.l_author_id == aux2->datos.l_author_id){
	  if((strcasecmp(aux->datos.ptr_name, aux2->datos.ptr_name) != 0) || (strcasecmp(aux->datos.ptr_surname, aux2->datos.ptr_surname) != 0)){
	    corrupto = 1;
	    printf(WRONG_DUALM, aux->datos.l_author_id);
	    mostrar_libro(aux->datos);
	    mostrar_libro(aux2->datos);
	  }
	}
      }
    }
  } 
  if(corrupto == 0){
    printf(NOWRONG);
  }
ENDF(mostrar_corruptos)
}

/**Función********************************************************************

  Resumen        Esta función imprime por pantalla un resumen de todos los datos de la lista.

  Parámetros    @param head Primer elemento de la lista enlazada a recorrer.

  Efec. Colat.   No esperados.

******************************************************************************/

void imprimir_resumen(nodo_ptr *head){
BEGINF(imprimir_resumen, 100317556, 100291133, 100318675, 100291133)
      if(head != NULL){
	  CABECERALISTADO();
	  while(head != NULL){
	    mostrar_resumen(head->datos);
	    head = head->siguiente;
	  }
	  PIELISTADO();
      } else {
	  printf(NOHAY);
      }
ENDF(imprimir_resumen)
}

/**Función********************************************************************

  Resumen       Se busca un libro en la lista enlazada mediante el ID introducido por el usuario.
		Si existe un libro con ese ID se imprimen sus datos.

  Parámetros   @param book_id El identificador del libro.
	        @param head Primer elemento de la lista enlazada.

  Efec. Colat.  No esperados
******************************************************************************/

void imprimir_libro(long book_id, nodo_ptr *head) {
BEGINF(imprimir_libro, 100317556, 100291133, 100318675, 100291133)
    int correcto = -1;    
    while (head != NULL) {
      if (head->datos.l_book_id == book_id) {
	correcto = 0;
	break;
      }
      head = head->siguiente;      
    }
    if (correcto == 0) {
      mostrar_libro(head->datos);
    } else {
      printf(NOTFOUND, book_id);
    }
ENDF(imprimir_libro)
}
/**Función********************************************************************

  Resumen       Esta función permite modificar cualquier parametro del libro cuyo ID pasas por parámetro.

  Parámetros   @param head Primer elemento de la lista enlazada.

  Efec. Colat.  Que el usuario introduzca mal los datos.

******************************************************************************/

void modificar_porID(nodo_ptr *head){
BEGINF(modificar_porID, 100307091, 100317556, 100317575, 100317556)
    long id=0;
    nodo_ptr *aux;
    printf(DAMEIDLIBRO);     
    id = int_read();  
    if (head!=NULL){ 
      for(aux=head;aux!=NULL;aux=aux->siguiente){
        if(id == aux->datos.l_book_id){
	    printf(INTRODUZCASIG);
	    printf(QTITLIBRO);      
	    free(aux->datos.ptr_title);
	    aux->datos.ptr_title = string_read();
	    printf(QNUMPAGINAS);
	    aux->datos.i_num_pages = int_read();
	    printf(QANYO);
	    aux->datos.i_year = int_read();
	    printf(QCALIDAD);
	    aux->datos.f_quality = float_read();
	    printf(QAUTORID);
	    aux->datos.l_author_id = int_read();
	    printf(QAUTORN);
	    free(aux->datos.ptr_name);
	    aux->datos.ptr_name = string_read();
	    printf(QAUTORA);
	    free(aux->datos.ptr_surname);
	    aux->datos.ptr_surname = string_read();
	    printf(LIBROCREADO, aux->datos.l_book_id, aux->datos.ptr_title);
	    break;
        }else{
	    printf(NOTFOUND,id);
	}
      }
    }else{
      printf(NOTFOUND,id);
    }
ENDF(modificar_porID)
}

/**Función********************************************************************

  Resumen        Se encarga de borrar el nodo del libro con el ID que le pasamos 
		 por teclado, lo busca en la lista y lo borra.
  
  Parámetros    @param id_number ID del libro a borrar.
		 @param head Primer elemento de la lista enlazada.
		 @return head El primer elemento de la lista enlazada después de borrar el nodo de ese libro.

  Efec. Colat.   No esperados.

******************************************************************************/

nodo_ptr* borrar_libro(long id_number, nodo_ptr* head){
BEGINF(borrar_libro, 100318675, 100291133, 100307091, 100291133)
  if(head == NULL) {
    printf(NOTFOUND,id_number);
  }else{ 
    nodo_ptr* aux = head;
    if(aux->datos.l_book_id == id_number)
    {
      head = head->siguiente;
      destruir_nodo(aux);     
    } else {         
      nodo_ptr * aux = head -> siguiente;
      nodo_ptr * prev = head;
      if(aux == NULL)
      {
	  printf(NOTFOUND,id_number);
      } else {
	  while(aux != NULL && aux->datos.l_book_id != id_number) {
	    prev = prev-> siguiente;
	    aux = aux-> siguiente;
	  }
	  if(aux != NULL) 
	  {
	    prev->siguiente = aux->siguiente;
	    destruir_nodo(aux); 
	  } else {
	    printf(NOTFOUND,id_number);
	  }
      } 
    }
  }
  return head;
ENDF(borrar_libro)
}

/**Función********************************************************************

  Resumen   	Ordena la lista por calidades (la de mayor calidad primero).
  
  Parámetros    @param head Puntero al primer elemento de la lista enlazada.

  Efec. Colat.   No esperados.

******************************************************************************/

void ordenar_lista (nodo_ptr ** head){
BEGINF(ordenar_lista, 100307091, 100318675, 100317575, 100318675)
   nodo_ptr * aux = NULL;
   nodo_ptr * p;  
   if(*head != NULL){
    while (*head != NULL){
	p = *head;
	*head = (*head)->siguiente;
	if (aux == NULL || aux->datos.f_quality < p->datos.f_quality){
	  p->siguiente = aux;
	  aux = p;
	}else {
	  nodo_ptr * q = aux;
	  while (q->siguiente != NULL && q->siguiente->datos.f_quality >= p->datos.f_quality)
	  q = q->siguiente;
	  p->siguiente = q->siguiente;
	  q->siguiente = p;
	}
    }
    *head = aux;
   } else {
     printf(NOHAY);
   }
ENDF(ordenar_lista)
}

/**Función********************************************************************

  Resumen   	Recorre la lista ordenada por calidad y la imprime.
  
  Parámetros    @param head Puntero al primer elemento de la lista enlazada.

  Efec. Colat.   No esperados.

******************************************************************************/

void imprimir_resumen_calidad (nodo_ptr *head){
BEGINF(imprimir_resumen, 100317556, 100291133, 100318675, 100291133)
      if(head != NULL){
	  CABECERALISTADO();
	  while(head != NULL){
	    mostrar_resumen_calidad(head->datos);
	    head = head->siguiente;
	  }
      } else {
	  printf(NOHAY);
      }
ENDF(imprimir_resumen)
}