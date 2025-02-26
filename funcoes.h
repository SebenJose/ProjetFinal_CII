#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

//? CORES
//? Cores do texto
#define REDFG "\033[31m"
#define GRNFG "\033[32m"
#define BLUFG "\033[34m"

//? Cores do fundo
#define WHTBG "\033[47m"

//? Animações de texto
#define BLINK "\033[5m"
#define BLINKS "\033[25m"
#define RESET "\033[0m"

//? CARRO
#define MAX_CARROS 100
#define TAM_LINHA 100

//? Estrutura do carro
typedef struct
{
    char marca[TAM_LINHA];
    char modelo[TAM_LINHA];
    int ano;
    char placa[TAM_LINHA];
} Carro;

//? Variáveis globais carros
extern Carro carros[MAX_CARROS]; // matriz global para armazenar os cadastros de carros
extern int totalCarros;          // variavel global para armazenar o total de carros

//? CLIENTES
#define MAX_CLIENTES 100

//? Estrutura clientes
typedef struct
{
    char nome[TAM_LINHA];
    char telefone[TAM_LINHA];
    char endereco[TAM_LINHA];
    char CPF[TAM_LINHA];
} Cliente;

//? Variáveis globais clientes
extern Cliente clientes[MAX_CLIENTES]; // matriz global para armazer os cadastros de clientes
extern int totalClientes;              // variavel global para armazenar o total dos clientes

//? Estrutura data
typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

//? Estrutura locação
typedef struct
{
    int codigoCliente;
    int codigoCarro;
    double valorLocacao;
    Data dataLocacao;
    Data dataDevolucao;
    char status[TAM_LINHA];
} Locacao;

//? Variáveis globais clientes
extern Locacao *locacoes; // matriz global para armazenar os cadastros de locacoes
extern int totalLocacoes; // variavel global para armazenar o total de locacoes

//! OUTRAS FUNÇÕES
void boasVindas(); // exibe a mensagem de boas vindas

void pontinhos(); // exibe os três pontinhos...

void lerCadastroTotal(); // le os cadastros totais

void menuPrincipal(); // exibe o menu principal

void menuCarros(); // menu para a aba carros

void menuLocacaoCarros(); // menu para a locacao de carros

void incluirLocacoes(); // funcao para realizar a inclusao de locacoes

void vizualizarLocacoes(); // funcao para a vizualizaçao das locacoes

void darBaixaLocacoes(); // funcao para dar baixa nas locacoes

void incluirCarros(); // funcao para realizar a inclusao de novos carros

void vizualizarCarros(); // funcao para a vizualizaçao dos cadastros ja efetuados

void menuClientes(); // menu da opcao clientes

void incluirClientes(); // funcao para fazer a inclusao de clientes

void vizualizarClientes(); // funcao para vizualizar os cadastros de clientes ja realizados

void limparTela(); // limpa a tela

void limparBuffer(); // funcao para limbar o scanf para tratar de entradas erradas

void limparMemoria(); // limpa o buffer do teclado

void pontinhos(); // funcao para printar diversos pontos

#endif // FUNCOES_H