
#include<iostream>
#include<time.h>	//seed de numero random 
#include<stdlib.h> 
#include<math.h>	//Funcion pow
#include<stdio.h> 
#include<fstream> 	//ARCHIVOS

using namespace std;
//Variables Globales
int k;
int **parte1;
int **parte2;
long int filas;
//Prototipos de funciones
void MenuPrincipal();
int Numero_Aleatorio();
void Binario(int);
void Conjunto();
void Cadena();
void SubMenu();
void LiberarMemoria();

//Funcion principal
int main(){
	cout<<"Programa que muestra el universo de las cadenas binarias (Sigma^k)."<<endl;
	MenuPrincipal();
	LiberarMemoria();
	return 0;
}

//Menú
void MenuPrincipal(){
	int opcion=0;
	do{
		cout<<"\t.Menu: "<<endl;
		cout<<"1. Insertar valor de k: "<<endl;
		cout<<"2. Generar valor aleatorio de k: "<<endl;
		cout<<"3. Salir "<<endl;
		cout<<"Opcion: ";
		cin>>opcion;
		system("cls");
		switch(opcion){
		case 1: 
			cout<<"Digite el valor de k : ";
			cin>>k;
			//cout<<"2^"<<k<<" = "<<pow(2,k)<<endl;
			Binario(k);
			Conjunto();
			Cadena();
			system("cls");
			cout<<"\t***CALCULO REALIZADO CON k = "<<k<<"***\n\n";
			LiberarMemoria();
			SubMenu();
		break;
		case 2: 
			k = Numero_Aleatorio();
			//cout<<"\nk = "<<k<<endl;
			//cout<<"2^"<<k<<" = "<<pow(2,k)<<endl;
			Binario(k);
			Conjunto();
			Cadena();
			system("cls");
			cout<<"\t***CALCULO REALIZADO CON k = "<<k<<"***\n\n";
			LiberarMemoria();
			SubMenu();
		break;
		}
		if(opcion > 3){
			cout<<"\nOpcion invalida. "<<endl;
			system("cls");
		}
	}while(opcion > 3);
}
//Genera un numero aleatorio entre 1 - 1000
int Numero_Aleatorio(){
	srand((unsigned)time(NULL));
	return (rand()%10)+1;
}

void Binario(int n){
	
	int resultado_div;
	filas = (pow(2,n))/2;
	//Reservando memoria para filas y columnas de la 1a mitad de las combinaciones
	parte1 = new int*[filas];
	for(int i = 0; i <filas; i++){
		parte1[i] = new int[n];
	}
	//Reservando memoria para filas y columnas de la 2da mitad de las combinaciones
	parte2 = new int*[filas];
	for(int i = 0; i <filas; i++){
		parte2[i] = new int[n];
	}
	//Utilizar metodo de la division para conseguir combinaciones
	for(int i=0; i<filas; i++)
	{
		resultado_div=i;
		for(int j=n-1; j>=0; j--)
		{
			if(resultado_div%2==0)
			{
				parte1[i][j]=0;
				parte2[i][j]=1;
			}
			else{
				parte1[i][j]=1;
				parte2[i][j]=0;
			}
			resultado_div = resultado_div/2;
		}
	}
}
//Imprimir en un archivo de texto el universo en forma de conjunto
void Conjunto(){
	int potencia,z,unos,contador=0;
	//Imprimir archivo
	ofstream conjunto;
	ofstream unosConjunto;
	conjunto.open("conjunto_universo.txt",ios::out); //Abrir archivo
	unosConjunto.open("unos_conjunto.txt",ios::out);
	
	if(conjunto.fail())
	{
		cout<<"ERROR al abrir archivo"<<endl;
		exit(1);
	}
	if(unosConjunto.fail())
	{
		cout<<"ERROR al abrir archivo"<<endl;
		exit(1);
	}
	
	conjunto<<"S*={e, ";
	unos = 0;
	contador=0;
	for(z=1;z<k;z++){
		potencia = pow(2,z);
		for(int i=0; i<potencia; i++)
		{
			for(int j=0; j<z; j++)
			{
				conjunto<<parte1[i][j+k-z];
				if(parte1[i][j+k-z] == 1)
				{
					unos += 1;
				}
			}
			unosConjunto<<contador<<" "<<unos<<endl;
			contador +=1 ;
			unos = 0;
			conjunto<<", ";		
		}
	}
	
	for(int i=0; i<filas; i++)
	{
		for(int j=0; j<k; j++)
		{
			conjunto<<parte1[i][j];
			if(parte1[i][j] == 1)
			{
				unos += 1;
			}
		}
		unosConjunto<<contador<<" "<<unos<<endl;
		contador +=1 ;
		unos = 0;
		conjunto<<", ";
	}
	unos=0;
	for(int i=filas-1; i>=0; i--)
	{
		for(int j=0; j<k; j++)
		{
			conjunto<<parte2[i][j];
			if(parte2[i][j] == 1)
			{
				unos += 1;
			}
		}
		if(i>0)
		{
			conjunto<<", ";
		}	
		unosConjunto<<contador<<" "<<unos<<endl;
		contador +=1 ;
		unos = 0;
		
	}	
	conjunto<<" }";
	
	//Cerrar archivo
	conjunto.close(); 
	unosConjunto.close();
}

