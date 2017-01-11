#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 5

void mostrarMenu();
void introducirNumeros();
int getSuma();
int getProducto();
int getMedia();
void createTxt();
void createXml();
void crearModa();

int numeros[MAXIMO];

main(){
	int opc;

	do{
		mostrarMenu();
		printf("Elige una opcion: \n");
		scanf("%d", &opc);

		switch (opc){
			case 1:
				introducirNumeros();
				break;
			case 2:
				printf("La suma es:%i\n", getSuma());
				break;
			case 3:
				printf("El producto es:%i\n",getProducto() );
				break;
			case 4:
				printf("La media es:%i\n", getMedia());
				break;				
			case 5:
				crearModa();
				break;
			case 6:
				createTxt();
				break;
			case 7:
				createXml();
				break;								
		}
	} while(opc!=8);
}

void mostrarMenu()
{
	printf("*****************************************\n");
	printf("1.Introducir numeros enteros entre 0 y 99\n");
	printf("2.Obtener y mostrar la suma de todos los numeros\n");
	printf("3.Obtener y mostrar el producto de todos los numeros\n");
	printf("4.Obtener y mostrar la media de todos los numeros\n");
	printf("5.Obtener y mostrar la moda de todos los numeros\n");
	printf("6.Guardar fichero como .txt\n");
	printf("7.Guardar fichero como .xml\n");
	printf("8.Salir\n");
	printf("*****************************************\n");
}

void introducirNumeros(){
	int numeroUsuario;
	int i;

	printf("Introducir numeros\n");
	
	for (i = 0; i < MAXIMO; i++) {
		printf("Introduce el numero %i:\n", i + 1);
		scanf("%i", &numeroUsuario);
		numeros[i] = numeroUsuario;
	}
}
int getSuma(){
	printf("Obtener suma numeros:\n");
	int i;
	int suma = 0;
	for(i=0;i<MAXIMO;i++){
		suma = suma + numeros[i];
	}
	return suma;
}
int getProducto(){
	printf("Obtener producto numeros:\n");
	int i;
	int producto = 1;
	for(i=0;i<MAXIMO;i++){
		producto = producto * numeros[i];
	}
	return producto;
}
int getMedia(){
	return getSuma() / MAXIMO;
}

void createTxt(){
	char nombreTxt[20];
	int i;
	FILE *fTxt;
	printf("Ponle un nombre al archivo .txt. No olvides poner la extension.");
	scanf("%s", &nombreTxt);
	fTxt= fopen(nombreTxt, "w");
	for(i=0;i<MAXIMO;i++){
		fprintf(fTxt, "%d\n", numeros[i]);
	}
	fclose(fTxt);
}

void createXml(){
	char nombreXml[20];
	int i;
	FILE *fXml;
	printf("Ponle un nombre al archivo .xml. No olvides poner la extension.");
	scanf("%s", &nombreXml);
	fXml= fopen(nombreXml, "w");
	for(i=0;i<MAXIMO;i++){
		fprintf(fXml, "<elemento%i>%d</elemento%i>\n", i+1, numeros[i], i+1);
	}
	fclose(fXml);
}

void crearModa(){
	int repNumero[]={0,0,0,0,0};			//Se crea un array para la repeticion de los numeros existentes.
	int i;					//Variable itineradora del for.
	int j;					//Variable itineradora del for.
	int mayor=0;
	for (i=0;i<MAXIMO;i++){
		for (j=0;j<MAXIMO;j++){
			if (numeros[i]==numeros[j]){
				repNumero[i]=repNumero[i]+1;
			}
		}	
	}
	for (i=0;i<MAXIMO;i++){
		if (repNumero[i]>mayor){
			mayor=i;
		}
	}
	printf("La moda de los numeros es: %d",numeros[mayor]);

}
