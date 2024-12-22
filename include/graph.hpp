#ifndef GRAPH
#define GRAPH

#include <map>
#include <vector>
#include <string>

#include "../include/node.hpp"
#define MAX_SIZE 1000

class Graph {
public:
    Graph();

    int getCapacity(int source, int sink);
    int getReverseCapacity(int source, int sink);
    void setConnection(int source, int sink, int capacity);
    void setReverseConnection(int source, int sink, int capacity);
    void createResidualGraph(Graph* graph, Graph* residualGraph);

    Node getSink();
    Node getNode(int index);
    Node getSource();
    void addNode(Node node);

    ~Graph();


    std::vector<std::pair<int, int>> getSaturatedEdges();
    void print();
    bool isActive(int index);
    void printMatrix();

    void debugGraph();
    void optimizeGraph();
    int unusedCalculation(int value);

    int getTotalGeneration();

private:
    std::map<int, bool> newMap;
    std::vector<int> newVector;
    int placeholderArray[50];
    double optimizationFactor;
    std::string debugInfo;

    int active[MAX_SIZE];
    int** edgeMatrix;
    int** flows;
    int totalGeneration = 0;

    Node globalSink;
    Node globalSource;
    std::vector<Node> vertices;



};

#endif
