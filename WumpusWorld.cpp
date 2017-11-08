//Wumpus World - Artificial Intelligence
//Bruno Henrique dos Santos Laier
//Version 0.7 08/11/2017
#include <iostream>
#include <cstdio>
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
		
		int WumpusMap[Linha][Coluna]; //posições por onde o wumpus já passou e posição atual
		int PosiLinha; // Linha em que o wumpus está
		int PosiCol;   // Coluna em que o wumpus está
			
	public:
		Wumpus();
		int getPosiLinha(); // Linha em que o wumpus está
		int getPosiCol();   // Coluna em que o wumpus está
		int UP(int **Mapa);
		int DOWN(int **Mapa);
		int RIGHT(int **Mapa);
		int LEFT(int **Mapa);
		int move(int **Mapa);
		void atualizaMatriz(int **Mapa);
		//void attackW();
		
		
};
Wumpus::Wumpus(){
	for(int i=0; i<Linha;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			WumpusMap[i][j]=0;
		}
	}
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
	WumpusMap[Linerand][Colrand]=wumpus;
	PosiLinha=Linerand;
	PosiCol=Colrand;
	
	
}
int Wumpus::getPosiLinha(){
	return PosiLinha;
}
int Wumpus::getPosiCol(){
	return PosiCol;
}

int Wumpus::UP(int **Mapa){
	if(PosiLinha!=0)
	{
		if((WumpusMap[PosiLinha-1][PosiCol]!=PosVisitada)&&(Mapa[PosiLinha-1][PosiCol]!=buraco)&&(Mapa[PosiLinha-1][PosiCol]!=ouro))
		{
			if(WumpusMap[PosiLinha-1][PosiCol]!=-2)
			{
				WumpusMap[PosiLinha-1][PosiCol]=player;
				WumpusMap[PosiLinha][PosiCol]=PosVisitada;
				PosiLinha--;
				return 1;
			}
		}
	}
	return 0;
}
int Wumpus::DOWN(int **Mapa){
	if(PosiLinha!=Linha-1)
	{
		if((WumpusMap[PosiLinha+1][PosiCol]!=PosVisitada)&&(Mapa[PosiLinha+1][PosiCol]!=buraco)&&(Mapa[PosiLinha+1][PosiCol]!=ouro))
		{
			if(WumpusMap[PosiLinha+1][PosiCol]!=-2)
			{
				WumpusMap[PosiLinha+1][PosiCol]=player;
				WumpusMap[PosiLinha][PosiCol]=PosVisitada;
				PosiLinha++;
				return 1;
			}
		}
	}
	return 0;
}
int Wumpus::RIGHT(int **Mapa){
	if(PosiCol!=Coluna-1)
	{
		if((WumpusMap[PosiLinha][PosiCol+1]!=PosVisitada)&&(Mapa[PosiLinha][PosiCol+1]!=buraco)&&(Mapa[PosiLinha][PosiCol+1]!=ouro))
		{
			if(WumpusMap[PosiLinha][PosiCol+1]!=-2)
			{
				WumpusMap[PosiLinha][PosiCol+1]=player;
				WumpusMap[PosiLinha][PosiCol]=PosVisitada;
				PosiCol++;
				return 1;
			}
		}
	}
	return 0;
}
int Wumpus::LEFT(int **Mapa){
	if(PosiCol!=0)
	{
		if((WumpusMap[PosiLinha][PosiCol-1]!=PosVisitada)&&(Mapa[PosiLinha][PosiCol-1]!=buraco)&&(Mapa[PosiLinha][PosiCol-1]!=ouro))
		{
			if(WumpusMap[PosiLinha][PosiCol-1]!=-2)
			{
				WumpusMap[PosiLinha][PosiCol-1]=player;
				WumpusMap[PosiLinha][PosiCol]=PosVisitada;
				PosiCol--;
				return 1;
			}
		}
	}
	return 0;
}

