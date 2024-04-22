#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"

struct Livro{
    char nome[40];
    char autor[30];
    char categoria[20];
    int paginas;
    int codigo;
    float preco;
};

struct No {
    livro dado;
    struct no* prox;
};


struct Lista{
    no* inicio;
};

struct Login{
    char usuario[20];
    int senha;
};

struct Conta{
    char email[80];
    char usuario[15];
    int senha;
};

void criarconta(){
    FILE* file2 = fopen("conta.b", "ab");
    conta a;
    printf("\nInforme um email valido:\n");
    scanf("%s", a.email);
    while (!verificaEmail(a.email)) {
        printf("\nInforme um email valido:\n");
        scanf("%s", a.email);
    }
    printf("Agora digite um nome de usuario valido: \n");
    scanf("%s", &a.usuario);
    printf("Para finalizar, crie uma senha com apenas numeros: \n");
    scanf("%d", &a.senha);
    fwrite(&a, sizeof(conta), 1, file2);
    printf("Conta criada com sucesso");
    fclose(file2);
}
int verificaEmail(char *email){
    FILE* file2 = fopen("conta.b", "ab");
    conta a;
    char *arroba = strchr(email, '@');
    if (arroba == NULL) {
        return 0;
    }
    if (strlen(email) >= 80) {
        return 0;
    }
    file2 = fopen("conta.b", "rb");
    while (fread(&a, sizeof(conta), 1, file2)) {
        if (strcmp(a.email, email) == 0) {
            fclose(file2);
            printf("Este email ja esta cadastrado no sistema.\n");
            return 0;
        }
    }
    fclose(file2);
    return 1;
}

