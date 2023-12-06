#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

//****** Estruturas de dados **********

typedef int bool;

typedef struct {
    int dia;
    int mes;
    int ano;
} DATA;

typedef struct {
    DATA DATA;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
    PONT fim;
} LISTA;

// ****** implementação das funcoes de Lista

void inicializarLista(LISTA* l) {
    l->inicio = NULL;
    l->fim = NULL;
}

int tamanho(LISTA* l) {
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL) {
        tam++;
        end = end->prox;
    }
    return tam; 
}

void limparLista(LISTA* lista) {
    PONT atual = lista->inicio;
    while (atual != NULL) {
        PONT temp = atual;
        atual = atual->prox;
        free(temp); // Libera a memória do nó atual
    }
    lista->inicio = NULL; // Atualiza o ponteiro da lista para indicar que está vazia
    lista->fim = NULL; // Se houver um ponteiro de fim, também o atualiza para indicar uma lista vazia
}

void exibirLista(LISTA* l) {
    PONT atual = l->inicio;
    printf("\nLista de datas:\n");
    int numero = 1;
    while (atual != NULL) {
        printf("(%d) %i / %i / %i \n", numero, atual->reg.DATA.dia, atual->reg.DATA.mes, atual->reg.DATA.ano);
        atual = atual->prox; 
        numero++;
    }
    printf("\n"); 
}

//remove um elemento especificado por DATA da lista 
void removerElemento(LISTA *lista, DATA data) {
  PONT atual = lista->inicio;
  PONT anterior = NULL;

  while (atual != NULL) {
    if (atual->reg.DATA.dia == data.dia &&
        atual->reg.DATA.mes == data.mes &&
        atual->reg.DATA.ano == data.ano) {

      if (anterior == NULL) {
        lista->inicio =
            atual->prox; // O elemento a ser removido é o primeiro da lista
      } else {
        anterior->prox = atual->prox; // Elemento a ser removido está no meio ou
                                      // no final da lista
      }

      free(atual); // Libera memória do nó removido
      return;
    }

    anterior = atual;
    atual = atual->prox;
  }

  printf("\nElemento não encontrado na lista.\n");
}

void reinicializarLista(LISTA* l) {
    PONT end = l->inicio;
    while (end != NULL) {
        PONT apagar = end;
        end = end->prox;
        free(apagar); 
    }
    l->inicio = NULL;
}

bool buscarData(LISTA* l, int dia, int mes, int ano) {
    PONT end = l->inicio;

    while (end != NULL) {
        if (end->reg.DATA.dia == dia && end->reg.DATA.mes == mes && end->reg.DATA.ano == ano) {
            return true;
        }
        end = end->prox;
    }

    return false;
}

bool inserirElemento(LISTA* l, DATA data) {
    PONT novoElemento = (PONT)malloc(sizeof(ELEMENTO));
    if (novoElemento == NULL) {
        printf("Erro ao alocar memória para o novo elemento.\n");
        return false;
    }

    novoElemento->reg.DATA = data;
    novoElemento->prox = l->inicio;
    l->inicio = novoElemento;

    return true;
}

void salvarEmArquivo(LISTA* l) {
    FILE* arquivo = fopen("index.bin", "wb"); // Abrir o arquivo binário para escrita em modo binário

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    PONT atual = l->inicio;

    while (atual != NULL) {
        // Escrever o conteúdo do nó no arquivo
        fwrite(&(atual->reg), sizeof(REGISTRO), 1, arquivo);
        atual = atual->prox;
    }

    fclose(arquivo); // Fechar o arquivo após a escrita
}

int compararDatas(DATA data1, DATA data2) {
    if (data1.ano < data2.ano || (data1.ano == data2.ano && data1.mes < data2.mes) || (data1.ano == data2.ano && data1.mes == data2.mes && data1.dia < data2.dia)) {
        return -1;
    } else if (data1.ano == data2.ano && data1.mes == data2.mes && data1.dia == data2.dia) {
        return 0;
    } else {
        return 1;
    }
}

void trocarDatas(DATA* data1, DATA* data2) {
    DATA temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

int particionar(DATA* arrayData, int baixo, int alto) {
    DATA pivo = arrayData[alto];
    int i = baixo - 1;

    for (int j = baixo; j <= alto - 1; j++) {
        if (compararDatas(arrayData[j], pivo) < 0) {
            i++;
            trocarDatas(&arrayData[i], &arrayData[j]);
        }
    }
    trocarDatas(&arrayData[i + 1], &arrayData[alto]);
    return i + 1;
}

void popularListaDeArquivo(LISTA* l) {
    FILE* arquivo = fopen("index.bin", "rb");
    if (arquivo == NULL) {
        printf("index.bin não encontrado. Criando um novo arquivo.\n");
        return;
    }

    REGISTRO reg;
    while (fread(&reg, sizeof(REGISTRO), 1, arquivo) == 1) {
        inserirElemento(l, reg.DATA);
    }
    fclose(arquivo);
}

void editarLista(LISTA* l) {
    int dia, mes, ano;
    printf("Digite a data a ser editada (dia mês ano): ");
    scanf("%d %d %d", &dia, &mes, &ano);

    PONT end = l->inicio;
    while (end != NULL) {
        if (end->reg.DATA.dia == dia && end->reg.DATA.mes == mes && end->reg.DATA.ano == ano) {
            printf("Digite a nova data (dia mês ano): ");
            scanf("%d %d %d", &end->reg.DATA.dia, &end->reg.DATA.mes, &end->reg.DATA.ano);
            return;
        }
        end = end->prox;
    }

    printf("Data não encontrada na lista.\n");
}

void ordenarRapido(DATA* arrayData, int baixo, int alto) {
    if (baixo < alto) {
        int pivo = particionar(arrayData, baixo, alto);
        ordenarRapido(arrayData, baixo, pivo - 1);
        ordenarRapido(arrayData, pivo + 1, alto);
    }
}

void ordenarLista(LISTA* l) {
    int tamanhoLista = tamanho(l);
    if (tamanhoLista > 1) {
        // Convertendo a lista para um array para facilitar a ordenação
        DATA* arrayData = (DATA*)malloc(tamanhoLista * sizeof(DATA));
        PONT end = l->inicio;
        for (int i = 0; i < tamanhoLista; i++) {
            arrayData[i] = end->reg.DATA;
            end = end->prox;
        }

        // Ordenando o array
        ordenarRapido(arrayData, 0, tamanhoLista - 1);

        // Atualizando a lista com o array ordenado
        end = l->inicio;
        for (int i = 0; i < tamanhoLista; i++) {
            end->reg.DATA = arrayData[i];
            end = end->prox;
        }

        free(arrayData);
    }
}