int Wumpus::move(int **Mapa){
	//int aux;
	for(int i=0;i<Linha;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			if(WumpusMap[i][j]<0)
				cout << -WumpusMap[i][j] << " ";
			else
				cout << WumpusMap[i][j] << " ";
		}
		cout << endl;
	}
	if(RIGHT(Mapa)){
		atualizaMatriz(Mapa);
		return 1;
	}
	else if(LEFT(Mapa)){
		atualizaMatriz(Mapa);
		return 1;
	}
	else if(DOWN(Mapa)){
		atualizaMatriz(Mapa);
		return 1;
	}
	else if(UP(Mapa)){
		atualizaMatriz(Mapa);
		return 1;
	}
	else{
		if(WumpusMap[((PosiLinha-1)>=0)?PosiLinha-1:PosiLinha][PosiCol]==PosVisitada)
		{
			WumpusMap[PosiLinha-1][PosiCol]=wumpus;
			WumpusMap[PosiLinha][PosiCol]=-2;
			PosiLinha--;
			atualizaMatriz(Mapa);
		}
		else if(WumpusMap[((PosiLinha+1)<Linha)?PosiLinha+1:PosiLinha][PosiCol]==PosVisitada)
		{
			WumpusMap[PosiLinha+1][PosiCol]=wumpus;
			WumpusMap[PosiLinha][PosiCol]=-2;
			PosiLinha++;
			atualizaMatriz(Mapa);
		}
		else if(WumpusMap[PosiLinha][((PosiCol+1)<Coluna)?PosiCol-1:PosiCol]==PosVisitada)
		{
			WumpusMap[PosiLinha][PosiCol-1]=wumpus;
			WumpusMap[PosiLinha][PosiCol]=-2;
			PosiCol--;
			atualizaMatriz(Mapa);
		}
		else if(WumpusMap[PosiLinha][((PosiCol+1)<Coluna)?PosiCol+1:PosiCol]==PosVisitada)
		{
			WumpusMap[PosiLinha][PosiCol+1]=wumpus;
			WumpusMap[PosiLinha][PosiCol]=-2;
			PosiCol++;
			atualizaMatriz(Mapa);
		}
		
		
		
		
	}
	return 1;
}
void Wumpus::atualizaMatriz(int **Mapa)
{
	for(int i=0;i< Linha ;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			if((Mapa[i][j]==wumpus)||(Mapa[i][j]==fedor))
			{
				Mapa[i][j]=0;
			}
		}
	}
	for(int i=0;i<Linha;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			if(Mapa[i][j]==ouro)
			{
				if(i-1>=0)
					Mapa[i-1][j]=brilho;
				if(i+1<Linha)	
					Mapa[i+1][j]=brilho;
				if(j-1>=0)					
					Mapa[i][j-1]=brilho;
				if(j+1<Coluna)					
					Mapa[i][j+1]=brilho;
			}
			if(Mapa[i][j]==buraco)
			{
				if(i-1>=0)
					Mapa[i-1][j]=brisa;
				if(i+1<Linha)	
					Mapa[i+1][j]=brisa;
				if(j-1>=0)					
					Mapa[i][j-1]=brisa;
				if(j+1<Coluna)					
					Mapa[i][j+1]=brisa;
			}
		}
	}
	int auxLinha = getPosiLinha();
	int auxColuna = getPosiCol();
	cout << "linha = " << auxLinha << "\ncoluna = " << auxColuna << endl;
	Mapa[auxLinha][auxColuna]=wumpus;
	if(auxLinha-1>=0)
		if((Mapa[auxLinha-1][auxColuna]!=buraco)&&(Mapa[auxLinha-1][auxColuna]!=ouro))
			Mapa[auxLinha-1][auxColuna]=fedor;
	if(auxLinha+1<Linha)	
		if((Mapa[auxLinha+1][auxColuna]!=buraco)&&(Mapa[auxLinha+1][auxColuna]!=ouro))
			Mapa[auxLinha+1][auxColuna]=fedor;
	if(auxColuna-1>=0)
		if((Mapa[auxLinha][auxColuna-1]!=buraco)&&(Mapa[auxLinha][auxColuna-1]!=ouro))
			Mapa[auxLinha][auxColuna-1]=fedor;
	if(auxColuna+1<Coluna)
		if((Mapa[auxLinha][auxColuna+1]!=buraco)&&(Mapa[auxLinha][auxColuna+1]!=ouro))
			Mapa[auxLinha][auxColuna+1]=fedor;
}
////////////////////////////////////////////////////////////////////////
class Player{
	private:
		int PlayerMap[Linha][Coluna];
		int PosiLinha;
		int PosiCol;		
	public:
		Player();
		int UP(int **Mapa);
		int DOWN(int **Mapa);
		int RIGHT(int **Mapa);
		int LEFT(int **Mapa);
		int getPosiLinha();
		int getPosiCol();
		int moveIA(int **Mapa);
		void moveP1(int **Mapa, char C);
		
		
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
	PosiLinha=0;
	PosiCol=0;	
}

