#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

int main()
{
    Music* acervo_main = loadDataBase();
    Music* copyAcervo = NULL;
    Descritor* list = NULL;
    desc_stack* playlistP = criaPilha();
    descFila* random_playlist = NULL;
    Item* newNodo = NULL;
    Item* removeNode = NULL;

    srand(time(NULL));

    int op = 0, op1 = 0, op2 = 0, op3 = 0, op5 = 0;
    int cod = 0, numMusicas = 0, cont = 0, indice = 0, verify = 0;
    int tamanhoAcervo = lenght_acervo();
    char title[256], name[256], search_title[256];
    char check;
    
    while(1)
    {
        printf("\n");
        printf("    --- MENU ---    \n\n");
        printf("1. Executar playlists\n2. Criar playlist\n3. Buscar musica\n4. Imprimir acervo\n5. Relatorio\n6. Sair\n\n");
        printf("Escolha uma opcao: ");
        setbuf(stdin, NULL);
        scanf("%d", &op);

        switch(op)
        {
            case 1:
                if(random_playlist == NULL && playlistP->Pilha == NULL)
                {
                    printf("\nErro: voce nao possui playlists, crie playlists para poder executar!\n\n");
                    break;
                }
                else if(random_playlist == NULL && playlistP->Pilha != NULL)
                {
                    printf("\n");
                    printf("    --- Executando playlist pessoal --- \n\n");
                    while(playlistP->Pilha != NULL)
                    {
                        removeNode = pop(playlistP);
                        exec_playlist(acervo_main, removeNode);
                        removeNode = NULL;
                    }
                    printf("\nPlaylist executada!\n\n");
                    verify = 1;
                    break;

                }
                else if(random_playlist != NULL && playlistP->Pilha == NULL)
                {
                    if(random_playlist->tamanho == 0)
                    {
                        printf("\nSua playlist aleatoria ja foi executada por completo, insira novas musicas!\n\n");
                        random_playlist = NULL;
                        break;
                    }
                    else
                    {
                        printf("\n");
                        printf("    --- Excutando playlist aleatoria --- \n\n");
                        while(random_playlist->head != NULL)
                        {
                            removeNode = dequeue(random_playlist);
                            exec_playlist(acervo_main, removeNode);
                            removeNode = NULL;
                        }
                        printf("\nPlaylist executada!\n\n");
                        verify = 1;
                        break;
                    }
                }
                else if(random_playlist != NULL && playlistP->Pilha != NULL)
                {
                    printf("\n");
                    printf("\t       --- Execucao de playlists ---   \n\n");
                    printf("\t[1] Playlist aleatoria  [2] Playlist pessoal   \n\n");
                    printf("Escolha qual playlist deseja executar: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &op1);

                    switch(op1)
                    {
                        case 1:
                            if(random_playlist->tamanho == 0)
                            {
                                printf("\nSua playlist aleatoria ja foi executada por completo, insira novas musicas!\n\n");
                                random_playlist = NULL;
                                break;
                            }
                            else
                            {
                                printf("\n");
                                printf("    --- Excutando playlist aleatoria --- \n\n");
                                while(random_playlist->head != NULL)
                                {
                                    removeNode = dequeue(random_playlist);
                                    exec_playlist(acervo_main, removeNode);
                                    removeNode = NULL;
                                }
                                printf("\nPlaylist executada!\n\n");
                                verify = 1;
                                break;
                            }
                            break;
                        case 2:
                            printf("\n");
                            printf("    --- Executando playlist pessoal --- \n\n");
                            while(playlistP->Pilha != NULL)
                            {
                                removeNode = pop(playlistP);
                                exec_playlist(acervo_main, removeNode);
                                removeNode = NULL;
                            }
                            printf("\nPlaylist executada!\n\n");
                            verify = 1;
                            break;
                        default:
                            printf("\nErro: opcao invalida!\n\n");
                    }
                }
                break;
            case 2:
                printf("\n");
                printf("\t       --- Criacao de playlist ---   \n\n");
                printf("\t[1] Playlist aleatoria  [2] Playlist pessoal  \n\n");
                printf("Selecione a playlist que deseja criar: ");
                setbuf(stdin, NULL);
                scanf("%d", &op2);

                switch(op2)
                {
                    case 1:
                        printf("\n");
                        printf("\t       --- Criacao de playlist aleatoria ---  \n\n");
                        printf("Informe quantas musicas deseja em sua playlist: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &numMusicas);
                        random_playlist = initializeQueue();
                        while(cont < numMusicas)
                        {
                            indice = index_random();
                            copyAcervo = criaMusica(acervo_main[indice].titulo, acervo_main[indice].artista, acervo_main[indice].letra, acervo_main[indice].codigo, acervo_main[indice].execucoes);
                            newNodo = criaItem(copyAcervo);
                            enqueue(random_playlist, newNodo);
                            newNodo = NULL;
                            copyAcervo = NULL;
                            cont++;
                        }
                        cont = 0;
                        printf("\nSua playlist aleatoria com %d musicas foi criada com sucesso!\n\n", lenghtQueue(random_playlist));
                        showQueue(random_playlist);
                        break;
                    case 2:
                        list = initialize_acervo(acervo_main, tamanhoAcervo);
                        printf("\n");
                        printf("\t  --- Criacao de playlist pessoal --- \n\n");
                        printf("Informe o codigo da musica que deseja inserir em sua playlist: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &cod);
                        newNodo = get_cod(list, cod);
                        if(newNodo == NULL)
                        {
                            printf("\nErro: a musica que deseja inserir nao esta presente no seu acervo, tente novamente!\n\n");
                            break;
                        }
                        else
                        {
                            push(playlistP, newNodo);
                            printf("\nSua playlist pessoal contem: %d musicas\n\n", lenght(playlistP));
                            imprimePilha(playlistP);
                        }
                        break;
                    default:
                        printf("\nErro: opcao invalida!\n\n");
                }
                break;
            case 3:
                printf("\n");
                printf("\t      --- Buscar musica ---   \n\n");
                printf("\t[1] Titulo  [2] Artista  [3] Codigo \n\n");
                printf("Selecione o tipo de busca que deseja realizar: ");
                setbuf(stdin, NULL);
                scanf("%d", &op3);

                switch(op3)
                {
                    case 1:
                        printf("\n");
                        printf("    --- Busca por titulo ---    \n\n");
                        printf("Informe o titulo da musica que deseja buscar: ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]s", title);
                        modify_String(title);
                        list = initialize_acervo(acervo_main, tamanhoAcervo);
                        get_title(list, title, tamanhoAcervo);
                        destroiLista(list);
                        break;
                    case 2:
                        printf("\n");
                        printf("    --- Busca por artista ---   \n\n");
                        printf("Informe o nome do artista que deseja buscar: ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]s", name);
                        modify_String(name);
                        list = initialize_acervo(acervo_main, tamanhoAcervo);
                        get_art(list, name, tamanhoAcervo);
                        destroiLista(list);
                        break;
                    case 3:
                        printf("\n");
                        printf("    --- Busca por codigo ---    \n\n");
                        printf("Informe o codigo da musica que deseja buscar: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &cod);
                        list = initialize_acervo(acervo_main, tamanhoAcervo);
                        imprimeItem(get_cod(list, cod));
                        destroiLista(list);
                        break;
                    default:
                        printf("\nErro: opcao invalida!\n\n");
                }
                break;
            case 4:
                list = initialize_acervo(acervo_main, tamanhoAcervo);
                imprimeLista(list);
                destroiLista(list);
                break;
            case 5:
                verify = 0;
                Relatorio_Acervo(acervo_main, tamanhoAcervo);
                printf("\nRelatorio criado com sucesso, o programa sera encerrado para realizar as atualizacoes...\n\n");
                printf("Programa encerrado!\n\n");
                exit(0);
                break;
            case 6:
                if(verify == 1)
                {
                    printf("\nVoce realizou execucoes em sua playlist e não atualizou seu banco de dados...\n");
                    printf("\nSe sair agora perdera suas informacoes, deseja salvar suas informacoes [S/N]: ");
                    setbuf(stdin, NULL);
                    scanf("%c", &check);

                    switch(check)
                    {
                        case 'S':
                            Relatorio_Acervo(acervo_main, tamanhoAcervo);
                            printf("\nBanco de dados atualizado com sucesso!\n\n");
                            printf("\nPrograma encerrado!\n\n");
                            exit(0);
                            break;
                        case 'N':
                            printf("\nPrograma encerrado!\n\n");
                            exit(0);
                            break;
                        default:
                            printf("\nInforme uma opcao valida!\n\n");
                    }
                }
                printf("\nPrograma encerrado!\n\n");
                exit(0);
                break;
            default:
                printf("\nErro: opcao invalida, selecione novamente!\n\n");
        }
    }

    return 0;
}