#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include "node.h"
#include "edge.h"
#include "nodeprocess.h"

template <class T>
class Graph
{

    public:

        Graph();
        ~Graph();
        Node<T>* addNode(Node<T>* n_parent=0, T n_object=0);
        void removeNode(Node<T>* n_node);
        Edge<T,T>* addEdge(Node<T>* n_node_out, Node<T>* n_node_in);
        void applyOnOutputNodes(Node<T>* n_node, NodeProcess<T>* n_process, bool n_apply_on_it=true);
        void applyOnInputNodes(Node<T>* n_node, NodeProcess<T>* n_process, bool n_apply_on_it=true);
        void applyOnAllNodes(NodeProcess<T>* n_process);
        std::string toDot() const;

        friend std::ostream& operator<<(std::ostream& n_out, const Graph<T>& n_graph)
        {
            n_out << n_graph.toDot() << std::endl;
            return n_out;
        }

    protected:

        void applyOnLinkedNodes
        (
            Node<T>* n_node,
            enum Node<T>::LinkDirection n_direction,
            NodeProcess<T>* n_process
        );

        void setNodesTag(bool n_tag);


    private:

        std::set<Edge<T,T>*> m_edges;
        std::set<Node<T>*> m_nodes;
};

#include "graph.tpp"

#endif // GRAPH_H
