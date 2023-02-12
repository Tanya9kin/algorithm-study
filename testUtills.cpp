#ifndef _UTILS
#define _UTILS

#include "./MyGraph.cpp"
#include "./Vertex.cpp"
#include <iostream>

using namespace std;

// TODO: function that gets a simple representation of a MyGraph and build a MyGraph from it

void builtTree(MyGraph *tree)
{
    cout << "in build MyGraph" << endl;
    Vertex *r1 = tree->addVertex(nullptr, 1);
    Vertex *r2 = tree->addVertex(nullptr, 2);
    Vertex *r3 = tree->addVertex(nullptr, 3);
    cout << "built roots" << endl;
    // first layer
    Vertex *v1r1 = tree->addVertex(r1, 11);
    Vertex *v2r1 = tree->addVertex(r1, 12);
    Vertex *v1r2 = tree->addVertex(r2, 21);
    Vertex *v2r2 = tree->addVertex(r2, 22);
    // second layer
    Vertex *u1v1 = tree->addVertex(v1r1, 111);
    Vertex *u2v1 = tree->addVertex(v1r1, 112);
    Vertex *u1v2 = tree->addVertex(v2r1, 121);
    // third layer
    Vertex *w1u2v1 = tree->addVertex(u2v1, 1121);
}

void buildMyGraph1(MyGraph *graph)
{
    cout << "in build MyGraph" << endl;
    Vertex *r1 = graph->addVertex(nullptr, 1);
    Vertex *r2 = graph->addVertex(nullptr, 2);
    Vertex *r3 = graph->addVertex(nullptr, 3);
    cout << "built roots" << endl;
    // first layer
    Vertex *v1r1 = graph->addVertex(r1, 11);
    Vertex *v2r1 = graph->addVertex(r1, 12);
    Vertex *v1r2 = graph->addVertex(r2, 21);
    Vertex *v2r2 = graph->addVertex(r2, 22);
    // second layer
    Vertex *u1v1 = graph->addVertex(v1r1, 111);
    Vertex *u2v1 = graph->addVertex(v1r1, 112);
    Vertex *u1v2 = graph->addVertex(v2r1, 121);
    // third layer
    Vertex *w1u2v1 = graph->addVertex(u2v1, 1121);

    // adding loops
    graph->addEdge(v1r1, v2r1);
    graph->addEdge(v2r1, r1);
}

// No loops, two parents for v2
// r1->v1->v2 r1->v2
void buildMyGraph2(MyGraph *graph)
{
    Vertex *r1 = graph->addVertex(nullptr, 1);
    Vertex *v1 = graph->addVertex(r1, 11);
    Vertex *v2 = graph->addVertex(r1, 12);

    graph->addEdge(v1, v2);
}

// loop v1->v2->v1
void buildMyGraph3(MyGraph *graph)
{
    Vertex *r1 = graph->addVertex(nullptr, 1);
    Vertex *v1 = graph->addVertex(r1, 11);
    Vertex *v2 = graph->addVertex(r1, 12);

    graph->addEdge(v1, v2);
    graph->addEdge(v2, v1);
}

// loop r1->v1->v2->r1
void buildMyGraph4(MyGraph *graph)
{
    Vertex *r1 = graph->addVertex(nullptr, 1);
    Vertex *v1 = graph->addVertex(r1, 11);
    Vertex *v2 = graph->addVertex(v1, 12);

    graph->addEdge(v2, r1);
}

// r1->v1 r1->v2 v2->v1 v1->v3 v3->r1
// loop r1->v1->v3->r1
void buildMyGraph5(MyGraph *graph)
{
    Vertex *r1 = graph->addVertex(nullptr, 1);
    Vertex *v1 = graph->addVertex(r1, 2);
    Vertex *v2 = graph->addVertex(r1, 3);
    Vertex *v3 = graph->addVertex(v1, 4);

    graph->addEdge(v2, v1);
    graph->addEdge(v3, r1);
}

#endif