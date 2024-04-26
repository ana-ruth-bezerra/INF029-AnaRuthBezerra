#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABULEIRO 10
#define NUM_NAVIOS 5

typedef struct
{
  int tamanho, afundado;
}
Navio;

typedef struct
{
  char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
  Navio navios[NUM_NAVIOS];
}
Jogador;

void inicializaTabuleiro(Jogador * jogador);
void imprimeTabuleiro(Jogador jogador);
void posicionaNavios(Jogador * jogador);
void atirar(Jogador * jogador, char tabuleiro_oponente[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna);
int verificaVitoria(Jogador jogador);

int main()
{
  Jogador jogador1, jogador2;

  inicializaTabuleiro(&jogador1);

  inicializaTabuleiro(&jogador2);

  printf("\t#### BATALHA NAVAL ####\n");

  printf("Jogador 1, posicione os seus navios: \n");
  
  posicionaNavios(&jogador1);

  printf("Jogador 2, posicione os seus navios: \n");
  
  posicionaNavios(&jogador2);
  int vezJogador1 = 1, linha, coluna;

  while(1)
  {

    if(vezJogador1)
    {

      printf("Vez do jogador 1\n");

      imprimeTabuleiro(jogador1);
      
      printf("Informe as coordenadas do tiro (linha e coluna): ");

      scanf("%d %d", &linha, &coluna);

      atirar(&jogador1, jogador2.tabuleiro, linha, coluna);
      vezJogador1 = 0;
      
      if(verificaVitoria(jogador1))
      {

        printf("Jogador 1 venceu!\n");

        break;
      }
    }

    else
    {

      printf("Vez do jogador 2\n");
      
      imprimeTabuleiro(jogador2);
      
      printf("Informe as coordenadas do tiro (linha e coluna): ");

      scanf("%d %d", &linha, &coluna);

      atirar(&jogador2, jogador1.tabuleiro, linha, coluna);
      vezJogador1 = 1;
      
      if(verificaVitoria(jogador2))
      {

        printf("Jogador 2 venceu!\n");

        break;
      }
    }
  }

  return 0;
}

void inicializaTabuleiro(Jogador * jogador)
{

  for(int i = 0; i < TAM_TABULEIRO; i ++){

    for(int j = 0; j < TAM_TABULEIRO; j++){
      jogador->tabuleiro[i][j] = ' ';
    }
  }
}

void imprimeTabuleiro(Jogador jogador)
{

  printf("   ");
  
  for(int i = 0; i < TAM_TABULEIRO; i ++)
  {

    printf("%d  ", i + 1);
  }
  printf("\n");

  for(int i = 0; i < TAM_TABULEIRO; i ++)
  {

    printf("%d ", i + 1);

    for(int j = 0; j < TAM_TABULEIRO; j ++)
    {

      printf("[%c]", jogador.tabuleiro[i][j]);
    }

    printf("\n");
  }
}

void posicionaNavios(Jogador * jogador)
{
  int tam_navios[NUM_NAVIOS] = {4, 3, 1, 1, 1};

  for(int i = 0; i < NUM_NAVIOS; i ++)
  {
   int linha, coluna, tamanho = tam_navios[i];

    printf("Posicione o navio de tamanho %d informando linha e coluna: ", tamanho);

    scanf("%d %d", &linha, &coluna);

    if(linha < 1 || linha > TAM_TABULEIRO || coluna < 1 ||
      (coluna + tamanho - 1 > TAM_TABULEIRO))
    {

      printf("Posição inválida! Por favor, tente novamente.\n");
      i --;

      continue;
    }
    int ocupada = 0;

    for(int j = 0; j < tamanho; j ++)
    {
      jogador->tabuleiro[linha - 1][coluna + j - 1] = 'N';
    }

    for(int k = 0; k < NUM_NAVIOS; k ++)
    {

      if(jogador->navios[k].tamanho == 0)
      {
        jogador->navios[k].tamanho = tamanho;
        jogador->navios[k].afundado = 0;

        break;
      }
    }
  }
}

void atirar(Jogador * jogador, char tabuleiro_oponente[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna)
{
  
  if(linha < 1 || linha > TAM_TABULEIRO || coluna < 1 || coluna > TAM_TABULEIRO)
  {
    
    printf("Coordenadas inválidas! Por favor, tente novamente.\n");
    
    return;
  }

  if(tabuleiro_oponente[linha - 1][coluna - 1] == 'X' || tabuleiro_oponente[linha - 1][coluna - 1] == 'O')
  {
    
    printf("Você já atirou nessa posição! Por favor, tente novamente.\n");
  
    return;
  }

  if(tabuleiro_oponente[linha - 1][coluna - 1] == 'N')
  {
    
    printf("Você acertou um navio!\n");
    tabuleiro_oponente[linha - 1][coluna - 1] = 'O';
    int navio_afundado = 1;
    
    for(int i = 0; i < NUM_NAVIOS; i++)
    {
      
      if(jogador->navios[i].tamanho == 0)
        
        continue;

      if(jogador->navios[i].afundado)
        
        continue;
      int tamanho = jogador->navios[i].tamanho;
      navio_afundado = 1;

      for(int j = 0; j < tamanho; j++)
      {
        
        if(tabuleiro_oponente[linha - 1][coluna - 1 - j] != 'O')
        {
          navio_afundado = 0;
          
          break;
        }
      }

      if(navio_afundado)
      {
        jogador->navios[i].afundado = 1;
        
        printf("Você afundou um navio!\n");
        
        break;
      }
    }
  }
    
  else
  {
    
    printf("Você errou o tiro!\n");
    tabuleiro_oponente[linha - 1][coluna - 1] = 'X';
  }
}

int verificaVitoria(Jogador jogador)
{
  
  for(int i = 0; i < NUM_NAVIOS; i ++)
  {
    
    if(jogador.navios[i].afundado == 0)
    {

      for(int linha = 0; linha < TAM_TABULEIRO; linha ++)
      {
          
        for(int coluna = 0; coluna < TAM_TABULEIRO; coluna ++)
        {
          
          if(jogador.tabuleiro[linha][coluna] == 'N')
          {

            return 0;
          }
        }
      }
      jogador.navios[i].afundado = 1;
    }
  }

  return 1;
}