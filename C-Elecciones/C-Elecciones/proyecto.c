//Proyecto  Adrian Montero

//Introduccion librerias
#include <stdio.h>
#include "pointeraser.h" // aportacion de Fernandopanyagua

#define numPartidos 6
#define numComunidades 4
#define numEscanBadajoz 6
#define numEscanCaceres 4
#define numEscanMadrid 36
#define numEscanMurcia 10

//Delcaracion de funciones
void mostrarMenu();
void selecFile();
void calcularDiputadosBadajoz();
void calcularDiputadosCaceres();
void calcularDiputadosMadrid();
void calcularDiputadosMurcia();
void abrirTable();
void cerrarTable();

//Funciones globales
int diputados[numPartidos]={0,0,0,0,0,0}; //0.PP 1.PSOE 2.IU-LV 3.UPyD 4.Podemos 5.Ciudadanos
long tbVotos[numComunidades][numPartidos]; //almacenara los vosotos por comunidades y partidos


main(){
	int eleccion;
	do{
		mostrarMenu();
		
		printf("Seleccione una opcion:\n");
		scanf("%d", &eleccion); //Almacenamos la opcion deseada

		switch(eleccion){ //Dependiendo de la opcion hace una funcion u otra
			case 1 :
				selecFile();
				break;
			case 2 :
				system("del elecciones.html"); //Nos aseguramos de que el archivo no existe
				abrirTable();
				calcularDiputadosBadajoz();
				calcularDiputadosCaceres();
				calcularDiputadosMadrid();
				calcularDiputadosMurcia();
				cerrarTable();
				break;
			default :
				break;
		}
	}while(eleccion != 4); //Mientras la opcion introducida sea distinta a "0"  se ejecutara el programa
}

void mostrarMenu(){
	//Mostramos el menu
		printf("************************\n");
		printf("1.Seleccionar fichero de entrada\n");
		printf("2.Calcular diputados y crear HTML\n");
		printf("4.Salir\n");
		printf("************************\n");
}

void selecFile(){
	int i; //iterador
	int j; //iterador
	char nameFile[40]; //almacena el nombre del archivo
	char linea[200]; //guarda el texto de las lineas del archivo
	long votos; //guarda los botos de cada partido

	FILE * fTxt;
	printf("Dame el nombre del fichero a leer con extension incluida: \n");
	scanf("%s", nameFile);

	fTxt=fopen(nameFile, "r");

	for (i = 0; i < numComunidades; ++i)
	{
		fscanf(fTxt, "%s", linea); //Leemos para que pase al siguiente (Linea de comunidades)
		for (j = 0; j < numPartidos; ++j)
		{
			fscanf(fTxt, "%s", linea); //Leemos para que pase al siguiente (Linea de nombre de partido)
			fscanf(fTxt, "%s", linea); //Leemos y lo almacenamos en tbVotos

			votos = getCifraSinPuntos(linea); 
			
			tbVotos[i][j] = votos; //almacenamos los botos en tbVotos
			printf("%lu\n", tbVotos[i][j]);
		}
	}
	fclose(fTxt);
}

