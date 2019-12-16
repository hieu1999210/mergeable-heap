#include "bin_node.h"

template<typename dataT, typename countT>
void
BinNode<dataT, countT>::init() {
    this->child = nullptr;
    this->parent = nullptr;
    this->sibling = nullptr;
    this->children_num = 0;
    this->data = nullptr;
}


template<typename dataT, typename countT>
void
BinNode<dataT, countT>::merge_tree(BinNode<dataT, countT> * subtree) {
    subtree->parent = this;
    subtree->sibling = this->child;
    this->child = subtree;
    ++this->children_num;
}


template<typename dataT, typename countT>
BinNode<dataT, countT> *
BinNode<dataT, countT>::merge_trees_list(BinNode<dataT, countT> * trees_list) {
    if (trees_list == nullptr) return this;

    BinNode<dataT, countT> * head1 = this; 
    BinNode<dataT, countT> * head2 = trees_list;
    BinNode<dataT, countT> * new_head;
    if (head1->children_num < head2->children_num) {
        new_head = head1;
        head1 = head1->sibling;
    } else {
        new_head = head2;
        head2 = head2->sibling;
    }
    BinNode<dataT, countT> * last_tree = new_head;

    while (head1 != nullptr && head2 != nullptr) {
        if (head1->children_num < head2->children_num) {
            last_tree->sibling = head1;
            head1 = head1->sibling;
        } else {
            last_tree->sibling = head2;
            head2 = head2->sibling;
        }
        last_tree = last_tree->sibling;
    }

    if (head1 != nullptr) {last_tree->sibling = head1;}
    else {last_tree->sibling = head2;}

    return new_head;
}


template<typename dataT, typename countT>
void
BinNode<dataT, countT>::display_tree() {
    this->display_node();
    std::cout << "[";
    if (this->child != nullptr) this->child->display_tree();
    std::cout << "]";
    if (this->sibling != nullptr) this->sibling->display_tree();
}