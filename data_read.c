/**CFile***********************************************************************

  Fichero     [data_read.c]

  Resumen     [Fichero para introducir datos por teclado.]

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
  TIPO DE GARANTÍAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#include "data_read.h"

/*---------------------------------------------------------------------------*/
/* Definición de las funciones                                               */
/*---------------------------------------------------------------------------*/

/**Función********************************************************************

  Resumen      Lee números enteros. En caso de introducir CTRL-D se cierra el programa.

  Parámetros   @return data Devuelve el número entero introducido.  

  Efec. Colat. Que el usuario introduzca erróneamente el dato.

******************************************************************************/

long menu_read(){
BEGINF(menu_read, 100317575, 100307091, 100317556, 100307091) 
    long data;
    ssize_t bytes_leidos;
    size_t numero_bytes;
    char *string;

    numero_bytes = 0;
    string = NULL;
    bytes_leidos = getline(&string, &numero_bytes, stdin);
     
    if (bytes_leidos == -1)
    {
      printf("\n");
      data = -1;
    } 
    else
    {
      string[strlen(string)-1]= '\0';
      data = strtol(string, NULL, 10);
    } 
    free(string);
    return data;
ENDF(menu_read)
}


/**Función********************************************************************

  Resumen      Lee números enteros.

  Parámetros   @return data Devuelve el número entero introducido.

  Efec. Colat. Que el usuario introduzca erróneamente el dato.

******************************************************************************/
 
long int_read(){
BEGINF(int_read, 100307091, 100291133, 100318675, 100291133)
    long data;
    ssize_t bytes_leidos;
    size_t numero_bytes;
    char *string;
 
    numero_bytes = 0;
    string = NULL;
    bytes_leidos = getline(&string, &numero_bytes, stdin);
      
    if (bytes_leidos == -1)
    {
      puts(ERRDATO);
    } 
    else
    {
      string[strlen(string)-1]= '\0';
      data = strtol(string, NULL, 10);
    }
 
    free(string);
    return data;
ENDF(int_read)
}

/**Función********************************************************************

  Resumen      Lee un número decimal.

  Parámetros   @return data Devuelve el número decimal introducido.

  Efec. Colat. Que el usuario introduzca erróneamente el dato.

******************************************************************************/
 
float float_read() {
BEGINF(float_read, 100318675, 100317575, 100317556, 100317575)
    float data;
    ssize_t bytes_leidos;
    size_t numero_bytes;
    char *string;   
       
    numero_bytes = 0;
    string = NULL;
    bytes_leidos = getline(&string, &numero_bytes, stdin);
       
    if (bytes_leidos == -1)
    {
      puts(ERRDATO);
    } 
    else
    {
      string[strlen(string)-1]= '\0';
      data = strtof(string, NULL); 
    }
     
    free(string);
    return data;
ENDF(float_read)
}
 
/**Función********************************************************************

  Resumen      Lee un String introducido por teclado.

  Parámetros   @return string Devuelve el string introducido.

  Efec. Colat. Fuga de memoria si no se libera el string. 
	       Que el usuario introduzca erróneamente el dato.


******************************************************************************/

char* string_read(){
BEGINF(string_read, 100317556, 100318675, 100291133, 100318675)
    ssize_t bytes_leidos;
    size_t numero_bytes;
    char *string;
 
    numero_bytes = 0;
    string = NULL;
    bytes_leidos = getline(&string, &numero_bytes, stdin);
       
    if (bytes_leidos == -1)
    {
      puts(ERRDATO);
    } 
    else
    {
      string[strlen(string)-1]= '\0';
    }
 
    return string;
ENDF(string_read)
}