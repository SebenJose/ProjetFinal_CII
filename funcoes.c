#include "funcoes.h"

void boasVindas()
{
    limparTela();
    printf("\t========== Seja bem-vindo ao %sSlockCar%s! ==========\n", REDFG, RESET);
    printf("\t          Sistema de locação de carros.\n\n");
    printf("\t=================================================\n\n");
    printf("Pressione %sENTER%s para se encaminhar ao MENU...", WHTBG, RESET);
}

void menuPrincipal()
{
    boasVindas();
    getchar();

    //? Menu principal:
    int opc;
    do
    {
        limparTela();
        printf("\t========== %sMENU%s ==========\n", BLUFG, RESET);
        printf("\t%s[1]%s - Locação de Carros. \n", WHTBG, RESET);
        printf("\t%s[2]%s - Carros. \n", WHTBG, RESET);
        printf("\t%s[3]%s - Clientes. \n", WHTBG, RESET);
        printf("\t%s[0]%s - %sSair%s. \n", WHTBG, RESET, REDFG, RESET);
        printf("\t==========================\n");
        printf("\nDigite a opção a seguir: ");

        if (scanf("%d", &opc) != 1)
        {
            limparBuffer();
            opc = -1;
        }
        switch (opc)
        {
        case 1:
            limparTela();
            menuLocacaoCarros(); //? Chama a função de menu do módulo de locação de carros
            break;

        case 2:
            limparTela();
            menuCarros(); //? Chama a função de menu do módulo de carros
            break;

        case 3:
            limparTela();
            menuClientes(); //? Chama a função de menu do módulo de clientes
            break;

        case 0:
            limparTela();
            printf("Saindo");
            pontinhos();
            break;

        default:
            printf("Opção %sindisponível%s, pressione %sENTER%s para continuar", REDFG, RESET, WHTBG, RESET);
            pontinhos();
            limparBuffer();

#ifdef _WIN322
            Sleep(500);
#endif
        }
    } while (opc != 0);
}

void menuLocacaoCarros()
{
    //? Menu para a aba de locação de carros
    int opc;
    do
    {
        limparTela();
        printf("\t========== %sLOCAÇÃO DE CARROS%s ==========\n", BLUFG, RESET);
        printf("\t%s[1]%s - Vizualizar locações.\n", WHTBG, RESET);
        printf("\t%s[2]%s - Incluir locações.\n", WHTBG, RESET);
        printf("\t%s[3]%s - Dar baixa locações.\n", WHTBG, RESET);
        printf("\t%s[0]%s - Voltar.\n", WHTBG, RESET);
        printf("\t=======================================\n");
        printf("\nDigite a opção a seguir: ");
        if (scanf("%d", &opc) != 1)
        {
            limparBuffer();
            opc = -1;
        }

        switch (opc)
        {
        case 1:
            //? Vizualizar as locações cadastradas
            limparTela();
            vizualizarLocacoes();
            getchar();
            break;

        case 2:
            //? Incluir novas locações
            limparTela();
            incluirLocacoes();
            getchar();
            break;

        case 3:
            //? Dar baixa nas locações
            limparTela();
            darBaixaLocacoes();
            getchar();
            break;

        case 0:
            //? Retornar ao menu principal
            limparTela();
            printf("Voltando");
            pontinhos();
            break;

        default:
            printf("Opção %sindisponível%s, pressione %sENTER%s para continuar", REDFG, RESET, WHTBG, RESET);
            pontinhos();
            limparBuffer();

#ifdef _WIN32
            Sleep(1000);
#endif
        }

        if (opc != 0)
        {
            printf("\nPressione %sENTER%s para continuar", WHTBG, RESET);
            pontinhos();
            getchar();
        }

    } while (opc != 0);
}

Locacao *locacoes; //? Matriz das locações
int totalLocacoes = 0;

