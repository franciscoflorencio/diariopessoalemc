#include "listaligada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define MAX_ENTRY_LENGTH 1000
#define TAMANHO_MAX_SENHA 50

// aqui começa os comandos do menu inicial

typedef struct {
  char date[20];
  char entry[MAX_ENTRY_LENGTH];
} DiaryEntry;

DiaryEntry entries[MAX_ENTRIES];
int numEntries = 0;

void addEntry() {
  if (numEntries >= MAX_ENTRIES) {
    printf("O diário está cheio. Não é possível adicionar mais entradas.\n");
    return;
  }

  DiaryEntry newEntry;
  printf("Digite a data (DD/MM/AAAA): ");
  scanf("%s", newEntry.date);
  printf("Digite a entrada: ");
  getchar(); // Limpar o buffer do teclado
  fgets(newEntry.entry, MAX_ENTRY_LENGTH, stdin);

  entries[numEntries++] = newEntry;
  printf("Entrada adicionada com sucesso!\n");
}

void editEntry() {
  int entryNumber;
  printf("Digite o número da entrada que deseja editar: ");
  scanf("%d", &entryNumber);

  if (entryNumber < 1 || entryNumber > numEntries) {
    printf("Número de entrada inválido.\n");
    return;
  }

  DiaryEntry *entry = &entries[entryNumber - 1];
  printf("Digite a nova entrada: ");
  getchar(); // Limpar o buffer do teclado
  fgets(entry->entry, MAX_ENTRY_LENGTH, stdin);

  printf("Entrada editada com sucesso!\n");
}

void viewEntriesByDate() {
  char date[20];
  printf("Digite a data (DD/MM/AAAA) para visualizar as entradas: ");
  scanf("%s", date);

  printf("Entradas para a data %s:\n", date);
  for (int i = 0; i < numEntries; i++) {
    if (strcmp(entries[i].date, date) == 0) {
      printf("Entrada %d:\n", i + 1);
      printf("%s\n", entries[i].entry);
    }
  }
}

void viewEntriesByNumber() {
  int entryNumber;
  printf("Digite o número da entrada que deseja visualizar: ");
  scanf("%d", &entryNumber);

  if (entryNumber < 1 || entryNumber > numEntries) {
    printf("Número de entrada inválido.\n");
    return;
  }

  DiaryEntry *entry = &entries[entryNumber - 1];
  printf("Entrada %d (%s):\n", entryNumber, entry->date);
  printf("%s\n", entry->entry);
}

// aqui termina o comando inicial
//
//
// aqui começa a implementacao da senha

void salvarSenha(const char *senha) {
  FILE *arquivo = fopen("senha.bin", "rb+");
  if (arquivo != NULL) {
    fwrite(senha, sizeof(char), strlen(senha) + 1, arquivo);
    fclose(arquivo);
    printf("Senha salva com sucesso!\n");
  } else {
    printf("Erro ao salvar a senha.\n");
  }
}

void lerSenha(char *senha) {
  FILE *arquivo = fopen("senha.bin", "rb+");
  if (arquivo != NULL) {
    fread(senha, sizeof(char), TAMANHO_MAX_SENHA, arquivo);
    fclose(arquivo);
  }
}

void atualizarSenha() {
  char senhaCorreta[TAMANHO_MAX_SENHA];
  char senhaAntiga[TAMANHO_MAX_SENHA];
  char novaSenha[TAMANHO_MAX_SENHA];

  // Lê a senha atual do arquivo
  lerSenha(senhaCorreta);

  // Solicita a senha antiga ao usuário
  printf("Digite a senha antiga: ");
  scanf("%s", senhaAntiga);

  // Verificar se a senha antiga está correta
  if (strcmp(senhaAntiga, senhaCorreta) == 0) {
    // Solicita a nova senha ao usuário
    printf("Digite a nova senha: ");
    scanf("%s", novaSenha);

    // Salva a nova senha no arquivo
    salvarSenha(novaSenha);

    printf("Senha atualizada com sucesso!\n");
  } else {
    printf("Senha antiga incorreta. Acesso negado.\n");
  }
}
// aqui termina a implementacao de senha

int main() {
  FILE *pa;
  int choice;
  char *senha = (char *)malloc(50 * sizeof(char));

  printf("Digite sua senha: ");
  scanf("%s", senha);

  salvarSenha(senha);

  while (1) {
    printf("\nMenu:\n");
    printf("1. Adicionar entrada\n");
    printf("2. Editar entrada\n");
    printf("3. Visualizar entradas por data\n");
    printf("4. Visualizar entrada por número\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      addEntry();
      break;
    case 2:
      editEntry();
      break;
    case 3:
      viewEntriesByDate();
      break;
    case 4:
      viewEntriesByNumber();
      break;
    case 5:
      printf("Encerrando o programa...\n");
      exit(0);
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  }

  return 0;
}
