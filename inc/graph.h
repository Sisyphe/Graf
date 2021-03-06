#ifndef GRAPH_H
#define GRAPH_H

#include <sstream>
#include <set>
#include "vertice.h"
#include "edge.h"
#include "verticeprocess.h"

template <class T, class U>
class Graph
{
    public:

        Graph();
        ~Graph();

        Vertice<T,U>* addVertice(T n_object=0);
        void removeVertice(Vertice<T,U>* n_vertice);

        void applyFrom
        (
            Vertice<T,U>* n_vertice,
            VerticeProcess<T,U>* n_process,
            typename Vertice<T,U>::LinkDirection = Vertice<T,U>::OUTPUT
        );

        void applyOnAllVertices(VerticeProcess<T,U>* n_process);

        std::string toDot() const;

        friend std::ostream& operator<<(std::ostream& n_out, const Graph<T,U>& n_graph)
        {
            n_out << n_graph.toDot() << std::endl;
            return n_out;
        }

    protected:

        void setVerticesTag(bool n_tag);
        void resetVertices(enum Vertice<T,U>::LinkDirection n_direction);

        std::set<Vertice<T,U>*> m_vertices;
};

#include "graph.tpp"

#endif // GRAPH_H