void incluirLocacoes()
{
    limparTela();

    //? Verificando se há carros e clientes cadastrados
    if (totalCarros == 0 && totalClientes == 0)
    {
        printf("%sNão%s há carros ou clientes cadastrados", REDFG, RESET);
        pontinhos();
        return;
    }
    //? Verificando se há clientes cadastrados
    if (totalClientes == 0)
    {
        printf("%sNão%s há clientes cadastrados", REDFG, RESET);
        pontinhos();
        return;
    }
    //? Verificando se há carros cadastrados
    if (totalCarros == 0)
    {
        printf("%sNão%s há carros cadastrados", REDFG, RESET);
        pontinhos();
        return;
    }
    //? Verificando se locacoes é nula para a primeira locacao
    if (locacoes == NULL)
    {
        locacoes = (Locacao *)malloc(sizeof(Locacao));
    }

    //? Solicita o nome do arquivo de entrada
    char nomeArquivo[TAM_LINHA];
    limparTela();
    printf("Exemplo de formatação para o arquivo de entrada:\n");
    printf("\n> Código do carro: %s123%s\n", GRNFG, RESET);
    printf("> Código do cliente: %s123%s\n", GRNFG, RESET);
    printf("> Valor da locação: %s99.99%s\n", GRNFG, RESET);
    printf("> Data da locação: %s01/01/2000%s\n", GRNFG, RESET);
    printf("> Data da devolução: %s07/01/2000%s\n", GRNFG, RESET);
    printf("> Status: %sAtiva%s", GRNFG, RESET);
    printf("\nCOLOQUE NO ARQUIVO DE ENTRADA %sAPENAS E SOMENTE%s OS DADOS DA LOCAÇÃO, %sCADA DADO EM UMA LINHA%s.\n", REDFG, RESET, REDFG, RESET);

    printf("\nDigite o %snome do arquivo%s de cadastro (ex: locacao_registro.txt): ", WHTBG, RESET);
    scanf("%s", nomeArquivo);

    //? Adiciona o caminho do arquivo de entrada
    char caminhoArquivoEntrada[TAM_LINHA + 20];
    snprintf(caminhoArquivoEntrada, sizeof(caminhoArquivoEntrada), "txt/Entradas/%s", nomeArquivo);

    //? Abre o arquivo
    FILE *arquivoEntrada = fopen(caminhoArquivoEntrada, "r");
    if (arquivoEntrada == NULL)
    {
        printf("%s%sERRO%s%s: Arquivo %snão%s encontrado", REDFG, BLINK, BLINKS, RESET, REDFG, RESET);
        pontinhos();
        return;
    }

    //? Criando o arquivo de confirmacao
    FILE *arquivoConfirmacao = fopen("txt/Saidas/cadastros_de_locacoes_realizados.txt", "w");
    fprintf(arquivoConfirmacao, "=======Cadastros realizados com %ssucesso%s!======\n\n", GRNFG, RESET);

    //? Criando o arquivo de confirmacao
    FILE *arquivoTotais = fopen("txt/CadastrosTotais/todas_as_locacoes.txt", "a");
    if (arquivoTotais == NULL)
    {
        printf("%s%sERRO%s%s: %sNão%s foi possível abrir o arquivo de todos os cadastros", REDFG, BLINK, BLINKS, RESET, REDFG, RESET);
        pontinhos();
        fclose(arquivoEntrada);
        fclose(arquivoConfirmacao);
        return;
    }

    //? Variáveis de leitura
    char linha[TAM_LINHA];
    int linhaAtual = 0;

    //? Variáveis temporarias
    Locacao *temp = locacoes;
    Locacao novaLocacao;

    //? Lê o arquivo de entrada linha por linha
    while (fgets(linha, TAM_LINHA, arquivoEntrada) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0'; //? Remove quebra de linha

        switch (linhaAtual % 6) //? Usa as seis primeiras linhas para adicionar um novo cadastro na formatação do arquivo de entrada
        {
        case 0:
            //? Verificando se o carro existe
            if (atoi(linha) > totalCarros + 1)
            {
                printf("Carro %d %snão%s cadastrado", atoi(linha), REDFG, RESET);
                pontinhos();
                fclose(arquivoEntrada);
                return;
            }
            novaLocacao.codigoCarro = atoi(linha); //? Adiciona o código do carro
            break;

        case 1:
            //? Verificando se o carro existe
            if (atoi(linha) > totalClientes + 1)
            {
                printf("Cliente %d %snão%s cadastrado", atoi(linha), REDFG, RESET);
                pontinhos();
                fclose(arquivoEntrada);
                return;
            }
            novaLocacao.codigoCliente = atoi(linha); //? Adiciona o código do cliente
            break;

        case 2:
            novaLocacao.valorLocacao = atof(linha); //? Adiciona o valor da locação
            break;

        case 3:
            sscanf(linha, "%d/%d/%d", &novaLocacao.dataLocacao.dia, &novaLocacao.dataLocacao.mes, &novaLocacao.dataLocacao.ano); //? Adiciona a data da locação
            break;

        case 4:
            sscanf(linha, "%d/%d/%d", &novaLocacao.dataDevolucao.dia, &novaLocacao.dataDevolucao.mes, &novaLocacao.dataDevolucao.ano); //? Adiciona a data de devolução
            break;

        case 5:
            strcpy(novaLocacao.status, linha);                                                //? Adiciona o status da locação
            temp = (Locacao *)realloc(locacoes, sizeof(*temp) * ((size_t)totalLocacoes + 1)); //? Realoca a memória para alocar a nova locação
            if (temp != NULL)
            {
                locacoes = temp;
                locacoes[totalLocacoes] = novaLocacao;

                //? Escrevendo o arquivo de confirmação
                fprintf(arquivoConfirmacao, "Locação %d:\n", totalLocacoes + 1);
                fprintf(arquivoConfirmacao, "Código do carro: %d\n", novaLocacao.codigoCarro);
                fprintf(arquivoConfirmacao, "Código do cliente: %d\n", novaLocacao.codigoCliente);
                fprintf(arquivoConfirmacao, "Valor da locação: %.2f\n", novaLocacao.valorLocacao);
                fprintf(arquivoConfirmacao, "Data da locação: %d/%d/%d\n", novaLocacao.dataLocacao.dia, novaLocacao.dataLocacao.mes, novaLocacao.dataLocacao.ano);
                fprintf(arquivoConfirmacao, "Data da devolução: %d/%d/%d\n", novaLocacao.dataDevolucao.dia, novaLocacao.dataDevolucao.mes, novaLocacao.dataDevolucao.ano);
                fprintf(arquivoConfirmacao, "Status: %s\n", novaLocacao.status);
                fprintf(arquivoConfirmacao, "-----------------------------\n\n");

                //? Escreve no arquivo de todos os cadastros
                fprintf(arquivoTotais, "Locação %d:\n", totalLocacoes + 1);
                fprintf(arquivoTotais, "Código do carro: %d\n", novaLocacao.codigoCarro);
                fprintf(arquivoTotais, "Código do cliente: %d\n", novaLocacao.codigoCliente);
                fprintf(arquivoTotais, "Valor da locação: %.2f\n", novaLocacao.valorLocacao);
                fprintf(arquivoTotais, "Data da locação: %d/%d/%d\n", novaLocacao.dataLocacao.dia, novaLocacao.dataLocacao.mes, novaLocacao.dataLocacao.ano);
                fprintf(arquivoTotais, "Data da devolução: %d/%d/%d\n", novaLocacao.dataDevolucao.dia, novaLocacao.dataDevolucao.mes, novaLocacao.dataDevolucao.ano);
                fprintf(arquivoTotais, "Status: %s\n", novaLocacao.status);
                fprintf(arquivoTotais, "-----------------------------\n\n");

                totalLocacoes++;
                break;
            }
            else
            {
                //? Caso não consiga alocar a memória
                printf("%s%sERRO%s%s: %sNão%s foi possível alocar memória", REDFG, BLINK, BLINKS, RESET, REDFG, RESET);
                pontinhos();
                fclose(arquivoEntrada);
                fclose(arquivoConfirmacao);
                fclose(arquivoTotais);
                return;
            }
        }

        linhaAtual++;
    }

    //? Fecha os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);
    fclose(arquivoTotais);

    printf("\n%d Locações cadastradas com %ssucesso%s!\n", totalLocacoes, GRNFG, RESET);
    printf("Comprovante %ssalvo%s em: txt/Saidas/cadastros_de_locacoes_realizados.txt\n", BLUFG, RESET);
    printf("Todos os cadastros %ssalvos%s em: txt/CadastrosTotais/todas_as_locacoes.txt\n", BLUFG, RESET);
}

