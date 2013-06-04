#include "graph.h"
#include "vertice.h"

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
    A->addOutputEdge(0,B);
    A->addOutputEdge(1,C);
    A->addOutputEdge(2,E);
    B->addOutputEdge(3,D);
    B->addOutputEdge(4,F);
    C->addOutputEdge(5,G);
    E->addOutputEdge(6,F);

    std::cout<<graph<<std::endl;

    VerticeProcess<char,int> process;
    graph.applyOnOutputVertices(A,&process);

    return 0;
}
