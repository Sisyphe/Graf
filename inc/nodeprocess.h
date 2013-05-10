#ifndef NODEPROCESS_H
#define NODEPROCESS_H

template<class T>
class NodeProcess
{
    public:
        virtual void applyOn(Node<T>* n_node);
};

#include "nodeprocess.tpp"

#endif // NODEPROCESS_H
