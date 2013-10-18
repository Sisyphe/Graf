//#include "graph.h"

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
void Graph<T,U>::applyFrom
(
    Vertice<T,U>* n_vertice,
    VerticeProcess<T,U>* n_process,
    typename Vertice<T,U>::LinkDirection
)
{
    if(n_process)
    {
        if(n_process->traversalMode() == VerticeProcess<T,U>::PREFIXED && n_vertice)
        {
            n_process->prefixedDFSFrom(n_vertice, n_process->direction());
        }
        else if(n_process->traversalMode() == VerticeProcess<T,U>::POSTFIXED && n_vertice)
        {
            n_process->postfixedBFSFrom(n_vertice, n_process->direction());
        }
        else if(n_process->traversalMode() == VerticeProcess<T,U>::ALL)
        {
            applyOnAllVertices(n_process);
        }
    }
}

template<class T, class U>
void Graph<T,U>::applyOnAllVertices(VerticeProcess<T,U>* n_process)
{
    typename Vertice<T,U>::It vertice_it=m_vertices.begin();

    for(; vertice_it!=m_vertices.end(); ++vertice_it)
    {
        if(!n_process->process(*vertice_it)) break;
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
