#include <stdio.h>

#include <stdlib.h>

#include <ncurses.h>

#include <string.h>

int password();

void addrecord();

void viewrecord();

void editrecord();

void editpassword();

void deleterecord();

struct record

{

  char time[6];

  char name[30];

  char place[25];

  char duration[10];

  char note[500];
};

int main()

{

  int ch;

  printf("\n\n\t***********************************\n");

  printf("\t*DIARIO PESSOAL PROTEGIDO POR SENHA*\n");

  printf("\t***********************************");

  while (1)

  {

    printf("\n\n\t\tMENU PRINCIAL:");

    printf("\n\n\tADICIONAR REGISTRO\t[1]");

    printf("\n\tVER REGISTRO\t[2]");

    printf("\n\tEDITAR REGISTRO\t[3]");

    printf("\n\tAPAGAR REGISTRO\t[4]");

    printf("\n\tEDITAR SENHA\t[5]");

    printf("\n\tSAIR\t\t[6]");

    printf("\n\n\tDIGITE SUA ESCOLHA:");

    scanf("%d", &ch);

    switch (ch)

    {

    case 1:

      addrecord();

      break;

    case 2:

      viewrecord();

      break;

    case 3:

      editrecord();

      break;

    case 4:

      deleterecord();

      break;

    case 5:

      editpassword();

      break;

    case 6:

      printf("\n\n\t\tOBRIGADO POR UTILIZAR O SOFTWARE ");

      getch();

      exit(0);

    default:

      printf("\nVOCE DIGITOU ALGO ERRADO..");

      printf("\nDIGITE OUTRA TECLA PARA TENTAR NOVAMENTE");

      getch();

      break;
    }

    system("cls");
  }

  return 0;
}

void addrecord()

{

  system("cls");

  FILE *fp;

  char another = 'Y', time[10];

  struct record e;

  char filename[15];

  int choice;

  printf("\n\n\t\t***************************\n");

  printf("\t\t* BEM VINDO AO MENU DE ADICAO *");

  printf("\n\t\t***************************\n\n");

  printf("\n\n\tDIGITE A DATA DO REGISTRO:[yyyy-mm-dd]:");

  fflush(stdin);

  scanf("%s", filename);

  fp = fopen(filename, "ab+");

  if (fp == NULL)

  {

    fp = fopen(filename, "wb+");

    if (fp == NULL)

    {

      printf("\nERRO NO SISTEMA...");

      printf("\nDIGITE QUALQUER TECLA PARA SAIR");

      getch();

      return;
    }
  }

  while (another == 'Y' || another == 'y')

  {

    choice = 0;

    fflush(stdin);

    printf("\n\tDIGITE O TEMPO:[hh:mm]:");

    scanf("%s", time);

    rewind(fp);

    while (fread(&e, sizeof(e), 1, fp) == 1)

    {

      if (strcmp(e.time, time) == 0)

      {

        printf("\n\tESSE REGISTRO JA EXISTE.\n");

        choice = 1;
      }
    }

    if (choice == 0)

    {

      strcpy(e.time, time);

      printf("\tDIGITE SEU NOME:");

      fflush(stdin);

      scanf("%s", e.name);

      fflush(stdin);

      printf("\tDIGITE SUA LOCALIZACAO:");

      scanf("%s", e.place);

      fflush(stdin);

      printf("\tDIGITE A DURACAO:");

      scanf("%s", e.duration);

      fflush(stdin);

      printf("\tNOTA:");

      scanf("%s", e.note);

      fwrite(&e, sizeof(e), 1, fp);

      printf("\nSEU REGISTRO ESTA SENDO ADICIONADO...\n");
    }

    printf("\n\tADICIONAR OUTRO REGISTRO...(Y/N) ");

    fflush(stdin);

    another = getchar();
  }

  fclose(fp);

  printf("\n\n\tDIGITE QUALQUER TECLA PARA SAIR...");

  getch();
}

