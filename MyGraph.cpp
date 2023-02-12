#ifndef _MYGRAPH_CLASS
#define _MYGRAPH_CLASS

#include <set>
#include <iostream>
#include <stack>
#include <queue>
#include <map>
#include "./Vertex.cpp"

using namespace std;

// template <typename T>
class MyGraph
{
    int idCounter;
    int size;
    // placeholder root to hold all sub raph
    Vertex *root;
    // set of vertexes for operations on all vertexes
    set<Vertex *> vertexSet;

    void resetVisited();

public:
    MyGraph();

    ~MyGraph();

    Vertex *addVertex(Vertex *parent, int data);

    void removeVertex(Vertex *vertex);

    void addEdge(Vertex *parent, Vertex *child);

    void recursiveDFS(Vertex *currRoot, void (*func)(Vertex *));

    void iterativeDFS(void (*func)(Vertex *));

    void recursiveBFS(void (*func)(Vertex *));

    void auxRecursiveBFS(queue<Vertex *> *queue, void (*func)(Vertex *));

    void iterativeBFS(void (*func)(Vertex *));

    void printMyGraphDFS(bool type);

    void printMyGraphBFS(bool type);

    bool checkDAG();

    void checkPossibleLoop(Vertex *child, Vertex *parent, bool &exists);

    void topologicalOrder(stack<int> &helperStack, Vertex *currRoot);

    void topologicalOrderPrint();
};

MyGraph::MyGraph()
{
    idCounter = 0;
    size = 0;
    root = new Vertex(0, 0); // only vertex with 0 as id
}

MyGraph::~MyGraph()
{
    for (auto const vertex : vertexSet)
    {
        delete vertex;
    }
}

void MyGraph::resetVisited()
{
    root->visited = false;
    for (auto const vertex : vertexSet)
    {
        vertex->visited = false;
    }
}

Vertex *MyGraph::addVertex(Vertex *parent, int data)
{
    Vertex *newVertex = new Vertex(++idCounter, data);

    if (parent != nullptr)
    {
        parent->addChild(newVertex); // note: need to deal with case of too much vertexes (> MAX_INT)
        newVertex->addParent(parent);
    }
    else if (parent == nullptr || parent == root)
    {
        root->addChild(newVertex);
    }
    vertexSet.insert(vertexSet.end(), newVertex);
    size++;
    return newVertex;
}

/*
 * remove vertex from its parents children list
 * remove vertex as the parent of its children (make them the imidiate children of root)
 * delete the vertex itself (clearing all memory from it)
 */
// Q: is it even possible to pass the root as input into this function? for now it isn't
// NOTE: this is not best practice function, some functionality should be moved to Vertex class
void MyGraph::removeVertex(Vertex *vertex)
{
    if (vertex == nullptr || vertex == root)
        return; // note: should throw exception instead

    for (auto child : vertex->children)
    {
        child->removeParent(vertex);
        if (child->orphan())
        {
            root->addChild(child);
            // this child has no parent, so not adding root as a parent
        }
    }
    for (auto parent : vertex->parents)
    {
        parent->removeChild(vertex);
    }
    vertexSet.erase(vertex);
    delete vertex;
    size--;
}

void MyGraph::recursiveDFS(Vertex *currRoot, void (*func)(Vertex *))
{
    currRoot->visited = true;

    if (currRoot != root)
    {
        func(currRoot);
    }

    for (auto child : currRoot->children)
    {
        if (!child->visited)
        {
            recursiveDFS(child, func);
        }
    }
}

void MyGraph::iterativeDFS(void (*func)(Vertex *))
{
    stack<Vertex *> toVisit;
    Vertex *current;
    for (auto const rootChild : root->children)
    {
        toVisit.push(rootChild);
    }

    while (!toVisit.empty())
    {
        current = toVisit.top();
        toVisit.pop();
        // this if is reached with true when there are two parent for current
        if (current->visited)
        {
            continue;
        }
        func(current);
        current->visited = true;
        for (auto const child : current->children)
        {
            if (!child->visited)
                toVisit.push(child);
        }
    }
}

