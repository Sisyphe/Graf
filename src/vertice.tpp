//#include "vertice.h"

template <class T, class U>
Vertice<T,U>::Vertice()
{
    init();
}

template <class T, class U>
Vertice<T,U>::Vertice(T n_content)
{
    setContent(n_content);

    init();
}

template <class T, class U>
void Vertice<T,U>::init()
{
    setTagged(false);
    resetEdgeIt(OUTPUT);
}

template<class T, class U>
Edge<T,U>* Vertice<T,U>::addInputEdge(U n_content, Vertice<T,U>* n_vertice)
{
    return new Edge<T,U>(n_content,n_vertice,this);
}

template<class T, class U>
Edge<T,U>* Vertice<T,U>::addOutputEdge(U n_content, Vertice<T,U>* n_vertice)
{
    return new Edge<T,U>(n_content,this,n_vertice);
}

template<class T, class U>
typename Vertice<T,U>::EdgePair Vertice<T,U>::addBidirectionnalEdge(U n_content, Vertice<T,U>* n_vertice)
{
    Vertice<T,U>::EdgePair t_pair;
    t_pair.input_edge=addEdge(n_content,n_vertice,this);
    t_pair.output_edge=addEdge(n_content,this,n_vertice);
    return t_pair;
}


template <class T, class U>
void Vertice<T,U>::registerOutputEdge(Edge<T,U>* n_edge)
{
    m_output_edges.insert(n_edge);
}

template <class T, class U>
void Vertice<T,U>::registerInputEdge(Edge<T,U>* n_edge)
{
    m_input_edges.insert(n_edge);
}

template <class T, class U>
void Vertice<T,U>::unregisterOutputEdge(Edge<T,U>* n_edge)
{
    m_output_edges.erase(n_edge);
}

template <class T, class U>
void Vertice<T,U>::unregisterInputEdge(Edge<T,U>* n_edge)
{
    m_input_edges.erase(n_edge);
}

template <class T, class U>
T Vertice<T,U>::content() const
{
    return m_content;
}

template <class T, class U>
void Vertice<T,U>::setContent(T n_content)
{
    m_content=n_content;
}

template <class T, class U>
typename Edge<T,U>::It Vertice<T,U>::outputEdgesBegin() const
{
    return m_output_edges.begin();
}

template <class T, class U>
typename Edge<T,U>::It Vertice<T,U>::outputEdgesEnd() const
{
    return m_output_edges.end();
}

template <class T, class U>
typename Edge<T,U>::It Vertice<T,U>::inputEdgesBegin() const
{
    return m_input_edges.begin();
}

template <class T, class U>
typename Edge<T,U>::It Vertice<T,U>::inputEdgesEnd() const
{
    return m_input_edges.end();
}

template <class T, class U>
bool Vertice<T,U>::isTagged() const
{
    return m_tag;
}

template <class T, class U>
void Vertice<T,U>::setTagged(bool n_tag)
{
    m_tag=n_tag;
}

template <class T, class U>
typename Edge<T,U>::It Vertice<T,U>::edgesBegin(LinkDirection n_direction) const
{
    if(n_direction==INPUT)
    {
        return inputEdgesBegin();
    }
    else
    {
        return outputEdgesBegin();
    }
}

template <class T, class U>
typename Edge<T,U>::It Vertice<T,U>::edgesEnd(LinkDirection n_direction) const
{
    if(n_direction==INPUT)
    {
        return inputEdgesEnd();
    }
    else
    {
        return outputEdgesEnd();
    }
}

template <class T, class U>
typename Edge<T,U>::It Vertice<T,U>::resetEdgeIt(LinkDirection n_direction)
{
    switch(n_direction)
    {
        case INPUT:
            m_edge_it=inputEdgesBegin();
            m_remaining_direction=NO_DIRECTION;
            break;
    
        case OUTPUT:
            m_edge_it=outputEdgesBegin();
            m_remaining_direction=NO_DIRECTION;
            break;

        case BOTH:
            m_edge_it=inputEdgesBegin();
            m_remaining_direction=OUTPUT;
            break;
            
        case NO_DIRECTION:
            m_edge_it=outputEdgesEnd();
            m_remaining_direction=NO_DIRECTION;
            break;
    }
    
    return m_edge_it;
}

template <class T, class U>
typename Edge<T,U>::It Vertice<T,U>::nextEdgeIt()
{
    typename Edge<T,U>::It t_edge_it=m_edge_it;
    
    if(m_edge_it == inputEdgesEnd())
    {
        if(m_remaining_direction == OUTPUT)
        {
            m_remaining_direction=NO_DIRECTION;
            m_edge_it=outputEdgesBegin();
            t_edge_it=m_edge_it;
        }
        else
        {
            m_edge_it=outputEdgesEnd();
            t_edge_it=m_edge_it;
        }
    }
    if(m_edge_it != outputEdgesEnd())
    {
        t_edge_it=m_edge_it++;
    }

    return t_edge_it;
}
