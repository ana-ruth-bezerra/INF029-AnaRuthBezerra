#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCESSO_CADASTRO -1
#define ERRO_CADASTRO_MATRICULA -2
#define ERRO_CADASTRO_SEXO -3
#define ERRO_DATA_INVALIDA -4
#define LISTA_VAZIA -5
#define SUCESSO_EXCLUSAO -6
#define NAO_ENCONTRADO -7

typedef struct dma{
  char dataCompleta[11];
  int dia;
  int mes;
  int ano; 
}Data;

typedef struct dados_aluno{
  int matricula;
  char nome[50];
  char sexo;
  Data data_nascimento;
  char cpf[15];
  struct dados_aluno *prox;
}Aluno;

typedef struct dados_professor{
  int matricula;
  char nome[50];
  char sexo;
  Data data_nascimento;
  char cpf[15];
  struct dados_professor *prox;
}Professor;

typedef struct dados_disciplina{
  int codigo;
  char nome[50];
  int *semestre;
  Professor *matricula;
  struct dados_disciplina *prox;
}Disciplina;

int menuGeral();
int menuAluno();
int menuProfessor();
int menuDisciplina();
int geraMatricula();
void mainAluno(Aluno** inicioListaAluno);
void mainProfessor(Professor** inicioListaProfessor);
void mainDisciplina(Disciplina** inicioListaDisciplina);
int inserirAluno(Aluno** inicio);
void listarAlunos(Aluno** inicio);
int excluirAlunoNaLista(Aluno** inicio, int matricula);
int excluirAluno(Aluno** inicio);
int inserirProfessor(Professor** inicio);
int excluirProfessorNaLista(Professor** inicio, int matricula);
int excluirProfessor(Professor** inicio);
void listarProfessor(Professor** inicio);
int inserirDisciplina(Disciplina** inicio);
int excluirDisciplina(Disciplina** inicio);
void listarDisciplina(Disciplina** inicio);
int excluirDisciplinaNaLista(Disciplina** inicio, int codigo);
int validar_data(char data[]);
int valida_data_numeros(int dia, int mes, int ano);
void liberarListaAluno(Aluno* inicio);
void liberarListaProfessor(Professor* inicio);
void liberarListaDisciplina(Disciplina* inicio);
void finalizarEscola(Aluno* inicio, Professor* inicioProf, Disciplina* inicioDisc);

int main(){
  Aluno* inicioListaAluno = NULL,  aluno;
  Professor* inicioListaProfessor = NULL,  professor;
  Disciplina* inicioListaDisciplina = NULL,  disciplina;
  int opcao, retorno, sair = 0;

  while(!sair){
    opcao = menuGeral();

    switch(opcao){

      case 0:{

        printf("Finalizando Escola\n");

        finalizarEscola(inicioListaAluno, inicioListaProfessor, inicioListaDisciplina);
        sair = 1;

        break;
      }

      case 1:{

        mainAluno(&inicioListaAluno);

        break;
      }

      case 2:{

        mainProfessor(&inicioListaProfessor);

        break;

      case 3:{

        mainDisciplina(&inicioListaDisciplina);

        break;
      }
      }

      default:{

        printf("Opcao Invalida\n");
      }
    }
  }
}

int geraMatricula(){
  static int num = 0;
  num++;

  return num;
}

int menuGeral(){
  int opcao;

  printf("Projeto Escola\n");
  printf("0 - Sair\n");
  printf("1 - Aluno\n");
  printf("2 - Professor\n");
  printf("3 - Disciplina\n");

  scanf("%d", &opcao);

  return opcao;
}

int menuAluno(){
  int opcao;

  printf("\tMódulo de Aluno\n");
  printf("\tDigite a opção: \n");
  printf("0 - Voltar para o menu geral\n");
  printf("1 - Inserir Aluno\n");
  printf("2 - Excluir Aluno\n");
  printf("3 - Listar Alunos\n");

  scanf("%d",&opcao);

  return opcao;
}

int menuProfessor(){
  int opcao;

  printf("\tMódulo de Professor\n");
  printf("\tDigite a opção: \n");
  printf("0 - Voltar para o menu geral\n");
  printf("1 - Inserir Professor\n");
  printf("2 - Excluir Professor\n");
  printf("3 - Listar Professor\n");

  scanf("%d",&opcao);

  return opcao;
}

