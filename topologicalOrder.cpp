#include "./testUtills.cpp"
#include <iostream>
#include "./MyGraph.cpp"

using namespace std;

int main()
{
    MyGraph graph1; // tree
    builtTree(&graph1);

    MyGraph graph2; // this doesnt work
    buildMyGraph2(&graph2);

    MyGraph graph3;
    buildMyGraph3(&graph3);

    MyGraph graph4;
    buildMyGraph4(&graph4);

    MyGraph graph5;
    buildMyGraph5(&graph5);

    cout << "graph1 shuold be DAG, actually: " << (graph1.checkDAG() ? "DAG" : "not DAG") << endl;
    cout << "graph2 shuold be DAG, actually: " << (graph2.checkDAG() ? "DAG" : "not DAG") << endl;
    cout << "graph3 shuold be not DAG, actually: " << (graph3.checkDAG() ? "DAG" : "not DAG") << endl;
    cout << "graph4 shuold be not DAG, actually: " << (graph4.checkDAG() ? "DAG" : "not DAG") << endl;
    cout << "graph5 shuold be not DAG, actually: " << (graph5.checkDAG() ? "DAG" : "not DAG") << endl;

    cout << " topological order on tree: " << endl;
    graph1.topologicalOrderPrint();
    cout << "topological order on graph2: " << endl;
    graph2.topologicalOrderPrint();
}