void viewrecord()

{

  FILE *fpte;

  system("cls");

  struct record customer;

  char time[6], choice, filename[14];

  int ch;

  printf("\n\n\t\t*******************************\n");

  printf("\t\t* AQUI É O MENU DE VISUALIZACAO *");

  printf("\n\t\t*******************************\n\n");

  choice = password();

  if (choice != 0)

  {

    return;
  }

  do

  {

    printf("\n\tDIGITE A DATA DO REGISTRO A SER VISUALIZADO:[yyyy-mm-dd]:");

    fflush(stdin);

    scanf("%s", filename);

    fpte = fopen(filename, "rb");

    if (fpte == NULL)

    {

      puts("\nO REGISTRO NAO EXISTE...\n");

      printf("DIGITE QUALQUER TECLA PARA SAIR...");

      getch();

      return;
    }

    system("cls");

    printf("\n\tCOMO VOCE GOSTARIA DE VISUALIZAR:\n");

    printf("\n\t1.O REGISTRO INTEIRO DO DIA.");

    printf("\n\t2.REGISTRO DE UM TEMPO FIXO.");

    printf("\n\t\tDIGITE SUA ESCOLHA:");

    scanf("%d", &ch);

    switch (ch)

    {

    case 1:

      printf("\nO REGISTRO TODO PARA %s EH:", filename);

      while (fread(&customer, sizeof(customer), 1, fpte) == 1)

      {

        printf("\n");

        printf("\nTEMPO: %s", customer.time);

        printf("\nSE ENCONTRANDO COM: %s", customer.name);

        printf("\nSE ENCONTRAR EM: %s", customer.place);

        printf("\nDURACAO: %s", customer.duration);

        printf("\nNOTA: %s", customer.note);

        printf("\n");
      }

      break;

    case 2:

      fflush(stdin);

      printf("\nDIGITE O TEMPO:[hh:mm]:");

      fgets(time, 6, stdin);

      while (fread(&customer, sizeof(customer), 1, fpte) == 1)

      {

        if (strcmp(customer.time, time) == 0)

        {

          printf("\nSEU REGISTRO EH:");

          printf("\nTEMPO: %s", customer.time);

          printf("\nSE ENCONTRO COM: %s", customer.name);

          printf("\nSE ENCONTRANDO EM: %s", customer.place);

          printf("\nDURACAO: %s", customer.duration);

          printf("\nNOTA: %s", customer.note);
        }
      }

      break;

    default:
      printf("\nVOCE DIGITOU ALGUMA OUTRA COISA...\n");

      break;
    }

    printf("\n\nVOCE GOSTARIA DE PROSSEGUIR A VISUALIZACAO...(Y/N):");

    fflush(stdin);

    scanf("%c", &choice);

  } while (choice == 'Y' || choice == 'y');

  fclose(fpte);

  return;
}

void editrecord()

