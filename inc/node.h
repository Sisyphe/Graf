#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <set>
#include <map>
#include "edge.h"

template<class T>
class Node
{
    public:

        typedef typename std::set<Node<T>*>::iterator It;

        enum LinkDirection
        {
            INPUT,
            OUTPUT
        };

        Node(T n_object=T());

        void registerOutputEdge(Edge<T>* n_edge);
        void registerInputEdge(Edge<T>* n_edge);
        void unregisterOutputEdge(Edge<T>* n_edge);
        void unregisterInputEdge(Edge<T>* n_edge);

        T object() const;
        void setObject(T n_object);

        typename Edge<T,T>::It outputEdgesBegin() const;
        typename Edge<T,T>::It outputEdgesEnd() const;
        typename Edge<T,T>::It inputEdgesBegin() const;
        typename Edge<T,T>::It inputEdgesEnd() const;
        typename Edge<T,T>::It edgesBegin(LinkDirection n_direction) const;
        typename Edge<T,T>::It edgesEnd(LinkDirection n_direction) const;

        bool isTagged() const;
        void setTagged(bool n_tag);

        friend std::ostream& operator<<(std::ostream& n_out, const Node<T>& n_node)
        {
            n_out << "\"" << &n_node << " " << n_node.object() << "\"";
            return n_out;
        }

    private:

        T m_object;
        std::set<Edge<T>*>m_output_edges ;
        std::set<Edge<T>*> m_input_edges;
        bool m_tag;
};

#include "node.tpp"

#endif // NODE_H