void calcularDiputadosBadajoz(){
	int i; //iterador
	int j; //iterador
	int k; //iterador
	int l; //iterador
	long tbDiputados[numPartidos][numEscanBadajoz]; //Tabla de divisiones
	int cont = 0;	//contador
	long numMayor = 0; //Numero mas alto de cada busqueda en la tabla de divisiones
	int cordX = 0; //Cordenada x del numero mayor
	int cordY = 0; //Cordenada y del numero mayor

	//Inicializamos los diputados, para en caso de repetir la opcion 2 que no se acumule.
	for(i=0; i<6; i++){
	diputados[i]=0;
	}

	// Hacer la tabla de divisiones
 	for(i=0;i<numPartidos;i++){
  		tbDiputados[i][0] = tbVotos[0][i];
 	}
	for(i=0; i < numPartidos; i++){
  		for(j=0; j < numEscanBadajoz; j++){
  			k = j + 1; //Si se hace directamente con j+1 hace el calculo mal
   			tbDiputados[i][j] = tbDiputados[i][0] / k;
   			//printf("%d\n", tbDiputados[i][j]);
  		}
 	}

	//Buscamos los partidos con mas votos y asignamos escaños
	for (l = 0; l < numEscanBadajoz; l++)
	{
		for(i=0; i < numPartidos; i++)
		{
			for(j=0; j < numEscanBadajoz; j++)
			{
				if(tbDiputados[i][j] > numMayor) //almacena el partidido con mas votos
				{
					numMayor = tbDiputados[i][j]; //guarda los votos del mas votado
					cordX = i; //guarda la cordenada i del mas votado
					cordY = j; //guarda la cordenada j del mas votado
				} else {
					continue;
				}
			}
		}
		if(cordX == 5){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 4){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 3){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 2){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 1){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 0){
			diputados[cordX] = diputados[cordX] + 1;
		}
		tbDiputados[cordX][cordY] = 0; //Quitamos el partido mas votado ya que no se pueden repetir
		//printf("%d : Numero: %lu, cordx: %d cordy: %d \n", l+1, numMayor, cordX, cordY); 
		numMayor = 0; //Inicializamos a 0 para comparar de nuevo el mas votado
	}

	//Mostramos los escaños por partidos
	printf("Badajoz \n");
	printf("%d PP \n", diputados[0]);
	printf("%d PSOE \n", diputados[1]);
	printf("%d IU-LV \n", diputados[2]);
	printf("%d UPyD \n", diputados[3]);
	printf("%d Podemos \n", diputados[4]);
	printf("%d Ciudadanos \n", diputados[5]);

	//Almacenamos los datos en el html.
	FILE * html;
	html = fopen("elecciones.html", "a");
		fprintf(html, "\n<tr>");
		fprintf(html, "\n\t<td></td>");
		fprintf(html, "\n\t<td></td>");
		fprintf(html, "\n\t<td>1</td>");
		fprintf(html, "\n\t<td>2</td>");
		fprintf(html, "\n\t<td>3</td>");
		fprintf(html, "\n\t<td>4</td>");
		fprintf(html, "\n\t<td>5</td>");
		fprintf(html, "\n\t<td>6</td>");
		fprintf(html, "\n</tr>");

		fprintf(html, "\n<tr>");
		fprintf(html, "\n\t<td></td>");
		fprintf(html, "\n\t<td></td>");
		fprintf(html, "\n\t<td>PP</td>");
		fprintf(html, "\n\t<td>PSOE</td>");
		fprintf(html, "\n\t<td>IU-LV</td>");
		fprintf(html, "\n\t<td>UPyD</td>");
		fprintf(html, "\n\t<td>Podemos</td>");
		fprintf(html, "\n\t<td>Ciudadanos</td>");
		fprintf(html, "\n</tr>");


		fprintf(html, "\n<tr>");
		fprintf(html, "\n\t<td>1</td>");
		fprintf(html, "\n\t<td>Badajoz</td>");
		fprintf(html, "\n\t<td>%d</td>",diputados[0]);
		fprintf(html, "\n\t<td>%d</td>",diputados[1]);
		fprintf(html, "\n\t<td>%d</td>",diputados[2]);
		fprintf(html, "\n\t<td>%d</td>",diputados[3]);
		fprintf(html, "\n\t<td>%d</td>",diputados[4]);
		fprintf(html, "\n\t<td>%d</td>",diputados[5]);
		fprintf(html, "\n</tr>");
	fclose(html);
		
}