{

  system("cls");

  FILE *fpte;

  struct record customer;

  char time[6], choice, filename[14];

  int num, count = 0;

  printf("\n\n\t\t*******************************\n");

  printf("\t\t* BEM VINDO AO MENU DE EDICAO *");

  printf("\n\t\t*******************************\n\n");

  choice = password();

  if (choice != 0)

  {

    return;
  }

  do

  {

    printf("\n\tDIGITE A DATA DO REGISTRO A SER EDITADO:[yyyy-mm-dd]:");

    fflush(stdin);

    scanf("%s", filename);

    printf("\n\tDIGITE O TEMPO:[hh:mm]:");

    fgets(time, 6, stdin);

    fpte = fopen(filename, "rb+");

    if (fpte == NULL)

    {

      printf("\nREGISTRO NAO EXISTE:");

      printf("\nDIGITE QUALQUER TECLA PARA VOLTAR");

      getch();

      return;
    }

    while (fread(&customer, sizeof(customer), 1, fpte) == 1)

    {

      if (strcmp(customer.time, time) == 0)

      {

        printf("\nSEU REGISTRO ANTIGO ERA");

        printf("\nTEMPO: %s", customer.time);

        printf("\nSE ENCONTRANDO COM: %s", customer.name);

        printf("\nSE ENCONTRANDO EM: %s", customer.place);

        printf("\nDURACAO: %s", customer.duration);

        printf("\nNOTA: %s", customer.note);

        printf("\n\n\t\tO QUE VOCE GOSTARIA DE EDITAR..");

        printf("\n1.TEMPO.");

        printf("\n2.PESSOA A SE ENCONTRAR.");

        printf("\n3.LUGAR DE ENCONTRO.");

        printf("\n4.DURACAO.");

        printf("\n5.NOTA.");

        printf("\n6.REGISTRO INTEIRO.");

        printf("\n7.VOLTAR PARA O MENU PRICIPAL.");

        do

        {

          printf("\n\tDIGITE SUA ESCOLHA:");

          fflush(stdin);

          scanf("%d", &num);

          fflush(stdin);

          switch (num)

          {

          case 1:
            printf("\nDIGITE UMA DATA NOVA:");

            printf("\nNOVO TEMPO:[hh:mm]:");

            scanf("%s", customer.time);

            break;

          case 2:
            printf("\nDIGITE UMA DATA NOVA:");

            printf("\nNOVA PESSOA SE ENCONTRAR:");

            scanf("%s", customer.name);

            break;

          case 3:
            printf("\nDIGITE UMA DATA NOVA:");

            printf("\nNOVO LUGAR DE ENCONTRO:");

            scanf("%s", customer.place);

            break;

          case 4:
            printf("\nDIGITE UMA NOVA DATA:");

            printf("\nDURACAO:");

            scanf("%s", customer.duration);

            break;

          case 5:
            printf("DIGITE A NOVA DATA:");

            printf("\nNOTA:");

            scanf("%s", customer.note);

            break;

          case 6:
            printf("\nDIGITE A NOVA DATA:");

            printf("\nNOVO TEMPO:[hh:mm]:");

            scanf("%s", customer.time);

            printf("\nNOVA PESSOA A SE ENCONTRAR:");

            scanf("%s", customer.name);

            printf("\nNOVO LUGAR DE ENCONTRO:");

            scanf("%s", customer.place);

            printf("\nDURACAO:");

            scanf("%s", customer.duration);

            printf("\nNOTA:");

            scanf("%s", customer.note);

            break;

          case 7:
            printf("\nDIGITE QUALQUER TECLA PARA VOLTAR...\n");

            getch();

            return;

            break;

          default:
            printf("\nVOCE DIGITOU ALGUMA OUTRA COISA...TENTE NOVAMENTE\n");

            break;
          }

        } while (num < 1 || num > 8);

        fseek(fpte, -sizeof(customer), SEEK_CUR);

        fwrite(&customer, sizeof(customer), 1, fpte);

        fseek(fpte, -sizeof(customer), SEEK_CUR);

        fread(&customer, sizeof(customer), 1, fpte);

        choice = 5;

        break;
      }
    }

    if (choice == 5)

    {

      system("cls");

      printf("\n\t\tEDICAO COMPLETA...\n");

      printf("--------------------\n");

      printf("O NOVO REGISTRO EH:\n");

      printf("--------------------\n");

      printf("\nTEMPO: %s", customer.time);

      printf("\nSE ENCONTRANDO COM: %s", customer.name);

      printf("\nSE ENCONTRANDO EM: %s", customer.place);

      printf("\nDURACAO: %s", customer.duration);

      printf("\nNOTA: %s", customer.note);

      fclose(fpte);

      printf("\n\n\tVOCE GOSTARIA DE EDITAR UM NOVO REGISTRO?(Y/N)");

      scanf("%c", &choice);

      count++;

    }

    else

    {

      printf("\nO REGISTRO NAO EXISTE::\n");

      printf("\nVOCE GOSTARIA DE TENTAR NOVAMENTE...(Y/N)");

      scanf("%c", &choice);
    }

  } while (choice == 'Y' || choice == 'y');

  fclose(fpte);

  if (count == 1)

    printf("\n%d O ARQUIVO FOI EDITADO...\n", count);

  else if (count == 2)

    printf("\n%d OS ARQUIVOS ESTAO EDITADOS..\n", count);
  else

    printf("\nNENHUM ARQUIVO EDITADO...\n");

  printf("\tDIGITE ENTER PARA SAIR DO MENU DE EDICAO.");

  getch();
}

