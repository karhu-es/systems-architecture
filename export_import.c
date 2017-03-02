/**CFile***********************************************************************

  Fichero     [export_import.c]

  Resumen     [Fichero que contiene las funciones necesarias para exportar e 
	      importar los datos de la lista enlazada.]

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

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÍFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÍAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#include "export_import.h"

/*---------------------------------------------------------------------------*/
/* Definición de las funciones                                               */
/*---------------------------------------------------------------------------*/

/**Función********************************************************************

  Resumen      Exporta todos los libros añadidos a un fichero escritos en binario.

  Parámetros   @param head  El primer elemento de la lista de libros añadidos a recorrer.
	       @param nombre El nombre del fichero dónde lo queremos exportar.

  Efec. Colat. Que haya demasiados libros a importar y tarde tiempo en exportar.

  Ver también  Comprobar que hay libros añadidos.

******************************************************************************/

void exportar_libros(nodo_ptr *head, char *nombre){
BEGINF(exportar_libros, 100317556, 100318675, 100317575, 100318675)
    FILE *archivo_nuevo;
    int contador = 0;
    struct book_info aux;
   
    if(head != NULL) {
	if ((archivo_nuevo = fopen(nombre, "wb")) == NULL)
	{ 
	  fprintf (stderr, ERRORARCH);
	} else {
	  while(head != NULL){
	    aux = head->datos;
	    fwrite(&aux, sizeof(struct book_info), 1, archivo_nuevo);
	    escribir_string_fichero(head->datos.ptr_title, archivo_nuevo);
	    escribir_string_fichero(head->datos.ptr_name, archivo_nuevo);
	    escribir_string_fichero(head->datos.ptr_surname, archivo_nuevo);
	    contador++;
	    head = head->siguiente;
	  }
	  printf(ESCRITOS, contador, nombre);
	  fclose(archivo_nuevo); 
	}
    } else {
	  printf(NOHAY);
    }
ENDF(exportar_libros)	
}

/**Función********************************************************************

  Resumen      Escribe el tamaño del String y a continuación su valor.

  Parámetros   @param s String que queremos escribir en el fichero
	       @param f Fichero donde se escribe el String

  Efec. Colat. Que el String sea igual a NULL.

******************************************************************************/

void escribir_string_fichero(char *s, FILE *f){
BEGINF(escribir_string_fichero, 100317556, 100318675, 100317575, 100318675)
	int n = strlen(s);
	fwrite(&n, sizeof(int), 1, f);
	fwrite(s, sizeof(char), n, f);
ENDF(escribir_string_fichero)
}
		
/**Función********************************************************************

  Resumen      Lee el string del fichero binario

  Parámetros   @param fichero Corresponde al fichero donde lee.
	       @return string String leído desde el fichero.	

  Efec. Colat. Que no haya nada por leer es decir, que el fichero esté vacío.

******************************************************************************/

char * leer_string_fichero(FILE *f){
BEGINF(leer_string_fichero, 100317575, 100307091, 100317556, 100307091)
   int tamano;
    int leidos = fread(&tamano, sizeof(int), 1, f);
    char * string;
    
    if(leidos != 1 || tamano < 0){
      fprintf(stderr, "Error de lectura\n");
    } else {
      string = calloc(tamano+1, sizeof(char));
      leidos = fread(string, sizeof(char), tamano, f);
	if(leidos != tamano){
	  fprintf(stderr, "Error de lectura\n");
	}
    }
    return string;
ENDF(leer_string_fichero)
}
 
 /**Función********************************************************************

  Resumen      Importa los datos del fichero binario a una estructura para añadirlos a una lista.

  Parámetros   @param head Primer elemento de la lista.
	       @param nombre Nombre del fichero binario que se va a leer.
	       @return head Devuelve el primer elemento después de importar los libros leídos a la lista.

  Efec. Colat. Que el fichero esté vacío o no exista.

******************************************************************************/
 
nodo_ptr *importar_libros(nodo_ptr *head, char *nombre){
BEGINF(importar_libros, 100317575, 100318675, 100317556, 100318675)
    FILE *ptr_archivo;
    int contador = 0;
    struct book_info aux;
   
    if ((ptr_archivo = fopen(nombre, "rb")) == NULL)
    { 
      fprintf (stderr, ERRORARCH);
    } 
    else
    {
      while(fread(&aux, sizeof(struct book_info), 1, ptr_archivo)){
	aux.ptr_title = leer_string_fichero(ptr_archivo);
	aux.ptr_name = leer_string_fichero(ptr_archivo);
	aux.ptr_surname = leer_string_fichero(ptr_archivo);
	printf(CARGANDO, aux.l_book_id);
	head = insertar_importados(&aux, head);
	contador++;
      }
      printf(LEIDOS, contador, nombre);
      fclose(ptr_archivo);
    }  
    return head;
ENDF(importar_libros)
}

/**Función********************************************************************

  Resumen      Pregunta al usuario si desea importar de un fichero y perder los datos guardados.

  Descripción  En caso de que el usuario confirme la importación, se borra la lista y se importan los datos leídos.

  Parámetros   @param head Comienzo de la lista
	       @param nombre El nombre del fichero binario a leer 
	       @return head Devuelve el primer elemento de la lista enlazada después de importar.

  Efec. Colat. Fugas de memoria, bucle por respuesta incorrecta por parte del usuario

******************************************************************************/

nodo_ptr *importar_seguro(nodo_ptr *head, char *f){
BEGINF(importar_seguro, 100317575, 100307091, 100317556, 100307091)
    printf(IMPORTSEGURO);
    char *respuesta = string_read();   
    if(strcasecmp(respuesta, "s") == 0){
      free(respuesta);
      if(head != NULL){
	borrar_lista(head);
	head = NULL;
      } 
      head = importar_libros(head, f);
    }else if(strcasecmp(respuesta, "N") == 0){
      free(respuesta);
    } else {
      free(respuesta);
      importar_seguro(head, f);
    }   
    return head;
ENDF(importar_seguro)
}
