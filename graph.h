#ifndef GRAPH_H
#define GRAPH_H

#define MAX_BUILDINGS 10
#define NAME_SIZE 30
#define NUM_BUILDINGS 5
#define INFINITE_DISTANCE 999999

typedef struct {
    int numBuildings;
    char names[MAX_BUILDINGS][NAME_SIZE];
    int adj[MAX_BUILDINGS][MAX_BUILDINGS];
} Graph;

void initializeGraph(Graph *graph);
void showMap(Graph *graph);
void showBuildings(Graph *graph);
int findBuildingByName(Graph *graph, char *name);
int findBuildingByNumber(Graph *graph, int number);
int shortestRoute(Graph *graph, int origin, int destination, int path[], int *pathSize);

#endif
