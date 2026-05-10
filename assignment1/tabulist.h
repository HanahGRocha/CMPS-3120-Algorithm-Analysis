#ifndef TABULIST_H
#define TABULIST_H
#include <queue>

struct TabuMove {
    int nodeID;
    int fromCluster;
    int toCluster;
};


class TabuList{
    private:
        int maxSize;
        std::queue<TabuMove> tabuQueue;

    public:
        explicit TabuList(int size);
        void addMove(const TabuMove &move);
        bool isTabu(const TabuMove &move);
};


#endif
