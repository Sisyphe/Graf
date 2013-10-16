#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
#include <set>
#include <map>
#include "edge.h"

class VerticeColor
{
    public:

        static const VerticeColor white;
        static const VerticeColor grey;
        static const VerticeColor black;

        VerticeColor():
            m_color(WHITE){}

        VerticeColor nextColor() const
        {
            return VerticeColor(Color((m_color + 1) % 3));
        }

        bool operator==(const VerticeColor& n_color) const
        {
            return m_color == n_color.m_color;
        }

    protected:

        enum Color
        {
            WHITE,
            GREY,
            BLACK
        };

        VerticeColor(Color n_color):
            m_color(n_color){}

        Color m_color;
};

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

        Edge<T,U>* addInputEdge(U n_content, Vertice<T,U>* n_vertice, bool n_avoid_duplicate=false);
        Edge<T,U>* addOutputEdge(U n_content, Vertice<T,U>* n_vertice, bool n_avoid_duplicate=false);
        EdgePair addBidirectionnalEdge(U n_content, Vertice<T,U>* n_vertice, bool n_avoid_duplicate=false);

        Edge<T,U>* findAdjacentEdge(U n_content, Vertice<T,U>* n_vertice) const;
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

        VerticeColor color() const;
        void setColor(VerticeColor n_color);
        void resetColors();

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
        VerticeColor m_color;
};

#include "vertice.tpp"

#endif // VERTICE_H
