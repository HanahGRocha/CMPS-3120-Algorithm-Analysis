#include "voronoi.h"
#include <algorithm>
using namespace std;

void oneMove(map<int, vector<Node>> &clusters, const vector<Node> &chNodes, TabuList &tabuList) {
    for (auto &[chId, nodes] : clusters) {
        for (auto &node : nodes) {
            int newCluster = -1;
            double bestReduction = 0;
            for (const auto &ch : chNodes) {
                if (ch.nID != chId) {
                    double oldDistance = euclindeanDistance(node, chNodes[chId]);
                    double newDistance = euclindeanDistance(node, ch);
                    double reduction = oldDistance - newDistance;
                    if (reduction > bestReduction && !tabuList.isTabu({node.nID, chId, ch.nID})) {
                        bestReduction = reduction;
                        newCluster = ch.nID;
                    }
                }
            }
            if (newCluster != -1) {
                clusters[newCluster].push_back(node);
                nodes.erase(remove(nodes.begin(), nodes.end(), node), nodes.end());
                tabuList.addMove({node.nID, chId, newCluster});
                return; // Exit after one move
            }
        }
    }
}

