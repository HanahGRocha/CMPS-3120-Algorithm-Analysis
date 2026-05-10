#include "clusters.h"
#include <cfloat>
#include <cmath>
#include <algorithm>
using namespace std;

map<int, vector<Node>> Cluster::AssignToClusters(const vector<Node> &leNodes, 
        const vector<Node> &chNodes) {
    map<int, vector<Node>> clusters;
    for (const auto &le : leNodes) {
        int closestCH = -1;
        double minDistance = DBL_MAX;
        for (const auto &ch : chNodes) {
            double dist = euclindeanDistance(le, ch);
            if (dist < minDistance) {
                minDistance = dist;
                closestCH = ch.nID;
            }
        }
        clusters[closestCH].push_back(le);
    }
    return clusters;
}

int Cluster::computeHopCount(double distance, double transmissionRange) {
    if (transmissionRange <= 0) return -1; // Avoid division by zero.
    return static_cast<int>(ceil(distance / transmissionRange));
}

