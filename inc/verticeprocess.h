#ifndef VERTICEPROCESS_H
#define VERTICEPROCESS_H

#include "vertice.h"
#include "edge.h"

template<class T, class U>
class VerticeProcess
{
    public:

        enum TraversalMode
        {
            ALL,
            PREFIXED,
            POSTFIXED
        };

        virtual ~VerticeProcess(){}

        virtual bool process(Vertice<T,U>* n_vertice);
        virtual bool checkEdge(Edge<T,U>* n_edge);
        virtual typename Vertice<T,U>::LinkDirection direction() const;
        virtual TraversalMode traversalMode() const;
};

#include "verticeprocess.tpp"

#endif // VERTICEPROCESS_H
