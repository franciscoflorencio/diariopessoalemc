#include "lista.h"
#include "senha.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAX_SENHA 50
#define MAX_TAMANHO 200
#define MAX_TAMANHO_ENT 4000

const char *nome_diretorio = "ArquivosUsuario";

//Assinatura das funçoes implementadas no final da main
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
      printf("1. Digite a senha.\n");
      printf("2. Mudar senha.\n");
      printf("3. Sair.\n");
      scanf("%d", &choice);

      switch (choice) {
      case 1:
        printf("Senha: ");
        scanf("%s", senha);
        lerSenha(pssw);
        if (strcmp(senha, pssw) == 0) {
          printf("\n... Senha correta, carregando menu...\n");
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

  LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
  inicializarLista(lista);
  popularListaDeArquivo(lista);

  while (1) {
    printf(" \nMenu\n");
    printf("\n1. Adicionar entrada.\n");
    printf("2. Editar entrada.\n");
    printf("3. Ler entrada (seleciona por data).\n");
    printf("4. Listar entradas por data.\n");
    printf("5. Excluir entrada (seleciona por data).\n");
    printf("6. Sair.\n");
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
      listarEntradasPorDatas(lista);
      break;
    case 5:
      excluiArquivo(lista);
      break;
    case 6:
      printf("Encerrando o programa...\n");
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

    printf("Digite a data (DD MM AAAA): ");
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
        printf("Digite a entrada: ");
        getchar();                                 // LimponteiroSenha o buffer do teclado
        fgets(texto, MAX_TAMANHO_ENT, stdin);      // grava entrada na variavel texto
        gravarTextoNoArquivo(texto, nome_diretorio, data);
        printf("\nEntrada adicionada com sucesso!\n");
    }
}

void editarEntrada(LISTA *lista) {
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data;
    pdata = &data;
    char texto[MAX_TAMANHO_ENT];

    printf("Digite a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

    //verifica se a data eh valida
    if((validarData(pdata)) == 0) return;

    //verifica se existe entrada com esta data
    if (buscarData(lista, data.dia, data.mes, data.ano)) {
        printf("Digite a entrada (sera adicionada ao final do arquivo):\n");
        getchar();                                 // LimponteiroSenha o buffer do teclado
        fgets(texto, MAX_TAMANHO_ENT, stdin);      // grava entrada na variavel texto
        adcionaTextoNoArquivo(texto, nome_diretorio, data);
        printf("\nEntrada adicionada ao registro anterior com sucesso!\n");
    } else {
        printf("\nNão existe arquivo com a data fornecida.\n");
    }
}

void LerEntradaPorData(LISTA *lista) {
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data;
    pdata = &data;
    char texto[MAX_TAMANHO_ENT];

    printf("Digite a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
    
     //verifica se a data eh valida
    if((validarData(pdata)) == 0) return;

     //verifica se existe entrada com esta data
    if (buscarData(lista, data.dia, data.mes, data.ano)){
        FILE *arquivoBuscado;
        //adciona o diretorio "ArquivosUsuario" ao nome do arquivo 
        char caminhoArquivoBuscado[MAX_TAMANHO + strlen(nome_diretorio) + 15];
        sprintf(caminhoArquivoBuscado, "%s/%d_%d_%d.txt", nome_diretorio, data.dia, data.mes, data.ano);
        
        arquivoBuscado = fopen(caminhoArquivoBuscado, "r");
        if (arquivoBuscado == NULL) {
            printf("Erro ao abrir o arquivo.\n");
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
  exibirLista(lista); 
}

//Exclui uma entrada do diario a ponteiroSenhartir de uma DATA fornecida
void excluiArquivo(LISTA *lista) {
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data;
    pdata = &data;

    printf("Digite a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

    //verifica se a data eh valida
    if((validarData(pdata)) == 0) return;

    //verifica se existe entrada com esta data
    if (buscarData(lista, data.dia, data.mes, data.ano)){
        char caminhoArquivoBuscado[MAX_TAMANHO + strlen(nome_diretorio) + 15];
        sprintf(caminhoArquivoBuscado, "%s/%d_%d_%d.txt", nome_diretorio, data.dia, data.mes, data.ano);

        if (remove(caminhoArquivoBuscado) == 0) {
        removerElemento(lista, data);
        printf("\nArquivo excluído com sucesso.\n"); } 
        else {
        printf("\nErro ao excluir o arquivo.\n");
        } } 
        else {
        printf("\nNão há entrada para esta data.\n");
    }
}