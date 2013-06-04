#ifndef EDGE_H
#define EDGE_H

#include <set>

template<class T, class U>
class Vertice;

template<class VerticeType, class EdgeType>
class Edge
{
    public:

        typedef typename std::set<Edge<VerticeType,EdgeType>*>::iterator It;

        Edge<VerticeType,EdgeType>
        (
            Vertice<VerticeType,EdgeType>* n_vertice_out=0,
            Vertice<VerticeType,EdgeType>* n_vertice_in=0
        );

        Edge<VerticeType,EdgeType>
        (
            EdgeType n_content,
            Vertice<VerticeType,EdgeType>* n_vertice_out=0,
            Vertice<VerticeType,EdgeType>* n_vertice_in=0
        );

        EdgeType content() const;
        void setContent(EdgeType n_content);

        Vertice<VerticeType,EdgeType>* outputVertice() const;
        Vertice<VerticeType,EdgeType>* inputVertice() const;

        friend std::ostream& operator<<(std::ostream& n_out, const Edge<VerticeType,EdgeType>& n_edge)
        {
            n_out  << n_edge.content();
            return n_out;
        }

    protected:

        void init
        (
             Vertice<VerticeType,EdgeType>* n_vertice_out,
             Vertice<VerticeType,EdgeType>* n_vertice_in
         );

        Vertice<VerticeType,EdgeType>* m_out_vertice;
        Vertice<VerticeType,EdgeType>* m_in_vertice;
        EdgeType m_content;
};

#include "edge.tpp"

#endif // EDGE_H
