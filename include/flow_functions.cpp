#include "flow_functions.hpp"
#include <queue>
#include <climits>
#include <algorithm>

// ----------------------------------------------------
// 1) BFS
// ----------------------------------------------------
bool processForwardEdge(Graph* residual, int currentNode, int adjacentNode, int* predecessors, bool* reversed, std::vector<bool>& visited, std::queue<int>& queue, int sinkID) {
    int capacity = residual->getCapacity(currentNode, adjacentNode);
    if (capacity > 0) {
        queue.push(adjacentNode);
        predecessors[adjacentNode] = currentNode;
        reversed[adjacentNode] = false;
        visited[adjacentNode] = true;
        return adjacentNode == sinkID;
    }
    return false;
}

bool processReverseEdge(Graph* residual, int currentNode, int adjacentNode, int* predecessors, bool* reversed, std::vector<bool>& visited, std::queue<int>& queue, int sinkID) {
    int capacity = residual->getReverseCapacity(currentNode, adjacentNode);
    if (capacity > 0) {
        queue.push(adjacentNode);
        predecessors[adjacentNode] = currentNode;
        reversed[adjacentNode] = true;
        visited[adjacentNode] = true;
        return adjacentNode == sinkID;
    }
    return false;
}

bool processAdjacentNodes(Graph* residual, int currentNode, int* predecessors, bool* reversed, std::vector<bool>& visited, std::queue<int>& queue, int sinkID) {
    for (int adjacentNode = 0; adjacentNode < MAX_SIZE; adjacentNode++) {
        if (currentNode == adjacentNode || visited[adjacentNode]) 
            continue;

        if (processForwardEdge(residual, currentNode, adjacentNode, predecessors, reversed, visited, queue, sinkID))
            return true;

        if (processReverseEdge(residual, currentNode, adjacentNode, predecessors, reversed, visited, queue, sinkID))
            return true;
    }
    return false;
}

bool BFS(Graph* residual, int* predecessors, bool* reversed, int sourceID, int sinkID) {
    std::vector<bool> visited(MAX_SIZE, false);
    std::queue<int> queue;
    queue.push(sourceID);
    visited[sourceID] = true;

    while (!queue.empty()) {
        int currentNode = queue.front();
        queue.pop();

        if (processAdjacentNodes(residual, currentNode, predecessors, reversed, visited, queue, sinkID))
            return true;
    }

    return false;
}

// ----------------------------------------------------
// 2) calculatePathFlow
// ----------------------------------------------------
int calculatePathFlow(Graph* residual, int* predecessors, bool* reversed, int sourceID, int sinkID) {
    int minFlow = INT_MAX;

    for (int currentNode = sinkID; currentNode != sourceID; currentNode = predecessors[currentNode]) {
        int previousNode = predecessors[currentNode];

        int availableCapacity = reversed[currentNode] 
            ? residual->getReverseCapacity(previousNode, currentNode) 
            : residual->getCapacity(previousNode, currentNode);

        minFlow = std::min(minFlow, availableCapacity);
    }

    return minFlow;
}

// ----------------------------------------------------
// 3) updateCapacities
// ----------------------------------------------------
void updateCapacities(Graph* residual, int* predecessors, bool* reversed, int pathFlow, int sourceID, int sinkID) {
    for (int currentNode = sinkID; currentNode != sourceID; currentNode = predecessors[currentNode]) {
        int previousNode = predecessors[currentNode];

        if (reversed[currentNode]) {
            // Ajustar capacidade no sentido reverso
            int reverseCapacity = residual->getReverseCapacity(previousNode, currentNode) - pathFlow;
            residual->setReverseConnection(previousNode, currentNode, reverseCapacity);

            // Aumentar capacidade no sentido forward inverso
            int forwardCapacity = residual->getCapacity(currentNode, previousNode) + pathFlow;
            residual->setConnection(currentNode, previousNode, forwardCapacity);
        } else {
            // Reduzir capacidade no sentido forward
            int forwardCapacity = residual->getCapacity(previousNode, currentNode) - pathFlow;
            residual->setConnection(previousNode, currentNode, forwardCapacity);

            // Ajustar capacidade no sentido reverso
            int reverseCapacity = residual->getReverseCapacity(currentNode, previousNode) + pathFlow;
            residual->setReverseConnection(currentNode, previousNode, reverseCapacity);
        }
    }
}

// ----------------------------------------------------
// 4) fordFulkerson
// ----------------------------------------------------
int fordFulkerson(Graph* residualGraph, Node source, Node sink) {
    int maxFlow = 0;
    int predecessors[MAX_SIZE];
    bool reversed[MAX_SIZE];

    while (true) {
        std::fill(predecessors, predecessors + MAX_SIZE, -1);
        std::fill(reversed, reversed + MAX_SIZE, false);

        // Executa BFS para encontrar um caminho aumentante
        if (!BFS(residualGraph, predecessors, reversed, source.getID(), sink.getID())) {
            break; 
        }

        // Calcula gargalo (pathFlow)
        int pathFlow = calculatePathFlow(residualGraph, predecessors, reversed, source.getID(), sink.getID());

        // Atualiza as capacidades no grafo residual
        updateCapacities(residualGraph, predecessors, reversed, pathFlow, source.getID(), sink.getID());

        // Soma ao fluxo máximo
        maxFlow += pathFlow;
    }

    return maxFlow;
}
