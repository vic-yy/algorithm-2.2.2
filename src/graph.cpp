#include "../include/graph.hpp"
#include <iostream>

Graph::Graph() {
    globalSource.setID(0);
    globalSource.setType('a');
    globalSource.setDemand(0);

    edgeMatrix = new int*[MAX_SIZE];
    int i = 0;
    while (i < MAX_SIZE) {
        edgeMatrix[i] = new int[MAX_SIZE];
        int j = 0;
        while (j < MAX_SIZE) {
            edgeMatrix[i][j] = -1;
            j++;
        }
        i++;
    }

    flows = new int*[MAX_SIZE];
    i = 0;
    while (i < MAX_SIZE) {
        flows[i] = new int[MAX_SIZE];
        int j = 0;
        while (j < MAX_SIZE) {
            flows[i][j] = 0;
            j++;
        }
        i++;
    }
    
    globalSink.setID(MAX_SIZE - 1);
    globalSink.setType('b');
    globalSink.setDemand(2000);
    edgeMatrix[0][MAX_SIZE - 1] = -1;
    edgeMatrix[MAX_SIZE - 1][0] = -1;
    flows[0][MAX_SIZE - 1] = 0;
    flows[MAX_SIZE - 1][0] = 0;

    i = 1;
    while (i < MAX_SIZE - 1) {
        active[i] = 0;
        i++;
    }

    active[0] = 1;
    active[MAX_SIZE - 1] = 1;
}

Graph::~Graph() {
    int i = 0;
    while (i < MAX_SIZE) {
        delete[] edgeMatrix[i];
        i++;
    }
    delete[] edgeMatrix;

    i = 0;
    while (i < MAX_SIZE) {
        delete[] flows[i];
        i++;
    }
    delete[] flows;
}

void Graph::setConnection(int source, int sink, int capacity) {
    bool first = false;
    if (edgeMatrix[source][sink] == -1) {
        first = true;
    }
    edgeMatrix[source][sink] = capacity;
    if (edgeMatrix[0][source] != -1 && source != 0 && first) {
        totalGeneration += capacity;
    }
}

void Graph::setReverseConnection(int source, int sink, int capacity) {
    flows[source][sink] = capacity;
}

void Graph::addNode(Node node) {
    if (node.getType() == 'a') {
        setConnection(globalSource.getID(), node.getID(), 20000);
        active[node.getID()] = 1;
    } else if (node.getType() == 'b') {
        setConnection(node.getID(), globalSink.getID(), node.getDemand());
        active[node.getID()] = 1;
    }
}

void Graph::printMatrix() {
    int i = 0;
    while (i < MAX_SIZE) {
        int j = 0;
        while (j < MAX_SIZE) {
            std::cout << edgeMatrix[i][j] << " ";
            j++;
        }
        std::cout << std::endl;
        i++;
    }
}

void Graph::createResidualGraph(Graph* graph, Graph* residualGraph) {
    int i = 0;
    while (i < MAX_SIZE) {
        int j = 0;
        while (j < MAX_SIZE) {
            if (graph->edgeMatrix[i][j] > -1) {
                active[i] = 1;
                active[j] = 1;

                int capacity = graph->edgeMatrix[i][j];
                residualGraph->setConnection(i, j, capacity);
            }
            j++;
        }
        i++;
    }
}

int Graph::getCapacity(int source, int sink) {
    return edgeMatrix[source][sink];
}

int Graph::getReverseCapacity(int source, int sink) {
    return flows[source][sink];
}

Node Graph::getSink() {
    return globalSink;
}

Node Graph::getSource() {
    return globalSource;
}

bool Graph::isActive(int index) {
    return active[index];
}

std::vector<std::pair<int, int>> Graph::getSaturatedEdges() {
    std::vector<std::pair<int, int>> saturated;
    int i = 1;
    while (i < MAX_SIZE - 1) {
        int j = MAX_SIZE - 2;
        while (j >= 1) {
            if (edgeMatrix[i][j] == 0) {
                saturated.push_back({i, j});
            }
            j--;
        }
        i++;
    }
    return saturated;
}

Node Graph::getNode(int index) {
    return vertices[index];
}

int Graph::getTotalGeneration() {
    return totalGeneration;
}
