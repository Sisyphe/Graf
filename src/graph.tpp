//#include "graph.h"
#include <sstream>
#include <map>
#include <queue>
#include <stack>

template<class T, class U>
Graph<T,U>::Graph()
{
}

template<class T, class U>
Graph<T,U>::~Graph()
{
    Vertice<T,U>* t_vertice=0;
    typename Vertice<T,U>::It vertice_it=m_vertices.begin();

    while(vertice_it!=m_vertices.end())
    {
        t_vertice=*vertice_it;
        ++vertice_it;
        removeVertice(t_vertice);
    }
}

template<class T, class U>
Vertice<T,U>* Graph<T,U>::addVertice(T n_object)
{
    Vertice<T,U>* t_vertice=new Vertice<T,U>(n_object);

    if(t_vertice)
    {
        m_vertices.insert(t_vertice);
    }

    return t_vertice;
}

template<class T, class U>
void Graph<T,U>::removeVertice(Vertice<T,U>* n_vertice)
{
    typename Edge<T,U>::It edge_it, end_it;

    edge_it=n_vertice->inputEdgesBegin();
    end_it=n_vertice->inputEdgesEnd();

    for(; edge_it!=end_it ; ++edge_it)
    {
        (*edge_it)->inputVertice()->unregisterInputEdge(*edge_it);
        (*edge_it)->outputVertice()->unregisterOutputEdge(*edge_it);
        delete (*edge_it);
    }

    edge_it=n_vertice->outputEdgesBegin();
    end_it=n_vertice->outputEdgesEnd();

    for(; edge_it!=end_it ; ++edge_it)
    {
        (*edge_it)->outputVertice()->unregisterOutputEdge(*edge_it);
        (*edge_it)->inputVertice()->unregisterInputEdge(*edge_it);
        delete (*edge_it);
    }

    m_vertices.erase(n_vertice);
    delete n_vertice;
}

template<class T, class U>
void Graph<T,U>::applyOnOutputVertices
(
    Vertice<T,U>* n_vertice,
    VerticeProcess<T,U>* n_process,
    bool n_apply_on_it
)
{
    applyDFSOnLinkedVertices(n_vertice, Vertice<T,U>::OUTPUT, n_process);
}

template<class T, class U>
void Graph<T,U>::applyOnInputVertices
(
    Vertice<T,U>* n_vertice,
    VerticeProcess<T,U>* n_process,
    bool n_apply_on_it
)
{
    applyDFSOnLinkedVertices(n_vertice, Vertice<T,U>::INPUT, n_process);
}

template<class T, class U>
void Graph<T,U>::applyBFSOnLinkedVertices
(
    Vertice<T,U>* n_vertice,
    enum Vertice<T,U>::LinkDirection n_direction,
    VerticeProcess<T,U>* n_process
)
{
    if(!m_vertices.empty() && n_process)
    {
        std::queue<Vertice<T,U>*> queue;
        typename Edge<T,U>::It child_it, end_it;

        setVerticesTag(false);

        n_vertice->setTagged(true);
        queue.push(n_vertice);

        while(!queue.empty())
        {
            n_vertice=queue.front();
            queue.pop();

            if(!n_process->applyOn(n_vertice)) break;

            if(n_direction & Vertice<T,U>::INPUT)
            {
                child_it=n_vertice->edgesBegin(Vertice<T,U>::INPUT);
                end_it=n_vertice->edgesEnd(Vertice<T,U>::INPUT);

                while(child_it!=end_it)
                {
                    if(n_process->checkEdge(*child_it))
                    {
                        n_vertice=(*child_it)->outputVertice();
                    }

                    if(!n_vertice->isTagged())
                    {
                        n_vertice->setTagged(true);
                        queue.push(n_vertice);
                    }

                    ++child_it;
                }
            }

            if(n_direction & Vertice<T,U>::OUTPUT)
            {
                child_it=n_vertice->edgesBegin(Vertice<T,U>::OUTPUT);
                end_it=n_vertice->edgesEnd(Vertice<T,U>::OUTPUT);

                while(child_it!=end_it)
                {
                    if(n_process->checkEdge(*child_it))
                    {
                        n_vertice=(*child_it)->inputVertice();
                    }

                    if(!n_vertice->isTagged())
                    {
                        n_vertice->setTagged(true);
                        queue.push(n_vertice);
                    }

                    ++child_it;
                }
            }
        }
    }
}
template<class T, class U>
void Graph<T,U>::applyDFSOnLinkedVertices
(
    Vertice<T,U>* n_vertice,
    enum Vertice<T,U>::LinkDirection n_direction,
    VerticeProcess<T,U>* n_process
)
{
    std::cout << "DFS" << std::endl;
    if(!m_vertices.empty() && n_process)
    {
        std::stack<Vertice<T,U>*> stack;
        Vertice<T,U>* t_vertice=n_vertice;
        typename Edge<T,U>::It child_it, end_it;

        resetVertices(Vertice<T,U>::OUTPUT);
        stack.push(t_vertice);
        t_vertice->setTagged(true);

        while(!stack.empty())
        {
            t_vertice=stack.top();
            child_it=t_vertice->nextEdgeIt();
            end_it=t_vertice->outputEdgesEnd();

            if(child_it == end_it)
            {
                stack.pop();
                std::cout << "finished: " << *t_vertice << std::endl;
            }
            else
            {
                t_vertice=(*child_it)->inputVertice();
                stack.push(t_vertice);
                t_vertice->setTagged(true);
            }
        }
    }
}