int Player::UP(int **Mapa){
	if(PosiLinha!=0)
	{
		if((IAGameMode==true) && (PlayerMap[PosiLinha-1][PosiCol]!=PosVisitada)&&(Mapa[PosiLinha-1][PosiCol]!=wumpus&&Mapa[PosiLinha-1][PosiCol]!=buraco))
		{
			if(PlayerMap[PosiLinha-1][PosiCol]!=-2)
			{
				PlayerMap[PosiLinha-1][PosiCol]=player;
				PlayerMap[PosiLinha][PosiCol]=PosVisitada;
				if(Mapa[PosiLinha-1][PosiCol]==ouro){
					return ouro;
				}
				PosiLinha-=1;
				return 1;
			}
		}
		else if(IAGameMode==false)
		{
			PlayerMap[PosiLinha-1][PosiCol]=player;
			PlayerMap[PosiLinha][PosiCol]=PosVisitada;
			PosiLinha-=1;
			return 1;
		}
	}
	return 0;
}
int Player::DOWN(int **Mapa){
	if(PosiLinha!=Linha-1)
	{
		if((IAGameMode==true) && (PlayerMap[PosiLinha+1][PosiCol]!=PosVisitada)&&(Mapa[PosiLinha+1][PosiCol]!=wumpus&&Mapa[PosiLinha+1][PosiCol]!=buraco))
		{
			if(PlayerMap[PosiLinha+1][PosiCol]!=-2)
			{
				PlayerMap[PosiLinha+1][PosiCol]=player;
				PlayerMap[PosiLinha][PosiCol]=PosVisitada;
				if(Mapa[PosiLinha+1][PosiCol]==ouro){
					return ouro;
				}
				PosiLinha+=1;
				return 1;
			}
		}
		else if(IAGameMode==false)
		{
			PlayerMap[PosiLinha+1][PosiCol]=player;
			PlayerMap[PosiLinha][PosiCol]=PosVisitada;
			PosiLinha+=1;
			return 1;
		}
	}
	return 0;
}
int Player::RIGHT(int **Mapa){
	if(PosiCol!=Coluna-1)
	{
		if((IAGameMode==true) && (PlayerMap[PosiLinha][PosiCol+1]!=PosVisitada)&&(Mapa[PosiLinha][PosiCol+1]!=wumpus&&Mapa[PosiLinha][PosiCol+1]!=buraco))
		{
			if(PlayerMap[PosiLinha][PosiCol+1]!=-2)
			{
				PlayerMap[PosiLinha][PosiCol+1]=player;
				PlayerMap[PosiLinha][PosiCol]=PosVisitada;
				if(Mapa[PosiLinha][PosiCol+1]==ouro){
					return ouro;
				}
				PosiCol+=1;
				return 1;
			}
		}
		else if(IAGameMode==false)
		{
			PlayerMap[PosiLinha][PosiCol+1]=player;
			PlayerMap[PosiLinha][PosiCol]=PosVisitada;
			PosiCol+=1;
			return 1;
		}
	}
	return 0;
}
int Player::LEFT(int **Mapa){
	if(PosiCol!=0)
	{
		if((IAGameMode==true) && (PlayerMap[PosiLinha][PosiCol-1]!=PosVisitada)&&(Mapa[PosiLinha][PosiCol-1]!=wumpus&&Mapa[PosiLinha][PosiCol-1]!=buraco))
		{
			if(PlayerMap[PosiLinha][PosiCol-1]!=-2)
			{
				PlayerMap[PosiLinha][PosiCol-1]=player;
				PlayerMap[PosiLinha][PosiCol]=PosVisitada;
				if(Mapa[PosiLinha][PosiCol-1]==ouro){
					return ouro;
				}
				PosiCol-=1;
				return 1;
			}
		}
		else if(IAGameMode==false)
		{
			PlayerMap[PosiLinha][PosiCol-1]=player;
			PlayerMap[PosiLinha][PosiCol]=PosVisitada;
			PosiCol-=1;
			return 1;
		}
		
	}
	return 0;
}

