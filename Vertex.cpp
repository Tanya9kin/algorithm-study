#ifndef _VERTEX_CLASS
#define _VERTEX_CLASS

#include <set>
#include <iostream>
#include "./MyGraph.cpp"

using namespace std;

/*
    using set for parents and children to ensure there are no duplicates of edges
*/
class Vertex
{
    friend class MyGraph;

    int id;
    int data;
    set<Vertex *> parents;
    set<Vertex *> children;
    bool visited;

    Vertex *addChild(Vertex *child);

    void removeChild(Vertex *child);

    void removeParent(Vertex *parent);

    void addParent(Vertex *parent);

    bool orphan();

public:
    Vertex(int id, int data) : id(id), data(data), children(), parents(), visited(false){};

    bool isLeaf();

    int getData();
};

// NOTE: set.erase(element) returns an integer indicating how many elements have been erased
// because set has only unique values, it returns either 0 or 1
void Vertex::removeChild(Vertex *child)
{
    this->children.erase(child);
}

void Vertex::removeParent(Vertex *parent)
{
    this->parents.erase(parent);
}

bool Vertex::isLeaf()
{
    return children.empty();
}

int Vertex::getData()
{
    return data;
}

Vertex *Vertex::addChild(Vertex *child)
{
    children.insert(child);
    return child;
}

void Vertex::addParent(Vertex *parent)
{
    this->parents.insert(parent);
}

bool Vertex::orphan()
{
    return parents.empty();
}

void printVertex(Vertex *vertex)
{
    cout << "vertex data is: " << vertex->getData() << endl;
}

#endif