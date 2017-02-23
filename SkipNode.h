//
// Created by Markus Springer on 05.04.16.
//

#ifndef UE3_SKIPNODE_H
#define UE3_SKIPNODE_H

#include <iostream>


template <class T>
class SkipNode {

    friend std::ostream & operator<<(std::ostream &os, const SkipNode<T> & node) {
        os << node.value;
        return os;
    }

public:

    T value;

    SkipNode<T> **forward; // array of pointers

    SkipNode(int level, const T &value)
    {
        forward = new SkipNode<T> * [level + 1];
        memset(forward, 0, sizeof(SkipNode<T>*)*(level + 1));
        this->value = value;
    }

    ~SkipNode()
    {
        delete [] forward;
    }

    SkipNode<T>* getForwardPointer() {
        return *forward;
    }
};

#endif //UE3_SKIPNODE_H