void calcularDiputadosCaceres(){
	int i; //iterador
	int j; //iterador
	int k; //iterador
	int l; //iterador
	long tbDiputados[numPartidos][numEscanCaceres]; //Tabla de divisiones
	int cont = 0;	//contador
	long numMayor = 0; //Numero mas alto de cada busqueda en la tabla de divisiones
	int cordX = 0; //Cordenada x del numero mayor
	int cordY = 0; //Cordenada y del numero mayor

	//Inicializamos los diputados, para en caso de repetir la opcion 2 que no se acumule.
	for(i=0; i<6; i++){
	diputados[i]=0;
	}

	// Hacer la tabla de divisiones
 	for(i=0;i<numPartidos;i++){
  		tbDiputados[i][0] = tbVotos[1][i];
 	}
	for(i=0; i < numPartidos; i++){
  		for(j=0; j < numEscanCaceres; j++){
  			k = j + 1; //Si se hace directamente con j+1 hace el calculo mal
   			tbDiputados[i][j] = tbDiputados[i][0] / k;
   			//printf("%d\n", tbDiputados[i][j]);
  		}
 	}

	//Buscamos los partidos con mas votos y asignamos escaños
	for (l = 0; l < numEscanCaceres; l++)
	{
		for(i=0; i < numPartidos; i++)
		{
			for(j=0; j < numEscanCaceres; j++)
			{
				if(tbDiputados[i][j] > numMayor) //almacena el partidido con mas votos
				{
					numMayor = tbDiputados[i][j]; //guarda los votos del mas votado
					cordX = i; //guarda la cordenada i del mas votado
					cordY = j; //guarda la cordenada j del mas votado
				} else {
					continue;
				}
			}
		}
		if(cordX == 5){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 4){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 3){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 2){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 1){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 0){
			diputados[cordX] = diputados[cordX] + 1;
		}
		tbDiputados[cordX][cordY] = 0; //Quitamos el partido mas votado ya que no se pueden repetir
		//printf("%d : Numero: %lu, cordx: %d cordy: %d \n", l+1, numMayor, cordX, cordY); 
		numMayor = 0; //Inicializamos a 0 para comparar de nuevo el mas votado
	}

	//Mostramos los escaños por partidos
	printf("Caceres \n");
	printf("%d PP \n", diputados[0]);
	printf("%d PSOE \n", diputados[1]);
	printf("%d IU-LV \n", diputados[2]);
	printf("%d UPyD \n", diputados[3]);
	printf("%d Podemos \n", diputados[4]);
	printf("%d Ciudadanos \n", diputados[5]);

	//Almacenamos los datos en el html.
	FILE * html;
	html = fopen("elecciones.html", "a");
		fprintf(html, "\n<tr>");
		fprintf(html, "\n\t<td>2</td>");
		fprintf(html, "\n\t<td>Caceres</td>");
		fprintf(html, "\n\t<td> %d</td>",diputados[0]);
		fprintf(html, "\n\t<td> %d</td>",diputados[1]);
		fprintf(html, "\n\t<td> %d</td>",diputados[2]);
		fprintf(html, "\n\t<td> %d</td>",diputados[3]);
		fprintf(html, "\n\t<td> %d</td>",diputados[4]);
		fprintf(html, "\n\t<td> %d</td>",diputados[5]);
		fprintf(html, "\n</tr>");
	fclose(html);
		
}

void calcularDiputadosMadrid(){
	int i; //iterador
	int j; //iterador
	int k; //iterador
	int l; //iterador
	long tbDiputados[numPartidos][numEscanMadrid]; //Tabla de divisiones
	int cont = 0;	//contador
	long numMayor = 0; //Numero mas alto de cada busqueda en la tabla de divisiones
	int cordX = 0; //Cordenada x del numero mayor
	int cordY = 0; //Cordenada y del numero mayor

	//Inicializamos los diputados, para en caso de repetir la opcion 2 que no se acumule.
	for(i=0; i<6; i++){
	diputados[i]=0;
	}

	// Hacer la tabla de divisiones
 	for(i=0;i<numPartidos;i++){
  		tbDiputados[i][0] = tbVotos[2][i];
 	}
	for(i=0; i < numPartidos; i++){
  		for(j=0; j < numEscanMadrid; j++){
  			k = j + 1; //Si se hace directamente con j+1 hace el calculo mal
   			tbDiputados[i][j] = tbDiputados[i][0] / k;
   			//printf("%d\n", tbDiputados[i][j]);
  		}
 	}

	//Buscamos los partidos con mas votos y asignamos escaños
	for (l = 0; l < numEscanMadrid; l++)
	{
		for(i=0; i < numPartidos; i++)
		{
			for(j=0; j < numEscanMadrid; j++)
			{
				if(tbDiputados[i][j] > numMayor) //almacena el partidido con mas votos
				{
					numMayor = tbDiputados[i][j]; //guarda los votos del mas votado
					cordX = i; //guarda la cordenada i del mas votado
					cordY = j; //guarda la cordenada j del mas votado
				} else {
					continue;
				}
			}
		}
		if(cordX == 5){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 4){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 3){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 2){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 1){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 0){
			diputados[cordX] = diputados[cordX] + 1;
		}
		tbDiputados[cordX][cordY] = 0; //Quitamos el partido mas votado ya que no se pueden repetir
		//printf("%d : Numero: %lu, cordx: %d cordy: %d \n", l+1, numMayor, cordX, cordY); 
		numMayor = 0; //Inicializamos a 0 para comparar de nuevo el mas votado
	}

	//Mostramos los escaños por partidos
	printf("Madrid \n");
	printf("%d PP \n", diputados[0]);
	printf("%d PSOE \n", diputados[1]);
	printf("%d IU-LV \n", diputados[2]);
	printf("%d UPyD \n", diputados[3]);
	printf("%d Podemos \n", diputados[4]);
	printf("%d Ciudadanos \n", diputados[5]);

	//Almacenamos los datos en el html.
	FILE * html;
	html = fopen("elecciones.html", "a");
		fprintf(html, "\n<tr>");
		fprintf(html, "\n\t<td>3</td>");
		fprintf(html, "\n\t<td>Madrid</td>");
		fprintf(html, "\n\t<td> %d</td>",diputados[0]);
		fprintf(html, "\n\t<td> %d</td>",diputados[1]);
		fprintf(html, "\n\t<td> %d</td>",diputados[2]);
		fprintf(html, "\n\t<td> %d</td>",diputados[3]);
		fprintf(html, "\n\t<td> %d</td>",diputados[4]);
		fprintf(html, "\n\t<td> %d</td>",diputados[5]);
		fprintf(html, "\n</tr>");
	fclose(html);	

}

