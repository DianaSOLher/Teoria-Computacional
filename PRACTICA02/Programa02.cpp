#include<iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<fstream>
#include<string.h>
#include<vector>
using namespace std;
//Variables globales
long int n=0;
long int *numerosPrimos;
long int unos;
ofstream conjuntoPrimos;
ofstream unosConjuntoPrimos;
vector<int> numeroBinario;
//Prototipo funciones
void menu();
int Numero_Aleatorio();
void calcularNumeroPrimo();
void binario();
void subMenu();
void archivos();
void imprimirV();
void limpiarV();

int main (){
	cout<<"Programa que muestra el lenguaje definido por los numeros primos"<<endl;
	menu();
	//liberar memoria;
	free(numerosPrimos);
	
}

void menu(){
	int opcion=0;
	do{
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"\t\t\tMENU"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"1. Insertar valor de n: "<<endl;
		cout<<"2. Generar valor aleatorio de n: "<<endl;
		cout<<"3. Salir "<<endl;
		cout<<"Opcion: ";
		cin>>opcion;
		switch(opcion){
			case 1: 
				system("cls");
				do{
					cout<<"Digite el valor de n que se encuentre en el rango [2,1000000] : ";
					cin>>n;
					if( n<2 || n>1000000 )
					{
						cout<<"Valor invalido, n debe encontrarse en el rango [2,1000000]"<<endl;
					}
				}while( n<2 || n>1000000 );
				system("cls");
				calcularNumeroPrimo();
				binario();
				cout<<"\t***CALCULO REALIZADO CON n = "<<n<<"***\n\n";
				subMenu();
			break;
			case 2: 
				n = Numero_Aleatorio();
				cout<<"\n n = "<<n<<endl;
				calcularNumeroPrimo();
				binario();
			break;
		}
		if(opcion > 3){
			cout<<"\nOpcion invalida. "<<endl;
			//system("pause");
		}
	}while(opcion > 3);
}
void subMenu(){
	int opcion=0;
	
	do{

		cout<<"1. Ingresar una nueva n "<<endl;
		cout<<"2. Salir "<<endl;
		cin>>opcion;
		switch(opcion){
			case 1: 
				free(numerosPrimos);
				system("cls");
				menu();
			break;
			case 2:
				free(numerosPrimos);
				exit(1);
			break;
		}
		if(opcion > 2){
			cout<<"\nOpcion invalida. "<<endl;
			//system("pause");
		}
	}while(opcion > 2);
}

//Genera un numero aleatorio entre 2 - 1000000
int Numero_Aleatorio(){
	srand(time(NULL));
	return (rand()%9)+1;
}

void calcularNumeroPrimo(){
	long int primo = 1;
	char esPrimo = 'T';
	long int numero = 2;
	//crear arreglo
	numerosPrimos = (long int*) malloc(n*sizeof(long int));
	//Caso base 2
	numerosPrimos[0] = 2; 
	do{
		esPrimo = 'T';
		numero += 1;
		//cout<<"\nnumero: "<<numero;
		for(long int i=2; i<numero; i++)
		{
			//cout<<numero<<"%"<<i<<"="<<numero%i<<endl;
			if( numero%i == 0 )
			{
				esPrimo = 'F';
			}
		}
		if(esPrimo == 'T'){
			numerosPrimos[primo]=numero;
			primo += 1;
			//cout<<numero<<" es primo "<<endl;
		}
	}while(primo<=n);
}

void binario(){
	
	long int resultado=0;
	int residuo=0;	
	archivos();
	conjuntoPrimos<<"S*={e, ";
	//caso base en 2
	resultado = numerosPrimos[0];
		unos=0;
		//cout<<"resultado = "<<resultado<<endl;
		do{
			residuo = resultado%2;
			//cout<<"residuo = "<<resultado<<endl;
			resultado = resultado / 2;
			if(residuo == 0)
			{
				numeroBinario.push_back(0);
			}
			else
			{
				numeroBinario.push_back(1);
				unos += 1;
			}
			if(resultado==0)
			{
				imprimirV();
				limpiarV();	
				conjuntoPrimos<<", ";
				unosConjuntoPrimos<<"1 "<<unos<<endl;
				unos=0;
			}	
		}while(resultado>0);	

	unos=0;
	for(int i = 1 ; i<n; i++)
	{	
		resultado = numerosPrimos[i];

		//cout<<"resultado = "<<resultado<<endl;
		do{
			residuo = resultado%2;
			//cout<<"residuo = "<<resultado<<endl;
			resultado = resultado / 2;
			if(residuo == 0)
			{
				numeroBinario.push_back(0);
			}
			else{
				numeroBinario.push_back(1);
				unos += 1;
			}
			if(resultado==0)
			{
				imprimirV();
				limpiarV();	
				if(i<n-1)
				{
					conjuntoPrimos<<", ";
				}
				unosConjuntoPrimos<<i+1<<" "<<unos<<endl;
				unos=0;
			}	
		}while(resultado>0);	
	}
	conjuntoPrimos<<" }";
	
	//Cerrar archivo
	conjuntoPrimos.close(); 
	unosConjuntoPrimos.close();
}

void imprimirV()
{
	for(int i = numeroBinario.size()-1; i>=0; i--)
	{
		conjuntoPrimos<<numeroBinario[i];
	}
}
void limpiarV()
{
	while (!numeroBinario.empty())
 	{
    	numeroBinario.pop_back();
  	}
}
//Imprimir en un archivo de texto el universo en forma de conjunto
void archivos(){
	
	conjuntoPrimos.open("conjuntoPrimos.txt",ios::out); //Abrir archivo
	unosConjuntoPrimos.open("unosConjuntoPrimos.txt",ios::out);
	
	if(conjuntoPrimos.fail())
	{
		cout<<"ERROR al abrir archivo"<<endl;
		exit(1);
	}
	if(unosConjuntoPrimos.fail())
	{
		cout<<"ERROR al abrir archivo"<<endl;
		exit(1);
	}
	
}
