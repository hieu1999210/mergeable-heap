#ifndef fibon_heap__
#define fibon_heap__
#include "fib_node.h"
template<typename dataT, typename countT>
bool 
cmp___(const dataT & left, const dataT & right) {return left < right;};

template<typename dataT, typename countT = int>
class
FibHeap {
    private:
        /* pointer to compare function
        indicate whether two elements are in the right order*/
        bool (*cmp)(const dataT &, const dataT &); 

        bool 
        cmp_node(FibNode<dataT, countT> * left, FibNode<dataT, countT> * right) {
            return cmp(*(left->data), *(right->data));
        }

        void
        consolidate();

        /* cut a node from its parent and move to root_list
        Note: ensure that the node is not in the roots list */
        void
        cut(FibNode<dataT, countT> * node);

        void
        cascading_cut(FibNode<dataT, countT> * node);

    public:
        countT tree_num;
        countT node_num;
        FibNode<dataT, countT> * root_list;
        FibNode<dataT, countT> * top_node;

        /* constructor */
        FibHeap(bool (*cmp)(const dataT &, const dataT &) = cmp___);

        bool 
        empty() {return top_node == nullptr;}

        countT 
        size() {return node_num;}

        dataT & 
        top() {return *(top_node->data);}

        /* extract the top element from heap */
        void
        pop();

        /*insert a element into Fibonacci heap
        Note that propriate compare function should be provided for non build-in type
        Description: new node is inserted into heap's root list */
        FibNode<dataT, countT> * 
        push(dataT & data);

        /*insert a element into Fibonacci heap
        Note that propriate compare function should be provided for non build-in type
        Description: new node is inserted into heap's root list */
        FibNode<dataT, countT> * 
        push(dataT && data);

        /*merge two heaps
        return the newly merged heap
        Note: the heap in arg should be delete if it's in heap memory*/
        FibHeap & 
        merge(FibHeap<dataT, countT> & heap);

        /* change value of a node
        ensure that the new value makes the node closer to the top of the heap*/
        void
        change_value(FibNode<dataT, countT> * node, dataT & new_data);

        /* change value of a node
        ensure that the new value makes the node closer to the top of the heap*/
        void
        change_value(FibNode<dataT, countT> * node, dataT && new_data);

        void 
        display();
        // void
        // delete_node(FibNode<dataT, countT> * node);
};

#include "fibon_heap.cpp"
#endif