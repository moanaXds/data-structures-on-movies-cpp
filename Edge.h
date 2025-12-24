#include <iostream>

using namespace std;

class Edge {
public:
    int to;
    Edge* next;

    Edge(int nextConnection)
    {
        to = nextConnection;
        next = NULL;
    }
};