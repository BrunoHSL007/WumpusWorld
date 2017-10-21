//Wumpus World - Artificial Intelligence
//Bruno Henrique dos Santos Laier
//Version 0.2 20/10/2017
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

bool IAGameMode=true;//IAGameMode true = player is IA false = normal player

const int Linha=10;
const int Coluna=10;

const int player=1;
const int ouro=2;
const int brilho=3;
const int wumpus=4;
const int fedor=5;
const int buraco=6;
const int brisa=7;

const int PosVisitada=-1;

int NroBuracos=4;


class Wumpus{
	private:
		
		//int WumpusMap[Linha][Coluna]; //posições por onde o wumpus já passou e posição atual
		int PosiLinhaW; // Linha em que o wumpus está
		int PosiColW;   // Coluna em que o wumpus está
			
	public:
		Wumpus();
		int getPosiLinhaW(); // Linha em que o wumpus está
		int getPosiColW();   // Coluna em que o wumpus está
		//void moveW();
		//void attackW();
		
		
};
Wumpus::Wumpus(){
	/*
	for(int i=0; i<Linha;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			WumpusMap[i][j]=0;
		}
	}
	*/
	int Linerand,Colrand;
	srand( (unsigned)time(NULL) );
	int aux=rand();
	Linerand =(aux % static_cast<int>(Linha));
	while(rand()!=aux)
	{
		srand( (unsigned)time(NULL) );
	};
	aux=rand();
	Colrand = (aux % static_cast<int>(Coluna));
	//WumpusMap[Linerand][Colrand]=wumpus;
	PosiLinhaW=Linerand;
	PosiColW=Colrand;
	
	
}

int Wumpus::getPosiLinhaW(){
	return PosiLinhaW;
}
int Wumpus::getPosiColW(){
	return PosiColW;
}
/*Wumpus::moveW(){
	if(PosiLinhaW!=0)// Para cima
	{
		if(WumpusMap[PosiLinhaW-1][PosiColW]>=0)
		{
			WumpusMap[PosiLinhaW-1][PosiColW]=wumpus;
			WumpusMap[PosiLinhaW][PosiColW]=PosVisitada;
			
		}
	}
	else if(PosiColW!=0)// Para esquerda
	{
		if(WumpusMap[PosiLinhaW][PosiColW-1]>=0)
		{
			WumpusMap[PosiLinhaW][PosiColW-1]=wumpus;
			WumpusMap[PosiLinhaW][PosiColW]=PosVisitada;
			
		}
	}
	else if(PosiLinhaW!=Linha-1)// Para baixo
	{
		if(WumpusMap[PosiLinhaW+1][PosiColW]>=0)
		{
			WumpusMap[PosiLinhaW+1][PosiColW]=wumpus;
			WumpusMap[PosiLinhaW][PosiColW]=PosVisitada;
			
		}
	}
	else if(PosiColW!=Coluna-1)// Para direita
	{
		if(WumpusMap[PosiLinhaW][PosiColW+1]>=0)
		{
			WumpusMap[PosiLinhaW][PosiColW+1]=wumpus;
			WumpusMap[PosiLinhaW][PosiColW]=PosVisitada;
			
		}
	}
	
}

Wumpus::attackW(){
	cout << "Você foi morto pelo Wumpus";
}*/


class WorldMAP : public Wumpus
{
	private:
		int Mapa[Linha][Coluna];
	public:
		WorldMAP();
		void printMapa(); //Ver questão da herança
};
WorldMAP::WorldMAP()
{
	Wumpus();
	/*int i;
	int **A;
	 
	A = (int **) calloc(Linha, sizeof(int *)); 
	for(i = 0; i < l; i++) 
		A[i] = (int *) calloc(Coluna, sizeof(int)); 
	
	return A;*/
	
	//Inicializando a matriz com 0
	for(int i=0;i< Linha ;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			Mapa[i][j]=0;
		}
	}
	//Colocando o Wumpus no mapa
	int auxLinha = getPosiLinhaW();
	int auxColuna = getPosiColW();
	Mapa[auxLinha][auxColuna]=wumpus;
	if(auxLinha-1>=0)
		Mapa[auxLinha-1][auxColuna]+=fedor;
	if(auxLinha+1<Linha)	
		Mapa[auxLinha+1][auxColuna]+=fedor;
	if(auxColuna-1>=0)
		Mapa[auxLinha][auxColuna-1]+=fedor;
	if(auxColuna+1<Coluna)
		Mapa[auxLinha][auxColuna+1]+=fedor;
	
	//Colocando o pote de Ouro no mapa
	srand( (unsigned)time(NULL) );
	int aux=rand();
	int LinerandOuro,ColrandOuro;
	aux=rand();
	LinerandOuro =(aux % static_cast<int>(Linha));
	aux=rand();
	ColrandOuro = (aux % static_cast<int>(Coluna));
	Mapa[LinerandOuro][ColrandOuro]+=ouro;
	if(LinerandOuro-1>=0)
		Mapa[LinerandOuro-1][ColrandOuro]+=brilho;
	if(LinerandOuro+1<Linha)	
		Mapa[LinerandOuro+1][ColrandOuro]+=brilho;
	if(ColrandOuro-1>=0)
		Mapa[LinerandOuro][ColrandOuro-1]+=brilho;
	if(ColrandOuro+1<Coluna)
		Mapa[LinerandOuro][ColrandOuro+1]+=brilho;
	int LinerandBuraco, ColrandBuraco;
	
	//Colocando os buracos no mapa
	for(int i=0;i<NroBuracos;i++)
	{
		aux=rand();
		LinerandBuraco =(aux % static_cast<int>(Linha));
		aux=rand();
		ColrandBuraco = (aux % static_cast<int>(Coluna));
		Mapa[LinerandBuraco][ColrandBuraco]+=buraco;
		if(LinerandBuraco-1>=0 && Mapa[LinerandBuraco-1][ColrandBuraco]==0)
			Mapa[LinerandBuraco-1][ColrandBuraco]+=brisa;
		if(LinerandBuraco+1<Linha && Mapa[LinerandBuraco+1][ColrandBuraco]==0)	
			Mapa[LinerandBuraco+1][ColrandBuraco]+=brisa;
		if(ColrandBuraco-1>=0 && Mapa[LinerandBuraco][ColrandBuraco-1]==0)
			Mapa[LinerandBuraco][ColrandBuraco-1]+=brisa;
		if(ColrandBuraco+1<Coluna && Mapa[LinerandBuraco][ColrandBuraco+1]==0)
			Mapa[LinerandBuraco][ColrandBuraco+1]+=brisa;
	}

}

