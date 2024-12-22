#ifndef NODE
#define NODE

class Node {
public:

    bool isSourceNode() const;
    bool isSinkNode() const;
    void reset();
    bool equals(const Node& other) const;
    int calculateNodePriority() const;

    void setID(int id);
    void setType(char type);
    void setDemand(int demand);

    int getID();
    char getType();
    int getDemand();

    Node();
    Node(int id, char type, int demand);

private:
    int x;
    int y;
    int id;
    char type;
    int demand;
};

#endif
