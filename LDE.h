typedef struct desc_LDE Descritor;
typedef struct nodo Item;
typedef struct musica Music;

struct desc_LDE
{
	Item *inicio;
	Item *fim;
	int tamanho;
};

struct nodo
{
	Item *prox;
	Item *ant;
	Music *info;
};

struct musica
{
	char titulo[256];
	char artista[256];
	char letra[256];
	int codigo;
	int execucoes;
};

Descritor* criaDesc(); // função que aloca memória para o descritor da LDE
Descritor* initialize_acervo(Music* acervo, int tamanhoAcervo); // função responsável por fazer cópias do acervo original
Music* criaMusica(char *title, char *art, char *let, int cod, int exec); // aloca memoria para as informações de uma nova música 
Music* loadDataBase(); // realiza o load do acervo para o programa principal
Item* criaItem(Music* infoMusica); // cria um novo nodo
Item* buscaLista(Descritor* lista, int posicao); // busca na lista um elemento
void get_title(Descritor* lista, char *title, int tamanhoAcervo); // realiza busca por titulo de uma música do acervo
Item* get_cod(Descritor* lista, int cod); // realiza busca por código de uma música do acervo
void get_art(Descritor* lista, char *name, int tamanhoAcervo); // Busca e imprime todas as músicas de um artista
void quebraFrase(Music* acervo, char *frase, int indice); // realiza a seperação dos dados do arquivo de entrada
void removeLista(Descritor* lista, int posicao); // remove um elemento da lista
void imprimeLista(Descritor* lista); // imprime a list
void imprimeItem(Item* item); // imprime as informacoes de um nodo
void insereLista(Descritor* lista, Item* info, int posicao); // insere um elemento na lista
void destroiLista(Descritor* lista); // libera a memoria alocada para a lista
void exec_playlist(Music* acervo, Item* infoMusica); // incrementa o numero de execucoes no acervo após execução da playlist
void modify_String(char *string); // converte a string informada pelo usuario para letras maiúsculas
void Relatorio_Acervo(Music* acervo, int tamanhoAcervo); // cria um backup do acervo
int tamanhoLista(Descritor* lista); // retorna a quantidade de elementos da lista
int lenght_acervo(); // retorna o tamanho do acervo original
int index_random(); // gera índices aleatórios para serem utilizados na criação das playlists aleatórias