void vizualizarLocacoes()
{
    limparTela();

    //? Verifica se há locações cadastradas
    if (totalLocacoes == 0)
    {
        printf("%sNenhuma%s locação ativa!\n", REDFG, RESET);
        return;
    }
    //? Vizualiza as locações cadastradas e as imprime
    printf("\n========== %sLOCAÇÕES CADASTRADAS%s ==========\n", BLUFG, RESET);
    for (int i = 0; i < totalLocacoes; i++)
    {
        printf("\nLocação %d:\n", i + 1);
        printf("Código do carro: %d\n", locacoes[i].codigoCarro);
        printf("Código do cliente %d\n", locacoes[i].codigoCliente);
        printf("Valor da locação %.2f\n", locacoes[i].valorLocacao);
        printf("Data de locação: %d/%d/%d\n", locacoes[i].dataLocacao.dia, locacoes[i].dataLocacao.mes, locacoes[i].dataLocacao.ano);
        printf("Data de devolução: %d/%d/%d\n", locacoes[i].dataDevolucao.dia, locacoes[i].dataDevolucao.mes, locacoes[i].dataDevolucao.ano);
        printf("Status: %s\n", locacoes[i].status);
        printf("-----------------------------\n");
    }
}

void darBaixaLocacoes()
{
    limparTela();

    int op = 1;
    //? Enquanto o usuário desejar dar baixa em locações
    while (op != 0)
    {
        limparTela();
        vizualizarLocacoes(); //? Vizualiza as locações cadastradas

        //? Verifica se há locações cadastradas
        if (totalLocacoes == 0)
        {
            return;
        }

        //? Solicita a locação que deseja dar baixa
        printf("\tQual locação deseja dar baixa? \n");
        scanf("%d", &op);
        Locacao temp;

        op--; //? Decrementa a opcção para o índice da matriz (para deixar mais intuitivo ao usuário)

        //? Move a locação para o final da matriz
        temp = locacoes[op];
        locacoes[op] = locacoes[totalLocacoes - 1];
        locacoes[totalLocacoes - 1] = temp;

        totalLocacoes--;                                                                                                //? Decrementa o total de locações
        printf("\nDeseja dar baixa em outra locação? \n%s[1]%s - Sim. \n%s[0]%s - Não.\n", WHTBG, RESET, WHTBG, RESET); //? Pergunta se deseja dar baixa em outra locação
        printf("\nDigite a opção a seguir: ");
        scanf("%d", &op);
    }

    system("cls");

    //? Criando o arquivo de confirmação
    FILE *arquivoConfirmacao = fopen("txt/CadastrosTotais/todas_as_locacoes.txt", "w");

    //? Escreve no arquivo de todos os cadastros a fim de salvar a baixa
    for (int i = 0; i < totalLocacoes; i++)
    {
        printf("\nLocação %d:\n", i + 1);
        printf("ID do Cliente %d\n", locacoes[i].codigoCliente);
        printf("ID do Carro: %d\n", locacoes[i].codigoCarro);
        printf("Valor da locação %.2f\n", locacoes[i].valorLocacao);
        printf("Data de locação: %d/%d/%d\n", locacoes[i].dataLocacao.dia, locacoes[i].dataLocacao.mes, locacoes[i].dataLocacao.ano);
        printf("Data de devolução: %d/%d/%d\n", locacoes[i].dataDevolucao.dia, locacoes[i].dataDevolucao.mes, locacoes[i].dataDevolucao.ano);
        printf("Status: %s\n", locacoes[i].status);
        printf("-----------------------------\n");

        //? Escrevendo o arquivo de confirmação
        fprintf(arquivoConfirmacao, "Locação %d:\n", totalLocacoes + 1);
        fprintf(arquivoConfirmacao, "Código do carro: %d\n", locacoes[i].codigoCarro);
        fprintf(arquivoConfirmacao, "Código do cliente: %d\n", locacoes[i].codigoCliente);
        fprintf(arquivoConfirmacao, "Valor da locação: %.2f\n", locacoes[i].valorLocacao);
        fprintf(arquivoConfirmacao, "Data da locação: %d/%d/%d\n", locacoes[i].dataLocacao.dia, locacoes[i].dataLocacao.mes, locacoes[i].dataLocacao.ano);
        fprintf(arquivoConfirmacao, "Data da devolução: %d/%d/%d\n", locacoes[i].dataDevolucao.dia, locacoes[i].dataDevolucao.mes, locacoes[i].dataDevolucao.ano);
        fprintf(arquivoConfirmacao, "Status: %s\n", locacoes[i].status);
        fprintf(arquivoConfirmacao, "-----------------------------\n\n");
    }

    //? Fecha o arquivo de confirmação
    fclose(arquivoConfirmacao);

    printf("Retornando ao menu");
    pontinhos();
}

