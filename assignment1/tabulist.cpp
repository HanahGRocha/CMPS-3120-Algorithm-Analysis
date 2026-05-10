#include "tabulist.h"
using namespace std;

TabuList::TabuList(int size) : maxSize(size) {}

void TabuList::addMove(const TabuMove &move) {
    if (tabuQueue.size() >= static_cast<std::queue<TabuMove>::size_type>(maxSize)) tabuQueue.pop();
    tabuQueue.push(move);
}

bool TabuList::isTabu(const TabuMove &move) {
    queue<TabuMove> tempQueue = tabuQueue;
    while (!tempQueue.empty()) {
        TabuMove current = tempQueue.front();
        tempQueue.pop();
        if (current.nodeID == move.nodeID && current.toCluster == move.fromCluster) return true;
    }
    return false;
}

