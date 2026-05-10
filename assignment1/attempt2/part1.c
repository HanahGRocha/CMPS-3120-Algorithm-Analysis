#include <iostream>
#include <vector>    // For using the vector container
#include <cmath>     // For math functions like sqrt and pow
#include <cstdlib>   // For random number generation
#include <limits>    // For limits of large/small values
#include <utility>   // Functions
using namespace std;


/* Structure to represent a point in a 2D plane with x and y coordinates */
struct Point {
    double x, y;
};

/* Function to calculate Euclidean distance between two points */
double euclideanDistance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
/*assign closest cluster head a node and collect hops of those assignments*/
vector<pair<int, int>> assignNodesToClustersAndCollectData(const vector<Point>& nodes, const vector<Point>& clusterHeads, double hopThreshold) {
    vector<pair<int, int>> assignments(nodes.size());
    // Pair of (nearestCluster, hopCount) for each node
    for (size_t i = 0; i < nodes.size(); ++i) {
        double minDistance = numeric_limits<double>::max();
        int nearestCluster = -1;
        int hopCount = 0;  // Initialize hop count

        for (size_t j = 0; j < clusterHeads.size(); ++j) {
            double distance = euclideanDistance(nodes[i], clusterHeads[j]);
            if (distance < minDistance) {
                minDistance = distance;
                nearestCluster = j;
                hopCount = static_cast<int>(distance / hopThreshold); // Calculate hop count based on distance
            }
        }
        assignments[i] = make_pair(nearestCluster, hopCount);  // Store the nearest cluster and hop count
    }
    return assignments;
}

/* Function to generate random points within a 2D plane */
vector<Point> generateRandomPoints(int numPoints, double maxX, double maxY) {
    vector<Point> points(numPoints);

    for (int i = 0; i < numPoints; ++i) {
        points[i].x = static_cast<double>(rand()) / RAND_MAX * maxX;
        points[i].y = static_cast<double>(rand()) / RAND_MAX * maxY;
    }
    return points;
}

int main() {
    const int numClusterHeads = 5; // Number of Cluster Heads
    const int numNodes = 50;       // Number of nodes
    const double planeSize = 100.0; // Size of the 2D plane
    const double hopThreshold = 10.0;  // Threshold distance for hop count

    // Generate random positions for cluster heads in the 2D plane
    vector<Point> clusterHeads = generateRandomPoints(numClusterHeads, planeSize, planeSize);

    // Generate random positions for low-end nodes in the 2D plane
    vector<Point> nodes = generateRandomPoints(numNodes, planeSize, planeSize);

    // Assign each node to the nearest cluster head and collect hop counts
    vector<pair<int, int>> assignments = assignNodesToClustersAndCollectData(nodes, clusterHeads, hopThreshold);

    // Output the positions of the cluster heads
    cout << "Cluster Heads:\n";
    for (size_t i = 0; i < clusterHeads.size(); ++i) {
        cout << "CH " << i << ": (" << clusterHeads[i].x << ", " << clusterHeads[i].y << ")\n";
    }

    // Output the node assignments and hop counts
    cout << "\nNode Assignments and Hop Counts:\n";
    for (size_t i = 0; i < nodes.size(); ++i) {
        cout << "Node " << i << ": (" << nodes[i].x << ", " << nodes[i].y << ") -> CH " 
            << assignments[i].first << " with " << assignments[i].second << " hops\n";
    }

    return 0;
}
