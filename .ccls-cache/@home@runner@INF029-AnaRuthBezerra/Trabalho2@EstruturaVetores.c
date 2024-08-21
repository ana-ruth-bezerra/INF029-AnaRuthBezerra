#include <stdio.h>
#include <stdlib.h>

#include "EstruturaVetores.h"

#define TAM 10

estrutura vetorPrincipal[TAM];

int criarEstruturaAuxiliar(int posicao, int tamanho){

  if(posicao < 1 || posicao > TAM){

    return POSICAO_INVALIDA;
  }
  
  if(tamanho < 1){

    return TAMANHO_INVALIDO;

  }
  
  if(vetorPrincipal[posicao - 1].estruturaAux != NULL){

    return JA_TEM_ESTRUTURA_AUXILIAR;
  }
  
  else{
    vetorPrincipal[posicao - 1].estruturaAux = (int*)malloc(sizeof(int)*tamanho);
  }
  
  if(vetorPrincipal[posicao - 1].estruturaAux == NULL){

    return SEM_ESPACO_DE_MEMORIA;
  }
  vetorPrincipal[posicao - 1].tamanho = tamanho;
  vetorPrincipal[posicao - 1].qtd = 0;

  return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor){

  if(posicao < 1 || posicao > TAM){

    return POSICAO_INVALIDA;
  }
  
  else{

    if(vetorPrincipal[posicao - 1].estruturaAux != NULL){

      if(vetorPrincipal[posicao - 1].qtd < vetorPrincipal[posicao - 1].tamanho){
        vetorPrincipal[posicao - 1].estruturaAux[vetorPrincipal[posicao - 1].qtd] = valor;
        vetorPrincipal[posicao - 1].qtd ++;

        return SUCESSO;
      }
        
      else{

        return SEM_ESPACO;
      }
    }
      
    else{

      return SEM_ESTRUTURA_AUXILIAR;
    }
  }
}

int excluirNumeroDoFinaldaEstrutura(int posicao){

  if(posicao < 1 || posicao > TAM){

    return POSICAO_INVALIDA;
  }
  
  if(vetorPrincipal[posicao - 1].estruturaAux == NULL){

    return SEM_ESTRUTURA_AUXILIAR;
  }
  
  if(vetorPrincipal[posicao - 1].qtd == 0){

    return ESTRUTURA_AUXILIAR_VAZIA;
  }
  vetorPrincipal[posicao - 1].qtd--;

  return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor){

  if(posicao < 1 || posicao > TAM){

    return POSICAO_INVALIDA;
  }
  
  if(vetorPrincipal[posicao - 1].estruturaAux == NULL){

    return SEM_ESTRUTURA_AUXILIAR;
  }
  
  if(vetorPrincipal[posicao - 1].qtd == 0){

    return ESTRUTURA_AUXILIAR_VAZIA;
  }
  
  for(int i = 0; i < vetorPrincipal[posicao - 1].qtd; i ++){

    if(vetorPrincipal[posicao - 1].estruturaAux[i] == valor){

      for(int j = i; j < vetorPrincipal[posicao - 1].qtd - 1; j ++){
        vetorPrincipal[posicao - 1].estruturaAux[j] = vetorPrincipal[posicao - 1].estruturaAux[j + 1];
      }
      vetorPrincipal[posicao - 1].qtd--;

      return SUCESSO;
    }
  }

  return NUMERO_INEXISTENTE;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){

  if(posicao < 1 || posicao > TAM){

    return POSICAO_INVALIDA;
  }

  if(vetorPrincipal[posicao - 1].estruturaAux == NULL){

    return SEM_ESTRUTURA_AUXILIAR;
  }

  for(int i = 0; i < vetorPrincipal[posicao - 1].qtd; i ++){
    vetorAux[i] = vetorPrincipal[posicao - 1].estruturaAux[i];
  }

  return SUCESSO;
}

