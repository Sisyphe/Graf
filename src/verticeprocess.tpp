//#include "verticeprocess.h"

template<class T, class U>
bool VerticeProcess<T,U>::process(Vertice<T,U>* n_vertice)
{
    //std::cout<<*n_vertice<<std::endl;
    return true;
}

template<class T, class U>
bool VerticeProcess<T,U>::checkEdge(Edge<T,U>* n_edge)
{
    return true;
}

template<class T, class U>
typename Vertice<T,U>::LinkDirection VerticeProcess<T,U>::direction() const
{
    return Vertice<T,U>::BOTH;
}

template<class T, class U>
typename VerticeProcess<T,U>::TraversalMode VerticeProcess<T,U>::traversalMode() const
{
    return VerticeProcess<T,U>::PREFIXED;
}