template<class T, class U>
void Graph<T,U>:: applyOnAllVertices(Vertice<T,U>* n_vertice, VerticeProcess<T,U>* n_process)
{
    applyOnLinkedVertices(n_vertice, Vertice<T,U>::BOTH, n_process);
}

template<class T, class U>
void Graph<T,U>::applyOnAllVertices(VerticeProcess<T,U>* n_process)
{
    typename Vertice<T,U>::It vertice_it=m_vertices.begin();

    for(; vertice_it!=m_vertices.end(); ++vertice_it)
    {
        if(!n_process->applyOn(*vertice_it)) break;
    }
}

template<class T, class U>
void Graph<T,U>::setVerticesTag(bool n_tag)
{
    typename Vertice<T,U>::It vertice_it=m_vertices.begin();

    for(; vertice_it!=m_vertices.end(); ++vertice_it)
    {
        (*vertice_it)->setTagged(n_tag);
    }
}

template<class T, class U>
void Graph<T,U>::resetVertices(enum Vertice<T,U>::LinkDirection n_direction)
{
    typename Vertice<T,U>::It vertice_it=m_vertices.begin();

    for(; vertice_it!=m_vertices.end(); ++vertice_it)
    {
        (*vertice_it)->setTagged(false);
        (*vertice_it)->resetEdgeIt(n_direction);
    }
}

template<class T, class U>
std::string Graph<T,U>::toDot() const
{
    std::stringstream stream;
    std::map<Vertice<T,U>*, int> t_vertice_map;
    int i=0;

    stream<<"digraph G {"<<std::endl;

    typename Vertice<T,U>::It vertice_it=m_vertices.begin();
    for(; vertice_it!=m_vertices.end(); ++vertice_it)
    {
        t_vertice_map[(*vertice_it)]=i;
        stream<<i<<"[label=\""<<(**vertice_it)<<"\"];"<<std::endl;
        ++i;
    }


    typename std::map<Vertice<T,U>*, int>::iterator t_map_it=t_vertice_map.begin();
    typename Edge<T,U>::It edge_it, edge_end;
    for(; t_map_it != t_vertice_map.end(); ++t_map_it)
    {
        edge_it=(*t_map_it).first->edgesBegin(Vertice<T,U>::OUTPUT);
        edge_end=(*t_map_it).first->edgesEnd(Vertice<T,U>::OUTPUT);
        for(; edge_it!=edge_end; ++edge_it)
        {
            stream<<(*t_map_it).second<<"->"
                  <<t_vertice_map[(*edge_it)->inputVertice()]
                  <<" [label=\" "<<(**edge_it)<<"\"];"<<std::endl;
        }
    }

    stream<<"}";

    return stream.str();
}
