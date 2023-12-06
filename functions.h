#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAMANHO 200

//confere se a data passada como argumento eh uma data valida
int validarData(DATA* data) {
  if (data->ano < 1000 || data->ano > 3000) {
    printf("\nData inválida, ano deve estar entre 1000 e 3000.\n");
    return 0;
  }
  if (data->mes < 1 || data->mes > 12) {
    printf("\nData inválida, mês deve estar entre 1 e 12.\n");
    return 0;
  }
  if (data->dia < 1 || data->dia > 31) {
    printf("\nData inválida, dia deve estar entre 1 e 31.\n");
    return 0;
  }

  // validacao de dias em meses especificos 
  if ((data->mes == 4 || data->mes == 6 || data->mes == 9 || data->mes == 11) &&
      data->dia > 30) {
    printf("\nData inválida, neste mês, o máximo de dias é 30.\n");
    return 0;
  }
  if (data->mes == 2) {
    if ((data->ano % 4 == 0 && data->ano % 100 != 0) || data->ano % 400 == 0) {
      if (data->dia > 29) {
        printf("\nData inválida, Fevereiro em ano bissexto tem no máximo 29 dias.\n");
        return 0;
      }
    } else {
      if (data->dia > 28) {
        printf("\nData inválida, Fevereiro em ano não bissexto tem no máximo 28 dias.\n");
        return 0;
      }
    }
  }
  return 1; // A data é válida
}

//cria um arquivo .txt com o nome igual a data escolhida
//depois a entrada fornecida eh gravada no arquivo recem criado
void gravarTextoNoArquivo(char *texto, const char *nome_diretorio, DATA data) {
  FILE *arquivo;
  char nomeArquivo[MAX_TAMANHO];

  // Criando o nome do arquivo usando os valores da estrutura de data
  sprintf(nomeArquivo, "%d_%d_%d.txt", data.dia, data.mes, data.ano);

  // Abrindo o arquivo para escrita
  char caminhoArquivo[MAX_TAMANHO + strlen(nome_diretorio) +
                      2]; // +2 para o '/' e o caractere nulo
  sprintf(caminhoArquivo, "%s/%s", nome_diretorio, nomeArquivo);
  arquivo = fopen(caminhoArquivo, "w");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  // Gravando o texto no arquivo
  fputs(texto, arquivo);

  // Fechando o arquivo
  fclose(arquivo);
}

//adciona texto em um arquivo txt ja criado anteriormente
//o novo texto eh adcionado no final do arquivo existente
void adcionaTextoNoArquivo(char *texto, const char *nome_diretorio, DATA data) {
  FILE *arquivo;
  char nomeArquivo[MAX_TAMANHO];

  // Criando o nome do arquivo usando os valores da estrutura de data
  sprintf(nomeArquivo, "%d_%d_%d.txt", data.dia, data.mes, data.ano);

  // Abrindo o arquivo para escrita no final
  char caminhoArquivo[MAX_TAMANHO + strlen(nome_diretorio) +
                      2]; // +2 para o '/' e o caractere nulo
  sprintf(caminhoArquivo, "%s/%s", nome_diretorio, nomeArquivo);
  arquivo = fopen(caminhoArquivo, "a");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  // Gravando o texto no arquivo
  fputs(texto, arquivo);

  // Fechando o arquivo
  fclose(arquivo);
}