int password()

{

  char pass[15] = {0}, check[15] = {0}, ch;

  FILE *fpp;

  int i = 0, j;

  printf("::POR RAZOES DE SEGURANCA::");

  printf("::APENAS TRES PROCESSOS SAO PERMITIDOS::");

  for (j = 0; j < 3; j++)

  {

    i = 0;

    printf("\n\n\tDIGITE A SENHA:");

    pass[0] = getch();

    while (pass[i] != '\r')

    {

      if (pass[i] == '\b')

      {

        i--;

        printf("\b");

        printf(" ");

        printf("\b");

        pass[i] = getch();

      }

      else

      {

        printf("*");

        i++;

        pass[i] = getch();
      }
    }

    pass[i] = '\0';

    fpp = fopen("SE", "r");

    if (fpp == NULL)

    {

      printf("\nERRO COM O SISTEMA DE ARQUIVOS...[ARQUIVO FALTANDO]\n");

      getch();

      return 1;

    }

    else

      i = 0;

    while (1)

    {

      ch = fgetc(fpp);

      if (ch == EOF)

      {

        check[i] = '\0';

        break;
      }

      check[i] = ch - 5;

      i++;
    }

    if (strcmp(pass, check) == 0)

    {

      printf("\n\n\tACESSO GARANTIDO...\n");

      return 0;

    }

    else

    {

      printf("\n\n\tSENHA INCORRETA..\n\n\tACESSO NEGADO...\n");
    }
  }

  printf("\n\n\t::VOCE DIGITOU A SENHA INCORRETA::VOCE NAO ESTA LIBERADO A "
         "ACESSAR "
         "QUALQUER ARQUIVO::\n\n\tDIGITE QUALQUER TECLA PARA VOLTAR...");

  getch();

  return 1;
}

void editpassword()

{

  system("cls");

  printf("\n");

  char pass[15] = {0}, confirm[15] = {0}, ch;

  int choice, i, check;

  FILE *fp;

  fp = fopen("SE", "rb");

  if (fp == NULL)

  {

    fp = fopen("SE", "wb");

    if (fp == NULL)

    {

      printf("ERRO DE SISTEMA...");

      getch();

      return;
    }

    fclose(fp);

    printf("\nSISTEMA RESTAURADO...\nSUA SENHA EH 'ENTER'\n DIGITE ENTER PARA "
           "MUDAR SENHA\n\n");

    getch();
  }

  fclose(fp);

  check = password();

  if (check == 1)

  {

    return;
  }

  do

  {

    if (check == 0)

    {

      i = 0;

      choice = 0;

      printf("\n\n\tDIGITE A NOVA SENHA:");

      fflush(stdin);

      pass[0] = getch();

      while (pass[i] != '\r')

      {

        if (pass[i] == '\b')

        {

          i--;

          printf("\b");

          printf(" ");

          printf("\b");

          pass[i] = getch();

        }

        else

        {

          printf("*");

          i++;

          pass[i] = getch();
        }
      }

      pass[i] = '\0';

      i = 0;

      printf("\n\tCONFIRMAR SENHA:");

      confirm[0] = getch();

      while (confirm[i] != '\r')

      {

        if (confirm[i] == '\b')

        {

          i--;

          printf("\b");

          printf(" ");

          printf("\b");

          confirm[i] = getch();

        }

        else

        {

          printf("*");

          i++;

          confirm[i] = getch();
        }
      }

      confirm[i] = '\0';

      if (strcmp(pass, confirm) == 0)

      {

        fp = fopen("SE", "wb");

        if (fp == NULL)

        {

          printf("\n\t\tERRO DE SISTEMA");

          getch();

          return;
        }

        i = 0;

        while (pass[i] != '\0')

        {

          ch = pass[i];

          putc(ch + 5, fp);

          i++;
        }

        putc(EOF, fp);

        fclose(fp);

      }

      else

      {

        printf("\n\tA NOVA SENHA NAO EH COMPATIVEL.");

        choice = 1;
      }
    }

  } while (choice == 1);

  printf("\n\n\tSENHA ALTERADA...\n\n\tDIGITE QUALQUER TECLA PARA VOLTAR...");

  getch();
}

