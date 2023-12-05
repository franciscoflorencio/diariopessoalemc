#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

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
  struct aux *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct {
  PONT inicio;
} LISTA;

void inicializarLista(LISTA *l) { l->inicio = NULL; }

int tamanho(LISTA *l) {
  PONT end = l->inicio;
  int tam = 0;
  while (end != NULL) {
    tam++;
    end = end->prox;
  }
  return tam;
}

void exibirLista(LISTA *l) {
  PONT end = l->inicio;
  printf("Lista: \" ");
  while (end != NULL) {
    printf("%d%d%d", end->reg.DATA.dia, end->reg.DATA.mes, end->reg.DATA.ano);
    end = end->prox;
  }
  printf("\"\n");
}

bool exclui(LISTA *l, int pos) {
  if (pos < 0 || pos > tamanho(l) - 1)
    return false;
  int i;
  ELEMENTO *p;
  ELEMENTO *apagar;
  if (pos == 0) {
    apagar = l->inicio;
    l->inicio = apagar->prox;
  } else {
    p = l->inicio;
    for (i = 0; i < pos - 1; i++)
      p = p->prox;
    apagar = p->prox;
    p->prox = apagar->prox;
  }
  free(apagar);
  return true;
}

void reinicializarLista(LISTA *l) {
  PONT end = l->inicio;
  while (end != NULL) {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  l->inicio = NULL;
}

bool buscarData(LISTA *l, int dia, int mes, int ano) {
  PONT end = l->inicio;

  while (end != NULL) {
    if (end->reg.DATA.dia == dia && end->reg.DATA.mes == mes &&
        end->reg.DATA.ano == ano) {
      return true;
    }
    end = end->prox;
  }

  return false;
}

void salvarEmArquivo(LISTA *l) {
  FILE *arquivo = fopen("index.bin", "wb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  PONT end = l->inicio;
  while (end != NULL) {
    fwrite(&(end->reg), sizeof(REGISTRO), 1, arquivo);
    end = end->prox;
  }
  fclose(arquivo);
}

bool insere(LISTA *l, REGISTRO reg, int pos) {
  if (pos < 0 || pos > tamanho(l))
    return false;
  ELEMENTO *novo = (ELEMENTO *)malloc(sizeof(ELEMENTO));
  novo->reg = reg;
  int i;
  ELEMENTO *p;
  if (pos == 0) {
    novo->prox = l->inicio;
    l->inicio = novo;
  } else {
    p = l->inicio;
    for (i = 0; i < pos - 1; i++)
      p = p->prox;
    novo->prox = p->prox;
    p->prox = novo;
  }
  return true;
}

void popularListaDeArquivo(LISTA *l) {
  FILE *arquivo = fopen("index.bin", "rb");
  if (arquivo == NULL) {
    printf("index.bin não encontrado. Criando um novo arquivo.\n");
    return;
  }

  REGISTRO data;
  int i = 0;
  while (fread(&data, sizeof(DATA), 1, arquivo) == 1) {
    insere(l, data, i);
    i++;
  }
  fclose(arquivo);
}

void editarLista(LISTA *l) {
  int dia, mes, ano;
  printf("Digite a data a ser editada (dia mês ano): ");
  scanf("%d %d %d", &dia, &mes, &ano);

  PONT end = l->inicio;
  while (end != NULL) {
    if (end->reg.DATA.dia == dia && end->reg.DATA.mes == mes &&
        end->reg.DATA.ano == ano) {
      printf("Digite a nova data (dia mês ano): ");
      scanf("%d %d %d", &end->reg.DATA.dia, &end->reg.DATA.mes,
            &end->reg.DATA.ano);
      return;
    }
    end = end->prox;
  }

  printf("Data não encontrada na lista.\n");
}

void trocarDatas(DATA *data1, DATA *data2) {
  DATA temp = *data1;
  *data1 = *data2;
  *data2 = temp;
}

int compararDatas(DATA data1, DATA data2) {
  if (data1.ano < data2.ano ||
      (data1.ano == data2.ano && data1.mes < data2.mes) ||
      (data1.ano == data2.ano && data1.mes == data2.mes &&
       data1.dia < data2.dia)) {
    return -1;
  } else if (data1.ano == data2.ano && data1.mes == data2.mes &&
             data1.dia == data2.dia) {
    return 0;
  } else {
    return 1;
  }
}

int particionar(DATA *arrayData, int baixo, int alto) {
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

void ordenarRapido(DATA *arrayData, int baixo, int alto) {
  if (baixo < alto) {
    int pivo = particionar(arrayData, baixo, alto);
    ordenarRapido(arrayData, baixo, pivo - 1);
    ordenarRapido(arrayData, pivo + 1, alto);
  }
}

void ordenarLista(LISTA *l) {
  int tamanhoLista = tamanho(l);
  if (tamanhoLista > 1) {
    // Convertendo a lista para um array para facilitar a ordenação
    DATA *arrayData = (DATA *)malloc(tamanhoLista * sizeof(DATA));
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
