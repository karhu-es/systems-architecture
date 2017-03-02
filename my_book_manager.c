/**CFile***********************************************************************

  Fichero     [my_book_manager.c]

  Resumen     [Fichero principal del proyecto.]

  Autor       [100317575, 100307091, 100317556, 100318675, 100291133]

  Copyright   [Copyright (c) 2012 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningÃºn tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentaciÃ³n para cualquier propÃ³sito siempre y cuando esta advertencia
  y los siguientes dos pÃ¡rrafos aparezcan en las copias.

  EN NINGÃšN CASO SE RECONOCERÃ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÃ‘OS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÃ“N, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÃ‘OS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÃFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÃAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÃCITAS
  DE LA COMERCIALIZACIÃ“N Y ADECUACIÃ“N PARA CUALQUIER PROPÃ“SITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÃ“N ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#include "my_book_manager.h"

/*---------------------------------------------------------------------------*/
/* Definición de las funciones                                               */
/*---------------------------------------------------------------------------*/

/**Función********************************************************************

  Resumen      Pregunta al usuario si desea salir del programa.

  Parámetros   @return -1 para terminar el programa. 0  para continuar.
  
  Efec. Colat. Que el usuario no introduzca bien los datos y se quede en bucle.

******************************************************************************/

int salir(){
BEGINF(salir, 100318675, 100317556, 100291133, 100317556)   
    printf(SALIRSEGURO);
    char *respuesta = string_read();
     
    if(strcasecmp(respuesta, "s") == 0){
      free(respuesta);
      return -1;
    }else if(strcasecmp(respuesta, "N") == 0){
      free(respuesta);
      return 1;
    } else {
      printf(ERROR);
      free(respuesta);
      return salir();
    }   
ENDF(salir)
}

/**Función********************************************************************

  Resumen      Imprime por pantalla el menú.   

  Efec. Colat. Ninguno.

******************************************************************************/

void menu(){
BEGINF(menu, 100291133, 100307091, 100318675, 100307091)
    CABECERAMENU();
    OPCIONESMENU();
#if defined(AVANZADAS)
    OPCIONESAVANZADAS();
#endif
ENDF(menu)
}

/**Función********************************************************************

  Resumen       Función que autosalva los datos introducidos siempre que hayan sido modificados los datos.

  DescripciÃ³n  Funcionamiento del hilo #2. Se tiene que haber activado la opción 9 del menú para crear dicho hilo.

  ParÃ¡metros   @param argumento estructura que contiene los datos necesarios para esta función.  
				-	head: el primer elemento de la lista enlazada de libros con la que estamos trabajando en el main. 
				-	mutex: para sincronizar el hilo principal y el hilo de autosalvado.				  
				-	opcion: opcion elegida por el usuario, para saber cuando decide terminar el programa.		  
				-	modificado: variable que indica si ha habido alguna modificación en los datos de la lista enlazada(TRUE). 
		@return NULL														  

  Efec. Colat. Que se realice el autosalvado aún siendo los mismos datos por haber hecho modificaciones en la lista.
  
******************************************************************************/

void *autosave(void *argumento){
BEGINF(autosave, 100317575, 100317556, 100307091, 100317556)
    struct arg_hilos *str = (struct arg_hilos *)argumento;
    int continuar = 1;
    int autosalvar = 1;
  
    do{
      pthread_mutex_lock(&str->mutex);
      autosalvar = str->modificado;
      if(str->head != NULL && autosalvar != FALSE){
	  printf(THREADAUTOSAVE, 1);
	  exportar_libros(str->head, "AUTOSAVE_demo.sbm");
	  str->modificado = FALSE;
      }
      continuar = str->opcion != EOF;
      pthread_mutex_unlock(&str->mutex);
      sleep(10);
    } while(continuar);
    return NULL;
ENDF(autosave)
}

/**Función********************************************************************

  Resumen      Lee una opción del menú por teclado y la ejecuta hasta que el usuario decida finalizar el programa.

  Parámetros   @param arg_count un valor entero
	       @param arg_strings[] una cadena de carácteres, String
	       @return 0 

  Efec. Colat. Que el usuario meta un valor que no coincida con ninguna posible opción del menú.

******************************************************************************/

int main(int arg_count, char *arg_strings[]) {
BEGINF(main, 100307091, 100317556, 100317575, 100317556)
    int leer;
    int contador = 0;
    int autosalvado = 0;
    pthread_t hilo2autosalvado;

    struct book_info ptr_book;
    struct arg_hilos estruct; 
    estruct.head=NULL;
    estruct.modificado = FALSE;

    pthread_mutex_init(&estruct.mutex, NULL);
    pthread_mutex_lock(&estruct.mutex);

    do
    {
      menu(); 
      if(contador == 1){
	  printf(EJECUTADO, contador);
      } else {
	  printf(EJECUTADOS, contador);
      }
      
      pthread_mutex_unlock(&estruct.mutex);
      leer = menu_read();
      pthread_mutex_lock(&estruct.mutex);
      
      estruct.opcion = leer;
      if(estruct.opcion > -1 && estruct.opcion < 11) {
	  contador++;
      }
	
      switch(estruct.opcion){
	    case -1:
	      break;
	    case 0:
	      estruct.opcion = salir();
	      break;
	    case 1:
	      crear_libro(&ptr_book);
	      estruct.head = insertar_lista(&ptr_book, estruct.head);
	      estruct.modificado = TRUE;
	      break;
	    case 2:
	      imprimir_resumen(estruct.head);
	      break;
	    case 3:
	      printf(DAMEIDLIBRO);
	      estruct.opcion = int_read();
	      imprimir_libro(estruct.opcion, estruct.head);
	      break;
	    case 4:
	      modificar_porID(estruct.head);
	      estruct.modificado = TRUE;
	      break;
	    case 5:
	      printf(DAMEIDLIBRO); 
	      estruct.opcion = int_read();
	      estruct.head = borrar_libro(estruct.opcion,estruct.head);
	      estruct.modificado = TRUE;
	      break;
	    case 6: 
	      exportar_libros(estruct.head, NOMBREFICHERO);
	      break;
	    case 7:
	      estruct.head = importar_seguro(estruct.head, NOMBREFICHERO);
	      estruct.modificado = TRUE;
	      break;
	    case 8:
	      mostrar_corruptos(estruct.head);
	      break;
	    case 9:
	      pthread_create(&hilo2autosalvado, NULL, (void *)autosave, &estruct);
	      autosalvado = 1;
	      printf(RUNNING);
	      break;
#if defined(AVANZADAS)
	    case 10:
	      ordenar_lista(&estruct.head);
	      imprimir_resumen_calidad(estruct.head);
	      break;
#endif
	    default:
	      printf(ERROR);
      }
    } while(estruct.opcion != EOF);

    pthread_mutex_unlock(&estruct.mutex);
    if(autosalvado == 1){
      pthread_join(hilo2autosalvado, NULL);
      printf(THREADAUTOSAVEEXIT);
    }
    pthread_mutex_destroy(&estruct.mutex);
    borrar_lista(estruct.head);
    return 0;
ENDF(main)
}
