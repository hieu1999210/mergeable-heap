#ifndef node_fibheap__
#define node_fibheap__
#include <iostream>

/* data container for Fibonacci heap */
template<typename dataT, typename countT=int> 
class
FibNode {
    private:
        void init();
    public:
        FibNode<dataT, countT> * parent;
        FibNode<dataT, countT> * child;
        FibNode<dataT, countT> * left;
        FibNode<dataT, countT> * right;
        countT children_num;
        dataT * data;
        /* indicates whether the node has lost a child
        since the last time the node was made the child of another node. */
        bool mark;


        /*constructor*/
        FibNode() {this->init();}

        
        FibNode<dataT, countT>(dataT && data) {
            this->init();
            this->data = &data;
        }


        FibNode<dataT, countT>(dataT & data) {
            this->init();
            this->data = &data;
        }


        /* helper function
        merge two doubly linked list
        return a node from the newly merged list

        description: insert entire arg list between current list's head and its right node */
        FibNode<dataT, countT>* 
        merge_list(FibNode<dataT, countT> * list);


        /* helper function of pop
        merge other tree as child of the current tree
        return root node 
        Note: the tree must be a tree of the heap (e.g its root in the root list of heap*/
        FibNode<dataT, countT> * 
        merge_tree(FibNode<dataT, countT> * subtree);


        /* helper function 
        remove node from the circular list
        return pointer to a node in the remain list (null if empty)

        Note: 
        - this procedure only remove the node
        and reconnect the rest of the circular list.
        - should keep track of the removed node before beginning the procedure
        - pointers of the removed node are left unchanged */
        FibNode<dataT, countT> *
        remove_from_list();


        void 
        display_node() {std::cout << *(this->data);}


        /*display from left to right */
        void 
        display_list();


        /*display tree in pre-order 
        in the child_list display to the right*/
        void 
        display_tree();
};
#include "fib_node.cpp"
#endif