int menuDisciplina(){
  int opcao;

  printf("\tMódulo de Disciplina\n");
  printf("\tDigite a opção: \n");
  printf("0 - Voltar para o menu geral\n");
  printf("1 - Inserir Disciplina\n");
  printf("2 - Excluir Disciplina\n");
  printf("3 - Listar Disciplina\n");

  scanf("%d",&opcao);

  return opcao;
}

void mainAluno(Aluno** inicioListaAluno){
  int opcao, retorno, sair = 0;

  while(!sair){
  opcao = menuAluno();

  switch(opcao){

    case 0:{
      sair = 1;

      break;
    }

    case 1:{
      retorno = inserirAluno(inicioListaAluno);

      if(retorno == SUCESSO_CADASTRO){ 

        printf("Aluno cadastrado com sucesso\n");
      }

      else{

        switch(retorno){

          case ERRO_CADASTRO_MATRICULA:{

            printf("Matrícula Inválida. Deve ser maior que 0.\n");

            break;
          }
          case ERRO_CADASTRO_SEXO:{

            printf("Sexo Inválido. Digite 'm' ou 'M' para Masculino ou 'f' ou 'F' para Feminino.\n");

            break;
          }
          case ERRO_DATA_INVALIDA:{

            printf("Data Inválida.\n");

            break;
          }
          default:{

            printf("Erro desconhecido.\n");
          }
        }
      }  

      break;
    }

    case 2:{
      retorno = excluirAluno(inicioListaAluno);

      if(retorno == SUCESSO_EXCLUSAO){ 
        printf("Aluno excluido com sucesso\n");
      }else{

        switch(retorno){
          case LISTA_VAZIA:{
            printf("Lista Vazia.\n");

            break;
          }
          case NAO_ENCONTRADO:{
            printf("Não foi encontrado o aluno com a matrícula digitada.\n");

            break;
          }
          default:{
            printf("Erro desconhecido.\n");
          }
        }
      }  

      break;
    }

    case 3:{
      listarAlunos(inicioListaAluno);

      break;
    }

    default:{

      printf("opcao inválida\n");
    }
  }
  }
}

void mainProfessor(Professor** inicioListaProfessor){
  int opcao, retorno, sair = 0;

  while(!sair){
    opcao = menuProfessor();

    switch(opcao){

      case 0:{
        sair = 1;

        break;
      }

      case 1:{
        retorno = inserirProfessor(inicioListaProfessor);

        if(retorno == SUCESSO_CADASTRO){ 

          printf("Professor cadastrado com sucesso\n");
        }

        else{

          switch(retorno){

            case ERRO_CADASTRO_MATRICULA:{

              printf("Matrícula Inválida. Deve ser maior que 0.\n");

              break;
            }

            case ERRO_CADASTRO_SEXO:{

              printf("Sexo Inválido. Digite 'm' ou 'M' para Masculino ou 'f' ou 'F' para Feminino.\n");

              break;
            }

            case ERRO_DATA_INVALIDA:{

              printf("Data Inválida.\n");

              break;
            }

            default:{

              printf("Erro desconhecido.\n");
            }
          }
        }  

        break;
      }

      case 2:{
        retorno = excluirProfessor(inicioListaProfessor);

        if(retorno == SUCESSO_EXCLUSAO){ 

          printf("Professor excluido com sucesso\n");
        }

        else{

          switch(retorno){

            case LISTA_VAZIA:{

              printf("Lista Vazia.\n");

              break;
            }

            case NAO_ENCONTRADO:{

              printf("Não foi encontrado o professor com a matrícula digitada.\n");

              break;
            }

            default:{

              printf("Erro desconhecido.\n");
            }
          }
        } 

        break;
      }

      case 3:{

        listarProfessor(inicioListaProfessor);

        break;	
      }

      default:{

        printf("opcao invalida\n");
      }
    }
  }
}

