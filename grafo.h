#ifndef GRAFO_H
#define GRAFO_H

#define MAX_PREDIOS 10
#define TAM_NOME 30
#define NUM_PREDIOS 5

typedef struct {
    int numPredios;
    char nomes[MAX_PREDIOS][TAM_NOME];
    int adj[MAX_PREDIOS][MAX_PREDIOS];
} Grafo;

void inicializarGrafo(Grafo *grafo);
void exibirMapa(Grafo *grafo);

#endif