void insertionSort(int vetor[], int tamanho){
  int i, j, key;

  for(i = 1; i < tamanho; i ++){
    key = vetor[i];
    j = i - 1;

    while(j >= 0 && vetor[j] > key){
      vetor[j + 1] = vetor[j];
      j --;
    }
    vetor[j + 1] = key;
  }
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){

  if(posicao < 1 || posicao > TAM){

    return POSICAO_INVALIDA;
  }
  
  if(vetorPrincipal[posicao - 1].estruturaAux == NULL){

    return SEM_ESTRUTURA_AUXILIAR;
  }

  for(int i = 0; i < vetorPrincipal[posicao - 1].qtd; i ++){
    vetorAux[i] = vetorPrincipal[posicao - 1].estruturaAux[i];
  }

  insertionSort(vetorAux, vetorPrincipal[posicao - 1].qtd);

  return SUCESSO;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){
  int k, cont = 0;

  for(int i = 0, k = 0; i < TAM; i ++){

    if(vetorPrincipal[i].qtd == 0){
      cont ++;
    }
    
    else{

      for(int j = 0; j < vetorPrincipal[i].qtd; j ++){
        vetorAux[k ++] = vetorPrincipal[i].estruturaAux[j];
      }
    }
  }

  if(cont == TAM){

    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  }

  return SUCESSO;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){
  int k = 0, cont = 0;

  for(int i = 0; i < TAM; i ++){

    if(vetorPrincipal[i].qtd == 0){
      cont ++;
    }
    
    else{

      for(int j = 0; j < vetorPrincipal[i].qtd; j ++){
        vetorAux[k ++] = vetorPrincipal[i].estruturaAux[j];
      }
    }
  }

  if(cont == TAM){

    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  }

  insertionSort(vetorAux, k);

  return SUCESSO;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){

  if(posicao < 1 || posicao > TAM){

    return POSICAO_INVALIDA;
  }

  if(vetorPrincipal[posicao - 1].estruturaAux == NULL){

    return SEM_ESTRUTURA_AUXILIAR;
  }
  novoTamanho = vetorPrincipal[posicao - 1].tamanho + novoTamanho;

  if(novoTamanho >= 1){
    int *vetorModificado = vetorPrincipal[posicao - 1].estruturaAux;
    vetorModificado = (int*)realloc(vetorPrincipal[posicao - 1].estruturaAux, sizeof(int)*novoTamanho);

    if(vetorPrincipal[posicao - 1].estruturaAux == NULL){

      return SEM_ESPACO_DE_MEMORIA;
    }

    if(novoTamanho < vetorPrincipal[posicao - 1].qtd){
      vetorPrincipal[posicao - 1].qtd = novoTamanho;
    }
    vetorPrincipal[posicao - 1].tamanho = novoTamanho;

    return SUCESSO;
  }
  
  else{

    return NOVO_TAMANHO_INVALIDO;
  }  
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao){

  if(posicao < 1 || posicao > TAM){
    
    return POSICAO_INVALIDA;
  }

  if(vetorPrincipal[posicao - 1].estruturaAux == NULL){

    return SEM_ESTRUTURA_AUXILIAR;
  }

  if(vetorPrincipal[posicao - 1].qtd == 0){

    return ESTRUTURA_AUXILIAR_VAZIA;
  }

  return vetorPrincipal[posicao - 1].qtd;
}

No *insereElementosNaLista(No *inicio, int valor){
  No *novo = (No*)malloc(sizeof(No));
  novo->conteudo = valor;
  novo->prox = NULL;

  if(inicio == NULL){
    inicio = novo;
  }
  
  else{
    No *atual = inicio;

    while(atual->prox != NULL){
      atual = atual->prox;
    }
    atual->prox = novo;
  }

  return inicio;
}

No *montarListaEncadeadaComCabecote(){
  int cont = 0;
  No *inicio = NULL;
  inicio = (No*)malloc(sizeof(No));

  for(int i = 0; i < TAM; i ++){

    if(vetorPrincipal[i].estruturaAux != NULL && vetorPrincipal[i].qtd > 0){

      for(int j = 0; j < vetorPrincipal[i].qtd; j ++){

        insereElementosNaLista(inicio, vetorPrincipal[i].estruturaAux[j]);
      }
      cont ++;
    }
  }

  if(cont > 0){

    return inicio;
  }
  
  else{

    return NULL;
  }  
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
  No *atual = inicio->prox;

  for(int i = 0; atual != NULL; i ++){
    vetorAux[i] = atual->conteudo;
    atual = atual->prox;
  }
}

void destruirListaEncadeadaComCabecote(No **inicio){
  No *prox, *atual = *inicio;

  while(atual != NULL){
    prox = atual->prox;

    free(atual);
    atual = prox;
  }
  *inicio = atual;
}

void inicializar(){

  for(int i = 0; i < TAM; i++){
    vetorPrincipal[i].estruturaAux = NULL;
  }
}

void finalizar(){

  for(int i = 0; i < TAM; i ++){

    free(vetorPrincipal[i].estruturaAux);
  }
}