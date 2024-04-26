// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Ana Ruth Bezerra
//  email: an.bezerra@gmail.com
//  Matrícula: 20212160030
//  Semestre: 2024.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "AnaRuthBezerra20212160030T1.h"

#define MESES_ANO 12

int isBissexto(int ano)
{

  return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int valida_data_numeros(int dia, int mes, int ano)
{

  if(dia < 1 || dia > 31 || mes < 1 || mes > 12)

    return 0;

  if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)

    return 0;

  int diasNoMes = (mes == 2) ? (isBissexto(ano) ? 29 : 28) : 31 - ((mes - 1) % 7 % 2);

  if(dia > diasNoMes)

    return 0;

  return 1;
}

DataQuebrada quebraData(char data[])
{
  char sDia[3], sMes[3], sAno[5];
  DataQuebrada dq;

  if(sscanf(data, "%2[^/]/%2[^/]/%4[^/]", sDia, sMes, sAno) != 3)
  {
    dq.valido = 0;

    return dq;
  }
  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);
  dq.valido = valida_data_numeros(dq.iDia, dq.iMes, dq.iAno);

  return dq;
}

int q1(char data[])
{
  DataQuebrada dataQuebrada = quebraData(data);

  return dataQuebrada.valido;
}

int contaDias(int diaInicial, int diaFinal, int mesInicial, int mesFinal, int anoInicial, int anoFinal)
{
  int meses[MESES_ANO] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int diasMesInicial, totalDias;

  if(mesFinal - mesInicial == 1 && anoFinal == anoInicial)
  {

    if((mesInicial == 2 && isBissexto(anoInicial)))
      meses[1] = 29;
    diasMesInicial = (meses[mesInicial - 1]) - diaInicial;
    totalDias = diasMesInicial + diaFinal;
  }

  else

    if(mesFinal - mesInicial == 1 && anoFinal > anoInicial)
    {
      int penultimoMes = mesFinal - 1;

      if(penultimoMes == 2 && isBissexto(anoFinal))
        meses[1] = 29; 
      diasMesInicial = (meses[mesInicial - 1]) - diaInicial;
      totalDias = diasMesInicial + diaFinal;
    }

    else
    {
      int penultimoMes = mesFinal - 1;

      if(penultimoMes == 2 && isBissexto(anoFinal))
        meses[1] = 29;
      diasMesInicial = (meses[penultimoMes - 1]) - diaInicial;
      totalDias = diasMesInicial + diaFinal;
    }

  return totalDias;
}

DiasMesesAnos q2(char datainicial[], char datafinal[])
{
  DataQuebrada dataInicial = quebraData(datainicial), dataFinal = quebraData(datafinal);
  DiasMesesAnos dma;

  if(!q1(datainicial))
  {
    dma.retorno = 2;

    return dma;
  }

  else
  
    if(!q1(datafinal))
    {
      dma.retorno = 3;
  
      return dma;
    }

    else
    {

      if(dataInicial.iAno > dataFinal.iAno)
      {
        dma.retorno = 4;

        return dma;
      }

      else 

        if(dataInicial.iAno <= dataFinal.iAno && dataInicial.iMes > dataFinal.iMes)
        {
          dma.retorno = 4;

          return dma;
        }

      else 

        if(dataInicial.iAno <= dataFinal.iAno && dataInicial.iMes == dataFinal.iMes && dataInicial.iDia > dataFinal.iDia)
        {
          dma.retorno = 4;

          return dma;
        }

      if(dataFinal.iAno >= dataInicial.iAno && dataFinal.iMes >= dataInicial.iMes && dataFinal.iDia >= dataInicial.iDia)
      {
        dma.qtdAnos = dataFinal.iAno - dataInicial.iAno;
        dma.qtdMeses = dataFinal.iMes - dataInicial.iMes;
        dma.qtdDias = dataFinal.iDia - dataInicial.iDia;
      }

      else 

        if(dataFinal.iAno >= dataInicial.iAno && dataFinal.iMes >= dataInicial.iMes && dataFinal.iDia < dataInicial.iDia)
        {
          dma.qtdAnos = dataFinal.iAno - dataInicial.iAno;
          dma.qtdMeses = dataFinal.iMes - dataInicial.iMes - 1;
          dma.qtdDias = contaDias(dataInicial.iDia, dataFinal.iDia, dataInicial.iMes, dataFinal.iMes, dataInicial.iAno, dataFinal.iAno);
        }

      else 

        if(dataFinal.iAno > dataInicial.iAno && dataFinal.iMes < dataInicial.iMes && dataFinal.iDia < dataInicial.iDia)
        {
          dma.qtdAnos = dataFinal.iAno - dataInicial.iAno - 1;
          dma.qtdMeses = (MESES_ANO - dataInicial.iMes) + dataFinal.iMes;
          dma.qtdDias = contaDias(dataInicial.iDia, dataFinal.iDia, dataInicial.iMes, dataFinal.iMes, dataInicial.iAno, dataFinal.iAno);
        }

      else

        if(dataFinal.iAno > dataInicial.iAno && dataFinal.iMes < dataInicial.iMes && dataFinal.iDia >= dataInicial.iDia)
        {
          dma.qtdAnos = dataFinal.iAno - dataInicial.iAno - 1;
          dma.qtdMeses = (MESES_ANO - dataInicial.iMes) + dataFinal.iMes;
          dma.qtdDias = dataFinal.iDia - dataInicial.iDia;
        }

      else

        if(dataFinal.iAno == dataInicial.iAno && dataFinal.iMes > dataInicial.iMes && dataFinal.iDia < dataInicial.iDia)
        {
          dma.qtdAnos = 0;
          dma.qtdMeses = dataFinal.iMes - dataInicial.iMes;
          dma.qtdDias = contaDias(dataInicial.iDia, dataFinal.iDia, dataInicial.iMes, dataFinal.iMes, dataInicial.iAno, dataFinal.iAno);
        }
    dma.retorno = 1;

    return dma;
  }
}

