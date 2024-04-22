#ifndef H_BIBLIOTECA
#define H_BIBLIOTECA

typedef struct Livro livro;
typedef struct Login login;
typedef struct Conta conta;

typedef struct No no;
typedef struct Lista lista;


void menuinicial();

void criarconta();

int verificaEmail(char *email);

void logar();

void cadastrar();

void listar();

int tamanho();

int tamanho2();

void editar(int codigo);

void adicionaFim(lista *lista, livro e);

void lerLista(lista *lista);

void salvaLista(lista *lista);

void deletar(lista *lista, int cod);

void excluir(int codigo);

void buscar (int cod);

void catalogos();

void mostrar(lista lista);

void compara(lista* lista, int cod);

void emprestimo(int cod);

void meusEmprestimos();

void ordenar();
#endif