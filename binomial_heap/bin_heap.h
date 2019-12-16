#ifndef bin_heap__
#define bin_heap__
#include "bin_node.h"
#include "stdio.h"
template<typename dataT>
bool 
cmp___(const dataT & left, const dataT & right) {return left < right;};
template<typename dataT, typename countT = int>
class
BinHeap {
    private: 
        /* pointer to compare function
        indicate whether two elements are in the right order*/
        bool (*cmp)(const dataT &, const dataT &); 

        bool 
        cmp_node(BinNode<dataT, countT> * left, BinNode<dataT, countT> * right) {
            return cmp(*(left->data), *(right->data));
        }

        /* merge trees that have the same children_num

        the cmp_node indicates wether the two nodes are in the right order
        trees are merge so that the right one (according to cmp_node) are the parents

        assume that there are at most 2 trees of each children_num
        and the list is in increasing order of children_num */
        BinNode<dataT, countT> *
        consolidate(BinNode<dataT, countT> * head);
    public:
        BinNode<dataT, countT> * trees_list;
        BinNode<dataT, countT> * top_node;
        // countT tree_num;
        countT node_num;

        // constructor
        BinHeap<dataT, countT>(bool (*cmp)(const dataT &, const dataT &) = cmp___);

        bool
        empty() {return trees_list == nullptr;}

        countT
        size() {return node_num;}

        dataT & 
        top() {return *(top_node->data);}

        /* extract the top element from heap */
        void
        pop();

        /*insert a element into heap
        Note that propriate compare function should be provided for non build-in type */
        BinNode<dataT, countT> * 
        push(dataT & data);

        /*insert a element into heap
        Note that propriate compare function should be provided for non build-in type */
        BinNode<dataT, countT> * 
        push(dataT && data);

        /*merge two heaps
        return the newly merged heap
        Note: the heap in arg should be delete if it's in heap memory*/
        void
        merge(BinHeap<dataT, countT> & heap);

        /* change value of a node
        ensure that the new value makes the node closer to the top of the heap*/
        void
        change_value(BinNode<dataT, countT> * node, dataT & new_data);

        /* change value of a node
        ensure that the new value makes the node closer to the top of the heap*/
        void
        change_value(BinNode<dataT, countT> * node, dataT && new_data);

        void
        display();
};

#include "bin_heap.cpp"
#endif