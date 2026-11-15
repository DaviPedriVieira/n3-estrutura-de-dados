// Davi Pedri Vieira e Stéfany Kitzberger

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define DECIMAL_BASE 10

void showMenu();
int readBuilding(Graph *graph, char *message);
void findShortestRoute(Graph *graph);
void verifyBuildingReachability(Graph *graph);
void showReachabilityMatrix(Graph *graph);

int main(void) {
    Graph campus;
    int option = -1;

    initializeGraph(&campus);

    while (option != 0) {

        showMenu();

        scanf("%i", &option);
        fflush(stdin);

        switch (option) {
            case 1:
                showMap(&campus);
                break;
            case 2:
                findShortestRoute(&campus);
                break;
            case 3:
                verifyBuildingReachability(&campus);
                break;
            case 4:
                showReachabilityMatrix(&campus);
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

void showMenu() {
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

int readBuilding(Graph *graph, char *message) {
    char input[NAME_SIZE];
    char *numberEnd;

    printf("%s", message);
    scanf(" %29[^\n]", input);

    int typedNumber = strtol(input, &numberEnd, DECIMAL_BASE);
    int isNumber = numberEnd != input && *numberEnd == '\0';
    if (isNumber) return findBuildingByNumber(graph, typedNumber);

    return findBuildingByName(graph, input);
}

void findShortestRoute(Graph *graph) {
    showBuildings(graph);

    int origin = readBuilding(graph, "\nOrigem (numero ou nome): ");
    if (origin == -1) {
        printf("\nPredio de origem nao encontrado!\n");
        return;
    }
    
    int destination = readBuilding(graph, "Destino (numero ou nome): ");
    if (destination == -1) {
        printf("\nPredio de destino nao encontrado!\n");
        return;
    }
    
    int pathSize;
    int path[MAX_BUILDINGS];
    int totalDistance = shortestRoute(graph, origin, destination, path, &pathSize);
    if (totalDistance == -1) {
        printf("\nNao existe caminho entre %s e %s.\n", graph->names[origin], graph->names[destination]);
        return;
    }

    printf("\nRota: ");
    for (int i = 0; i < pathSize; i++) {
        if (i > 0) {
            printf(" -> ");
        }
        printf("%s", graph->names[path[i]]);
    }
    printf("\nDistancia total: %i m\n", totalDistance);
}

void verifyBuildingReachability(Graph *graph) {
    int reachability[MAX_BUILDINGS][MAX_BUILDINGS];

    calculateReachability(graph, reachability);

    showBuildings(graph);

    int origin = readBuilding(graph, "\nOrigem (numero ou nome): ");
    if (origin == -1) {
        printf("\nPredio de origem nao encontrado!\n");
        return;
    }
    
    int destination = readBuilding(graph, "Destino (numero ou nome): ");
    if (destination == -1) {
        printf("\nPredio de destino nao encontrado!\n");
        return;
    }

    if(reachability[origin][destination] == 1) {
        printf("\nOs prédios %s e %s estão conectados.\n", graph->names[origin], graph->names[destination]);
    } else {
        printf("\nNao existe caminho entre %s e %s.\n", graph->names[origin], graph->names[destination]);
    }
}

void showReachabilityMatrix(Graph *graph) {
    int reachability[MAX_BUILDINGS][MAX_BUILDINGS];

    calculateReachability(graph, reachability);

    printf("\n========== MATRIZ DE ALCANCABILIDADE ==========\n\n");
    printf("%15s", "");

    for (int column = 0; column < graph->numBuildings; column++) {
        printf("%15s", graph->names[column]);
    }

    printf("\n");

    for (int row = 0; row < graph->numBuildings; row++) {
        printf("%15s", graph->names[row]);

        for (int column = 0; column < graph->numBuildings; column++) {
            printf("%15d", reachability[row][column]);
        }

        printf("\n");
    }

    printf("\n1 - Existe caminho\n");
    printf("0 - Nao existe caminho\n");
}

