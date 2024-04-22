
#include <stdio.h>
#include "Biblioteca.h"

void menuinicial(){
    printf("\nBem vindo a nossa biblioteca!\n");
    printf("=============================\n");
    printf("Porfavor, escolha uma opção: \n");
    printf("1 - Fazer login\n");
    printf("2 - Criar conta\n");
    printf("0 - Sair\n");
}
void menu(){
    printf("\nMenu Principal:\n");
    printf("1 - Cadastar um novo livro\n");
    printf("2 - Consultar acervo\n");
    printf("3 - Editar livro\n");
    printf("4 - Excluir um livro do acervo\n");
    printf("5 - Ordenar por codigo\n");
    printf("6 - Buscar livro\n");
    printf("7 - Catalogos de interesse\n");
    printf("8 - Emprestimo de livros\n");
    printf("9 - Meus emprestimos\n");
    printf("0 - Sair\n");
    printf("================================\n");
}
int main(){
    int op;
    menuinicial();
    scanf("%d", &op);
    while (op != 0) {
        if (op == 1) {
            logar();
            break;
        } else if (op == 2) {
            criarconta();
            menuinicial();
            scanf("%d", &op);
        }
    }
    menu();
    scanf("%d", &op);           
    while (op != 0){
        if (op == 1) {
            cadastrar();
        } else if (op == 2) {
            listar();
        } else if (op == 3) {
            int codigo;
            printf("Informe o codigo do livro que deseja editar: ");
            scanf("%d", &codigo);
            editar(codigo);
        } else if (op == 4) {
            int codigo;
            printf("Informe o codigo do livro que deseja excluir: ");
            scanf("%d", &codigo);
            excluir(codigo);
        }else if(op == 5){
            ordenar();
        }else if (op == 6) {
            int codigo;
            printf("Informe o codigo do livro que deseja buscar: ");
            scanf("%d", &codigo);
            buscar(codigo);
        }else if (op == 7) {
            catalogos();
        }else if (op == 8) {
            int codigo;
            printf("Informe o codigo do livro que deseja pedir emprestimo: ");
            scanf("%d", &codigo);
            emprestimo(codigo);
        }else if (op == 9) {
            meusEmprestimos();
        }
        menu();
        scanf("%d", &op);
    }
    return 0;
}