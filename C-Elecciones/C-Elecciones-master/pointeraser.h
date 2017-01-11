/************************************************************************************
PointEraser es una micro-librer�a que contiene una �nica funci�n
dedicada a eliminar puntos de cadenas de caracteres con d�gitos num�ricos que 
contienen el punto como separador de millares.

Versi�n 1.0.
Fernando Paniagua, 2015.
(www.fernandopaniagua.com)

Esta librer�a se puede usar, copiar, modificar y redistribuir con libertad, siempre 
y cuando la obra derivada mantenga estos mismos derechos (lo que se conoce como 
copyleft). Y hablando de otra cosa... no tiene ninguna garant�a. Si la usas es bajo 
tu propia responsabilidad.
                                  
             @@@@@@@@;            
           @@@@@@@@@@@@`          
          @@@@      '@@@#         
         @@@          @@@+        
        @@@     :;`    '@@        
       +@@    @@@@@@+   @@@       
       @@.  `@@@@@@@@@   @@.      
      .@@   @@@@  '@@@;  #@@      
      @@@  #@@#     @@@   @@      
      @@:           @@@   @@      
      @@`           .@@`  @@      
      @@.           '@@   @@      
      @@+  @@@      @@@   @@      
      :@@   @@@.   @@@@  :@@      
       @@   @@@@@@@@@@   @@'      
       @@@   #@@@@@@@   :@@       
        @@#    +@@@`    @@'       
        :@@@           @@@        
         +@@@`       @@@@         
          .@@@@@#+@@@@@@          
            @@@@@@@@@@            
               '@@#,              



"�No me preocupes con los detalles, muchacho! �S�lo ayudame a encontrar los planos!"
Dr. Fred Edison.

************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Elimina el car�cter punto (.) de una cadena y
convierte el resto a una variable de tipo long.

Par�metros de entrada: puntero a una cadena (debe contener d�gitos num�ricos y puntos).
Retorno: un long con el valor de la cadena sin los puntos.
*/
long getCifraSinPuntos(char *cadenaConPuntos){
	int i=0;//Iterador del array de origen
	int iArrayDestino=0;//Iterador del array de destino
	char sCifraSP[100];//Array de char con la cifra Sin Puntos
	long lCifra;//Cifra destino

	for (i=0;i<strlen(cadenaConPuntos);i++){
		if (cadenaConPuntos[i]!='.') {
			sCifraSP[iArrayDestino]=cadenaConPuntos[i];
			iArrayDestino++;
		}
	}
	lCifra = strtol(sCifraSP,NULL,10);
	return lCifra;
}