//#include "edge.h"

template<class VerticeType, class EdgeType>
Edge<VerticeType,EdgeType>::Edge
(
    Vertice<VerticeType,EdgeType>* n_out_vertice,
    Vertice<VerticeType,EdgeType>* n_in_vertice
)
{
    init(n_out_vertice,n_in_vertice);
}

template<class VerticeType, class EdgeType>
Edge<VerticeType,EdgeType>::Edge
(
    EdgeType n_content,
    Vertice<VerticeType,EdgeType>* n_out_vertice,
    Vertice<VerticeType,EdgeType>* n_in_vertice
)
{
    setContent(n_content);

    init(n_out_vertice,n_in_vertice);
}

template<class VerticeType, class EdgeType>
void Edge<VerticeType,EdgeType>::init
(
    Vertice<VerticeType,EdgeType>* n_out_vertice,
    Vertice<VerticeType,EdgeType>* n_in_vertice
)
{
    if(n_out_vertice && n_in_vertice)
    {
        m_out_vertice=n_out_vertice;
        m_in_vertice=n_in_vertice;

        m_out_vertice->registerOutputEdge(this);
        m_in_vertice->registerInputEdge(this);
    }
    else
    {
        m_out_vertice=0;
        m_in_vertice=0;
    }
}

template <class VerticeType, class EdgeType>
EdgeType Edge<VerticeType,EdgeType>::content() const
{
    return m_content;
}

template <class VerticeType, class EdgeType>
void Edge<VerticeType,EdgeType>::setContent(EdgeType n_content)
{
    m_content=n_content;
}

template<class VerticeType, class EdgeType>
Vertice<VerticeType,EdgeType>* Edge<VerticeType, EdgeType>::outputVertice() const
{
    return m_out_vertice;
}

template<class VerticeType, class EdgeType>
Vertice<VerticeType,EdgeType>* Edge<VerticeType, EdgeType>::inputVertice() const
{
    return m_in_vertice;
}

template<class VerticeType, class EdgeType>
Vertice<VerticeType,EdgeType>* Edge<VerticeType, EdgeType>::getOppositeVerticeOf(Vertice<VerticeType,EdgeType>* n_vertice) const
{
    if(n_vertice == m_in_vertice)
        return m_out_vertice;

    if(n_vertice == m_out_vertice)
        return m_in_vertice;

    return 0;
}