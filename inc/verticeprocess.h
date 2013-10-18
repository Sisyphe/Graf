#ifndef VERTICEPROCESS_H
#define VERTICEPROCESS_H

#include "vertice.h"
#include "edge.h"
#include <vector>

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

        VerticeProcess
        (
            TraversalMode n_traversal_mode = ALL,
            typename Vertice<T,U>::LinkDirection n_direction = Vertice<T,U>::BOTH
        );

        virtual ~VerticeProcess(){}

        virtual bool process(Vertice<T,U>* n_vertice);
        virtual bool checkEdge(Edge<T,U>* n_edge);
        virtual typename Vertice<T,U>::LinkDirection direction() const;
        virtual TraversalMode traversalMode() const;
        void applyFrom(Vertice<T,U>* n_vertice, typename Vertice<T,U>::LinkDirection n_direction = Vertice<T,U>::OUTPUT);
        void prefixedDFSFrom(Vertice<T,U>* n_vertice, typename Vertice<T,U>::LinkDirection n_direction = Vertice<T,U>::OUTPUT);
        void postfixedBFSFrom(Vertice<T,U>* n_vertice, typename Vertice<T,U>::LinkDirection n_direction = Vertice<T,U>::OUTPUT);
        void resetProcessedVertices();

    protected:

        std::vector<Vertice<T,U>*> m_processed_vertices;
        typename Vertice<T,U>::LinkDirection m_direction;
        TraversalMode m_traversal_mode;
};

#include "verticeprocess.tpp"

#endif // VERTICEPROCESS_H