void menuCarros()
{
    //? Menu para a aba de carros
    int opc;
    do
    {
        limparTela();
        printf("\t========== %sCARROS%s ==========\n", BLUFG, RESET);
        printf("\t%s[1]%s - Vizualizar Cadastros.\n", WHTBG, RESET);
        printf("\t%s[2]%s - Incluir Cadastros.\n", WHTBG, RESET);
        printf("\t%s[0]%s - Voltar.\n", WHTBG, RESET);
        printf("\t============================\n");
        printf("\nDigite a opção a seguir: ");
        if (scanf("%d", &opc) != 1)
        {
            opc = -1;
        }

        switch (opc)
        {
        case 1:
            limparTela();
            vizualizarCarros(); //? Chama a função de vizualização de carros
            getchar();
            break;

        case 2:
            limparTela();
            incluirCarros(); //? Chama a função de inclusão de carros
            getchar();
            break;

        case 0:
            limparTela();
            printf("Voltando"); //? Retorna ao menu principal
            pontinhos();
            break;

        default:
            printf("Opção %sindisponível%s, pressione %sENTER%s para continuar", REDFG, RESET, WHTBG, RESET);
            pontinhos();
            limparBuffer();

#ifdef _WIN32
            Sleep(500); //? Timer de 1 segundo quando for dado uma opção inválida
#endif
        }

        if (opc != 0)
        {
            printf("Pressione %sENTER%s para continuar", WHTBG, RESET);
            pontinhos();
            getchar();
        }
    } while (opc != 0);
}

