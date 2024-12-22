#ifndef FLOW_FUNCTIONS_HPP
#define FLOW_FUNCTIONS_HPP

#include "../include/graph.hpp"

bool BFS(Graph* residual, int* predecessors, bool* reversed, int sourceID, int sinkID);
int calculatePathFlow(Graph* residual, int* predecessors, bool* reversed, int sourceID, int sinkID);
void updateCapacities(Graph* residual, int* predecessors, bool* reversed, int pathFlow, int sourceID, int sinkID);
int fordFulkerson(Graph* residualGraph, Node source, Node sink);

#endif 
