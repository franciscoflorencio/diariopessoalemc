/*
Biblioteca que contém todas as funções necessárias para a implementação de senha no programa principal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAX_SENHA 50 //Define um tamanho máximo de senha.

void salvarSenha(char *senha) { //Função para salvar senha.
  FILE *arquivo = fopen("senha.bin", "wb+"); //Cria (ou abre, caso não exista) um arquivo binário, no modo de escrita e leitura, para gravar a senha.
  if (arquivo != NULL) { //Verifica se o arquivo foi aberto com sucesso.
    fwrite(senha, sizeof(char), strlen(senha) + 1, arquivo); //Grava a senha no arquivo.
    fclose(arquivo); //Fecha o arquivo.
    printf("\nSenha salva com sucesso!\n"); //Mensagem de sucesso ao salvar a senha.
  } else { //Caso o arquivo não seja aberto com sucesso.
    printf("\nErro ao salvar a senha.\n"); //Mensagem de erro.
  }
}

void lerSenha(char *senha) { //Função para ler a senha.
  FILE *arquivo = fopen("senha.bin", "rb+"); //Abre o arquivo binário de senha no modo de leitura.
  if (arquivo != NULL) { //Se o arquivo não estiver vazio.
    fread(senha, sizeof(char), TAMANHO_MAX_SENHA, arquivo); //Lê a senha no arquivo.
    fclose(arquivo); //Fecha o arquivo.
  }
}

void atualizarSenha() { //Função para atualizar senha.
  char senhaCorreta[TAMANHO_MAX_SENHA]; //Variável para armazenar a senha correta (atual).
  char senhaAntiga[TAMANHO_MAX_SENHA]; //Variável para armazenar a senha "antiga" (atual até o momento).
  char novaSenha[TAMANHO_MAX_SENHA]; //Variável para armazenar a nova senha pretendida pelo usuário.

  lerSenha(senhaCorreta); // Lê a senha atual do arquivo.

  printf("\nDigite a senha antiga: "); // Solicita a senha antiga ao usuário.
  scanf("%s", senhaAntiga); //Atribui à variável.

  if (strcmp(senhaAntiga, senhaCorreta) == 0) { // Verifica se a senha "antiga" está correta.
    printf("\nDigite a nova senha: "); // Solicita a nova senha ao usuário.
    scanf("%s", novaSenha); //Atribui à variável.

    salvarSenha(novaSenha); // Salva a nova senha no arquivo.

    printf("\nSenha atualizada com sucesso!\n"); //Mensagem de sucesso ao salvar senha.
  } else { //Caso a senha atual inserida pelo usuário esteja incorreta.
    printf("\nSenha antiga incorreta. Acesso negado.\n"); //Mensagem de acesso negado.
  }
}