Carro carros[MAX_CARROS]; //? Matriz dos carros
int totalCarros = 0;

void incluirCarros()
{
    limparTela();

    //? Solicita o nome do arquivo de entrada
    char nomeArquivo[TAM_LINHA];

    printf("Exemplo de formatação para o arquivo de entrada:\n");
    printf("\n> Marca: %sFiat%s\n", GRNFG, RESET);
    printf("> Modelo: %sPalio%s\n", GRNFG, RESET);
    printf("> Ano: %s2011%s\n", GRNFG, RESET);
    printf("> Placa: %sABC123%s\n", GRNFG, RESET);
    printf("\nCOLOQUE NO ARQUIVO DE ENTRADA %sAPENAS E SOMENTE%s OS DADOS DO CARRO, %sCADA DADO EM UMA LINHA%s.\n", REDFG, RESET, REDFG, RESET);

    printf("\nDigite o nome do arquivo de cadastro (ex: carros_registro.txt): ");
    scanf("%s", nomeArquivo);

    //? Adiciona o caminho do arquivo de entrada
    char caminhoArquivoEntrada[TAM_LINHA + 20];
    snprintf(caminhoArquivoEntrada, sizeof(caminhoArquivoEntrada), "txt/Entradas/%s", nomeArquivo);

    //? Abre o arquivo
    FILE *arquivoEntrada = fopen(caminhoArquivoEntrada, "r");
    if (arquivoEntrada == NULL)
    {
        printf("ERRO: arquivo nao encontrado. \n");
        return;
    }

    //? Criando o arquivo de confirmação
    FILE *arquivoConfirmacao = fopen("txt/Saidas/cadastros_de_carros_realizados.txt", "w");
    fprintf(arquivoConfirmacao, "=======Cadastros realizados com %ssucesso%s!======\n\n", GRNFG, RESET);

    //? Abre o arquivo de todos os cadastros no modo de adição
    FILE *arquivoTodosCadastros = fopen("txt/CadastrosTotais/todos_os_carros.txt", "a");
    if (arquivoTodosCadastros == NULL)
    {
        printf("ERRO: não foi possível abrir o arquivo de todos os cadastros");
        fclose(arquivoEntrada);
        fclose(arquivoConfirmacao);
        return;
    }

    //? Variáveis de leitura
    char linha[TAM_LINHA];
    int linhaAtual = 0;
    Carro novoCarro;

    //? Lê o arquivo de entrada linha por linha
    while (fgets(linha, TAM_LINHA, arquivoEntrada) != NULL && totalCarros < MAX_CARROS)
    {
        linha[strcspn(linha, "\n")] = '\0'; //? Remove quebra de linha

        switch (linhaAtual % 4) //? Usa as quatro primeiras linhas para adicionar um novo cadastro na formatação do arquivo de entrada
        {
        case 0:
            strcpy(novoCarro.marca, linha); //? Adiciona a marca do carro
            break;
        case 1:
            strcpy(novoCarro.modelo, linha); //? Adiciona o modelo do carro
            break;
        case 2:
            novoCarro.ano = atoi(linha); //? Adiciona o ano do carro
            break;
        case 3:
            strcpy(novoCarro.placa, linha); //? Adiciona a placa do carro

            //? Adiciona o carro na matriz
            carros[totalCarros] = novoCarro;

            //? Escrevendo o arquivo de confirmação
            fprintf(arquivoConfirmacao, "Carro %d:\n", totalCarros + 1);
            fprintf(arquivoConfirmacao, "Marca: %s\n", novoCarro.marca);
            fprintf(arquivoConfirmacao, "Modelo: %s\n", novoCarro.modelo);
            fprintf(arquivoConfirmacao, "Ano: %d\n", novoCarro.ano);
            fprintf(arquivoConfirmacao, "Placa: %s\n", novoCarro.placa);
            fprintf(arquivoConfirmacao, "-----------------------------\n\n");

            //? Escreve no arquivo de todos os cadastros
            fprintf(arquivoTodosCadastros, "Carro %d:\n", totalCarros + 1);
            fprintf(arquivoTodosCadastros, "Marca: %s\n", novoCarro.marca);
            fprintf(arquivoTodosCadastros, "Modelo: %s\n", novoCarro.modelo);
            fprintf(arquivoTodosCadastros, "Ano: %d\n", novoCarro.ano);
            fprintf(arquivoTodosCadastros, "Placa: %s\n", novoCarro.placa);
            fprintf(arquivoTodosCadastros, "-----------------------------\n\n");

            totalCarros++;
            break;
        }
        linhaAtual++;
    }

    //? Fecha os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);
    fclose(arquivoTodosCadastros);

    printf("\n%d Carros cadastrados com %ssucesso%s!\n", totalCarros, GRNFG, RESET);
    printf("Comprovante %ssalvo%s em: txt/Saidas/cadastros_de_carros_realizados.txt\n", GRNFG, RESET);
    printf("Todos os cadastros %ssalvos%s em: txt/CadastrosTotais/todos_os_carros.txt\n", GRNFG, RESET);
}

