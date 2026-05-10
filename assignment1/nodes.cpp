#include "nodes.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;

double euclindeanDistance(const Node &a, const Node &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

vector<Node> generateNodes(int count, double minX, double maxX, double minY, double maxY) {
    vector<Node> nodes;
    srand(time(0)); // Seed for random number generation.
    for (int i = 0; i < count; i++) {
        double x = minX + (rand() / (double)RAND_MAX) * (maxX - minX);
        double y = minY + (rand() / (double)RAND_MAX) * (maxY - minY);
        nodes.push_back(Node(x, y)); // Assuming Node has a constructor taking x, y.
    }
    return nodes;
}


