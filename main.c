#include "funcoes.h"

int main(void)
{
    setlocale(LC_ALL, "Portuguese_Brasil.1252");
    limparTela();
    menuPrincipal();
    limparMemoria();

    return 0;
}