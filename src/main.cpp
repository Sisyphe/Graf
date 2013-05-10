#include "graph.h"
#include "node.h"

int main()
{
    Graph<char> graph;
    Node<char>* A=graph.addNode(0,'A');
    Node<char>* B=graph.addNode(0,'B');
    Node<char>* C=graph.addNode(0,'C');
    Node<char>* D=graph.addNode(0,'D');
    Node<char>* E=graph.addNode(0,'E');
    Node<char>* F=graph.addNode(0,'F');
    Node<char>* G=graph.addNode(0,'G');
    graph.addEdge(A,B);
    graph.addEdge(A,C);
    graph.addEdge(A,E);
    graph.addEdge(B,D);
    graph.addEdge(B,F);
    graph.addEdge(C,G);
    graph.addEdge(E,F);

    std::cout<<graph<<std::endl;

    NodeProcess<char> process;
    graph.applyOnInputNodes(F,&process);

    return 0;
}
