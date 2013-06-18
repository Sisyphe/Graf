#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
#include <set>
#include <map>
#include "edge.h"

template<class T, class U>
class Vertice
{
    public:

        typedef typename std::set<Vertice<T,U>*>::iterator It;

        enum LinkDirection
        {
            NO_DIRECTION=0x00,
            INPUT=0x01,
            OUTPUT=0x02,
            BOTH=0x03
        };

        struct EdgePair
        {
            Edge<T,U>* input_edge;
            Edge<T,U>* output_edge;
        };

        Vertice();
        Vertice(T n_content);
        void init();

        Edge<T,U>* addInputEdge(U n_content, Vertice<T,U>* n_vertice);
        Edge<T,U>* addOutputEdge(U n_content, Vertice<T,U>* n_vertice);
        EdgePair addBidirectionnalEdge(U n_content, Vertice<T,U>* n_vertice);

        void registerOutputEdge(Edge<T,U>* n_edge);
        void registerInputEdge(Edge<T,U>* n_edge);
        void unregisterOutputEdge(Edge<T,U>* n_edge);
        void unregisterInputEdge(Edge<T,U>* n_edge);

        T content() const;
        void setContent(T n_content);

        typename Edge<T,U>::It outputEdgesBegin() const;
        typename Edge<T,U>::It outputEdgesEnd() const;
        typename Edge<T,U>::It inputEdgesBegin() const;
        typename Edge<T,U>::It inputEdgesEnd() const;
        typename Edge<T,U>::It edgesBegin(LinkDirection n_direction) const;
        typename Edge<T,U>::It edgesEnd(LinkDirection n_direction) const;
        typename Edge<T,U>::It resetEdgeIt(LinkDirection n_direction);
        typename Edge<T,U>::It nextEdgeIt();

        bool isTagged() const;
        void setTagged(bool n_tag);

        friend std::ostream& operator<<(std::ostream& n_out, const Vertice<T,U>& n_vertice)
        {
            n_out << n_vertice.content();
            return n_out;
        }

    protected:

        T m_content;
        std::set<Edge<T,U>*>m_output_edges ;
        std::set<Edge<T,U>*> m_input_edges;
        bool m_tag;
        typename Edge<T,U>::It m_edge_it;
        LinkDirection m_remaining_direction;
};

#include "vertice.tpp"

#endif // VERTICE_H