void logar(){
    FILE* file2 = fopen("conta.b", "rb");
    conta a; 
    char usuario1[15];
    int senha1;
    int logado = 0;
    while(logado != 1){
    printf("Nome de usuario: ");
    scanf("%s", usuario1);
    printf("Senha: ");
    scanf("%d", &senha1);
        while (fread(&a, sizeof(conta), 1, file2)) {
            if (strcmp(a.usuario, usuario1) == 0 && a.senha == senha1) {
                printf("Login efetuado com sucesso!\n");
                logado = 1;
            } 
        } 
        if(logado == 0){
            printf("Nome de usuario ou senha incorreto, tente novamente! \n");
        }  
    }   
}
void cadastrar() {
    int op;
    FILE* file = fopen("livro.b", "ab");
    livro a;
    printf("Informe o nome do livro separado por '_':\n");
    scanf("%s", a.nome);
    printf("Informe o autor do livro separado por '_':\n");
    scanf("%s", a.autor);
    printf("Informe o numero de paginas:\n");
    scanf("%d", &a.paginas);
    printf("Informe o codigo de 3 digitos do livro:\n");
    scanf("%d", &a.codigo);
    printf("Informe o preço:\n");
    scanf("%f", &a.preco);
    printf("Selecione a categoria do livro: \n");
    printf("1 - Ciencias Exatas\n");
    printf("2 - Ciencias Sociais\n");
    printf("3 - Literatura\n");
    printf("4 - Autoajuda\n");
    printf("5 - Outros\n");
    scanf("%d", &op);
        if (op == 1)
        {
            strcpy(a.categoria, "Ciencias Exatas");
        }else if (op == 2){
            strcpy(a.categoria, "Ciencias Sociais");
        }else if(op == 3){
            strcpy(a.categoria, "Literatura");
        }else if(op == 4){
            strcpy(a.categoria, "Autoajuda");
        }else if(op >= 5){  
            strcpy(a.categoria, "Outros");    
        } 
    fwrite(&a, sizeof(livro), 1, file);
    fclose(file);
}
void listar() {
    FILE* file = fopen("livro.b", "rb");
    livro a;
    if(tamanho() == 0){
    	printf("\nAinda nao ha nenhum livro cadastrado.\n");
    }else{
        while (fread(&a, sizeof(livro), 1, file)) {
            printf("\n%s - %s. %d pag\nCategoria: %s\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.categoria, a.codigo, a.preco);
        }
        fclose(file);
    }
}
int tamanho() {
    FILE* file = fopen("livro.b", "rb");
    livro a;
    int cont = 0;
    while (fread(&a, sizeof(livro), 1, file)) {
        cont++;
    }
    fclose(file);
    return cont;
}
int tamanho2() {
    FILE* file3 = fopen("emprestimo.b", "rb");
    livro a;
    int cont = 0;
    while (fread(&a, sizeof(livro), 1, file3)) {
        cont++;
    }
    fclose(file3);
    return cont;
}
void editar(int codigo){
    FILE *file = fopen("livro.b", "rb+");
    livro a;
    int op;
    int encontrado = 0;
    while (fread(&a, sizeof(livro), 1, file)) {
        if (a.codigo == codigo) {
            encontrado = 1;
            printf("Livro encontrado:\n");
            printf("Informe o que deseja editar: \n");
            printf("1 - Nome\n");
            printf("2 - Autor\n");
            printf("3 - Preco\n");
            scanf("%d", &op);
            if(op == 1)
            {
                printf("Informe o novo nome: ");
                scanf("%s", a.nome);
            }else if (op == 2){
                printf("Informe o autor: ");
                scanf("%s", a.autor);
            }else if (op == 3){
                printf("Informe o novo preco: ");
                scanf("%f", &a.preco);
            }
            
            fseek(file, -sizeof(livro), SEEK_CUR);
            fwrite(&a, sizeof(livro), 1, file);
            break;
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Livro nao encontrado.\n");
    } else {
        printf("Livro editado com sucesso!\n");
    }
}
void adicionaFim(lista *lista, livro e) {
    no* novo = (no*) malloc(sizeof(no));
    novo->dado = e;
    novo->prox = NULL;
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    }
    else {
        no* pi;
        for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox);
        pi->prox = novo;
    }
}
void lerLista(lista *lista) {
  FILE *file = fopen("livro.b", "rb");
  livro e;
  while (fread(&e, sizeof(livro), 1, file)) {
      adicionaFim(lista, e);
  }
  fclose(file);
}
void salvaLista(lista *lista) {
  FILE *file = fopen("livro.b", "wb");
  no* pi;
  for (pi = lista->inicio; pi != NULL; pi = pi->prox) {
    fwrite(&pi->dado, sizeof(livro), 1, file);
  }
  fclose(file);
}

void deletar(lista *lista, int cod) {
  if (lista->inicio == NULL) {
    printf("Ainda nao ha livros cadastrados\n");
  }
  else {
      no* pa = NULL;
      no* pi;
      for (pi = lista->inicio; pi->prox != NULL && pi->dado.codigo != cod; pi = pi->prox) {
        pa = pi;
      }
      if (pa == NULL) {
        if (pi->dado.codigo == cod) {
          lista->inicio = pi->prox;
          free(pi);
        }
        else {
          printf("Livro nao encontrado\n");
        }
      }
      else {
        if (pi->dado.codigo == cod) {
          pa->prox = pi->prox;
          free(pi);
        }
        else {
          printf("Livro nao encontrado\n");
        }
      }
  }
}

void excluir(int codigo) {
    lista lista;
    lista.inicio = NULL;
    lerLista(&lista);
    deletar(&lista, codigo);
    salvaLista(&lista);
}