int Player::getPosiLinha(){
	return PosiLinha;
}
int Player::getPosiCol(){
	return PosiCol;
}
int Player::moveIA(int **Mapa){
	int aux;
	if((aux=UP(Mapa))>=1){
		if(aux==2)
		{
			return 2;
		}
		return 1;
	}
	else if((aux=LEFT(Mapa))>=1){
		if(aux==2)
		{
			return 2;
		}
		return 1;
	}
	else if((aux=DOWN(Mapa))>=1){
		if(aux==2)
		{
			return 2;
		}
		return 1;
	}
	else if((aux=RIGHT(Mapa))>=1){
		if(aux==2)
		{
			return 2;
		}
		return 1;
	}
	else{
		if(PlayerMap[PosiLinha][PosiCol+1]==PosVisitada)
		{
			PlayerMap[PosiLinha][PosiCol+1]=player;
			PlayerMap[PosiLinha][PosiCol]=-2;
			PosiCol++;
		}
		else if(PlayerMap[PosiLinha+1][PosiCol]==PosVisitada)
		{
			PlayerMap[PosiLinha+1][PosiCol]=player;
			PlayerMap[PosiLinha][PosiCol]=-2;
			PosiLinha++;
		}
		else if(PlayerMap[PosiLinha][PosiCol-1]==PosVisitada)
		{
			PlayerMap[PosiLinha][PosiCol-1]=player;
			PlayerMap[PosiLinha][PosiCol]=-2;
			PosiCol--;
		}
		else if(PlayerMap[PosiLinha-1][PosiCol]==PosVisitada)
		{
			PlayerMap[PosiLinha-1][PosiCol]=player;
			PlayerMap[PosiLinha][PosiCol]=-2;
			PosiLinha--;
		}
		
		
		
		
	}
	return 1;
}
void Player::moveP1(int **Mapa, char C){
	switch(C)
	{
		case 'w' : UP(Mapa);break;
		case 's' : DOWN(Mapa);break;
		case 'a' : LEFT(Mapa);break;
		case 'd' : RIGHT(Mapa);break;
	}
}
////////////////////////////////////////////////////////////////////////
void printMapa(int** Mapa,Player P1)
{
	bool flag=false;
	int auxLinha = P1.getPosiLinha();
	int auxColuna = P1.getPosiCol();
	int MapAux[Linha][Coluna];
	for(int i=0;i<Linha;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			MapAux[i][j]=Mapa[i][j];
		}
	}
	MapAux[auxLinha][auxColuna] = player;
	cout << "┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐";
	for(int i=0;i<Linha;i++)
	{
		
		if(flag==false)
			flag=true;
		else
			cout << "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ";
		
		
		switch(i)
		{
			case 1 : cout << "█ - Player 1";break;
			case 2 : cout << "2 - Ouro";break;
			case 3 : cout << "3 - Brilho";break;
			case 4 : cout << "4 - Wumpus";break;
			case 5 : cout << "5 - Fedor";break;
			case 6 : cout << "6 - Buraco";break;
			case 7 : cout << "7 - Brisa";break;
			case 8 : if(IAGameMode==false) cout << "Comandos";break;
			case 9 : if(IAGameMode==false) cout << " A S D";break;
		}
		cout <<"\n│ ";
		for(int j=0;j<Coluna;j++)
		{
			if(MapAux[i][j]!=0){
				if(MapAux[i][j]==1)
					cout << "█ │ ";
				else
					cout << MapAux[i][j] << " │ ";
			}
			else
			cout << "  │ ";
		}
		if(i==8 && IAGameMode==false)
		{
			cout << "       W";
		}
		cout << endl;
	}
	cout << "└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘     Pressione Enter para continuar" << endl;
	
}
////////////////////////////////////////////////////////////////////////
int **inicializaMatriz(int** Mapa, Wumpus W){
	//Inicializando a matriz com 0
	for(int i=0;i< Linha ;i++)
	{
		for(int j=0;j<Coluna;j++)
		{
			Mapa[i][j]=0;
		}
	}
	
	//Colocando o Wumpus no mapa
	int auxLinha = W.getPosiLinha();
	int auxColuna = W.getPosiCol();
	Mapa[auxLinha][auxColuna]=wumpus;
	if(auxLinha-1>=0)
		Mapa[auxLinha-1][auxColuna]=fedor;
	if(auxLinha+1<Linha)	
		Mapa[auxLinha+1][auxColuna]=fedor;
	if(auxColuna-1>=0)
		Mapa[auxLinha][auxColuna-1]=fedor;
	if(auxColuna+1<Coluna)
		Mapa[auxLinha][auxColuna+1]=fedor;
		
	//Colocando o pote de Ouro no mapa
	srand( (unsigned)time(NULL) );
	int aux=rand();
	int LinerandBuraco, ColrandBuraco;
	//Colocando os buracos no mapa
	for(int i=0;i<NroBuracos;i++)
	{
		aux=rand();
		LinerandBuraco =(aux % static_cast<int>(Linha));
		aux=rand();
		ColrandBuraco = (aux % static_cast<int>(Coluna));
		Mapa[LinerandBuraco][ColrandBuraco]=buraco;
		if(LinerandBuraco-1>=0 && Mapa[LinerandBuraco-1][ColrandBuraco]==0)
			Mapa[LinerandBuraco-1][ColrandBuraco]=brisa;
		if(LinerandBuraco+1<Linha && Mapa[LinerandBuraco+1][ColrandBuraco]==0)	
			Mapa[LinerandBuraco+1][ColrandBuraco]=brisa;
		if(ColrandBuraco-1>=0 && Mapa[LinerandBuraco][ColrandBuraco-1]==0)
			Mapa[LinerandBuraco][ColrandBuraco-1]=brisa;
		if(ColrandBuraco+1<Coluna && Mapa[LinerandBuraco][ColrandBuraco+1]==0)
			Mapa[LinerandBuraco][ColrandBuraco+1]=brisa;
	}
	aux=rand();
	int LinerandOuro,ColrandOuro;
	aux=rand();
	LinerandOuro =(aux % static_cast<int>(Linha));
	aux=rand();
	ColrandOuro = (aux % static_cast<int>(Coluna));
	Mapa[LinerandOuro][ColrandOuro]=ouro;
	if(LinerandOuro-1>=0)
		Mapa[LinerandOuro-1][ColrandOuro]=brilho;
	if(LinerandOuro+1<Linha)	
		Mapa[LinerandOuro+1][ColrandOuro]=brilho;
	if(ColrandOuro-1>=0)
		Mapa[LinerandOuro][ColrandOuro-1]=brilho;
	if(ColrandOuro+1<Coluna)
		Mapa[LinerandOuro][ColrandOuro+1]=brilho;
	
	
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
int verificaPosicaoAtual(int **Mapa,Player P1){
	int l=P1.getPosiLinha();
	int c=P1.getPosiCol();
	if(Mapa[l][c]==buraco)
	{
		return 3;
	}
	if(Mapa[l][c]==wumpus)
	{
		return 2;
	}
	if(Mapa[l][c]==ouro)
	{
		return 1;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////
int main()
{
	char op;
	do
	{
		printf("\e[H\e[2J");
		cout << "   ╔══════════════════════╗\n";
		cout << "   ║ Mundo do Wumpus - IA ║\n";
		cout << "   ╚══════════════════════╝\n";
		cout << "Qual é o tipo de jogo que deseja?\n1 - Player\n2 - Inteligência Artificial"<<endl;
		cin >> op;
	}
	while(op!='1' && op!='2');
	
	if(op=='1')
	{
		IAGameMode=false;
	}
	else
	{
		IAGameMode=true;
	}
	int var;
	do
	{
		printf("\e[H\e[2J");
		cout << "   ╔══════════════════════╗\n";
		cout << "   ║ Mundo do Wumpus - IA ║\n";
		cout << "   ╚══════════════════════╝\n";
		cout << "Numero de buracos espalhados pelo mapa: "<<endl;
		cin >> var;
	}
	while(var<0 || var>10);
	NroBuracos=var;
	if(op=='1')
	{
		IAGameMode=false;
	}
	else
	{
		IAGameMode=true;
	}
	Wumpus W;
	Player P1;
	//GAME Game;
	int** Mapa=alocaMatriz(Linha,Coluna);
	
	inicializaMatriz(Mapa,W);
	printMapa(Mapa,P1);
	
	
	
	
	printf("\e[H\e[2J");
	printMapa(Mapa,P1);
	getchar();
	
	if(IAGameMode==false)
	{
		int status=0;
		//bool vezP1=true;
		bool vez=false;
		do
		{
			char C;
			if(vez==false){
				cin >> C;
				P1.moveP1(Mapa, C);
				vez=true;
			}
			else if(vez==true){
				W.move(Mapa);
				vez=false;
			}
			//atualizaMatriz(Mapa,W);
			printf("\e[H\e[2J");
			printMapa(Mapa,P1);
			
			if(status==1)
			{
				cout<< "Ouro encontrado, ache a saída"<<endl;
				for(int i=0;i<Linha;i++)
				{
					for(int j=0;j<Coluna;j++)
					{
						if(Mapa[i][j]==ouro)
						{
							Mapa[i][j]=0;
						}
						if(Mapa[i][j]==brilho)
						{
							Mapa[i][j]=0;
						}
					}
				}
				if((P1.getPosiLinha()==0)&&(P1.getPosiCol()==0))
				{
					status=5;
				}
			}
			else{
					status=verificaPosicaoAtual(Mapa,P1);
			}
		}
		while(status<2);
		if(status==3)
		{
			cout<<"Você caiu em um buraco!"<<endl;
		}
		else if(status==2)
		{
			cout<<"Você foi morto pelo Wumpus!"<<endl;
		}
		else if(status==5)
		{
			cout << "Parabéns! Você encontrou o ouro e saiu da caverna!";
		}
		//int **Mapa;
		//Mapa=alocaMatriz(Linha,Coluna);
		//inicializaMatriz(Mapa);
		//PrintMatriz(Mapa);
	}
	else{
		int aux=1;
		bool vez=false;
		printf("\e[H\e[2J");
		printMapa(Mapa,P1);
		getchar();
		
		do
		{
			if(vez==false){
				aux=P1.moveIA(Mapa);
				vez=true;
			}
			else if(vez==true){
				W.move(Mapa);
				vez=false;
			}
			
			printf("\e[H\e[2J");
			printMapa(Mapa,P1);
			if(aux==2)
			{
				cout << "Parabéns! Você encontrou o ouro e saiu da caverna!"<<endl;
			}
			if(aux==0)
			{
				cout << "Ouro não encontrado!"<<endl;
			}
			getchar();
		}
		while(aux==1);
		
	}
	return 0;
}
