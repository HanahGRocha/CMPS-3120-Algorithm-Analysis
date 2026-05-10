#ifndef VORONOI_H
#define VORONOI_H

#include "nodes.h"
#include "clusters.h"
#include "tabulist.h"

void oneMove(std::map<int, std::vector<Node>> &clusters, const std::vector<Node> &chNodes, 
        TabuList &tabulist);


#endif
