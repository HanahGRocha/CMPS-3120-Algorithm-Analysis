#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
};

// Helper function to generate random points
vector<Point> generateRandomPoints(int numPoints, double maxX, double maxY) {
    vector<Point> points;
    for (int i = 0; i < numPoints; ++i) {
        points.push_back({rand() % static_cast<int>(maxX), rand() % static_cast<int>(maxY)});
    }
    return points;
}

// Helper function to calculate Euclidean distance
double euclideanDistance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Move structure to hold info for each move in the neighborhood
struct Move {
    size_t nodeIndex;  
    size_t oldCluster; 
    size_t newCluster; 
    int hopCountChange;
};

class TabuSearch {
public:
    TabuSearch(const vector<Point>& nodes, const vector<Point>& clusterHeads, double hopThreshold, int maxIterations)
        : nodes(nodes), clusterHeads(clusterHeads), hopThreshold(hopThreshold), maxIterations(maxIterations) {
        assignments = assignNodesToClustersAndCollectData(nodes, clusterHeads, hopThreshold);
    }

    // Function to perform the Tabu Search
    void optimize() {
        int iteration = 0;
        int bestHopCount = calculateTotalHopCount();
        vector<pair<int, int>> bestAssignments = assignments;

        while (iteration < maxIterations) {
            vector<Move> neighborhood = generateNeighborhood();
            Move bestMove = findBestMove(neighborhood);
            
            if (bestMove.hopCountChange < 0) {
                // Apply the best move
                assignments[bestMove.nodeIndex].first = bestMove.newCluster;
                bestHopCount += bestMove.hopCountChange;
            }
            iteration++;

            // Update the best solution
            if (calculateTotalHopCount() < bestHopCount) {
                bestHopCount = calculateTotalHopCount();
                bestAssignments = assignments;
            }

            // Update the Tabu list and neighbor
            tabuList.push_back(bestMove);
            if (tabuList.size() > tabuListSize) {
                tabuList.erase(tabuList.begin());
            }
        }

        // Output the optimized assignments
        cout << "\nOptimized Node Assignments and Hop Counts:\n";
        for (size_t i = 0; i < nodes.size(); ++i) {
            cout << "Node " << i << ": (" << nodes[i].x << ", " << nodes[i].y << ") -> CH "
                 << assignments[i].first << " with " << assignments[i].second << " hops\n";
        }
    }

private:
    vector<Point> nodes;
    vector<Point> clusterHeads;
    double hopThreshold;
    int maxIterations;
    int tabuListSize = 10; // Max size tabulist
    vector<pair<int, int>> assignments;
    vector<Move> tabuList;

    // Function to assign nodes to clusters and calculate hop counts - 1st assignment
    vector<pair<int, int>> assignNodesToClustersAndCollectData(const vector<Point>& nodes, const vector<Point>& clusterHeads, double hopThreshold) {
        vector<pair<int, int>> nodeAssignments;
        for (size_t i = 0; i < nodes.size(); ++i) {
            // Find the closest cluster head to the node
            size_t closestCluster = 0;
            double minDistance = euclideanDistance(nodes[i], clusterHeads[0]);
            for (size_t j = 1; j < clusterHeads.size(); ++j) {
                double distance = euclideanDistance(nodes[i], clusterHeads[j]);
                if (distance < minDistance) {
                    closestCluster = j;
                    minDistance = distance;
                }
            }
            // Assign node to the closest cluster
            int hopCount = static_cast<int>(minDistance / hopThreshold);
            nodeAssignments.push_back({closestCluster, hopCount});
        }
        return nodeAssignments;
    }

    // Function to calculate the total hop count
    int calculateTotalHopCount() {
        int totalHopCount = 0;
        for (const auto& assignment : assignments) {
            totalHopCount += assignment.second;
        }
        return totalHopCount;
    }

    // Function to generate neighborhood outputs
    vector<Move> generateNeighborhood() {
        vector<Move> neighborhood;
        
        // Single Move
        for (size_t i = 0; i < assignments.size(); ++i) {
            for (size_t j = 0; j < clusterHeads.size(); ++j) {
                if (assignments[i].first != j) {
                    size_t oldCluster = assignments[i].first;
                    assignments[i].first = j;
                    int newHopCount = static_cast<int>(euclideanDistance(nodes[i], clusterHeads[j]) / hopThreshold);
                    int hopCountChange = newHopCount - assignments[i].second;
                    neighborhood.push_back({i, oldCluster, j, hopCountChange});
                    assignments[i].first = oldCluster; // revert the change
                }
            }
        }
        
        // Pairwise Exchange - adjacent clusters
        for (size_t i = 0; i < clusterHeads.size() - 1; ++i) {
            for (size_t j = i + 1; j < clusterHeads.size(); ++j) {
                for (size_t node1 = 0; node1 < nodes.size(); ++node1) {
                    for (size_t node2 = 0; node2 < nodes.size(); ++node2) {
                        if (assignments[node1].first == i && assignments[node2].first == j) {
                            swap(assignments[node1].first, assignments[node2].first);
                            int hopCountChange1 = static_cast<int>(euclideanDistance(nodes[node1], clusterHeads[i]) / hopThreshold) 
                                                - assignments[node1].second;
                            int hopCountChange2 = static_cast<int>(euclideanDistance(nodes[node2], clusterHeads[j]) / hopThreshold) 
                                                - assignments[node2].second;
                            neighborhood.push_back({node1, i, j, hopCountChange1});
                            neighborhood.push_back({node2, j, i, hopCountChange2});
                            swap(assignments[node1].first, assignments[node2].first); // revert the swap
                        }
                    }
                }
            }
        }

        return neighborhood;
    }

    // Function to find the best move in the neighborhood that reduces hop count
    Move findBestMove(const vector<Move>& neighborhood) {
               Move bestMove = {0, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), std::numeric_limits<int>::max()};

        for (const auto& move : neighborhood) {
            // Avoid Tabu moves
            if (findTabu(move)) continue;
            
            if (move.hopCountChange < bestMove.hopCountChange) {
                bestMove = move;
            }
        }
        return bestMove;
    }

    // Function to check if a move is in the Tabu list
    bool findTabu(const Move& move) {
        for (const auto& tabuMove : tabuList) {
            if (tabuMove.nodeIndex == move.nodeIndex && tabuMove.newCluster == move.newCluster) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    srand(time(0));  // Set random seed for reproduction

    const int numClusterHeads = 5;
    const int numNodes = 50;
    const double planeSize = 100.0;
    const double hopThreshold = 10.0;
    const int maxIterations = 100;

    vector<Point> clusterHeads = generateRandomPoints(numClusterHeads, planeSize, planeSize);
    vector<Point> nodes = generateRandomPoints(numNodes, planeSize, planeSize);

    TabuSearch tabuSearch(nodes, clusterHeads, hopThreshold, maxIterations);
    tabuSearch.optimize();

    return 0;
}

