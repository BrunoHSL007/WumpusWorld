//Wumpus World - Artificial Intelligence
//Bruno Henrique dos Santos Laier
//Version 0.1 18/10/2017
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int Linha=10;
int Coluna=10;

const int player=1;
const int ouro=2;
const int brisa=3;
const int wumpus=4;
const int fedor=5;
const int buraco=6;

int **inicializaMatriz(int** Mapa){
	for(int i=0;i< Linha ;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			Mapa[i][j]=0;
		}
	}
	int Linerand,Colrand;
	
	//Colocando o Wumpus no mapa
	srand( (unsigned)time(NULL) );
	int aux=rand();
	Linerand =(aux % static_cast<int>(Linha));
	while(rand()!=aux)
	{
		srand( (unsigned)time(NULL) );
	};
	aux=rand();
	Colrand = (aux % static_cast<int>(Coluna));
	Mapa[Linerand][Colrand]=wumpus;
	if(Linerand-1>=0)
		Mapa[Linerand-1][Colrand]=fedor;
	if(Linerand+1<Linha)	
		Mapa[Linerand+1][Colrand]=fedor;
	if(Colrand-1>=0)
		Mapa[Linerand][Colrand-1]=fedor;
	if(Colrand+1<Coluna)
		Mapa[Linerand][Colrand+1]=fedor;
	
	int LinerandOuro,ColrandOuro;
	//while(rand()!=aux)
	//{
	//	srand( (unsigned)time(NULL) );
	//};
	do
	{
		aux=rand();
		//Colocando o pote de ouro no mapa
		LinerandOuro =(aux % static_cast<int>(Linha));
		//while(rand()!=aux)
		//{
		//	srand( (unsigned)time(NULL) );
		//};
		aux=rand();
		ColrandOuro = (aux % static_cast<int>(Coluna));
	}
	while((ColrandOuro==Colrand) && (Linerand==LinerandOuro));
	Mapa[LinerandOuro][ColrandOuro]=ouro;
	if(LinerandOuro-1>=0)
		Mapa[LinerandOuro-1][ColrandOuro]=brisa;
	if(LinerandOuro+1<Linha)	
		Mapa[LinerandOuro+1][ColrandOuro]=brisa;
	if(ColrandOuro-1>=0)
		Mapa[LinerandOuro][ColrandOuro-1]=brisa;
	if(ColrandOuro+1<Coluna)
		Mapa[LinerandOuro][ColrandOuro+1]=brisa;
	
	return Mapa;
}
int **alocaMatriz(int l, int c)
{
	int i;
	int **A;
	 
	A = (int **) calloc(l, sizeof(int *)); 
	for(i = 0; i < l; i++) 
		A[i] = (int *) calloc(c, sizeof(int)); 
	
	return A; 

}
void PrintMatriz(int **Mapa)
{
	for(int i=0;i<Linha;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			cout << Mapa[i][j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	int **Mapa;
	Mapa=alocaMatriz(Linha,Coluna);
	
	
	inicializaMatriz(Mapa);
	PrintMatriz(Mapa);
	return 0;
}