void mainDisciplina(Disciplina** inicioListaDisciplina){
  int opcao, retorno, sair = 0;

  while(!sair){
    opcao = menuDisciplina();

    switch(opcao){

      case 0:{
        sair = 1;

        break;
      }

      case 1:{
        retorno = inserirDisciplina(inicioListaDisciplina);

        if(retorno == SUCESSO_CADASTRO){ 

          printf("Disciplina cadastrada com sucesso\n");
        }

        else{

          switch(retorno){

            case ERRO_CADASTRO_MATRICULA:{

              printf("Matrícula Inválida. Deve ser maior que 0.\n");

              break;
            }

            case ERRO_CADASTRO_SEXO:{

              printf("Sexo Inválido. Digite 'm' ou 'M' para Masculino ou 'f' ou 'F' para Feminino.\n");

              break;
            }

            case ERRO_DATA_INVALIDA:{

              printf("Data Inválida.\n");

              break;
            }

            default:{

              printf("Erro desconhecido.\n");
            }
          }
        }  

        break;
      }

      case 2:{
        retorno = excluirDisciplina(inicioListaDisciplina);

        if(retorno == SUCESSO_EXCLUSAO){ 

          printf("Disciplina excluida com sucesso\n");

        }

        else{

          switch(retorno){

            case LISTA_VAZIA:{

              printf("Lista Vazia.\n");

              break;
            }

            case NAO_ENCONTRADO:{

              printf("Não foi encontrado o professor com a matrícula digitada.\n");

              break;
            }

            default:{

              printf("Erro desconhecido.\n");
            }
          }
        }  

        break;
      }

      case 3:{

        listarDisciplina(inicioListaDisciplina);

        break;	
      }

      default:{
        printf("Opcao Invalida\n");
      }
    }
  }
}

void inserirAlunoNaLista(Aluno** inicio, Aluno* novoAluno){
  Aluno *atual;

  if(*inicio == NULL)
    *inicio = novoAluno;

  else{
    atual = *inicio;

    while(atual->prox != NULL)
      atual = atual->prox;
    atual->prox = novoAluno;
    }
  novoAluno->prox = NULL;
}

void inserirProfessorNaLista(Professor** inicio, Professor* novoProfessor){
  Professor *atual;

  if(*inicio == NULL)
    *inicio = novoProfessor;

  else{
    atual = *inicio;

    while(atual->prox != NULL)
      atual = atual->prox;
    atual->prox = novoProfessor;
  }
  novoProfessor->prox = NULL;
}

void inserirDisciplinaNaLista(Disciplina** inicio, Disciplina* novaDisciplina){
  Disciplina *atual;

  if(*inicio == NULL)
    *inicio = novaDisciplina;

  else{
    atual = *inicio;

    while(atual->prox != NULL)
      atual = atual->prox;
    atual->prox = novaDisciplina;
  }
  novaDisciplina->prox = NULL;
}

int inserirAluno(Aluno** inicio){
  int retorno = SUCESSO_CADASTRO;
  Aluno* novoAluno = (Aluno*)malloc(sizeof(Aluno));

  printf("\n\tCadastro de Aluno\n");
  getchar();

  printf("Digite o nome: ");
  fgets(novoAluno->nome, 50, stdin); 
  size_t ln = strlen(novoAluno->nome) - 1;

  if(novoAluno->nome[ln] == '\n')
    novoAluno->nome[ln] = '\0';

  printf("Digite o sexo: ");
  scanf("%c", &novoAluno->sexo);
  novoAluno->sexo = toupper(novoAluno->sexo);

  if(novoAluno->sexo != 'M' && novoAluno->sexo != 'F'){

    retorno = ERRO_CADASTRO_SEXO;
  }

  else{
    char data[11];

    printf("Digite a data de nascimento: ");

    scanf("%s", novoAluno->data_nascimento.dataCompleta);

    getchar();
    int dataValida = validar_data(novoAluno->data_nascimento.dataCompleta);

    if(dataValida == 0){

      retorno = ERRO_DATA_INVALIDA;
    }

    else{

      printf("Digite o CPF: ");

      fgets(novoAluno->cpf, 15, stdin); 
      ln = strlen(novoAluno->cpf) - 1; 

      if(novoAluno->cpf[ln] == '\n')
        novoAluno->cpf[ln] = '\0';
    }
  }

  if(retorno == SUCESSO_CADASTRO){
    novoAluno->matricula = geraMatricula();

    inserirAlunoNaLista(inicio, novoAluno);

    return SUCESSO_CADASTRO;
  }

  else{

    free(novoAluno);

    return retorno;
  }  
}

