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
// Última atualização: 07/05/2021

// #################################################
#define AnaRuthBezerra20212160030T1_H

typedef struct dq
{
  int iDia, iMes, iAno, valido; // 0 se inválido, e 1 se válido 
}
DataQuebrada;

typedef struct qtd
{
  int qtdDias, qtdMeses, qtdAnos, retorno;
}
DiasMesesAnos;

int isBissexto(int ano);
int valida_data_numeros(int dia, int mes, int ano);
DataQuebrada quebraData(char data[]);
int q1(char data[]);
int contaDias(int diaInicial, int diaFinal, int mesInicial, int mesFinal, int anoInicial, int anoFinal);
DiasMesesAnos q2(char datainicial[], char datafinal[]);
int q3(char *texto, char c, int isCaseSensitive);
int q4(char *strTexto, char *strBusca, int posicoes[30]);
int q5(int num);
int q6(int numerobase, int numerobusca);