void vizualizarCarros()
{
    limparTela();

    //? Verifica se há carros cadastrados
    if (totalCarros == 0)
    {
        printf("%sNenhum%s cadastro efetuado!\n", REDFG, RESET);
        return;
    }

    limparTela();

    //? Vizualiza os carros cadastrados e os imprime
    printf("\t========== %sCARROS CADASTRADOS%s ==========\n", BLUFG, RESET);
    for (int i = 0; i < totalCarros; i++)
    {
        printf("\nCarro %d:\n", i + 1);
        printf("Marca: %s\n", carros[i].marca);
        printf("Modelo: %s\n", carros[i].modelo);
        printf("Ano: %d\n", carros[i].ano);
        printf("Placa: %s\n", carros[i].placa);
        printf("-----------------------------\n");
    }
}

Cliente clientes[MAX_CLIENTES]; //? Matriz dos clientes
int totalClientes = 0;

void menuClientes()
{
    //? Menu para a aba de clientes
    int opc;
    do
    {
        limparTela();
        printf("\t========== %sCLIENTES%s ==========\n", BLUFG, RESET);
        printf("\t%s[1]%s - Vizualizar cadastros.\n", WHTBG, RESET);
        printf("\t%s[2]%s - Incluir cadastros.\n", WHTBG, RESET);
        printf("\t%s[0]%s - Voltar.\n", WHTBG, RESET);
        printf("\t=============================\n");
        printf("\nDigite a opção a seguir: ");
        if (scanf("%d", &opc) != 1)
        {
            opc = -1;
        }

        switch (opc)
        {
        case 1:
            limparTela();
            vizualizarClientes(); //? Chama a função de vizualização de clientes
            getchar();
            break;

        case 2:
            limparTela();
            incluirClientes(); //? Chama a função de inclusão de clientes
            getchar();
            break;

        case 0:
            limparTela();
            printf("Voltando"); //? Retorna ao menu principal
            pontinhos();
            break;

        default:
            printf("Opção %sindisponível%s, pressione %sENTER%s para continuar", REDFG, RESET, WHTBG, RESET);
            pontinhos();
            limparBuffer();

#ifdef _WIN32
            Sleep(500); //? Timer de 1 segundo após dar uma opção inválida
#endif
        }

        if (opc != 0)
        {
            printf("Pressione %sENTER%s para continuar", WHTBG, RESET);
            pontinhos();
            getchar();
        }
    } while (opc != 0);
}

