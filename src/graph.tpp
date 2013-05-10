//#include "graph.h"
#include <sstream>
#include <map>
#include <queue>

template<class T>
Graph<T>::Graph()
{
}

template<class T>
Graph<T>::~Graph()
{
    Node<T>* t_node=0;
    typename Node<T>::It node_it=m_nodes.begin();

    while(node_it!=m_nodes.end())
    {
        t_node=*node_it;
        ++node_it;
        removeNode(t_node);
    }
}

template<class T>
Node<T>* Graph<T>::addNode(Node<T>* n_parent, T n_object)
{
    Node<T>* t_node=new Node<T>(n_object);

    if(n_parent ) addEdge(n_parent,t_node);

    if(t_node)
    {
        m_nodes.insert(t_node);
    }

    return t_node;
}

template<class T>
void Graph<T>::removeNode(Node<T>* n_node)
{
    typename Edge<T,T>::It edge_it, end_it;

    edge_it=n_node->inputEdgesBegin();
    end_it=n_node->inputEdgesEnd();

    for(; edge_it!=end_it ; ++edge_it)
    {
        (*edge_it)->inputNode()->unregisterInputEdge(*edge_it);
        delete (*edge_it);
        m_edges.erase(*edge_it);
    }

    edge_it=n_node->outputEdgesBegin();
    end_it=n_node->outputEdgesEnd();

    for(; edge_it!=end_it ; ++edge_it)
    {
        (*edge_it)->outputNode()->unregisterOutputEdge(*edge_it);
        delete (*edge_it);
        m_edges.erase(*edge_it);
    }

    m_nodes.erase(n_node);
    delete n_node;
}

template<class T>
Edge<T,T>* Graph<T>::addEdge(Node<T>* n_node_out, Node<T>* n_node_in)
{
    Edge<T,T>* t_edge=new Edge<T,T>(n_node_out, n_node_in);

    if(t_edge)
    {
        m_edges.insert(t_edge);
    }

    return t_edge;
}

template<class T>
void Graph<T>::applyOnOutputNodes
(
    Node<T>* n_node,
    NodeProcess<T>* n_process,
    bool n_apply_on_it
)
{
    applyOnLinkedNodes(n_node, Node<T>::OUTPUT, n_process);
}

template<class T>
void Graph<T>::applyOnInputNodes
(
    Node<T>* n_node,
    NodeProcess<T>* n_process,
    bool n_apply_on_it
)
{
    applyOnLinkedNodes(n_node, Node<T>::INPUT, n_process);
}

template<class T>
void Graph<T>::applyOnLinkedNodes
(
    Node<T>* n_node,
    enum Node<T>::LinkDirection n_direction,
    NodeProcess<T>* n_process
)
{
    if(!m_nodes.empty() && n_process)
    {
        std::queue<Node<T>*> queue;
        typename Edge<T,T>::It child_it, end_it;

        setNodesTag(false);

        n_node->setTagged(true);
        queue.push(n_node);

        while(!queue.empty())
        {
            n_node=queue.front();
            queue.pop();

            n_process->applyOn(n_node);

            child_it=n_node->edgesBegin(n_direction);
            end_it=n_node->edgesEnd(n_direction);

            while(child_it!=end_it)
            {
                if(n_direction==Node<T>::INPUT)
                    n_node=(*child_it)->outputNode();
                else
                    n_node=(*child_it)->inputNode();

                if(!n_node->isTagged())
                {
                    n_node->setTagged(true);
                    queue.push(n_node);
                }

                ++child_it;
            }
        }
    }
}

template<class T>
void Graph<T>::applyOnAllNodes(NodeProcess<T>* n_process)
{
    typename Node<T>::It node_it=m_nodes.begin();

    for(; node_it!=m_nodes.end(); ++node_it)
    {
        n_process->applyOn(*node_it);
    }
}

template<class T>
void Graph<T>::setNodesTag(bool n_tag)
{
    typename Node<T>::It node_it=m_nodes.begin();

    for(; node_it!=m_nodes.end(); ++node_it)
    {
        (*node_it)->setTagged(n_tag);
    }
}

template<class T>
std::string Graph<T>::toDot() const
{
    std::stringstream stream;
    std::map<Node<T>*, int> t_node_map;
    int i=0;

    stream<<"digraph G {"<<std::endl;

    typename Node<T>::It node_it=m_nodes.begin();
    for(; node_it!=m_nodes.end(); ++node_it)
    {
        t_node_map[(*node_it)]=i;
        stream<<i<<"[label="<<(**node_it)<<"];"<<std::endl;
        ++i;
    }

    typename Edge<T,T>::It edge_it=m_edges.begin();
    for(; edge_it!=m_edges.end(); ++edge_it)
    {
        stream<<t_node_map[(*edge_it)->outputNode()]<<"->"
              <<t_node_map[(*edge_it)->inputNode()]<<" ;"<<std::endl;
    }

    stream<<"}";

    return stream.str();
}