void buscar (int cod) {
    FILE* file = fopen("livro.b", "rb");
    livro a;
    int entrou = 0;
    while (fread(&a, sizeof(livro), 1, file)) {
        if (a.codigo == cod) {
            printf("\n%s - %s. %d pag\nCategoria: %s\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.categoria, a.codigo, a.preco);
            entrou = 1;
        }
    }
    if (entrou == 0) {
        printf("Livro nao encontrado\n");
    }
    fclose(file);
}
void catalogos(){
    FILE* file = fopen("livro.b", "rb");
    livro a;
    int enc = 0;
    int op;
    printf("\nSelecione uma opcao:\n");
    printf("1 - Ciencias Exatas\n");
    printf("2 - Ciencias Sociais\n");
    printf("3 - Literatura\n");
    printf("4 - Autoajuda\n");
    printf("5 - Outros\n");
    scanf("%d", &op);
    if (op == 1){
        while (fread(&a, sizeof(livro), 1, file)) {
            if(strcmp(a.categoria, "Ciencias Exatas") == 0){
                printf("\n%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }
    }else if (op == 2){
        while (fread(&a, sizeof(livro), 1, file)) {
            if(strcmp(a.categoria, "Ciencias Sociais") == 0){
                printf("%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }
    }else if(op == 3){
        while (fread(&a, sizeof(livro), 1, file)) {
            if(strcmp(a.categoria, "Literatura") == 0){
                printf("%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }
    }else if(op == 4){
        while (fread(&a, sizeof(livro), 1, file)) {
            if(strcmp(a.categoria, "Autoajuda") == 0){
                printf("%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }
    }else if(op >= 5){
        while (fread(&a, sizeof(livro), 1, file)) { 
            if(strcmp(a.categoria, "Outros") == 0){
                printf("%s - %s. %d pag\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.codigo, a.preco);
                enc = 1;
            }
        }   
    }
    fclose(file);
    if (!enc) {
        printf("Catalogo vazio\n");
    }
}

void mostrar(lista lista) {
    no* pi;
    for (pi = lista.inicio; pi != NULL; pi = pi->prox){
        livro dado = pi->dado;
        printf("\n%s - %s. %d pag\nCategoria: %s\nCodigo: %d \n%.2f R$\n", dado.nome, dado.autor, dado.paginas, dado.categoria, dado.codigo, dado.preco);
    }
}

void emprestimo(int cod){
    no* pi;
    lista lista;
    lista.inicio = NULL;
    lerLista(&lista);
    compara(&lista, cod);
}
void compara(lista* lista, int cod){
    no* pi;
    for (pi = lista->inicio; pi != NULL && pi->dado.codigo != cod; pi = pi->prox);
    if (pi == NULL) {
      printf("Livro nao encontrado\n");
    }
    else {
        FILE *file3 = fopen("emprestimo.b", "wb");
        no* pi;
        for (pi = lista->inicio; pi != NULL; pi = pi->prox) {
            fwrite(&pi->dado, sizeof(livro), 1, file3);
            livro dado = pi->dado;
            printf("\n%s - %s. %d pag\nCategoria: %s\nCodigo: %d \n%.2f R$\n", dado.nome, dado.autor, dado.paginas, dado.categoria, dado.codigo, dado.preco);
            printf("\nOperacao realizada com sucesso, visite a aba 'meus emprestimos' para ver seus emprestimos\n");
        }
        fclose(file3); 
    }
}

void meusEmprestimos(){
    FILE* file3 = fopen("emprestimo.b", "rb");
    livro a;
    if(tamanho2() == 0){
    	printf("\nNenhum emprestimo efetuado.\n");
    }else{
        while (fread(&a, sizeof(livro), 1, file3)) {
            printf("\n%s - %s. %d pag\nCategoria: %s\nCodigo: %d \n%.2f R$\n", a.nome, a.autor, a.paginas, a.categoria, a.codigo, a.preco);
        }
    }
    fclose(file3);
}

void ordenar() {
    lista lista;
    lista.inicio = NULL;
    lerLista(&lista);
    int aux;
    int n = tamanho();
    no* livro1 = lista.inicio;
    for (int i = 0; i < n - 1; i++) {
        aux = 0;
        no *livro2 = livro1->prox;
        for (int j = 0; j < n - i - 1; j++){
            if (livro1->dado.codigo > livro2->dado.codigo){
                livro temp = livro1->dado;
                livro1->dado = livro2->dado;
                livro2->dado = temp;
                aux = 1;
            }
            livro2 = livro2->prox;
        }

        livro1 = livro1->prox;
    }
    if (aux = 1){
        salvaLista(&lista);
        printf("\nLivros ordenados por codigo! Consulte o acervo.\n");
    }
}
