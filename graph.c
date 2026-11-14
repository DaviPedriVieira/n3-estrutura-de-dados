#include <stdio.h>
#include <ctype.h>

#include "graph.h"

void initializeGraph(Graph *graph) {
    Graph initial = {
        NUM_BUILDINGS,
        {
            "Refeitorio",
            "Biblioteca",
            "Bloco A",
            "Laboratorio",
            "Bloco B"
        },
        {
            {    0, 280, 190,   0,   0 },
            {  280,   0, 160,   0,   0 },
            {  190, 160,   0, 210,   0 },
            {    0,   0, 210,   0, 240 },
            {    0,   0,   0, 240,   0 }
        }
    };

    *graph = initial;
}

void showMap(Graph *graph) {
    printf("\n===== MAPA DO CAMPUS =====\n\n");

    for (int i = 0; i < graph->numBuildings; i++)
    {
        for (int j = 0; j < graph->numBuildings; j++)
        {
            if(graph->adj[i][j] == 0) continue;

            printf("%s <-> %s: %im \n", graph->names[i], graph->names[j], graph->adj[i][j]);
        }
    }
}

void showBuildings(Graph *graph) {
    printf("\nPredios:\n");
    for (int i = 0; i < graph->numBuildings; i++) {
        printf("  %i - %s\n", i, graph->names[i]);
    }
}

int reachedEndOfText(char *text) {
    return *text == '\0';
}

int compareNames(char *name1, char *name2) {
    while (!reachedEndOfText(name1) && !reachedEndOfText(name2)) {
        if (tolower(*name1) != tolower(*name2)) return 0;

        name1++;
        name2++;
    }

    return *name1 == *name2;
}

int findBuildingByName(Graph *graph, char *name) {
    for (int i = 0; i < graph->numBuildings; i++) {
        if (compareNames(graph->names[i], name)) {
            return i;
        }
    }
    return -1;
}

int findBuildingByNumber(Graph *graph, int number) {
    if (number >= 0 && number < graph->numBuildings) return number;
    return -1;
}

int findClosestUnvisited(Graph *graph, int distances[], int visited[]) {
    int closest = -1;
    for (int i = 0; i < graph->numBuildings; i++) {
        if (!visited[i] && distances[i] != INFINITE_DISTANCE && (closest == -1 || distances[i] < distances[closest])) {
            closest = i;
        }
    }
    return closest;
}

void dijkstra(Graph *graph, int origin, int distances[], int previous[]) {
    int visited[MAX_BUILDINGS];

    // 1. Inicializacao
    for (int i = 0; i < graph->numBuildings; i++) {
        distances[i] = INFINITE_DISTANCE;
        visited[i] = 0;
        previous[i] = -1;
    }

    distances[origin] = 0;

    // 2. A cada rodada, fecha o predio nao visitado mais proximo
    for (int i = 0; i < graph->numBuildings; i++) {
        int closest = findClosestUnvisited(graph, distances, visited);
        if (closest == -1) break;

        visited[closest] = 1;

        // 3. Para cada vizinho, verifica se passar pelo predio mais proximo encurta o caminho ate ele e, se encurtar, atualiza a distancia e o anterior
        for (int j = 0; j < graph->numBuildings; j++) {
            int distanceToNeighbor = graph->adj[closest][j];
            if (distanceToNeighbor > 0 && !visited[j] && distances[closest] + distanceToNeighbor < distances[j]) {
                distances[j] = distances[closest] + distanceToNeighbor;
                previous[j] = closest;
            }
        }
    }
}

void buildPath(int previous[], int destination, int path[], int *pathSize) {
    *pathSize = 0;

    // 4. Monta o caminho do destino ate a origem
    for (int building = destination; building != -1; building = previous[building]) {
        path[*pathSize] = building;
        (*pathSize)++;
    }

    // 5. Inverte para ficar da origem ao destino
    for (int i = 0; i < *pathSize / 2; i++) {
        int end = *pathSize - 1 - i;
        int aux = path[i];

        path[i] = path[end];
        path[end] = aux;
    }
}

int shortestRoute(Graph *graph, int origin, int destination, int path[], int *pathSize) {
    int distances[MAX_BUILDINGS];
    int previous[MAX_BUILDINGS];

    dijkstra(graph, origin, distances, previous);

    if (distances[destination] == INFINITE_DISTANCE) return -1;

    buildPath(previous, destination, path, pathSize);

    return distances[destination];
}
