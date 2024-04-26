#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define NUM_NAVIOS 5

typedef struct
{
  int x, y;
}
Coordenada;

typedef struct
{
  Coordenada posicao;
  int acertou;
}
Navio;


void inicializaTabuleiro(char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO])
{

  for(int i = 0; i < TAM_TABULEIRO; i ++){

    for(int j = 0; j < TAM_TABULEIRO; j ++){
      tabuleiro[i][j] = ' ';
    }
  }
}

void imprimeTabuleiro(char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO])
{

  printf("   ");

  for(int i = 1; i < TAM_TABULEIRO; i ++)
  {

    printf("%d  ", i);
  }
  printf("\n");

  for(int i = 1; i < TAM_TABULEIRO; i ++)
  {

    printf("%d ", i);

    for(int j = 1; j < TAM_TABULEIRO; j ++)
    {

      printf("[%c]", tabuleiro[i][j]);
    }

    printf("\n");
  }
}

void posicionaNavios(Navio navios[NUM_NAVIOS], char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int jogador)
{
  
  printf("Jogador %d, posicione seus navios:\n", jogador);
  
  for(int i = 0; i < NUM_NAVIOS; i++)
  {
    int x, y;
    
    printf("Posicione o navio %d (x y): ", i ++);
    
    scanf("%d %d", &x, &y);
    
    while(x < 0 || x >= TAM_TABULEIRO || y < 0 || y >= TAM_TABULEIRO || tabuleiro[x][y] == 'N')
    {
      
      printf("Posição inválida! Tente novamente: ");
      
      scanf("%d %d", &x, &y);
    }
    navios[i].posicao.x = x;
    navios[i].posicao.y = y;
    navios[i].acertou = 0;
    tabuleiro[x][y] = 'N';
  }
}

int ehValida(int x, int y)
{
  
  return x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO;
}

int atingiuCoordenada(Navio navios[NUM_NAVIOS], int x, int y)
{

  for(int i = 0; i < NUM_NAVIOS; i++)
  {
    
    if(navios[i].posicao.x == x && navios[i].posicao.y == y)
    {
      
      return navios[i].acertou;
    }
  }
  
  return 0;
}

void atirar(Navio navios[NUM_NAVIOS], char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int x, int y, int jogador) 
{
  if(!ehValida(x, y)) 
  {
    
    printf("Coordenada inválida!\n");
    
    return;
  }
  
  if(tabuleiro[x][y] == ' ')
  {
    
    printf("Água!\n");
  }
  
  else
    
    if(tabuleiro[x][y] == 'N' && !ehValida(x, y))
    {
      
      printf("Acertou um navio!\n");
      
      for (int i = 0; i < NUM_NAVIOS; i++)
      {
        if(navios[i].posicao.x == x && navios[i].posicao.y == y) 
        {
          navios[i].acertou = 1;
          
          break;
        }
      }
    }
    
    else
    {
    
      printf("Esta coordenada já foi atingida!\n");
    }
  tabuleiro[x][y] = 'X';

  int naviosRestantes = 0;
  
  for(int i = 0; i < NUM_NAVIOS; i++)
  {
    if(!navios[i].acertou)
    {
      naviosRestantes ++;
    }
  }

  if(naviosRestantes == 0)
  {
    
    printf("Parabéns, jogador %d! Você afundou todos os navios do adversário!\n", jogador);
    
    exit(0);
  }
}

int main() {
  char tabuleiro1[TAM_TABULEIRO][TAM_TABULEIRO], tabuleiro2[TAM_TABULEIRO][TAM_TABULEIRO];
  Navio navio1[NUM_NAVIOS], navio2[NUM_NAVIOS];

  inicializaTabuleiro(tabuleiro1);
  inicializaTabuleiro(tabuleiro2);

  posicionaNavios(navio1, tabuleiro1, 1);
  posicionaNavios(navio2, tabuleiro2, 2);

  printf("Bem-vindo ao Jogo da Batalha Naval!\n\n");
  printf("Jogador 1, este é o seu tabuleiro:\n");
  imprimeTabuleiro(tabuleiro1);
  printf("\nJogador 2, este é o seu tabuleiro:\n");
  imprimeTabuleiro(tabuleiro2);

  int jogadorAtual = 1;
  
  while(1)
  {
    int x, y;
    
    printf("\nJogador %d, digite as coordenadas do seu tiro (x y): ", jogadorAtual);
    
    scanf("%d %d", &x, &y);
    
    printf("\n");

    if(jogadorAtual == 1)
    {
      atirar(navio2, tabuleiro2, x, y, jogadorAtual);

      imprimeTabuleiro(tabuleiro2);
    }
    
    else
    {
      
      atirar(navio1, tabuleiro1, x, y, jogadorAtual);
      
      imprimeTabuleiro(tabuleiro1);
    }

    jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
  }

  return 0;
}