void deleterecord()

{

  system("cls");

  FILE *fp, *fptr;

  struct record file;

  char filename[15], another = 'Y', time[10];
  ;

  int choice, check;

  printf("\n\n\t\t*************************\n");

  printf("\t\t* BEM VINDO AO MENU DE DELECAO *");

  printf("\n\t\t*************************\n\n");

  check = password();

  if (check == 1)

  {

    return;
  }

  while (another == 'Y')

  {

    printf("\n\n\tO QUE VOCE GOSTARIA DE DELETAR.");

    printf("\n\n\t#DELETAR TODO O REGISTRO\t\t\t[1]");

    printf("\n\t#DELETAR UM REGISTRO PARTICULAR PELO TEMPO\t[2]");

    do

    {

      printf("\n\t\tDIGITE SUA OPCAO:");

      scanf("%d", &choice);

      switch (choice)

      {

      case 1:

        printf("\n\tDIGITE A DATA DO REGISTRO A SER DELETADA:[yyyy-mm-dd]:");

        fflush(stdin);

        scanf("%s", filename);

        fp = fopen(filename, "wb");

        if (fp == NULL)

        {

          printf("\nO ARQUIVO NAO EXISTE");

          printf("\nDIGITE QUALQUER TECLA PARA VOLTAR.");

          getch();

          return;
        }

        fclose(fp);

        remove(filename);

        printf("\nDELETADO COM SUCESSO...");

        break;

      case 2:

        printf("\n\tDIGITE A DATA DO REGISTRO:[yyyy-mm-dd]:");

        fflush(stdin);

        scanf("%s", filename);

        fp = fopen(filename, "rb");

        if (fp == NULL)

        {

          printf("\nO ARQUIVO NAO EXISTE");

          printf("\nDIGITE QUALQUER TECLA PARA VOLTAR.");

          getch();

          return;
        }

        fptr = fopen("temp", "wb");

        if (fptr == NULL)

        {

          printf("\nERRO DE SISTEMA");

          printf("\nDIGITE QUALQUER TECLA PARA VOLTAR");

          getch();

          return;
        }

        printf("\n\tDIGITE O TEMPO DO REGISTRO A SER DELETADO:[hh:mm]:");

        fflush(stdin);

        scanf("%s", time);

        while (fread(&file, sizeof(file), 1, fp) == 1)

        {

          if (strcmp(file.time, time) != 0)

            fwrite(&file, sizeof(file), 1, fptr);
        }

        fclose(fp);

        fclose(fptr);

        remove(filename);

        rename("temp", filename);

        printf("\nDELETADO COM SUCESSO...");

        break;

      default:

        printf("\n\tVOCE FEZ ALGUMA ESCOLHA ERRADA");

        break;
      }

    } while (choice < 1 || choice > 2);

    printf("\n\tVOCE GOSTARIA DE DELETAR ALGUM OUTRO REGISTRO.(Y/N):");

    fflush(stdin);

    scanf("%c", &another);
  }

  printf("\n\n\tDIGITE QUALQUER SENHA PARA SAIR...");

  getch();
}