int q3(char texto[], char c, int isCaseSensitive)
{
  int i, qtdOcorrencias = 0;

  if(!isCaseSensitive)
  {
    if(c >= 'A' && c <= 'Z')
      c = c - 'A' + 'a';
  }
  int len = strlen(texto);

  for(i = 0; i < len; i++)
  {
    char currentChar = texto[i];

    if(!isCaseSensitive)
    {

      if(currentChar >= 'A' && currentChar <= 'Z')
        currentChar = currentChar - 'A' + 'a';
    }

    if(currentChar == c)
      qtdOcorrencias++;
  }

  return qtdOcorrencias;
}

int q4(char *strTexto, char *strBusca, int posicoes[30])
{
  int tamTexto = strlen(strTexto), tamBusca = strlen(strBusca), qtdOcorrencias = 0;

  for(int i = 0; i <= tamTexto - tamBusca; i++)
  {
    int j;
    bool encontrou = true;

    for(j = 0; j < tamBusca; j++)
    {
      char charTexto = strTexto[i + j], charBusca = strBusca[j];

      if(charTexto >= 'A' && charTexto <= 'Z')
        charTexto = charTexto - 'A' + 'a';

      if(charBusca >= 'A' && charBusca <= 'Z')
        charBusca = charBusca - 'A' + 'a';

      if(charTexto != charBusca)
      {
        encontrou = false;

        break;
      }
    }

    if(encontrou)
    {
      posicoes[qtdOcorrencias * 2] = i + 1;
      posicoes[qtdOcorrencias * 2 + 1] = i + tamBusca;
      qtdOcorrencias++;
      i += tamBusca - 1;
    }
  }

  return qtdOcorrencias;
}

int q5(int num)
{
  int N = 0;

  while(num > 0)
  {
    int digito = num % 10;
    N = N * 10 + digito;
    num /= 10;
  }

  return N;
}

int q6(int numerobase, int numerobusca)
{
  int maiorBase = 1, qtdOcorrencias = 0;

  for(int N = numerobusca; N >= 10; N /= 10, maiorBase++);

  for(int K = numerobase; K > 0; K /= 10)
  {
    int restoBase = K % 10, restoBusca = numerobusca % 10;

    if(maiorBase == 1 && numerobusca == restoBase)
      qtdOcorrencias ++;

    if(maiorBase > 1 && K % 10 == restoBusca)
    {
      int contador = 0, auxiliar = numerobusca;

      for(int L = K; L > 0 ; L /= 10)
      {
        restoBusca = auxiliar % 10;

        if(L % 10 == restoBusca)
        {
          contador ++;
          auxiliar /= 10;
        }

        else

          break;

        if(contador == maiorBase)
        {
          qtdOcorrencias++;
          K /= pow(10,(maiorBase - 1));
        }      
      }
    }
  }

  return qtdOcorrencias;
}