//Imprimir en un archivo de texto el universo en forma de cadena 
void Cadena(){
	int potencia,z,longitud,unos,cadenas;
	//Imprimir archivo
	ofstream cadena;
	ofstream unosCadena;
	cadena.open("cadena_universo.txt",ios::out); //Abrir archivo
	unosCadena.open("unos_cadena.txt",ios::out);
	if(cadena.fail())
	{
		cout<<"ERROR al abrir archivo"<<endl;
		exit(1);
	}
	if(unosCadena.fail())
	{
		cout<<"ERROR al abrir archivo"<<endl;
		exit(1);
	}
	longitud = 0;
	cadenas = 0;
	unos = 0;
	for(z=1;z<k;z++){
		potencia = pow(2,z);
		for(int i=0; i<potencia; i++)
		{
			for(int j=0; j<z; j++)
			{
			
				if(longitud == 32){
					
					longitud=0;
					unosCadena<<cadenas<<" "<<unos<<endl;
					cadenas += 1;
					unos=0;
				}
				if(parte1[i][j+k-z] == 1)
				{
					unos += 1;
					//cout<<"\nunos: "<<unos;
				}
				cadena<<parte1[i][j+k-z];
				longitud += 1;
				//cout<<"\nlong: "<<longitud;	
			}
			if(longitud == 0)
			{
				//cout<<"\ncadenas: "<<cadenas;
				unosCadena<<cadenas<<" "<<unos<<endl;
				cadenas += 1;
			}	
		}
	}

	for(int i=0; i<filas; i++)
	{
		
		for(int j=0; j<k; j++)
		{
			
			if(longitud == 32){
			
				longitud=0;	
				unosCadena<<cadenas<<" "<<unos<<endl;
				cadenas += 1;
				unos=0;
			}
			if(parte1[i][j] == 1)
			{
				unos += 1;
				//cout<<"\nunos: "<<unos;
			}
			cadena<<parte1[i][j];
			longitud += 1;
			//cout<<"\nlong: "<<longitud;
		}
	}
	
	for(int i=filas-1; i>=0; i--)
	{
		
		for(int j=0; j<k; j++)
		{
			
			if(longitud == 32){
				
				longitud=0;
				unosCadena<<cadenas<<" "<<unos<<endl;
				cadenas += 1;	
				unos=0;
			}
			if(parte2[i][j] == 1)
			{
				unos += 1;
			//	cout<<"\nunos: "<<unos;
			}
			cadena<<parte2[i][j];
			longitud += 1;
			//cout<<"\nlong: "<<longitud;
		}
		if(i == 0)
		{
		
			//cout<<"\ncadenas: "<<cadenas;
			unosCadena<<cadenas<<" "<<unos<<endl;
			cadenas += 1;
		}
	}	
	//Cerrar archivo
	cadena.close();
	unosCadena.close(); 
	
}

//Submenu
void SubMenu(){
	int opcion=0;
	do{
		cout<<"\tMenu Secundario "<<endl;
		cout<<"1. Ingresar una nueva k "<<endl;
		cout<<"2. Salir "<<endl;
		cin>>opcion;
		switch(opcion){
			case 1: 
				system("cls");
				MenuPrincipal();
			break;
			case 2:
				exit(1);
			break;
		}
		if(opcion > 2){
			cout<<"\nOpcion invalida. "<<endl;
			system("pause");
		}
	}while(opcion > 2);
}

//Liberar memoria
void LiberarMemoria(){
	
	for(int i=0; i<k; i++)
	{
		free(parte1[i]);
		free(parte2[i]);
	}
	free(parte1);
	free(parte2);
}
