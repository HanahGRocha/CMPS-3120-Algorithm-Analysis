#ifndef NODES_H
#define NODES_H

#include <vector>

struct Node {
    int nID;
    double x, y;

    Node(double x_val, double y_val) : nID(-1), x(x_val), y(y_val) {} 

    bool operator==(const Node& other) const {
        return nID == other.nID && x == other.x && y == other.y;
    }

};

double euclindeanDistance(const Node &a, const Node &b);

std::vector<Node> generateNodes(int count, double minX, double maxX, double minY, double maxY);


#endif 