void calcularDiputadosMurcia(){
	int i; //iterador
	int j; //iterador
	int k; //iterador
	int l; //iterador
	long tbDiputados[numPartidos][numEscanMurcia]; //Tabla de divisiones
	int cont = 0;	//contador
	long numMayor = 0; //Numero mas alto de cada busqueda en la tabla de divisiones
	int cordX = 0; //Cordenada x del numero mayor
	int cordY = 0; //Cordenada y del numero mayor

	//Inicializamos los diputados, para en caso de repetir la opcion 2 que no se acumule.
	for(i=0; i<6; i++){
	diputados[i]=0;
	}

	// Hacer la tabla de divisiones
 	for(i=0;i<numPartidos;i++){
  		tbDiputados[i][0] = tbVotos[3][i];
 	}
	for(i=0; i < numPartidos; i++){
  		for(j=0; j < numEscanMurcia; j++){
  			k = j + 1; //Si se hace directamente con j+1 hace el calculo mal
   			tbDiputados[i][j] = tbDiputados[i][0] / k;
   			//printf("%d\n", tbDiputados[i][j]);
  		}
 	}


	//Buscamos los partidos con mas votos y asignamos escaños
	for (l = 0; l < numEscanMurcia; l++)
	{
		for(i=0; i < numPartidos; i++)
		{
			for(j=0; j < numEscanMurcia; j++)
			{
				if(tbDiputados[i][j] > numMayor) //almacena el partidido con mas votos
				{
					numMayor = tbDiputados[i][j]; //guarda los votos del mas votado
					cordX = i; //guarda la cordenada i del mas votado
					cordY = j; //guarda la cordenada j del mas votado
				} else {
					continue;
				}
			}
		}
		if(cordX == 5){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 4){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 3){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 2){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 1){
			diputados[cordX] = diputados[cordX] + 1;
		} else if(cordX == 0){
			diputados[cordX] = diputados[cordX] + 1;
		}
		tbDiputados[cordX][cordY] = 0; //Quitamos el partido mas votado ya que no se pueden repetir
		//printf("%d : Numero: %lu, cordx: %d cordy: %d \n", l+1, numMayor, cordX, cordY); 
		numMayor = 0; //Inicializamos a 0 para comparar de nuevo el mas votado
	}

	//Mostramos los escaños por partidos
	printf("Murcia \n");
	printf("%d PP \n", diputados[0]);
	printf("%d PSOE \n", diputados[1]);
	printf("%d IU-LV \n", diputados[2]);
	printf("%d UPyD \n", diputados[3]);
	printf("%d Podemos \n", diputados[4]);
	printf("%d Ciudadanos \n", diputados[5]);

	//Almacenamos los datos en el html.
	FILE * html;
	html = fopen("elecciones.html", "a");
		fprintf(html, "\n<tr>");
		fprintf(html, "\n\t<td>4</td>");
		fprintf(html, "\n\t<td>Murcia</td>");
		fprintf(html, "\n\t<td> %d</td>",diputados[0]);
		fprintf(html, "\n\t<td> %d</td>",diputados[1]);
		fprintf(html, "\n\t<td> %d</td>",diputados[2]);
		fprintf(html, "\n\t<td> %d</td>",diputados[3]);
		fprintf(html, "\n\t<td> %d</td>",diputados[4]);
		fprintf(html, "\n\t<td> %d</td>",diputados[5]);
		fprintf(html, "\n</tr>");
	fclose(html);
	
}

void abrirTable(){
	//Creamos un html y creamos los primeros datos
	FILE * html;
	html = fopen("elecciones.html", "a");
		fprintf(html, "\n<html>");
		fprintf(html, "\n<head>");
		fprintf(html, "\n<title>Elecciones Adrian Montero</title>");
		fprintf(html, "\n</head>");
		fprintf(html, "\n<body>");
		fprintf(html, "\n<table border='1px'>");
	fclose(html);
}

void cerrarTable(){
	//Cerramos el html
	FILE * html;
	html = fopen("elecciones.html", "a");
		fprintf(html, "\n</table>");
		fprintf(html, "\n</body>");
		fprintf(html, "\n</html>");
	fclose(html);
}