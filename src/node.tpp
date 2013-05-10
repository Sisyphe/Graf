//#include "node.h"

template <class T>
Node<T>::Node(T n_object)
{
    setObject(n_object);

    setTagged(false);
}

template <class T>
void Node<T>::registerOutputEdge(Edge<T>* n_edge)
{
    m_output_edges.insert(n_edge);
}

template <class T>
void Node<T>::registerInputEdge(Edge<T>* n_edge)
{
    m_input_edges.insert(n_edge);
}

template <class T>
void Node<T>::unregisterOutputEdge(Edge<T>* n_edge)
{
    m_output_edges.erase(n_edge);
}

template <class T>
void Node<T>::unregisterInputEdge(Edge<T>* n_edge)
{
    m_input_edges.erase(n_edge);
}

template <class T>
T Node<T>::object() const
{
    return m_object;
}

template <class T>
void Node<T>::setObject(T n_object)
{
    m_object=n_object;
}

template <class T>
typename Edge<T,T>::It Node<T>::outputEdgesBegin() const
{
    return m_output_edges.begin();
}

template <class T>
typename Edge<T,T>::It Node<T>::outputEdgesEnd() const
{
    return m_output_edges.end();
}

template <class T>
typename Edge<T,T>::It Node<T>::inputEdgesBegin() const
{
    return m_input_edges.begin();
}

template <class T>
typename Edge<T,T>::It Node<T>::inputEdgesEnd() const
{
    return m_input_edges.end();
}

template <class T>
bool Node<T>::isTagged() const
{
    return m_tag;
}

template <class T>
void Node<T>::setTagged(bool n_tag)
{
    m_tag=n_tag;
}

template <class T>
typename Edge<T,T>::It Node<T>::edgesBegin(LinkDirection n_direction) const
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

template <class T>
typename Edge<T,T>::It Node<T>::edgesEnd(LinkDirection n_direction) const
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
