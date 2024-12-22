#include <iostream>
#include "../include/flow_functions.hpp"
#include "../include/flow_functions.cpp"

// Declarações de constantes/defines
#ifndef MAX_SIZE
#endif

// ------------------- DECLARAÇÃO DAS FUNÇÕES AUXILIARES -------------------
void initCapacities(int**& capacities);
void readInput(int& numNodes, int& numEdges);
void readNodes(int numNodes, int& totalDemand, Graph& powerGrid, Graph& residualGraph);
void readEdges(int numEdges, Graph& powerGrid, Graph& residualGraph, int** capacities);
int computeMaxFlow(Graph& powerGrid, Graph& residualGraph, int totalDemand, int** capacities);
void cleanupCapacities(int** capacities);

// --------------------------- FUNÇÃO PRINCIPAL ----------------------------
int main() {
    int numNodes = 0;
    int numEdges = 0;
    int totalDemand = 0;

    // Criação dos grafos
    Graph powerGrid;
    Graph residualGraph;

    // Alocação dinâmica da matriz capacities
    int** capacities;
    initCapacities(capacities);

    // 1) Ler quantidades de nós e arestas
    readInput(numNodes, numEdges);

    // 2) Ler nós e calcular demanda total
    readNodes(numNodes, totalDemand, powerGrid, residualGraph);

    // 3) Ler arestas
    readEdges(numEdges, powerGrid, residualGraph, capacities);

    // 4) Calcular fluxo máximo e mostrar resultados
    computeMaxFlow(powerGrid, residualGraph, totalDemand, capacities);

    // 5) Liberar memória
    cleanupCapacities(capacities);

    return 0;
}

// -------------------------- IMPLEMENTAÇÕES -------------------------------

// 1) Inicializar a matriz de capacidades
void initCapacities(int**& capacities) {
    capacities = new int*[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        capacities[i] = new int[MAX_SIZE];
        for (int j = 0; j < MAX_SIZE; j++) {
            capacities[i][j] = -1;
        }
    }
}

// 2) Ler valores de entrada básicos: número de nós e arestas
void readInput(int& numNodes, int& numEdges) {
    std::cin >> numNodes >> numEdges;
}

// 3) Ler os nós, atribuir tipo e demanda, adicionar aos grafos, bem como acumular demanda total
void readNodes(int numNodes, int& totalDemand, Graph& powerGrid, Graph& residualGraph) {
    for (int i = 0; i < numNodes; i++) {
        int id, demand;
        char type;

        std::cin >> id >> demand;
        totalDemand += demand;
        type = (demand == 0) ? 'a' : 'b';

        Node node(id, type, demand);
        powerGrid.addNode(node);
        residualGraph.addNode(node);
    }
}

// 4) Ler as arestas e preencher as conexões no grafo e na matriz capacities
void readEdges(int numEdges, Graph& powerGrid, Graph& residualGraph, int** capacities) {
    for (int i = 0; i < numEdges; i++) {
        int source, sink, capacity;
        std::cin >> source >> sink >> capacity;

        powerGrid.setConnection(source, sink, capacity);
        residualGraph.setConnection(source, sink, capacity);
        capacities[source][sink] = capacity;
    }
}

// 5) Calcular o fluxo máximo e imprimir todos os resultados
int computeMaxFlow(Graph& powerGrid, Graph& residualGraph, int totalDemand, int** capacities) {
    // Cálculo do Ford-Fulkerson
    int maxFlow = fordFulkerson(&residualGraph, powerGrid.getSource(), powerGrid.getSink());

    // Impressão dos resultados
    std::cout << maxFlow << std::endl;
    std::cout << (totalDemand - maxFlow) << std::endl;
    std::cout << (residualGraph.getTotalGeneration() - maxFlow) << std::endl;

    // Encontrar arestas saturadas
    std::vector<std::pair<int, int>> saturatedEdges = residualGraph.getSaturatedEdges();
    std::cout << saturatedEdges.size() << std::endl;

    // Enquanto houver arestas saturadas, imprimir a de maior capacidade e remover do vetor
    while (!saturatedEdges.empty()) {
        int highestCapacity = 0;
        int bestSource = -1, bestSink = -1;
        size_t indexOfHighest = 0;

        for (size_t index = 0; index < saturatedEdges.size(); ++index) {
            int i = saturatedEdges[index].first;
            int j = saturatedEdges[index].second;
            if (capacities[i][j] > highestCapacity) {
                highestCapacity = capacities[i][j];
                bestSource = i;
                bestSink = j;
                indexOfHighest = index;
            }
        }

        if (bestSource != -1 && bestSink != -1) {
            std::cout << bestSource << " " << bestSink << " " << highestCapacity << std::endl;
        }

        saturatedEdges.erase(saturatedEdges.begin() + indexOfHighest);
    }

    return maxFlow;
}

// 6) Liberar a memória alocada para a matriz capacities
void cleanupCapacities(int** capacities) {
    for (int i = 0; i < MAX_SIZE; i++) {
        delete[] capacities[i];
    }
    delete[] capacities;
}