int inserirProfessor(Professor** inicio){
  int retorno = SUCESSO_CADASTRO;
  Professor* novoProfessor = (Professor*)malloc(sizeof(Professor));

  printf("\n\tCadastro de Professor\n");

  getchar();

  printf("Digite o nome: ");

  fgets(novoProfessor->nome, 50, stdin); 
  size_t ln = strlen(novoProfessor->nome) - 1;

  if(novoProfessor->nome[ln] == '\n')
    novoProfessor->nome[ln] = '\0';

  printf("Digite o sexo: ");

  scanf("%c", &novoProfessor->sexo);
  novoProfessor->sexo = toupper(novoProfessor->sexo);

  if(novoProfessor->sexo != 'M' && novoProfessor->sexo != 'F'){

    retorno = ERRO_CADASTRO_SEXO;
  }else{
    char data[11];

    printf("Digite a data de nascimento: ");

    scanf("%s", novoProfessor->data_nascimento.dataCompleta);

    getchar();
    int dataValida = validar_data(novoProfessor->data_nascimento.dataCompleta);

    if(dataValida == 0){

      retorno = ERRO_DATA_INVALIDA;
    }

    else{
      printf("Digite o CPF: ");

      fgets(novoProfessor->cpf, 15, stdin); 
      ln = strlen(novoProfessor->cpf) - 1; 

      if(novoProfessor->cpf[ln] == '\n')
        novoProfessor->cpf[ln] = '\0';
    }
  }

  if(retorno == SUCESSO_CADASTRO){
    novoProfessor->matricula = geraMatricula();

    inserirProfessorNaLista(inicio, novoProfessor);

    return SUCESSO_CADASTRO;
  }

  else{

    free(novoProfessor);

    return retorno;
  }
}

int inserirDisciplina(Disciplina** inicio){
  int retorno = SUCESSO_CADASTRO;
  Disciplina* novaDisciplina = (Disciplina*)malloc(sizeof(Disciplina));

  printf("\n\tCadastro de Disciplina\n");

  getchar();

  printf("Digite o nome da disciplina: ");

  fgets(novaDisciplina->nome, 50, stdin); 
  size_t ln = strlen(novaDisciplina->nome) - 1;

  if(novaDisciplina->nome[ln] == '\n')
    novaDisciplina->nome[ln] = '\0';
    
  printf("Digite o semestre: ");

  scanf("%ls", novaDisciplina->semestre);

  // fgets(novaDisciplina->semestre, 50, stdin);
  // ln = strlen(novaDisciplina->semestre) - 1;

  // if(novaDisciplina->semestre[ln] == '\n')
  //   novaDisciplina->semestre[ln] = '\0';
  
  printf("Digite o nome do professor: ");
  Disciplina *professor = malloc(sizeof(Disciplina));

  fgets(novaDisciplina->matricula, 50, stdin);

  if(retorno == SUCESSO_CADASTRO){
    novaDisciplina->codigo = geraMatricula();
    
    inserirDisciplinaNaLista(inicio, novaDisciplina);

    return SUCESSO_CADASTRO;
  }

  else{

    free(novaDisciplina);

    return retorno;
  }  
}

int excluirAlunoNaLista(Aluno** inicio, int matricula){

  if(*inicio == NULL)

    return LISTA_VAZIA;
  Aluno* anterior = *inicio, * atual = *inicio, * proximo = atual->prox;
  int achou = 0;

  while(atual != NULL){

    if(atual->matricula == matricula){
      achou = 1;

      break;
    }
    anterior = atual;
    atual = proximo;

    if(atual != NULL)
      proximo = atual->prox;
  }

  if(achou){

    if(atual == *inicio)
      *inicio = proximo;
    else
      anterior->prox = atual->prox;

    free(atual);

    return SUCESSO_EXCLUSAO;
  }

  else

    return NAO_ENCONTRADO;
}

int excluirProfessorNaLista(Professor** inicio, int matricula){

  if(*inicio == NULL)

    return LISTA_VAZIA;

  Professor* anterior = *inicio, * atual = *inicio, * proximo = atual->prox;
  int achou = 0;

  while(atual != NULL){

    if(atual->matricula == matricula){
      achou = 1;

      break;
    }
    anterior = atual;
    atual = proximo;

    if(atual != NULL)
      proximo = atual->prox;
  }

  if(achou){

    if(atual == *inicio)
      *inicio = proximo;

    else
      anterior->prox = atual->prox;

    free(atual);

    return SUCESSO_EXCLUSAO;
  }

  else

    return NAO_ENCONTRADO;
}

int excluirDisciplinaNaLista(Disciplina** inicio, int codigo){

  if(*inicio == NULL)

    return LISTA_VAZIA;

  Disciplina* anterior = *inicio, * atual = *inicio, * proximo = atual->prox;
  int achou = 0;

  while(atual != NULL){

    if(atual->codigo == codigo){
      achou = 1;

      break;
    }
    anterior = atual;
    atual = proximo;

    if(atual != NULL)
      proximo = atual->prox;
  }

  if(achou){

    if(atual == *inicio)
      *inicio = proximo;

    else
      anterior->prox = atual->prox;

    free(atual);

    return SUCESSO_EXCLUSAO;
  }

  else

    return NAO_ENCONTRADO;
}

