#include <iostream>
#include <vector>
#include "nodes.h"
#include "clusters.h"
#include "tabulist.h"
#include "voronoi.h"
using namespace std;

int main() {
    const int numCHs = 5, numLENodes = 50, tabuSize = 10;
    const double minX = 0, maxX = 100, minY = 0, maxY = 100, transmissionRange = 10;

    // Generate nodes
    vector<Node> chNodes = generateNodes(numCHs, minX, maxX, minY, maxY);
    vector<Node> leNodes = generateNodes(numLENodes, minX, maxX, minY, maxY);

    // Create Voronoi diagram
    Cluster clusterManager;
    map<int, vector<Node>> clusters = clusterManager.AssignToClusters(leNodes, chNodes);

    // Initialize Tabu List
    TabuList tabuList(tabuSize);

    // Perform optimization
    for (int iteration = 0; iteration < 100; ++iteration) {
        oneMove(clusters, chNodes, tabuList);
    }

    cout << "Optimization completed." << endl;
    return 0;
}

