//
// Created by Markus Springer on 02.04.16.
//

#ifndef UE3_SKIPSET_H
#define UE3_SKIPSET_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <functional>
#include "SkipNode.h"

using namespace std;
const float P = 0.5;

template<typename T, typename C = less<T>, const int MAXLEVEL=32>
class SkipSet {
    SkipNode<T> *header;
    int level;
    SkipNode<T> *tail;
public:

    SkipSet() {
        header = new SkipNode<T>(MAXLEVEL, T());
        tail = new SkipNode<T>(MAXLEVEL, T());
        level = 0;
    }
    virtual ~SkipSet() {
        delete header;

        SkipNode<T> *cur = new SkipNode<T>(MAXLEVEL, T());

        while(cur != nullptr) {
            SkipNode<T> *next = cur->getForwardPointer();
            delete cur;
            cur = next;
        }

    }

    void insert(const T &);

    void print();

    bool contains(const T &) const;

    void erase(const T &);
    int random_level();
    float frand();


    class SkipSetIterator {
    private:
        SkipNode<T> *ptr;

    public:

        SkipSetIterator(){
            this->ptr = nullptr;
        }


        SkipSetIterator(SkipNode<T> node){
            this->ptr = &node;
        }

        SkipSetIterator(const SkipSetIterator &it) {
            this->ptr = it.ptr;
        }

        bool operator ==(const SkipSetIterator &rhs){
            return ptr == rhs.ptr;
        }


        bool operator ==(const std::nullptr_t &rhs){
            return ptr == rhs;
        }

        bool operator !=(const SkipSetIterator &rhs){
            return ptr != rhs.ptr;
        }

        SkipSetIterator & operator++(){
            ptr = ptr->forward[1];
            return *this;
        }

        SkipSetIterator operator++(int){
            SkipSetIterator copy(*this);
            operator++();
            return copy;
        }


        SkipNode<T> & operator*(){
            return *ptr;
        }

    };

    typedef SkipSetIterator iterator;

    iterator begin() const{
        return iterator(*header->forward[1]);
    };

    iterator end() const{

        return iterator(*tail);
    };

};


template <class T, typename C, const int MAXLEVEL>
float SkipSet<T, C, MAXLEVEL>::frand() {
    return (float) rand() / RAND_MAX;
}

template <class T, typename C, const int MAXLEVEL>
int SkipSet<T, C, MAXLEVEL>::random_level() {
    static bool first = true;

    if (first) {
        srand( (unsigned)time( NULL ) );
        first = false;
    }

    int lvl = (int)(log(frand())/log(1.-P));
    return lvl < MAXLEVEL ? lvl : MAXLEVEL;
}

template <class T, typename C, const int MAXLEVEL>
void SkipSet<T, C, MAXLEVEL>::print() {

    SkipNode<T> *x = header->forward[0];
    cout << "{";
    while (x != NULL) {
        cout << *x;
        x = x->forward[0];
        if (x != NULL)
            cout << ",";
    }
    cout << "}\n";

}

template <class T, typename C, const int MAXLEVEL>

bool SkipSet<T, C, MAXLEVEL>::contains(const T &search_value) const {
    const SkipNode<T> *x = header;
    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && C()(x->forward[i]->value, search_value)) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    return x != NULL && x->value == search_value;
}

template <class T, typename C, const int MAXLEVEL>
void SkipSet<T, C, MAXLEVEL>::insert(const T &value) {
    SkipNode<T> *x = header;
    SkipNode<T> *update[MAXLEVEL + 1];
    memset(update, 0, sizeof(SkipNode<T>*)*(MAXLEVEL + 1));

    for (int i = level; i >= 0; i--) {

        while (x->forward[i] != NULL && C()(x->forward[i]->value, value)) {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];

    if (x == NULL || x->value != value) {
        int lvl = random_level();

        if (lvl > level) {
            for (int i = level + 1; i <= lvl; i++) {
                update[i] = header;
            }
            level = lvl;
        }
        x = new SkipNode<T>(lvl, value);
        for (int i = 0; i <= lvl; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
}
template <class T, typename C, const int MAXLEVEL>
void SkipSet<T, C, MAXLEVEL>::erase(const T &value) {
    SkipNode<T> *x = header;
    SkipNode<T> *update[MAXLEVEL + 1];
    memset(update, 0, sizeof(SkipNode<T>*)*(MAXLEVEL + 1));

    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && C()(x->forward[i]->value, value)) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    if (x->value == value) {
        for (int i = 0; i <= level; i++) {
            if (update[i]->forward[i] != x)
                break;
            update[i]->forward[i] = x->forward[i];
        }
        delete x;
        while (level > 0 && header->forward[level] == NULL) {
            level--;
        }
    }
}

#endif //UE3_SKIPSET_H
