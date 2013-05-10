//#include "edge.h"

template<class OutType, class InType>
Edge<OutType,InType>::Edge(Node<OutType>* n_out_node, Node<InType>* n_in_node)
{
    if(n_out_node && n_in_node)
    {
        m_out_node=n_out_node;
        m_in_node=n_in_node;

        m_out_node->registerOutputEdge(this);
        m_in_node->registerInputEdge(this);
    }
    else
    {
        m_out_node=0;
        m_in_node=0;
    }
}

template<class OutType, class InType>
Node<OutType>* Edge<OutType, InType>::outputNode() const
{
    return m_out_node;
}

template<class OutType, class InType>
Node<InType>* Edge<OutType, InType>::inputNode() const
{
    return m_in_node;
}