int excluirAluno(Aluno** inicio){
  int matricula;

  printf("Digite a matrícula: ");  

  scanf("%d", &matricula);

  getchar();

  return excluirAlunoNaLista(inicio, matricula);
}

int excluirProfessor(Professor** inicio){
  int matricula;

  printf("Digite a matrícula: ");   

  scanf("%d", &matricula);

  getchar();

  return excluirProfessorNaLista(inicio, matricula);
}

int excluirDisciplina(Disciplina** inicio){
  int codigo;

  printf("Digite o codigo da disciplina: \n");   

  scanf("%d", &codigo);

  getchar();

  return excluirDisciplinaNaLista(inicio, codigo);
}

void listarAlunos(Aluno** inicio){
  Aluno* alunoAtual = *inicio;

  if(*inicio == NULL){

    printf("Lista Vazia\n");
  }

  else{

    printf("\n\tAlunos Cadastrados\n");

    do{

      printf("Matrícula: %d\n", alunoAtual->matricula);
      printf("Nome: %s\n", alunoAtual->nome);
      printf("Sexo: %c\n", alunoAtual->sexo);
      printf("Data Nascimento: %s\n", alunoAtual->data_nascimento.dataCompleta);
      printf("CPF: %s\n", alunoAtual->cpf);
      printf("\n");
        
      alunoAtual = alunoAtual->prox;
    }

    while(alunoAtual != NULL);
  }
}

void listarProfessor(Professor** inicio){
  Professor* professorAtual = *inicio;

  if(*inicio == NULL){

    printf("Lista Vazia\n");
  }

  else{

    printf("\n\tProfessores Cadastrados\n");

    do{

      printf("Matrícula: %d\n", professorAtual->matricula);
      printf("Nome: %s\n", professorAtual->nome);
      printf("Sexo: %c\n", professorAtual->sexo);
      printf("Data Nascimento: %s\n", professorAtual->data_nascimento.dataCompleta);
      printf("CPF: %s\n", professorAtual->cpf);
      printf("\n");
      
      professorAtual = professorAtual->prox;
    }

    while(professorAtual != NULL);
  }
}

void listarDisciplina(Disciplina** inicio){
  Disciplina *disciplinaAtual = *inicio;

  if(*inicio == NULL){

    printf("Lista Vazia\n");
  }

  else{

    printf("\n\tProfessores Cadastrados\n");

    do{

      printf("Nome: %s\n", disciplinaAtual->nome);
      printf("Codigo: %d\n", disciplinaAtual->codigo);
      printf("Semestre: %ls\n", disciplinaAtual->semestre);
      printf("Professor: %s\n", disciplinaAtual->matricula);
      printf("\n");
      
      disciplinaAtual = disciplinaAtual->prox;
    }

    while(disciplinaAtual != NULL);
  }
}

void liberarListaAluno(Aluno* inicio){
  Aluno* atual = inicio, * tmp;

  while(atual != NULL){
    tmp = atual->prox;

    free(atual);
    atual = tmp;
  }
}

void liberarListaProfessor(Professor* inicio){
  Professor* atual = inicio, * tmp;

  while(atual != NULL){
    tmp = atual->prox;

    free(atual);
    atual = tmp;
  }
}

void liberarListaDisciplina(Disciplina* inicio){
  Disciplina* atual = inicio, * tmp;

  while(atual != NULL){
    tmp = atual->prox;

    free(atual);
    atual = tmp;
  }
}

int validar_data(char data[]){

  return 1;
  int dia, mes, ano, i;
  char sDia[3], sMes[3], sAno[5];

  for(i = 0; data[i] != '/' && i < 2; i++){
    sDia[i] = data[i];   
  }
  sDia[i] = '\0';

  strcpy(sDia, data);
  int retorno = valida_data_numeros(dia, mes, ano);

  return retorno;
}

int valida_data_numeros(int dia, int mes, int ano){

  return 1;

  if(dia < 1 || dia > 31)

    return 0;

  if(mes < 1 || mes > 12)

    return 0;

  if(ano <= 0)

    return 0;
}

void finalizarEscola(Aluno* inicio, Professor* inicioProf, Disciplina* inicioDisc){

  liberarListaAluno(inicio);

  liberarListaProfessor(inicioProf);

  liberarListaDisciplina(inicioDisc);
}