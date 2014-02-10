//#include "verticeprocess.h"
#include <queue>
#include <stack>
#include <iostream>

template<class T, class U>
VerticeProcess<T,U>::VerticeProcess
(
    TraversalMode n_traversal_mode,
    typename Vertice<T,U>::LinkDirection n_direction
):
    m_direction(n_direction),
    m_traversal_mode(n_traversal_mode)
{
}

template<class T, class U>
bool VerticeProcess<T,U>::process(Vertice<T,U>* n_vertice)
{
    std::cout<<*n_vertice<<std::endl;
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
    return m_direction;
}

template<class T, class U>
typename VerticeProcess<T,U>::TraversalMode VerticeProcess<T,U>::traversalMode() const
{
    return m_traversal_mode;
}


template <class T, class U>
void VerticeProcess<T, U>::applyFrom(Vertice<T, U>* n_vertice, typename Vertice<T,U>::LinkDirection n_direction)
{
    if(traversalMode() == VerticeProcess<T, U>::PREFIXED && n_vertice)
    {
        prefixedDFSFrom(n_vertice);
    }
    else if(traversalMode() == VerticeProcess<T, U>::POSTFIXED && n_vertice)
    {
        postfixedBFSFrom(n_vertice);
    }
}

template <class T, class U>
void VerticeProcess<T, U>::prefixedDFSFrom(Vertice<T, U>* n_vertice, typename Vertice<T,U>::LinkDirection n_direction)
{
    if(n_vertice)
    {
        Vertice<T, U>* t_vertice = n_vertice;
        Vertice<T, U>* t_opposite_vertice = 0;
        std::queue<Vertice<T, U>*> queue;
        typename Edge<T, U>::It edge_it, end_it;

        queue.push(t_vertice);
        t_vertice->setTagged(true);
        t_vertice->resetEdgeIt(n_direction);
        m_processed_vertices.push_back(t_vertice);

        while(!queue.empty())
        {
            t_vertice = queue.front();
            queue.pop();
            t_opposite_vertice = 0;

            if(!process(t_vertice)) break;

            edge_it = t_vertice->nextEdgeIt();
            end_it = t_vertice->edgesEnd(n_direction);

            while(edge_it != end_it)
            {
                if(checkEdge(*edge_it))
                {
                    t_opposite_vertice = (*edge_it)->getOppositeVerticeOf(t_vertice);
                }

                if(t_opposite_vertice && !t_opposite_vertice->isTagged())
                {
                    queue.push(t_opposite_vertice);
                    t_opposite_vertice->setTagged(true);
                    t_opposite_vertice->resetEdgeIt(n_direction);
                    m_processed_vertices.push_back(t_opposite_vertice);
                }

                edge_it = t_vertice->nextEdgeIt();
            }
        }
    }

    resetProcessedVertices();
}

template <class T, class U>
void VerticeProcess<T, U>::postfixedBFSFrom(Vertice<T, U>* n_vertice, typename Vertice<T,U>::LinkDirection n_direction)
{
    if(n_vertice)
    {
        std::stack<Vertice<T, U>*> stack;
        Vertice<T, U>* t_vertice = n_vertice;
        Vertice<T, U>* t_opposite_vertice = 0;
        typename Edge<T, U>::It edge_it, end_it;
        Edge<T, U>* t_edge = 0;

        stack.push(t_vertice);
        t_vertice->setTagged(true);
        t_vertice->resetEdgeIt(n_direction);
        m_processed_vertices.push_back(t_vertice);

        while(!stack.empty())
        {
            t_vertice = stack.top();
            t_opposite_vertice = t_vertice;
            edge_it = t_vertice->nextEdgeIt();
            end_it = t_vertice->edgesEnd(n_direction);
            t_edge = *edge_it;

            while(edge_it != end_it && (!checkEdge(t_edge) || t_opposite_vertice->isTagged()))
            {
                if(checkEdge(t_edge))
                {
                    t_opposite_vertice = (t_edge)->getOppositeVerticeOf(t_vertice);
                }

                if(t_opposite_vertice->isTagged())
                {
                    edge_it = t_vertice->nextEdgeIt();
                    t_edge = *edge_it;
                }
            }

            if(!t_opposite_vertice->isTagged())
            {
                stack.push(t_opposite_vertice);
                t_opposite_vertice->resetEdgeIt(n_direction);
                t_opposite_vertice->setTagged(true);
                m_processed_vertices.push_back(t_opposite_vertice);
            }
            else
            {
                stack.pop();
                if(!process(t_vertice)) break;
            }
        }
    }

    resetProcessedVertices();
}

template <class T, class U>
void VerticeProcess<T, U>::resetProcessedVertices()
{
    typename std::vector<Vertice<T, U>*>::iterator t_processed_vertice_it = m_processed_vertices.begin();

    for(; t_processed_vertice_it != m_processed_vertices.end(); ++t_processed_vertice_it)
    {
        (*t_processed_vertice_it)->setTagged(false);
    }

    m_processed_vertices.clear();
}
