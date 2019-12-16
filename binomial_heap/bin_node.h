#ifndef node_binomialheap__
#define node_binomialheap__
#include <iostream>

template<typename dataT, typename countT = int>
class 
BinNode {
    private:
        void init();
    public:
        BinNode<dataT, countT> * parent;

        // the leftmost child
        BinNode<dataT, countT> * child;

        // right sibling
        BinNode<dataT, countT> * sibling;

        // degree
        countT children_num;
        dataT * data;

        BinNode() {this->init();}

        BinNode(dataT & data) {
            this->init();
            this->data = &data;
        }

        BinNode(dataT && data) {
            this->init();
            this->data = &data;
        }

        void
        merge_tree(BinNode<dataT, countT> * subtree);

        // merge two trees lists of increasing children_num into one
        BinNode<dataT, countT> *
        merge_trees_list(BinNode<dataT, countT> * trees_list);

        void
        display_node() {std::cout << *data;}

        void
        display_tree();
};
#include "bin_node.cpp"
#endif