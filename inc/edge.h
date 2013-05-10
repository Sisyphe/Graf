#ifndef EDGE_H
#define EDGE_H

template<class T>
class Node;

template<class OutType, class InType=OutType>
class Edge
{
    public:

        typedef typename std::set<Edge<OutType,InType>*>::iterator It;

        Edge<OutType,InType>(Node<OutType>* n_node_out=0, Node<InType>* n_node_in=0);
        Node<OutType>* outputNode() const;
        Node<InType>* inputNode() const;

    private:

        Node<OutType>* m_out_node;
        Node<InType>* m_in_node;
};

#include "edge.tpp"

#endif // EDGE_H
