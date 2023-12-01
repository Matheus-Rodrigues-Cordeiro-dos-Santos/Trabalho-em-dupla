// Integrantes: Matheus Rodrigues Cordeiro dos Santos/Danilo Miguel da Silva.
#include <locale.h>
#include <stdio.h>
#include <string.h>
// Deu certo no DevC++.
typedef struct {
  char nome[20];
  char tel[20];
  char filme[20];
  char status;
} reg;

int tamanho(FILE *);
void cadastrar(FILE *);
void consultar(FILE *);
void excluir(FILE *);

int main() {
  int op;
  FILE *arq;

  if ((arq = fopen("dados1.dat", "rb+")) == NULL) {
    if ((arq = fopen("dados1.dat", "wb+")) == NULL) {
      printf("Falha ao abrir o arquivo!\n");
      system("pause");
    }
  }

  do {
    system("CLS");
    printf("\n======= LOCADORA IPANEMA ======= \n");
    printf("1.Alugar Filme\n");
    printf("2.Consultar Filmes Alugados\n");
    printf("3.Excluir cadastro\n");
    printf("4.Sair\n");
    printf("===========Contatos:%d=\n", tamanho(arq));
    printf("Opcao:");
    scanf("%d", &op);
    switch (op) {
    case 1: // cadastrar novo filme
      cadastrar(arq);
      break;
    case 2: // consultar filme
      consultar(arq);
      break;

      break;
    case 3: // exclui um cadastro de filme
      excluir(arq);
      break;

    case 4:
      fclose(arq);
    }
  } while (op != 4);
}

void cadastrar(FILE *arq) {
  reg contato;
  char confirma;
  contato.status = ' ';
  fflush(stdin);

  printf("Cadastrando novo cliente:\n");
  printf("\nNumero do cliente:%d\n", tamanho(arq) + 1);
  printf("Nome..........:"); // getchar();
  gets(contato.nome);
  getchar();
  printf("Telefone......:");
  gets(contato.tel);
  getchar();
  printf("Filme........:");
  gets(contato.filme);
  getchar();
  printf("Confirma <s/n>:");
  fflush(stdin);
  scanf("%c", &confirma);
  getchar();

  if (toupper(confirma) == 'S') {
    printf("\ngravando...\n\n");
    fseek(arq, 0, SEEK_END);
    fwrite(&contato, sizeof(reg), 1, arq);
  }
  system("pause");
}

void consultar(FILE *arq) {
  reg contato;
  int nr;
  printf("\nConsulta pelo codigo\n");
  printf("\nInforme o Codigo...:");
  scanf("%d", &nr);
  if ((nr <= tamanho(arq)) && (nr > 0)) {
    fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
    fread(&contato, sizeof(reg), 1, arq);
    if (contato.status == ' ') {
      printf("\nNome......:%s", contato.nome);
      printf("\nTelefone..:%s", contato.tel);
      printf("\nFilme....:%s\n\n", contato.filme);
    }

    else
      printf("\nCadastro excluido! \n");

  } else {
    printf("\nNumero de cadastro invalido!\n");
  }
  system("pause");
}

void excluir(FILE *arq) {
  reg contato;
  char confirma;
  int nr;

  printf("\nInforme o codigo de cadastro para excluir\n");
  scanf("%d", &nr);
  if ((nr <= tamanho(arq)) && (nr > 0)) {
    fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
    fread(&contato, sizeof(reg), 1, arq);
    if (contato.status == ' ') {
      printf("\nNome......:%s", contato.nome);
      printf("\nTelefone..:%s", contato.tel);
      printf("\nFilme....:%s\n", contato.filme);
      printf("\nConfirma a exclusao: <s/n>");
      getchar();
      scanf("%c", &confirma);

      if (toupper(confirma) == 'S') {
        printf("\nexcluindo...\n\n");
        fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
        contato.status = '*';
        fwrite(&contato, sizeof(reg), 1, arq);
      }
    } else
      printf("Cadastro inexistente! \n");
  } else {
    printf("\nNumero de cadastro invalido!\n");
  }
  system("pause");
}

int tamanho(FILE *arq) {
  fseek(arq, 0, SEEK_END);
  return ftell(arq) / sizeof(reg);
}