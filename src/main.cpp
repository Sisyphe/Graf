#include "graph.h"
#include "vertice.h"
#include <iostream>

int main()
{
    Graph<char,int> graph;
    Vertice<char,int>* A=graph.addVertice('A');
    Vertice<char,int>* B=graph.addVertice('B');
    Vertice<char,int>* C=graph.addVertice('C');
    Vertice<char,int>* D=graph.addVertice('D');
    Vertice<char,int>* E=graph.addVertice('E');
    Vertice<char,int>* F=graph.addVertice('F');
    Vertice<char,int>* G=graph.addVertice('G');
//     A->addOutputEdge(0,B);
//     A->addOutputEdge(1,C);
//     A->addOutputEdge(2,E);
//     B->addOutputEdge(3,D);
//     B->addOutputEdge(4,F);
//     C->addOutputEdge(5,G);
//     E->addOutputEdge(6,F);
//     G->addOutputEdge(7,A);

    int i=0;
    A->addOutputEdge(i++,B);
    B->addOutputEdge(i++,A);
    B->addOutputEdge(i++,C);
    A->addOutputEdge(i++,D);
    B->addOutputEdge(i++,D);
    C->addOutputEdge(i++,D);
    E->addOutputEdge(i++,D);
    F->addOutputEdge(i++,D);
    G->addOutputEdge(i++,D);

    std::cout<<graph<<std::endl;

    VerticeProcess<char,int> process(VerticeProcess<char,int>::POSTFIXED, Vertice<char,int>::OUTPUT);
    graph.applyFrom(A, &process);
    graph.applyFrom(A, &process);

    /*Vertice<char,int>* A = graph.addVertice('A');
    Vertice<char,int>* B = graph.addVertice('B');
    A->addOutputEdge(0,B);
    VerticeProcess<char,int> process;
    graph.postfixedTraversalOf(B,Vertice<char,int>::INPUT, &process);*/

    return 0;
}
