#ifndef CLUSTERS_H
#define CLUSTERS_H


#include <vector>
#include <map>
#include "nodes.h"

class Cluster {
    public:
        std::map<int, std::vector<Node>> AssignToClusters(const std::vector<Node> &leNodes, 
                const std::vector<Node> &chNodes);
    
        int computeHopCount(double distance, double transmissionRange);


};


#endif
