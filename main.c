// Davi Pedri Vieira e Stéfany Kitzberger

#include <stdio.h>
#include "grafo.h"

void exibirMenu();

int main(void) {
    Grafo campus;
    int opcao = -1;

    inicializarGrafo(&campus);

    while (opcao != 0) {

        exibirMenu();

        scanf("%i", &opcao);

        switch (opcao) {
            case 1:
                exibirMapa(&campus);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 0:
                printf("\nEncerrando...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    }

    return 0;
}

void exibirMenu() {
    printf("\n");
    printf("========================================\n");
    printf("       SISTEMA DE ROTAS DO CAMPUS\n");
    printf("========================================\n");
    printf("\n");
    printf("1 - Exibir mapa do campus\n");
    printf("2 - Encontrar menor rota entre dois predios\n");
    printf("3 - Verificar conexao entre dois predios\n");
    printf("4 - Exibir matriz de alcancabilidade\n");
    printf("0 - Sair\n");
    printf("\n");
    printf("Escolha uma opcao: ");
}