void WorldMAP::printMapa()
{
	bool flag=false;
	cout << "┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐" << endl;
	for(int i=0;i<Linha;i++)
	{
		
		if(flag==false)
			flag=true;
		else
			cout << "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤" << endl;
			
		cout <<"│ ";
		for(int j=0;j<Coluna;j++)
		{
			cout << Mapa[i][j] << " │ ";
		}
		cout << endl;
	}
	cout << "└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘" << endl;
}


class Player : public WorldMAP{
	private:
		int PlayerMap[Linha][Coluna];
		int PosiLinha;
		int PosiCol;		
	public:
		Player();
		void moveIA();
		void UP();
		void DOWN();
		void RIGHT();
		void LEFT();
		
		
		
};

Player::Player(){
	for(int i=0; i<Linha;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			PlayerMap[i][j]=0;
		}
	}
	PlayerMap[0][0]=player;	
}

void Player::UP(){
	if(PosiLinha!=0)
	{
		PlayerMap[PosiLinha-1][PosiCol]=player;
		PlayerMap[PosiLinha][PosiCol]=PosVisitada;
		
	}
}
void Player::DOWN(){
	if(PosiLinha!=Linha-1)
	{
		PlayerMap[PosiLinha+1][PosiCol]=player;
		PlayerMap[PosiLinha][PosiCol]=PosVisitada;
		
	}
}
void Player::RIGHT(){
	if(PosiCol!=Coluna-1)
		{
			PlayerMap[PosiLinha][PosiCol+1]=player;
			PlayerMap[PosiLinha][PosiCol]=PosVisitada;
			
		}
}
void Player::LEFT(){
	if(PosiCol!=0)
	{
		PlayerMap[PosiLinha][PosiCol-1]=player;
		PlayerMap[PosiLinha][PosiCol]=PosVisitada;
		
	}
}

void Player::moveIA(){
	
	/*if(PosiLinhaW!=0)// Para cima
	{
		if(WumpusMap[PosiLinhaW-1][PosiColW]>=0)
		{
			WumpusMap[PosiLinhaW-1][PosiColW]=wumpus;
			WumpusMap[PosiLinhaW][PosiColW]=PosVisitada;
			
		}
	}
	else if(PosiColW!=0)// Para esquerda
	{
		if(WumpusMap[PosiLinhaW][PosiColW-1]>=0)
		{
			WumpusMap[PosiLinhaW][PosiColW-1]=wumpus;
			WumpusMap[PosiLinhaW][PosiColW]=PosVisitada;
			
		}
	}
	else if(PosiLinhaW!=Linha-1)// Para baixo
	{
		if(WumpusMap[PosiLinhaW+1][PosiColW]>=0)
		{
			WumpusMap[PosiLinhaW+1][PosiColW]=wumpus;
			WumpusMap[PosiLinhaW][PosiColW]=PosVisitada;
			
		}
	}
	else if(PosiColW!=Coluna-1)// Para direita
	{
		if(WumpusMap[PosiLinhaW][PosiColW+1]>=0)
		{
			WumpusMap[PosiLinhaW][PosiColW+1]=wumpus;
			WumpusMap[PosiLinhaW][PosiColW]=PosVisitada;
			
		}
	}*/
}
int main()
{
	WorldMAP GameMap;
	GameMap.printMapa();
	//int **Mapa;
	//Mapa=alocaMatriz(Linha,Coluna);
	//inicializaMatriz(Mapa);
	//PrintMatriz(Mapa);
	return 0;
}
