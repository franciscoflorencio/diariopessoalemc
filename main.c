/* Este programa funciona como um diario de registros pessoais com salvamento local dos arquivos de texto.
o programa foi feito para o projeto final da turma de programacao de computadores de 2023.2
Neste arquivo main estão definidas e implementadas as funções que sao chamadas no contexto do menu principal do programa. 
As demais implementações de funções foram feitas nos 3 arquivos .h incluidos abaixo.*/
#include "lista.h"
#include "senha.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAX_SENHA 50
#define MAX_TAMANHO 200
#define MAX_TAMANHO_ENT 4000

//Assinatura das funçoes implementadas no final da main, essas funcoes sao usadas para o menu principal do programa
void adicionarEntrada(LISTA *lista);
void editarEntrada(LISTA *lista);
void LerEntradaPorData(LISTA *lista);
void listarEntradasPorDatas(LISTA *lista);
void excluiArquivo(LISTA *lista);

int main(){
  FILE *ponteiroSenha;
  ponteiroSenha = fopen("senha.bin", "rb");
  int choice, k = 1;
  char *senha = (char *)malloc(50 * sizeof(char));
  char *pssw = (char *)malloc(50 * sizeof(char));
  
  char banner[] = 
        "  █████   ██████  █████ ████\n"
        " ███░░   ███░░███░░███ ░███\n"
        "░░█████ ░███████  ░███ ░███\n"
        " ░░░░███░███░░░   ░███ ░███\n"
        " ██████ ░░██████  ░░████████\n"
        "░░░░░░   ░░░░░░    ░░░░░░░░\n"
        "               ██████████   █████   █████████   ███████████   █████    ███████\n"
        "              ░░███░░░░███ ░░███   ███░░░░░███ ░░███░░░░░███ ░░███   ███░░░░░███\n"
        "               ░███   ░░███ ░███  ░███    ░███  ░███    ░███  ░███  ███     ░░███\n"
        "               ░███    ░███ ░███  ░███████████  ░██████████   ░███ ░███      ░███\n"
        "               ░███    ░███ ░███  ░███░░░░░███  ░███░░░░░███  ░███ ░███      ░███\n"
        "               ░███    ███  ░███  ░███    ░███  ░███    ░███  ░███ ░░███     ███\n"
        "               ██████████   █████ █████   █████ █████   █████ █████ ░░░███████░\n"
        "              ░░░░░░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░    ░░░░░░░\n";
  
  printf("\n");
  printf("%s", banner); // Imprime o banner na tela
  printf("\n");

  if (!ponteiroSenha) {
    printf("Primeira vez entrando? Digite uma senha, por favor: ");
    scanf("%s", senha);
    salvarSenha(senha);
  } else {
    while (k) {
      printf("\n******** Login ********\n");
      printf("\n%s[1]%s Digite a senha.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
      printf("%s[2]%s Mudar senha.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
      printf("%s[3]%s Sair.\n\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
      scanf("%d", &choice);

      printf("\n");
      switch (choice) {
      case 1:
        printf("Senha: ");
        scanf("%s", senha);
        lerSenha(pssw);
        if (strcmp(senha, pssw) == 0) {
          printf("\n... Senha correta, carregando menu ...\n");
          k--;
        } else {
          printf("\nSenha incorreta! Tente novamente!\n");
        }
        break;

      case 2:
        atualizarSenha();
        break;

      case 3:
        printf("Encerrando o programa...\n");
        exit(0);
      default:
        printf("Opção inválida. Tente novamente.\n");
      }
    }
  }

  criaDiretorio();  //funcao implementada no head "functions". verifica se existe um diretorio e se nao existir cria um 

  //aqui uma lista é inicializada e alocada dinamicamente
  LISTA *lista = (LISTA *)malloc(sizeof(LISTA));  //alocação da lista
  inicializarLista(lista);  // funcao implementada no head "lista". inicializa uma lista
  popularListaDeArquivo(lista); //funcao implementada no head "lista". ler um arquivo de index binario e coloca na lista 

  while (1) {
    printf("\n******************* Menu *******************\n");
    printf("\n%s[1]%s Adicionar entrada.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[2]%s Editar entrada.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[3]%s Ler entrada (seleciona por data).\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[4]%s Excluir entrada (seleciona por data).\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[5]%s Listar entradas por data.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[6]%s Salvar e sair.\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("\nEscolha uma opção: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      adicionarEntrada(lista);
      break;
    case 2:
      editarEntrada(lista);
      break;
    case 3:
      LerEntradaPorData(lista);
      break;
    case 4:
      excluiArquivo(lista);
      break;
    case 5:
      listarEntradasPorDatas(lista);
      break;
    case 6:
      printf("\nEncerrando o programa...\n");
      salvarEmArquivo(lista);
      exit(0);
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  }

  return 0;
}

//grava texto do usuario, insere a data referente ao texto na lista
//ordena a lista e depois salva o texto em um arquivo txt
void adicionarEntrada(LISTA *lista) {
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data; 
    pdata = &data;
    char texto[MAX_TAMANHO_ENT];

    printf("\nDigite a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

    //verifica se a data eh valida
    if((validarData(pdata)) == 0) return;

    //verifica se existe entrada com esta data
    if (buscarData(lista, data.dia, data.mes, data.ano)) {
        printf("\nData já ocupada.\n");
    } 
        else {
        inserirElemento(lista, data);              // Insere data na lista
        ordenarLista(lista);                       // Ordena a lista
        printf("\nDigite a entrada: ");
        getchar();                                 // LimponteiroSenha o buffer do teclado
        fgets(texto, MAX_TAMANHO_ENT, stdin);      // grava entrada na variavel texto
        gravarTextoNoArquivo(texto, nome_diretorio, data);
        printf("\nEntrada adicionada com sucesso!\n");
    }
}

//funcao recebe uma data e, se existir entrada com tal data, grava texto novo no final do arquivo
void editarEntrada(LISTA *lista) {
    //declaracao das variaveis locais da funcao
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data;
    pdata = &data;
    char texto[MAX_TAMANHO_ENT];

    printf("\nDigite a data (DD MM AAAA): "); 
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano); //salva entrada 

    //verifica se a data eh valida
    if((validarData(pdata)) == 0) return;

    if (buscarData(lista, data.dia, data.mes, data.ano)) { //verifica se existe entrada com esta data
        printf("\nDigite a entrada (sera adicionada ao final do arquivo):\n");
        getchar();                                 // limpa o buffer do teclado
        fgets(texto, MAX_TAMANHO_ENT, stdin);      // grava entrada na variavel texto
        adcionaTextoNoArquivo(texto, nome_diretorio, data); //funcao implementada no head "functions". adciona o char texto no final do arquivo
        printf("\nEntrada adicionada ao registro anterior com sucesso!\n"); 
    } else {
        printf("\nNão existe arquivo com a data fornecida.\n");
    }
}

//funcao recebe uma data e, se existir registro com ela, abre e printa o arquivo pra leitura em tela
void LerEntradaPorData(LISTA *lista) {
    //declaracao das variaveis locais da funcao
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data;
    pdata = &data;
    char texto[MAX_TAMANHO_ENT];

    printf("\nDigite a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano); //grava a data fornecida na variavel data
    
    if((validarData(pdata)) == 0) return; //verifica se a data eh valida
 
    if (buscarData(lista, data.dia, data.mes, data.ano)){ //verifica se existe entrada com esta data
        FILE *arquivoBuscado; 
        //as duas linhas seguintes adcionam o diretorio "ArquivosUsuario" ao nome do arquivo para abertura correta
        char caminhoArquivoBuscado[MAX_TAMANHO + strlen(nome_diretorio) + 15];
        sprintf(caminhoArquivoBuscado, "%s/%d_%d_%d.txt", nome_diretorio, data.dia, data.mes, data.ano);
        
        arquivoBuscado = fopen(caminhoArquivoBuscado, "r"); //abre arquivo para leitura
        if (arquivoBuscado == NULL) { //verifica se a abertura foi bem sucedida 
            printf("\nErro ao abrir o arquivo.\n");
            return;
        }

        printf("\nA entrada desse dia é:\n");

        // Ler linhas até que não haja mais para ler
        while (fgets(texto, sizeof(texto), arquivoBuscado) != NULL) {
            printf("%s", texto);
        }

        fclose(arquivoBuscado); }
        else {
            printf("\nNão há entrada para esta data.\n");
    }
}

//imprime a lista atual com todas as entradas
void listarEntradasPorDatas(LISTA *lista) { 
  if (lista->inicio == NULL) {
    printf("\nVocê não possui entradas.\n"); 
    return;
  }
  exibirLista(lista); //funcao implementada no head "lista", pecorre a lista inteira e printa na tela
}

//Exclui uma entrada do diario a ponteiroSenhartir de uma DATA fornecida
void excluiArquivo(LISTA *lista) {
    //declaracao das variaveis locais da funcao
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data;
    pdata = &data;

    printf("\nDigite a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano); //grava a data fornecida na variavel data

    if((validarData(pdata)) == 0) return; //verifica se a data eh valida

    if (buscarData(lista, data.dia, data.mes, data.ano)){ //verifica se existe entrada com esta data
        //as duas linhas seguintes adcionam o diretorio "ArquivosUsuario" ao nome do arquivo para excluir 
        char caminhoArquivoBuscado[MAX_TAMANHO + strlen(nome_diretorio) + 15];
        sprintf(caminhoArquivoBuscado, "%s/%d_%d_%d.txt", nome_diretorio, data.dia, data.mes, data.ano);

        if (remove(caminhoArquivoBuscado) == 0) {
        removerElemento(lista, data); //funcao implementada no head "lista". procura e remove um elemento fornecido da lista
        printf("\nArquivo excluído com sucesso.\n"); } 
        else {
        printf("\nErro ao excluir o arquivo.\n");
        } } 
        else {
        printf("\nNão há entrada para esta data.\n");
    }
}