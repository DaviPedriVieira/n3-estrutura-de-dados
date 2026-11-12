#include <stdio.h>

#include "grafo.h"

void inicializarGrafo(Grafo *grafo) {
    Grafo inicial = {
        NUM_PREDIOS,
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

    *grafo = inicial;
}

void exibirMapa(Grafo *grafo) {
    printf("\n===== MAPA DO CAMPUS =====\n\n");

    for (int i = 0; i < grafo->numPredios; i++)
    {
        for (int j = 0; j < grafo->numPredios; j++)
        {
            if(grafo->adj[i][j] == 0) continue;

            printf("%s <-> %s: %dm \n", grafo->nomes[i], grafo->nomes[j], grafo->adj[i][j]);
        }
    }
}