void incluirClientes()
{
    limparTela();

    //? Solicita o nome do arquivo de entrada
    char nomeArquivoCli[TAM_LINHA];

    printf("Exemplo de formatação para o arquivo de entrada:\n");
    printf("\n> Nome: %sJosé%s\n", GRNFG, RESET);
    printf("> Telefone: %s(42) 9984-2578%s\n", GRNFG, RESET);
    printf("> Endereço: %sRua São Paulo%s\n", GRNFG, RESET);
    printf("> CPF: %s189.005.302-64%s\n", GRNFG, RESET);
    printf("\nCOLOQUE NO ARQUIVO DE ENTRADA %sAPENAS E SOMENTE%s OS DADOS DO CLIENTE, %sCADA DADO%s EM UMA LINHA.\n", REDFG, RESET, REDFG, RESET);

    printf("\nDigite o nome do arquivo de cadastro (ex: cliente_registro.txt): ");
    scanf("%s", nomeArquivoCli);

    char caminhoArquivoEntrada[TAM_LINHA + 20];
    snprintf(caminhoArquivoEntrada, sizeof(caminhoArquivoEntrada), "txt/Entradas/%s", nomeArquivoCli);

    //? Arquivo de entrada
    FILE *arquivoEntrada = fopen(caminhoArquivoEntrada, "r");
    if (arquivoEntrada == NULL)
    {
        printf("%s%sERRO%s%s: Arquivo %snão%s encontrado", REDFG, BLINK, BLINKS, RESET, REDFG, RESET);
        pontinhos();
        return;
    }

    //? Criando o arquivo de confirmação
    FILE *arquivoConfirmacao = fopen("txt/Saidas/cadastros_de_clientes_realizados.txt", "w");
    fprintf(arquivoConfirmacao, "=======Cadastros realizados com %sucesso%s!======\n\n", GRNFG, RESET);

    //? Abre o arquivo de todos os cadastros no modo de adição
    FILE *arquivoTodosCadastros = fopen("txt/CadastrosTotais/todos_os_clientes.txt", "a");
    if (arquivoTodosCadastros == NULL)
    {
        printf("%s%sERRO%s%s: %sNão%s foi possível abrir o arquivo de todos os cadastros", REDFG, BLINK, BLINKS, RESET, REDFG, RESET);
        pontinhos();
        fclose(arquivoEntrada);
        fclose(arquivoConfirmacao);
        return;
    }

    //? Variáveis de leitura
    char linha[TAM_LINHA];
    int linhaAtual = 0;

    Cliente novoCliente;

    //? Lê o arquivo de entrada linha por linha
    while (fgets(linha, TAM_LINHA, arquivoEntrada) != NULL && totalClientes < MAX_CLIENTES)
    {
        linha[strcspn(linha, "\n")] = '\0'; //? Remove quebra de linha

        switch (linhaAtual % 4) //? Usa as quatro primeiras linhas para adicionar um novo cadastro na formatação do arquivo de entrada
        {
        case 0:
            strcpy(novoCliente.nome, linha); //? Adiciona o nome do cliente
            break;
        case 1:
            strcpy(novoCliente.telefone, linha); //? Adiciona o telefone do cliente
            break;
        case 2:
            strcpy(novoCliente.endereco, linha); //? Adiciona o endereço do cliente
            break;
        case 3:
            strcpy(novoCliente.CPF, linha); //? Adiciona o CPF do cliente

            //? Adiciona o carro a matriz
            clientes[totalClientes] = novoCliente;

            //? Escrevendo o arquivo de confirmação
            fprintf(arquivoConfirmacao, "Cliente %d:\n", totalClientes + 1);
            fprintf(arquivoConfirmacao, "Nome: %s\n", novoCliente.nome);
            fprintf(arquivoConfirmacao, "Telefone: %s\n", novoCliente.telefone);
            fprintf(arquivoConfirmacao, "Endereço: %s\n", novoCliente.endereco);
            fprintf(arquivoConfirmacao, "CPF: %s\n", novoCliente.CPF);
            fprintf(arquivoConfirmacao, "-----------------------------\n\n");

            //? Escreve no arquivo de todos os cadastros
            fprintf(arquivoTodosCadastros, "Cliente %d:\n", totalClientes + 1);
            fprintf(arquivoTodosCadastros, "Nome: %s\n", novoCliente.nome);
            fprintf(arquivoTodosCadastros, "Telefone: %s\n", novoCliente.telefone);
            fprintf(arquivoTodosCadastros, "Endereço: %s\n", novoCliente.endereco);
            fprintf(arquivoTodosCadastros, "CPF: %s\n", novoCliente.CPF);
            fprintf(arquivoTodosCadastros, "-----------------------------\n\n");

            totalClientes++;
            break;
        }
        linhaAtual++;
    }

    //? Fecha os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);
    fclose(arquivoTodosCadastros);

    printf("\n%d Clientes cadastrados com %ssucesso%s!\n", totalClientes, GRNFG, RESET);
    printf("Detalhes %ssalvos%s em: txt/Saidas/cadastros_de_clientes_realizados.txt\n", BLUFG, RESET);
    printf("\nTodos os cadastros %ssalvos%s em: txt/CadastrosTotais/todos_os_clientes.txt\n", BLUFG, RESET);
}

void vizualizarClientes()
{
    limparTela();

    //? Verifica se há clientes cadastrados
    if (totalClientes == 0)
    {
        printf("%sNenhum%s cadastro efetuado!\n", REDFG, RESET);
        return;
    }

    //? Vizualiza os clientes cadastrados e os imprime
    printf("\n========== %sCLIENTES CADASTRADOS%s ==========\n", BLUFG, RESET);
    for (int i = 0; i < totalClientes; i++)
    {
        printf("\nClientes %d:\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Endereço: %s\n", clientes[i].endereco);
        printf("CPF: %s\n", clientes[i].CPF);
        printf("-----------------------------\n");
    }
}

//! Funções adicionais:

void limparTela()
{
#ifdef _WIN32
    system("cls");
#endif
}

void pontinhos()
{
    //? Simula uma animação de reticências (...)
    for (int i = 0; i < 3; i++)
    {
        Sleep(300);
        printf(".");
    }
    printf("\n");
}

void limparMemoria()
{
    //? Libera a memória alocada para as locações
    free(locacoes);
    locacoes = NULL;
}

void limparBuffer()
{
    //? Limpa o buffer do teclado
    int b;
    while ((b = getchar()) != '\n' && b != EOF)
        ;
}