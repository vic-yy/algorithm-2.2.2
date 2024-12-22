#include "../include/node.hpp"


void Node::reset() {
    id = -1;
    type = ' ';
    demand = -1;
}

bool Node::equals(const Node& other) const {
    return id == other.id && type == other.type && demand == other.demand;
}

int Node::calculateNodePriority() const {
    return demand > 0 ? demand * id : id * -1;
}

Node::Node() {
    id = -1;
    type = ' ';
    demand = -1;
}

Node::Node(int id, char type, int demand) {
    this->id = id;
    this->type = type;
    this->demand = demand;
}

void Node::setID(int id) {
    this->id = id;
}

int Node::getID() {
    return id;
}

void Node::setType(char type) {
    this->type = type;
}

char Node::getType() {
    return type;
}

bool Node::isSourceNode() const {
    return type == 'a';
}

bool Node::isSinkNode() const {
    return type == 'b';
}

void Node::setDemand(int demand) {
    this->demand = demand;
}

int Node::getDemand() {
    return demand;
}