void MyGraph::iterativeBFS(void (*func)(Vertex *))
{
    queue<Vertex *> toVisit;
    Vertex *current = root;
    toVisit.push(current);

    while (!toVisit.empty())
    {
        current = toVisit.front();
        toVisit.pop();
        if (current->visited)
        {
            continue;
        }
        if (current != root)
        {
            func(current);
        }
        current->visited = true;
        for (auto const child : current->children)
        {
            if (!child->visited)
                toVisit.push(child);
        }
    }
}

// NOTE : now it goes through all the roots one by one
void MyGraph::recursiveBFS(void (*func)(Vertex *))
{
    queue<Vertex *> queue;
    root->visited = true;
    for (auto const child : root->children)
    {
        queue.push(child);
    }
    auxRecursiveBFS(&queue, func);
}

void MyGraph::auxRecursiveBFS(queue<Vertex *> *queue, void (*func)(Vertex *))
{
    if (queue->empty())
        return;
    Vertex *current = queue->front();
    queue->pop();
    func(current);
    for (auto const child : current->children)
    {
        if (!child->visited)
        {
            child->visited = true;
            queue->push(child);
        }
    }
    auxRecursiveBFS(queue, func);
}

void MyGraph::printMyGraphDFS(bool type)
{
    if (type == false)
        recursiveDFS(root, &printVertex);
    else
        iterativeDFS(&printVertex);

    resetVisited();
}

void MyGraph::printMyGraphBFS(bool type)
{
    if (!type)
        recursiveBFS(&printVertex);
    else
        iterativeBFS(&printVertex);

    resetVisited();
}

// addEdge allows the MyGraph to become a general MyGraph and not just a set of trees
// might add a loop
void MyGraph::addEdge(Vertex *parent, Vertex *child)
{
    if (parent != nullptr && child != nullptr)
    {
        child->addParent(parent);
        parent->addChild(child);
    }
}

bool MyGraph::checkDAG()
{
    stack<Vertex *> toVisit;
    Vertex *current = root;
    toVisit.push(current);

    map<Vertex *, Vertex *> possibleLoops;

    while (!toVisit.empty())
    {
        current = toVisit.top();
        toVisit.pop();

        // if a vertex has two parents, it will be added to the stack twice.
        // on the second time it would have been seen already, so continue.
        if (current->visited)
        {
            continue;
        }
        current->visited = true;
        for (auto const child : current->children)
        {
            if (!child->visited)
            {
                toVisit.push(child);
            }
            else
            {
                // write down the possible loop (and check it later via DFS from child, to see if current is reachable)
                possibleLoops.insert({child, current});
            }
        }
    }

    resetVisited();

    bool loopExists = false;
    for (auto const pair : possibleLoops)
    {
        checkPossibleLoop(pair.first, pair.second, loopExists);
        resetVisited();
        if (loopExists == true)
        {
            break;
        }
    }

    return !loopExists;
}

void MyGraph::checkPossibleLoop(Vertex *currRoot, Vertex *parent, bool &exists)
{

    currRoot->visited = true;

    if (currRoot == parent)
    {
        exists = true;
    }

    for (auto child : currRoot->children)
    {
        if (!child->visited)
        {
            checkPossibleLoop(child, parent, exists);
        }
    }
}

void MyGraph::topologicalOrder(stack<int> &helperStack, Vertex *currRoot)
{
    if (!currRoot->visited)
    {
        currRoot->visited = true;
        for (auto child : currRoot->children)
        {
            topologicalOrder(helperStack, child);
        }
        helperStack.push(currRoot->data);
    }
}

// functionality undefined on MyGraph that is not DAG
void MyGraph::topologicalOrderPrint()
{
    stack<int> ordered;

    topologicalOrder(ordered, root);

    while (!ordered.empty())
    {
        cout << ordered.top() << " --> ";
        ordered.pop();
    }
    cout << "end" << endl;

    resetVisited();
}
#endif